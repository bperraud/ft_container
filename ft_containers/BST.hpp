/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/19 23:23:13 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BST_H_
#define _BST_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <ostream>             // output streams

template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<std::pair<const Key, T> > >	// map::allocator_type
class BST {


public :
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef std::pair<const Key, T>						value_type;
	typedef Compare										key_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer		const_pointer;

	typedef std::ptrdiff_t								difference_type;
	typedef std::size_t									size_type;


public:
	struct _Node {
		value_type _info;
		_Node* _left;
		_Node* _right;
		explicit _Node (const value_type& v) : _info(v), _left(), _right() {}
	};

private:
    _Node*				_root;
	allocator_type		_allocator;
	key_compare			_key_compare;

	_Node*& _findNode (const value_type& v) {
		_Node **res = &_root;
		while (*res)
		{
			if (v == (*res)->_info) break;
			else res = v < (*res)->_info ? &(*res)->_left : &(*res)->_right;
		}
		return *res;   //  pointer to place where v is or should be
	}
	_Node*& _nextLeaf (const value_type& v) {
		_Node **res = &_root;
		while (*res)
			res = v < (*res)->_info ? &(*res)->_left : &(*res)->_right;
		return *res;
	}
	_Node* _erase (_Node*& target) {
		_Node *const res = target; // saved
		if (target) {
			_Node *subst = target->_right;
			if (subst) {
				_Node *father = 0;
				while (subst->_left) {father = subst; subst = subst->_left;}
				if (father) {
					father->_left = subst->_right;
					subst->_right = target->_right;
				}
				subst->_left  = target->_left;
			} else subst = target->_left;
			target->_left = 0; target->_right = 0;
			target = subst;
		}
		return res;   // old isolated _Node (not yet deleted)
	}

    static _Node* _cp (const _Node* r) // recursive
    {return r ? new _Node(*r) : 0;}

protected:
    static const value_type _NOT_FOUND;                      // "not found" element

public:

    /* ------------------------------ Construction ------------------------------ */

	BST( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() )
		: _root( 0 ), _allocator( alloc ), _key_compare(comp) {
	}

	/* -------------------------------- Observers ------------------------------- */

	bool isEmpty () const {return !_root;}

	bool isNotFound (const value_type& v) {
		return &v == &_NOT_FOUND;
	}

	const value_type& find (const value_type& v) const {
		const _Node *const res = const_cast<BST*>(this)->_findNode(v);
		return res ? res->_info : _NOT_FOUND;
	}

	bool exists (const value_type& v) const {return !isNotFound(find(v));}


	// Setters
	const value_type& insert (const value_type& v) {  // always add
		return (_nextLeaf(v) = new _Node(v))->_info;
	}


    //virtual BST& operator= (const BST&);

    // Destructor
    virtual ~BST () {delete _root;}  // recursive
    // Associated function
    //template <typename U>
    //friend inline std::ostream& operator<< (std::ostream&, const BST<U>&);

	// Operator
	BST &operator++() {
		//return _nextLeaf (const value_type& v)
	};
	BST operator++( int ) ;
	BST &operator--() ;
	BST operator--( int ) ;

};


#endif
