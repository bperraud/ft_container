/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/19 18:44:10 by bperraud         ###   ########.fr       */
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


private:
    // Implementation
	struct _Node {
		const value_type _info;
		BST left, right;
		explicit _Node (const value_type& v) : _info(v), left(), right() {}
	};

    _Node*				_root;
	allocator_type		_allocator;
	key_compare			_key_compare;


	_Node*& _findNode (const value_type& v)  {
		_Node **res = &_root;
		while (*res)
		{
			if (v == (*res)->info) break;
			else res = v < (*res)->info ? &(*res)->left._root : &(*res)->right._root;
		}
		return *res;   //  pointer to place where v is or should be
	}

	_Node*& _nextLeaf (const value_type& v)  {
		_Node **res = &_root;
		while (*res)
			res = v < (*res)->info ? &(*res)->left._root : &(*res)->right._root;
		return *res;
	}

	_Node* _erase (_Node*& target) {
		_Node *const res = target; // saved
		if (target) {
			_Node *subst = target->right._root;
			if (subst) {
				_Node *father = 0;
				while (subst->left._root) {father = subst; subst = subst->left._root;}
				if (father) {
					father->left._root = subst->right._root;
					subst->right._root = target->right._root;
				}
				subst->left._root  = target->left._root;
			} else subst = target->left._root;
			target->left._root = 0; target->right._root = 0;
			target = subst;
		}
		return res;   // old isolated _Node (not yet deleted)
	}

    static _Node* _cp (const _Node* r) // recursive
    {return r ? new _Node(*r) : 0;}

protected:
    //static const value_type _NOT_FOUND = 0;                      // "not found" element

public:

    /* ------------------------------ Construction ------------------------------ */

	BST( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() )
		:_root( 0 ), _allocator( alloc ), _key_compare(comp) {
	}

	/* -------------------------------- Observers ------------------------------- */

    //virtual BST& operator= (const BST&);

    // Destructor
    virtual ~BST () {delete _root;}  // recursive
    // Associated function
    //template <typename U>
    //friend inline std::ostream& operator<< (std::ostream&, const BST<U>&);

	// Operator
	BST &operator++() ;
	BST operator++( int ) ;
	BST &operator--() ;
	BST operator--( int ) ;

}; // BST<T>

//template <typename T>
//const T BST<T>::_NOT_FOUND = 0;


//template <typename T>
//BST<T>::BST( const key_compare &comp = key_compare(), const allocator_type &alloc = node_allocator_type() )
//	:_root( _end ), _allocator( alloc ),_key_compare( extended_key_compare( _end, comp ) ) {
//}


#endif // _BST_H_
