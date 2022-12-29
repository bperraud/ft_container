/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/29 13:03:23 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_H
#define BST_H

#include <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include <ostream>             // output streams
#include "map.hpp"

#include "pair.hpp"

template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
class BST {

public :
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const Key, T>						value_type;
	typedef Compare										key_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer		const_pointer;

	typedef std::ptrdiff_t								difference_type;
	typedef std::size_t									size_type;

private:
	struct _Node {
		value_type	_info;
		_Node*		_father;
		_Node*		_left;
		_Node*		_right;

		explicit _Node () {};
		explicit _Node (const value_type& v) : _info(v), _father(), _left(), _right(){}

		_Node* next() {
			_Node *node = this;
			if (node->_right) {
				// Find leftmost node in right subtree
				node = node->_right;
				while (node->_left) node = node->_left;
				return node;
			}
			// Go up the tree until we find an ancestor whose left child is also an ancestor
			_Node *ancestor = node->_father;
			while (ancestor && ancestor->_left != node) {
				node = ancestor;
				ancestor = ancestor->_father;
			}
			return ancestor;
		}

		_Node* previous() {
			_Node *node = this;
			if (node->_left) {
				// Find rightmost node in left subtree
				node = node->_left;
				while (node->_right) node = node->_right;
				return node;
			}
			// Go up the tree until we find an ancestor whose right child is also an ancestor
			_Node *ancestor = node->_father;
			while (ancestor && ancestor->_right != node) {
				node = ancestor;
				ancestor = ancestor->_father;
			}
			return ancestor;
		}
	};

public :
	typedef _Node&		node_reference;
	typedef _Node*		node_pointer;

private :
	class extended_key_compare {
		node_pointer	_end;
		node_pointer	_rend;
		key_compare		_comp;

	public:
		extended_key_compare( node_pointer end, node_pointer rend, const key_compare &comp )
		: _end(end), _rend(rend), _comp(comp) {}

	bool operator()( const key_type &a, const key_type &b ) const {
		if ( &a == &_end->_info.first ) { return false; }
		if ( &b == &_end->_info.first ) { return true; }
		if ( &a == &_rend->_info.first ) { return true; }
		if ( &b == &_rend->_info.first ) { return false; }
			return _comp( a, b );
		}
        const key_compare &key_comp() const { return _comp; }
    };


private:
    node_pointer			_root;
	node_pointer			_end;
	node_pointer			_rend;
	allocator_type			_allocator;
	extended_key_compare	_key_compare;
	size_type				_size;

protected:
	static const value_type _NOT_FOUND;                      // "not found" element

public:

    /* ------------------------------ Construction ------------------------------ */

	BST( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() )
		: _root(0), _end(new _Node()), _rend(new _Node()), _allocator(alloc),
		_key_compare( extended_key_compare(_end, _rend, comp)), _size(0) {
	}

	/* -------------------------------- Observers ------------------------------- */

	size_type size() const {return _size;}

	bool isEmpty () const {return !_root;}

	bool isNotFound (const value_type& v) {
		return &v == &_NOT_FOUND;
	}

/*
	const value_type& find (const value_type& v) const {
		const _Node *const res = const_cast<BST*>(this)->_findNode(v);
		return res ? res->_info : _NOT_FOUND;
	}
	*/

	node_pointer find (const key_type& key) const {
		node_pointer node = _findNode(key);
		if (node)
			return node;
		else
		{
			return _end;
		}
	}

	// true if Key of v is in tree
	bool exists (const key_type& key) const {
		return find(key) != _end;
	}

	node_pointer	end() {
		return _end;
	}

	node_pointer	begin() {
		return _rend->next();
	}

	node_pointer	rend() {
		return _rend;
	}

	node_pointer findMin() {
		if (_root == 0)
			return 0;
		_Node* current = _root;
		while (current->_left)
		{
			current = current->_left;
		}
		return current;
	}

	node_pointer findMax() {
		if (_root == 0)
			return 0;
		_Node* current = _root;
		while (current->_right)
		{
			current = current->_right;
		}
		return current;
	}

	bool	isEmpty() {
		return _root->_right == _end && _root->_left == _rend;
	}

	ft::pair<node_pointer, bool> insert(const value_type& val) {
		_Node *curr = _root;
		while (curr) {
			if (_key_compare(val.first, curr->_info.first)) {
				if (curr->_left) {
					curr = curr->_left;
				}
				else {
					curr->_left = new _Node(val);
					curr->_left->_father = curr;
					_size += 1;
					return ft::pair<node_pointer, bool>(curr->_left, true);
				}
			}
			else if (_key_compare(curr->_info.first, val.first)) {
				if (curr->_right) {
					curr = curr->_right;
				} else {
					curr->_right = new _Node(val);
					curr->_right->_father = curr;
					_size += 1;
					return ft::pair<node_pointer, bool>(curr->_right, true);
				}
			}
			else {
				return ft::pair<node_pointer, bool>(curr, false);
			}
		}
		if (!_root) {
			_root = new _Node(val);
			_root->_right = _end;
			_root->_left = _rend;
			_end->_father = _root;
			_rend->_father = _root;
		}
		return ft::pair<node_pointer, bool>(_root, false);;
	}

    //virtual BST& operator= (const BST&);

    // Destructor
    virtual ~BST () {
		delete _root;
		delete _end;
		delete _rend;
	}  // recursive

    // Associated function
    //template <typename U>
    //friend inline std::ostream& operator<< (std::ostream&, const BST<U>&);

private:

	node_pointer _findNode (const key_type& k) const {
		node_pointer res = _root;
		while (res)
		{
			if ( _key_compare(k, (res)->_info.first)) {
				res = res->_left;
			}
			else if (_key_compare((res)->_info.first, k)) {
				res = res->_right;
			}
			else {
				return res;
			}
		}
		return 0; //  if not found return 0
	}

	/*
	_Node*& _findNode (const key_type& k) {
		_Node **res = &_root;
		while (*res)
		{
			if ( _key_compare(k, (*res)->_info.first)) {
				res = &(*res)->_left;
			}
			else if (_key_compare((*res)->_info.first, k)) {
				res = &(*res)->_right;
			}
			else {
				break;
			}
		}
		return *res; //  pointer to place where v is or should be
	}
	*/


	node_pointer _erase (_Node*& target) {
		node_pointer const res = target;  // saved
		if (target) {
			node_pointer subst = target->_right;
			if (subst) {
				node_pointer father = 0;
				while (subst->_left) {
					father = subst;
					subst = subst->_left;
				}
				if (father) {
					father->_left = subst->_right;
					if (subst->_right) {  // Update father of subst->_right
						subst->_right->_father = father;
					}
					subst->_right = target->_right;
				}
				subst->_left = target->_left;
				if (target->_left) {  // Update father of target->_left
					target->_left->_father = subst;
				}
			}
			else {
				subst = target->_left;
				if (subst) {  // Update father of target->_left
					subst->_father = target->_father;
				}
			}
			target->_left = 0;
			target->_right = 0;
			target = subst;
		}
		return res;  // old isolated _Node (not yet deleted)
	}

	static node_pointer _cp (const node_pointer r) // recursive
	{return r ? new _Node(*r) : 0;}

};

#endif
