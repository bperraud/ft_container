/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:51:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/29 13:02:14 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "BST.hpp"
#include "Iterator.hpp"
#include "pair.hpp"

namespace ft {

template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
class map {

public :
	typedef BST<Key, T, Compare, Allocator> 			tree_type;

	// iterator class
    template <typename U>
	class normal_iterator {
    public:
        typedef typename U::value_type			value_type;
        typedef typename U::reference			reference;
        typedef typename U::pointer				pointer;
        typedef typename U::difference_type		difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;


		typedef typename U::node_reference		node_reference;
		typedef typename U::node_pointer		node_pointer;

        //typedef typename U::iterator_category iterator_category;

    private:
		node_pointer	_current_node;

    public:
		normal_iterator() : _current_node() {}

		normal_iterator(node_pointer node) : _current_node( node ) {}

		normal_iterator &operator++() {
			_current_node = _current_node->next();
            return *this;
        }

        normal_iterator operator++( int ) {
			_current_node = _current_node->next();
			return *this;
		}

        normal_iterator &operator--() {
            _current_node = _current_node->previous();
            return *this;
        }
        normal_iterator operator--( int ) {
            _current_node = _current_node->previous();
			return *this;
		}

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
	typedef ft::pair<const Key, T>						value_type;
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
	size_type			_size;
	tree_type			_tree;

public:

	/* ------------------------------ Construction ------------------------------ */

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
	_allocator(alloc), _size(0), _tree( tree_type(comp, alloc)) {
	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
	const allocator_type& alloc = allocator_type()) {
		(void) first;
		(void) last;
		(void) comp;
		(void) alloc;
	}

	/* -------------------------------- Iterators ------------------------------- */

	iterator 				begin() {return _tree.begin(); }
	iterator 				end() { return _tree.end();}
	const_iterator 			begin() const { return _tree.begin(); }
	const_iterator 			end() const  { return _tree.end();}
	reverse_iterator 		rbegin() {return iterator(_tree.end());}
	reverse_iterator 		rend() { return iterator(_tree.begin());}
	const_reverse_iterator 	rbegin() const {return iterator(_tree.end());}
	const_reverse_iterator 	rend() const { return iterator(_tree.begin()); }
	const_iterator 			cbegin() const { return _tree.begin(); }
	const_iterator 			cend() const { return _tree.end();}
	const_reverse_iterator 	crbegin() const {return iterator(_tree.end());}
	const_reverse_iterator 	crend() const { return iterator(_tree.begin());}

	/* ----------------------------- Element access ----------------------------- */

	mapped_type& operator[] (const key_type& k) {
		//return _tree.insert( value_type( k, mapped_type() ) ).first->second;
	}

	mapped_type& at (const key_type& k);
	const mapped_type& at (const key_type& k) const;

	/* -------------------------------- Modifiers ------------------------------- */

	ft::pair<iterator, bool> insert( const value_type &val ) {
		return _tree.insert( val );
    }

	iterator find (const key_type& k) {
		return _tree.find(k);
	}

	const_iterator find (const key_type& k) const {
		return _tree.find(k);
	}


	/* -------------------------------- Capacity -------------------------------- */

	bool		empty () const {return  _tree.size() == 0;}
	size_type	size () const { return _tree.size();}
	size_type	max_size () const {return _allocator.max_size();}

	/* -------------------------------- Observers ------------------------------- */

    key_compare   key_comp() const { return key_compare(); }
    //value_compare value_comp() const { return value_compare(); }


	/* -------------------------------- Destructor ------------------------------ */

	~map () {};

private :

	bool _exists (const key_type &k) {
		return _tree.exists(k);
	}

};

} //namespace ft

#endif
