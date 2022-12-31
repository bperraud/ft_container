/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/31 13:16:46 by bperraud         ###   ########.fr       */
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

	typedef typename Allocator::template rebind< _Node >::other node_allocator_type;


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
	node_pointer			_end;
	node_pointer			_rend;
    node_pointer			_root;
	node_allocator_type		_allocator;
	extended_key_compare	_key_compare;
	size_type				_size;

protected:
	static const value_type _NOT_FOUND;                      // "not found" element

public:

    /* ------------------------------ Construction ------------------------------ */

	BST( const key_compare &comp = key_compare(), const allocator_type &alloc = node_allocator_type() () )
		: _end(construct_node(value_type())), _rend(construct_node(value_type())), _root(0), _allocator(alloc),
		//: _end(construct_node(_Node())), _rend(construct_node(_Node())), _root(_end), _allocator(alloc),
		_key_compare( extended_key_compare(_end, _rend, comp)), _size(0) {

	}

	//BST &operator=( const BST &other ) {
	//	//clear();
	//	node_pointer first = begin();
	//	while (first != end())
	//	{
	//		insert(*first);
	//		first++;
	//	}
	//	return *this;
	//}

	node_pointer construct_node(const value_type &val)
	{
		node_pointer node = _allocator.allocate(1);
        _allocator.construct(node, _Node(val));
		return node;
	}

	//node_pointer construct_node(const node_reference other)
	//{
	//	node_pointer node = _allocator.allocate(1);
    //    _allocator.construct(node, other);
	//	return node;
	//}

	/* -------------------------------- Iterators ------------------------------- */

	node_pointer	end() {return _end;}
	node_pointer	end() const { return _end;}
	node_pointer	begin() { return _rend->next(); }
	node_pointer	begin() const { return _rend->next();}
	node_pointer	rend() { return _rend; }
	node_pointer	rend() const { return _rend;}

	/* -------------------------------- Capacity -------------------------------- */

	size_type max_size() const {return _allocator.max_size();}

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
			return _end;
	}

	// true if Key of v is in tree
	bool exists (const key_type& key) const {
		return find(key) != _end;
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

	/* -------------------------------- Modifiers ------------------------------- */

	void init_root(const value_type& val) {
		_root = construct_node(val);
		_root->_father = 0;
		_root->_right = _end;
		_root->_left = _rend;
		_end->_father = _root;
		_rend->_father = _root;
		_size += 1;
	}

	ft::pair<node_pointer, bool> insert(const value_type& val) {
		_Node *curr = _root;
		if (!_root) {
			init_root(val);
			return ft::pair<node_pointer, bool>(_root, true);
		}
		while (curr) {
			if (_key_compare(val.first, curr->_info.first)) {
				if (curr->_left) {
					curr = curr->_left;
				}
				else {
					curr->_left = construct_node(val);
					curr->_left->_father = curr;
					_size += 1;
					return ft::pair<node_pointer, bool>(curr->_left, true);
				}
			}
			else if (_key_compare(curr->_info.first, val.first)) {
				if (curr->_right) {
					curr = curr->_right;
				} else {
					curr->_right = construct_node(val);
					curr->_right->_father = curr;
					_size += 1;
					return ft::pair<node_pointer, bool>(curr->_right, true);
				}
			}
			else {
				return ft::pair<node_pointer, bool>(curr, false);
			}
		}
		return ft::pair<node_pointer, bool>(_root, false);
	}

	ft::pair<node_pointer, bool> insert(node_pointer position, const value_type& val) {
		if (!_root) {
			init_root(val);
			return ft::pair<node_pointer, bool>(_root, true);
		}
		if (_key_compare(position->_info.first, val.first) && !position->_right) {
			position->_right = construct_node(val);
			position->_right->_father = position;
			_size += 1;
			return ft::pair<node_pointer, bool>(position->_right, true);
		}
		return insert(val);
	}

	void swap_node_value(node_pointer first_node, node_pointer second_node)
	{
		node_pointer first_node_right = first_node->_right;
		node_pointer first_node_left = first_node->_left;
		node_pointer first_node_father = first_node->_father;

		first_node->_right = second_node->_right;
		first_node->_left = second_node->_left;
		first_node->_father = second_node->_father;

		second_node->_right = first_node_right;
		second_node->_left = first_node_left;
		second_node->_father = first_node_father;
	}

	void erase(node_pointer target)
	{
		node_pointer const res = target; // save pointer to delete
		if (target == _root)
		{
			std::cout << "root erase" << std::endl;
			return ;
		}
		if (target)
		{
			// save pointer to node being deleted
			node_pointer subst = target->_right;
			if (subst)
			{
				node_pointer father = 0;
				while (subst->_left)
				{
					father = subst;
					subst = subst->_left;
				}
				if (father)
				{
					father->_left = subst->_right;
					subst->_right = target->_right;
				}
				subst->_left = target->_left;
			}
			else
				subst = target->_left;
			// update father pointer of substituted node
			if (subst)
				subst->_father = target->_father;
			// update father's child pointer to point to substituted node
			if (target->_father)
			{
				if (target->_father->_left == target)
					target->_father->_left = subst;
				else
					target->_father->_right = subst;
			}
			// if node being deleted is root, update _root pointer
			else
			{
				_root = subst;

				std::cout << "begin : " << begin()->_info.second << std::endl;
				std::cout << "end : " << end()->_info.second << std::endl;
				//_rend = _root->_left;
				//_end = _root->_right;
			}
			// reset pointers of deleted node
			target->_left = 0;
			target->_right = 0;
			target->_father = 0;
			target = subst;
			// destroy and deallocate deleted node
			_size--;
			_allocator.destroy(res);
			_allocator.deallocate(res, 1);
		}
	}

	//void erase(node_pointer node) {
	//	if (_root == node)
	//		std::cout << "root" << std::endl;
	//	if (!node) return;
	//	// If node has no children or only one child, just delete it
	//	if (!node->_left || !node->_right) {
	//		node_pointer child = node->_left ? node->_left : node->_right;
	//		if (node->_father) {
	//			// Update parent's child pointer
	//			if (node->_father->_left == node) {
	//				node->_father->_left = child;
	//			} else {
	//				node->_father->_right = child;
	//			}
	//		}
	//		else // Set root pointer to node's child
	//			_root = child;
	//		if (child)
	//			child->_father = node->_father;
	//		_size--;
	//		_allocator.destroy(node);
    //    	_allocator.deallocate(node, 1);
	//		return;
	//	}
	//	// If node has two children, find inorder successor and swap pointers
	//	node_pointer succ = node->_right;
	//	while (succ->_left) succ = succ->_left;
	//	node_pointer succ_right = succ->_right;
	//	node_pointer succ_father = succ->_father;
	//	if (succ->_father->_left == succ) {
	//		succ->_father->_left = node;
	//	} else {
	//		succ->_father->_right = node;
	//	}
	//	node->_right = succ_right;
	//	node->_father = succ_father;
	//	if (succ_right) succ_right->_father = node;
	//	// Delete inorder successor(succ);
	//	_size--;
	//	_allocator.destroy(succ);
	//	_allocator.deallocate(succ, 1);
	//}

	node_pointer lower_bound( const key_type &k ) { return _lower_bound(k); }
	node_pointer lower_bound( const key_type &k ) const {
		return _lower_bound(k);
	}

	node_pointer upper_bound( const key_type &k ) { return _upper_bound(k); }
	node_pointer upper_bound( const key_type &k ) const {
		return _upper_bound(k);
	}

    //virtual BST& operator= (const BST&);

	/* -------------------------------- Allocator ------------------------------ */

	allocator_type get_allocator() const {
		return _allocator;
	}

    /* -------------------------------- Destructor ------------------------------ */

    virtual ~BST () {
		delete _root;
		delete _end;
		delete _rend;
	}  // recursive with BST node

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

	node_pointer _lower_bound(const key_type& key) const
	{
		node_pointer current = begin();
		while (current && current != _end) {
			if (!_key_compare(current->_info.first, key)) {
				// key is not less than current node's key, return current node
				return current;
			}
			//std::cout << "current node lower: " << current->_info.first << std::endl;
			current = current->next();
		}

		// key was not found, return end iterator
		return _end;
	}

	node_pointer _upper_bound(const key_type& key) const
	{
		node_pointer current = begin();
		while (current && current != _end) {
			if (_key_compare(key, current->_info.first)) {
				// key is less than current node's key, return current node
				return current;
			}
			//std::cout << "current node upper : " << current->_info.first << std::endl;
			current =  current->next();
		}

		// key was not found, return end iterator
		return _end;
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

	static node_pointer _cp (const node_pointer r) // recursive
	{return r ? new _Node(*r) : 0;}

};

#endif
