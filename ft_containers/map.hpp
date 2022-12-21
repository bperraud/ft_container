/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:51:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/21 19:13:45 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef map_H
#define map_H

#include "BST.hpp"
#include "Iterator.hpp"

namespace ft {

const int INITIAL_CAPACITY = 10;

template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<std::pair<const Key, T> > >	// map::allocator_type
class map {


public :
	typedef BST<Key, T, Compare, Allocator> 			tree_type;

	// iterator class
    template <typename U>
	class normal_iterator {
    public:
        typedef typename U::value_type        value_type;
        typedef typename U::reference         reference;
        typedef typename U::pointer           pointer;
        typedef typename U::difference_type   difference_type;

		typedef typename U::_Node				node_reference;
		typedef typename U::_Node*				node_pointer;

        //typedef typename U::iterator_category iterator_category;

    private:
		node_pointer _current_node;

    public:
        normal_iterator() : _current_node() {}

		normal_iterator(node_pointer node) : _current_node( node ) {}

		normal_iterator &operator++() {
			node_reference node = *_current_node;
            node++;
			_current_node = &node;
            return *this;
        }

        normal_iterator operator++( int ) {
			node_reference node = *_current_node;
            node++;
			_current_node = &node;
			return *this;
		}

        normal_iterator &operator--() {
            _current_node--;
            return *this;
        }
        normal_iterator operator--( int ) { return _current_node--; }

		pointer operator->() { return &_current_node->_info; }


		reference operator*() { return _current_node->_info; }
		reference operator*() const { return _current_node->_info;}


		/*

        normal_iterator( const normal_iterator &other ) : _tree( other._tree ) {}
        normal_iterator( const U &other ) : _tree( other ) {}
        normal_iterator &operator=( const normal_iterator &other ) {
            _tree = other._tree;
            return *this;
        }


        reference operator*() { return *_tree; }
        typename normal_iterator< tree_const_iterator >::reference operator*() const {
            return *_it;
        }
		typename normal_iterator< tree_const_iterator >::reference operator*() const {
            return *_tree;
        }

        pointer operator->() { return _tree.operator->(); }
        typename normal_iterator< tree_const_iterator >::pointer operator->() const {
            return _it.operator->();
        }

        template < typename V >
        bool operator==( const normal_iterator< V > &other ) const {
            return U( *this ) == V( other );
        }
        bool operator==( const U &other ) const { return T( *this ) == other; }

        template < typename V >
        bool operator!=( const normal_iterator< V > &other ) const {
            return !( *this == other );
        }
        bool operator!=( const U &other ) const { return !( *this == other ); }

        operator U() const { return U( _it ); }
	};

        operator normal_iterator< tree_const_iterator >() const {
            return normal_iterator< tree_const_iterator >( _it );
        }
	*/
	};

	/*
    typedef normal_iterator< tree_iterator >			iterator;
    typedef normal_iterator< tree_const_iterator >		const_iterator;
    typedef ft::reverse_iterator< iterator >			reverse_iterator;
    typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;
	*/

public :
	//typedef BST<Key, T, Compare, Allocator> 			tree_type;

	typedef normal_iterator< tree_type >				iterator;
    typedef normal_iterator< const tree_type >			const_iterator;
    typedef ft::reverse_iterator< iterator >			reverse_iterator;
    typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;


public:

	//struct value_compare {
    //    bool operator()( const value_type &a, const value_type &b ) const {
    //        return key_compare()( a.first, b.first );
    //    }
    //};

	// types:
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

	//typedef Vect<typename Allocator::value_type>	vector_type;

private:
	allocator_type		_allocator;
	size_type			_capacity;
	size_type			_size;
	tree_type			_tree;

public:

	/* ------------------------------ Construction ------------------------------ */

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
	_allocator(alloc), _capacity(INITIAL_CAPACITY), _size(0), _tree( tree_type(comp, alloc)) {
	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
	const allocator_type& alloc = allocator_type()) {
	}

	/* -------------------------------- Iterators ------------------------------- */

	iterator 				begin() {return _tree.findMin(_tree.getRoot()); }

	/*
	iterator 				end() { return _vector._data + _vector._size; }
	const_iterator 			begin() const { return _vector._data; }
	const_iterator 			end() const  { return begin() + _vector._size; }
	reverse_iterator 		rbegin() {return begin() + _vector._size ;}
	reverse_iterator 		rend() { return _vector._data ; }
	const_reverse_iterator 	rbegin() const {return begin() + _vector._size ;}
	const_reverse_iterator 	rend() const { return _vector._data; }
	const_iterator 			cbegin() const { return _vector._data;}
	const_iterator 			cend() const { return begin() + _vector._size; }
	const_reverse_iterator 	crbegin() const {return begin() + _vector._size ;}
	const_reverse_iterator 	crend() const { return _vector._data ; }
	*/

	/* ----------------------------- Element access ----------------------------- */

	mapped_type& operator[] (const key_type& k);

	mapped_type& at (const key_type& k);
	const mapped_type& at (const key_type& k) const;

	/* -------------------------------- Modifiers ------------------------------- */

	void insert( const value_type &val ) {
        _tree.insert( val );
    }

	/* -------------------------------- Capacity -------------------------------- */

	bool		empty () const {return _size == 0;}
	size_type	size () const { return _size;}
	size_type	max_size () const {return _allocator.max_size();}

	/* -------------------------------- Observers ------------------------------- */

    key_compare   key_comp() const { return key_compare(); }
    //value_compare value_comp() const { return value_compare(); }


	/* -------------------------------- Destructor ------------------------------ */

	~map () {};
};

} //namespace ft

#endif
