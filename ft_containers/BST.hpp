/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2023/04/11 00:25:18 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_H
#define BST_H

#include <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include <ostream>             // output streams
#include "map.hpp"

#include <queue>
#include <cmath>

#include "Iterator.hpp"
#include "pair.hpp"
#include "utility.hpp"
#include <stack>

template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<ft::pair<const Key, T> > >		// map::allocator_type
class BST {

public :
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const Key, T>						value_type;

	typedef Compare										key_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::const_pointer		const_pointer;
	typedef	typename allocator_type::pointer			pointer;

    //typedef std::bidirectional_iterator_tag				iterator_category;
	typedef ft::bidirectional_iterator_tag				iterator_category;
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
				while (node->_left)
					node = node->_left;
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
				while (node->_right)
					node = node->_right;
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

		bool operator==( const _Node &other ) const {
			return ( _info == other._info );
		}
		bool operator<( const _Node &other ) const {
			return _info < other._info;
		}
		bool operator!=( const _Node &other ) const { return !( *this == other ); }
		bool operator<=( const _Node &other ) const { return !( *this < other ); }
		bool operator>( const _Node &other ) const { return ( other < *this ); }
		bool operator>=( const _Node &other ) const { return !( *this < other ); }
	};

	typedef typename Allocator::template rebind< _Node >::other node_allocator_type;

public :
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

public:

    /* ------------------------------ Construction ------------------------------ */

	BST( const key_compare &comp = key_compare(), const allocator_type &alloc = node_allocator_type())
		: _end(construct_node(value_type())), _rend(construct_node(value_type())), _root(0), _allocator(alloc),
		_key_compare( extended_key_compare(_end, _rend, comp)), _size(0) {
	}

	BST( const BST &other )
		: _end(construct_node(value_type())), _rend(construct_node(value_type())), _root(0), _allocator(other._allocator),
		_key_compare( extended_key_compare(_end, _rend, other._key_compare.key_comp() ) ), _size(0) {
		*this = other;
	}

	#if 0
	BST &operator=( const BST &other ) {
		clear();
		node_pointer first = other.begin();
		while (first != other.end())
		{
			insert(first->_info);
			first = first->next();
		}
		return *this;
	}
	#else
	BST& operator=(const BST& other) {
		if (this != &other) { // Check for self-assignment
			clear(); // Clear the existing tree
			if (other._root == 0) { // If the other tree is empty, return an empty tree
				return *this;
			}
			_root = new _Node(other._root->_info); // Create a new root node for the tree
			std::stack<std::pair<_Node*, _Node*> > nodes_to_copy; // A stack of pairs of (original node, copied node)
			nodes_to_copy.push(std::make_pair(other._root, _root)); // Push the root nodes onto the stack
			while (!nodes_to_copy.empty()) {
				std::pair<_Node*, _Node*> curr_pair = nodes_to_copy.top(); // Get the top node and its copy from the stack
				nodes_to_copy.pop();
				_Node* curr_node = curr_pair.first;
				_Node* curr_copy = curr_pair.second;
				if (curr_node->_right) { // Copy right child
					_Node* new_right = new _Node(curr_node->_right->_info);
					curr_copy->_right = new_right;
					new_right->_father = curr_copy;
					nodes_to_copy.push(std::make_pair(curr_node->_right, new_right)); // Push right child onto stack
				}
				if (curr_node->_left) { // Copy left child
					_Node* new_left = new _Node(curr_node->_left->_info);
					curr_copy->_left = new_left;
					new_left->_father = curr_copy;
					nodes_to_copy.push(std::make_pair(curr_node->_left, new_left)); // Push left child onto stack
				}
			}
		}
		return *this;
	}

	#endif

	node_pointer construct_node(const value_type &val)
	{
		node_pointer node = _allocator.allocate(1);
        _allocator.construct(node, _Node(val));
		return node;
	}

	/* -------------------------------- Iterators ------------------------------- */

	node_pointer	end() {return _end;}
	node_pointer	end() const { return _end;}
	node_pointer	begin() {return _rend->next(); }
	node_pointer	begin() const { return _rend->next();}
	node_pointer	rend() { return _rend; }
	node_pointer	rend() const { return _rend;}

	/* -------------------------------- Capacity -------------------------------- */

	size_type max_size() const {return _allocator.max_size();}

	/* -------------------------------- Observers ------------------------------- */

	size_type size() const {return _size;}

	bool isEmpty () const {return _size == 0;}

	node_pointer find (const key_type& key) const {
		node_pointer res = _root;
		while (res)
		{
			if ( _key_compare(key, res->_info.first)) {
				res = res->_left;
			}
			else if (_key_compare(res->_info.first, key)) {
				res = res->_right;
			}
			else {
				return res;
			}
		}
		return _end; // if not found return _end
	}

	bool exists (const key_type& key) const {
		return find(key) != _end;
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
		return _insert(val, _root);
	}

	ft::pair< node_pointer, bool > insert( node_pointer hint, const value_type &val ) {
        if ( _is_upper_bound(hint, val.first) ) {
            return _insert(val, hint);
        }
        return _insert(val, _root);
    }

	void erase(node_pointer target)
	{
		node_pointer const res = target; // save pointer to node being deleted
		if (target)
		{
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
					if (father->_left) father->_left->_father = father;
					subst->_right = target->_right;
					if (subst->_right) subst->_right->_father = subst;
				}
				subst->_left = target->_left;
				if (subst->_left) subst->_left->_father = subst;
			}
			else
				subst = target->_left;
			// update father pointer of substituted node
			if (subst) subst->_father = target->_father;
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
				_root->_father = 0;
				_rend->_father = _root;
				_end->_father = _root;
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

	node_pointer lower_bound( const key_type &k ) { return _lower_bound(k); }
	node_pointer lower_bound( const key_type &k ) const {
		return _lower_bound(k);
	}

	node_pointer upper_bound( const key_type &k ) { return _upper_bound(k); }
	node_pointer upper_bound( const key_type &k ) const {
		return _upper_bound(k);
	}

    void swap (BST& x) {
		ft::swap(x._root, _root);
		ft::swap(x._end, _end);
		ft::swap(x._rend, _rend);
		ft::swap(x._size, _size);
	}

	/* -------------------------------- Allocator ------------------------------ */

	allocator_type get_allocator() const {
		return _allocator;
	}

	void clear()
	{
		while (_size) {
			erase(begin());
		}
	}
    /* -------------------------------- Destructor ------------------------------ */

	~BST () {
		clear();
		_allocator.destroy(_end);
		_allocator.deallocate(_end, 1);
		_allocator.destroy(_rend);
		_allocator.deallocate(_rend, 1);
	}

	/* -------------------------- Relational operators -------------------------- */

    bool operator==( const BST &other ) const {
		if (_size != other.size())
			return false;
		node_pointer first = begin();
		node_pointer first_other = other.begin();
		while (first != end() ){
			if ( first->_info != first_other->_info ) {
				return false;
			}
			first = first->next();
			first_other = first_other->next();
		}
		return true;
    }

    bool operator<( const BST &other ) const {
		node_pointer first = begin();
		node_pointer first_other = other.begin();
		while ( first != end() ) {
			if ( first_other == other.end() || first_other->_info < first->_info) {
				return false;
			}
			else if ( first->_info < first_other->_info ) {
				return true;
			}
			first = first->next();
			first_other = first_other->next();
		}
		return first_other != other.end();
    }

    bool operator!=( const BST &other ) const {
        return !( *this == other );
    }
    bool operator>( const BST &other ) const { return other < *this; }
    bool operator<=( const BST &other ) const {
        return !( other < *this );
    }
    bool operator>=( const BST &other ) const {
        return !( *this < other );
    }


private:

	ft::pair<node_pointer, bool> _insert(const value_type& val, node_pointer node) {
		if (!_root) {
			init_root(val);
			return ft::make_pair(_root, true);
		}
		node_pointer curr = node;
		while (curr) {
			if (_key_compare(val.first, curr->_info.first)) {
				if (curr->_left) {
					curr = curr->_left;
				}
				else {
					curr->_left = construct_node(val);
					curr->_left->_father = curr;
					_size += 1;
					return ft::make_pair(curr->_left, true);
				}
			}
			else if (_key_compare(curr->_info.first, val.first)) {
				if (curr->_right) {
					curr = curr->_right;
				} else {
					curr->_right = construct_node(val);
					curr->_right->_father = curr;
					_size += 1;
					return ft::make_pair(curr->_right, true);
				}
			}
			else {
				return ft::make_pair(curr, false);
			}
		}
		return ft::make_pair(_root, false);
	}

	bool _is_upper_bound( node_pointer current, const key_type &k ) const {
		if ((current && !current->previous()) || !_root)
			return true;
		return ( current == begin() || !_key_compare( k, current->previous()->_info.first ) )
			&& _key_compare( k, current->_info.first );
	} // k est plus petit que le précedent + plus petit que hint

	node_pointer _lower_bound(const key_type& key) const
	{
		node_pointer current = begin();
		while (current && current != _end) {
			if (!_key_compare(current->_info.first, key)) {
				// key is not less than current node's key, return current node
				return current;
			}
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
			current =  current->next();
		}
		// key was not found, return end iterator
		return _end;
	}

};

#endif
