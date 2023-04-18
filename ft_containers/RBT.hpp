/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2023/04/19 00:33:17 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_H
#define RBT_H

#include <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include <ostream>             // output streams
#include "map.hpp"

#include <queue>
#include <cmath>

#include "Iterator.hpp"
#include "pair.hpp"
#include "utility.hpp"

enum Color { RED, BLACK };

template<
	class Key,														// map::key_type
	class T,														// map::mapped_type
	class Compare = std::less<Key>,									// map::key_compare
	class Allocator = std::allocator<ft::pair<const Key, T> > >		// map::allocator_type
class RBT {

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
		Color		_color;

		explicit _Node () {};
		explicit _Node (const value_type& v) : _info(v), _father(), _left(), _right(), _color(RED){}

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

	RBT( const key_compare &comp = key_compare(), const allocator_type &alloc = node_allocator_type() () )
		: _end(construct_node(value_type())), _rend(construct_node(value_type())), _root(0), _allocator(alloc),
		_key_compare( extended_key_compare(_end, _rend, comp)), _size(0) {
	}

	RBT( const RBT &other )
		: _end(construct_node(value_type())), _rend(construct_node(value_type())), _root(0), _allocator(other._allocator),
		_key_compare( extended_key_compare(_end, _rend, other._key_compare.key_comp() ) ), _size(0) {
		*this = other;
	}

	RBT &operator=( const RBT &other ) {
		return *this;
		clear();
		node_pointer first = other.begin();
		while (first != other.end())
		{
			insert(first->_info);
			first = first->next();
		}
		return *this;
	}

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
		_root->_color = BLACK;
		_root->_father = 0;
		_root->_right = _end;
		_root->_left = _rend;
		_end->_father = _root;
		_rend->_father = _root;
		_size += 1;
	}

	ft::pair<node_pointer, bool> insert(const value_type& val) {
		//return _insert_bst(val, _root);
		return _insert_rbt(val, _root);
	}

	ft::pair< node_pointer, bool > insert( node_pointer hint, const value_type &val ) {
		if ( _is_upper_bound(hint, val.first) ) {
			return _insert_bst(val, hint);
		}
		return _insert_bst(val, _root);
	}

	#if 1
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
	#else
	void erase(node_pointer node) {
		if (!node) {
			return;
		}
		node_pointer child, x;
		if (node->_left && node->_right) {
			node_pointer temp = node->_right;
			while (temp->_left) {
				temp = temp->_left;
			}
			node->_info.~value_type();
       		new (&node->_info) value_type(temp->_info);
			node = temp;
		}
		if (!node->_left) {
			child = node->_right;
		} else {
			child = node->_left;
		}
		x = node->_father;
		if (child) {
			child->_father = node->_father;
		}
		if (!x) {
			_root = child;
		} else if (node == x->_left) {
			x->_left = child;
		} else {
			x->_right = child;
		}
		if (node->_color == BLACK) {
			while (child != _root && (!child || child->_color == BLACK)) {
				if (child == x->_left) {
					node_pointer w = x->_right;
					if (w->_color == RED) {
						w->_color = BLACK;
						x->_color = RED;
						_rotate_left(x);
						w = x->_right;
					}
					if ((!w->_left || w->_left->_color == BLACK) && (!w->_right || w->_right->_color == BLACK)) {
						w->_color = RED;
						child = x;
						x = x->_father;
					} else {
						if (!w->_right || w->_right->_color == BLACK) {
							if (w->_left) {
								w->_left->_color = BLACK;
							}
							w->_color = RED;
							_rotate_right(w);
							w = x->_right;
						}
						w->_color = x->_color;
						x->_color = BLACK;
						if (w->_right) {
							w->_right->_color = BLACK;
						}
						_rotate_left(x);
						break;
					}
				} else {
					node_pointer w = x->_left;
					if (w->_color == RED) {
						w->_color = BLACK;
						x->_color = RED;
						_rotate_right(x);
						w = x->_left;
					}
					if ((!w->_right || w->_right->_color == BLACK) && (!w->_left || w->_left->_color == BLACK)) {
						w->_color = RED;
						child = x;
						x = x->_father;
					} else {
						if (!w->_left || w->_left->_color == BLACK) {
							if (w->_right) {
								w->_right->_color = BLACK;
							}
							w->_color = RED;
							_rotate_left(w);
							w = x->_left;
						}
						w->_color = x->_color;
						x->_color = BLACK;
						if (w->_left) {
							w->_left->_color = BLACK;
						}
						_rotate_right(x);
						break;
					}
				}
			}
			if (child) {
				child->_color = BLACK;
			}
		}
		_allocator.destroy(node);
		_allocator.deallocate(node, 1);
		_size -= 1;
	}
	#endif

	node_pointer lower_bound( const key_type &k ) { return _lower_bound(k); }
	node_pointer lower_bound( const key_type &k ) const {
		return _lower_bound(k);
	}

	node_pointer upper_bound( const key_type &k ) { return _upper_bound(k); }
	node_pointer upper_bound( const key_type &k ) const {
		return _upper_bound(k);
	}

	void swap (RBT& x) {
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

	~RBT () {
		clear();
		_allocator.destroy(_end);
		_allocator.deallocate(_end, 1);
		_allocator.destroy(_rend);
		_allocator.deallocate(_rend, 1);
	}

	/* -------------------------- Relational operators -------------------------- */

	bool operator==( const RBT &other ) const {
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

	bool operator<( const RBT &other ) const {
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

	bool operator!=( const RBT &other ) const {
		return !( *this == other );
	}
	bool operator>( const RBT &other ) const { return other < *this; }
	bool operator<=( const RBT &other ) const {
		return !( other < *this );
	}
	bool operator>=( const RBT &other ) const {
		return !( *this < other );
	}


	//void printTreeDiagram() {
	//	if (_root == 0) return;

	//	std::queue<std::pair<_Node*, int> > _q;  // use a queue to store nodes and their depths
	//	_q.push({_root, 0});  // start with the root node at depth 0

	//	while (!_q.empty()) {
	//		_Node* _node = _q.front().first;
	//		int _depth = _q.front().second;
	//		_q.pop();

	//		std::cout << "Node value: " << _node->_info.second << ", depth: " << _depth << std::endl;

	//		if (_node->_left) _q.push({_node->_left, _depth + 1});  // add left child to queue
	//		if (_node->_right) _q.push({_node->_right, _depth + 1});  // add right child to queue
	//	}
	//}

private:

	ft::pair<node_pointer, bool> _insert_rbt(const value_type& val, node_pointer node) {
		ft::pair<node_pointer, bool> res = _insert_bst(val, node);
		node_pointer x = res.first;

		// If the node is not inserted, return
		if (!res.second) {
			return ft::make_pair(x, false);
		}

		// Color the new node red
		x->_color = RED;

		balance_insertion(x);

		return res;
	}

	void balance_insertion(node_pointer node) {
		node_pointer uncle;
		while (node->_father && node->_father->_color == RED) {
			if (node->_father == node->_father->_father->_left) {
				uncle = node->_father->_father->_right;
				if (uncle && uncle->_color == RED) {
					node->_father->_color = BLACK;
					uncle->_color = BLACK;
					node->_father->_father->_color = RED;
					node = node->_father->_father;
				} else {
					if (node == node->_father->_right) {
						node = node->_father;
						_rotate_left(node);
					}
					node->_father->_color = BLACK;
					node->_father->_father->_color = RED;
					_rotate_right(node->_father->_father);
				}
			} else {
				uncle = node->_father->_father->_left;
				if (uncle && uncle->_color == RED) {
					node->_father->_color = BLACK;
					uncle->_color = BLACK;
					node->_father->_father->_color = RED;
					node = node->_father->_father;
				} else {
					if (node == node->_father->_left) {
						node = node->_father;
						_rotate_right(node);
					}
					node->_father->_color = BLACK;
					node->_father->_father->_color = RED;
					_rotate_left(node->_father->_father);
				}
			}
		}
		_root->_color = BLACK;
	}

	ft::pair<node_pointer, bool> _insert_bst(const value_type& val, node_pointer node) {
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

	// Helper function to flip the colors of a node and its children
	void flip_colors(node_pointer node) {
		node->_color = RED;
		node->_left->_color = BLACK;
		node->_right->_color = BLACK;
	}

	void _rotate_right(node_pointer x) {
		node_pointer y = x->_left;
		if (y == 0) {
			return; // Nothing to do if y is null
		}
		x->_left = y->_right;
		if (y->_right) {
			y->_right->_father = x;
		}
		y->_father = x->_father;
		if (!x->_father) {
			_root = y;
		} else if (x == x->_father->_right) {
			x->_father->_right = y;
		} else {
			x->_father->_left = y;
		}
		y->_right = x;
		x->_father = y;
	}

	void _rotate_left(node_pointer x) {
		node_pointer y = x->_right;
		if (y == 0) {
			return; // Nothing to do if y is null
		}
		x->_right = y->_left;
		if (y->_left) {
			y->_left->_father = x;
		}
		y->_father = x->_father;
		if (!x->_father) {
			_root = y;
		} else if (x == x->_father->_left) {
			x->_father->_left = y;
		} else {
			x->_father->_right = y;
		}
		y->_left = x;
		x->_father = y;
	}




	void fixInsert(node_pointer node) {
		while (node != _root && node->_father->_color == RED) {
			if (node->_father == node->_father->_father->_left) {
				node_pointer uncle = node->_father->_father->_right;
				if (uncle != NULL && uncle->_color == RED) {
					node->_father->_color = BLACK;
					uncle->_color = BLACK;
					node->_father->_father->_color = RED;
					node = node->_father->_father;
				} else {
					if (node == node->_father->_right) {
						node = node->_father;
						rotateLeft(node);
					}
					node->_father->_color = BLACK;
					node->_father->_father->_color = RED;
					rotateRight(node->_father->_father);
				}
			} else {
				node_pointer uncle = node->_father->_father->_left;
				if (uncle != NULL && uncle->_color == RED) {
					node->_father->_color = BLACK;
					uncle->_color = BLACK;
					node->_father->_father->_color = RED;
					node = node->_father->_father;
				} else {
					if (node == node->_father->_left) {
						node = node->_father;
						rotateRight(node);
					}
					node->_father->_color = BLACK;
					node->_father->_father->_color = RED;
					rotateLeft(node->_father->_father);
				}
			}
		}
		_root->color = BLACK;
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
