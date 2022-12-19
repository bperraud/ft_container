/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:51:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/19 15:48:47 by bperraud         ###   ########.fr       */
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

	// iterator class
    template <typename U>
	class normal_iterator {
    public:
        typedef typename U::value_type        value_type;
        typedef typename U::reference         reference;
        typedef typename U::pointer           pointer;
        typedef typename U::difference_type   difference_type;
        typedef typename U::iterator_category iterator_category;

    private:
        U _it;

    public:
        normal_iterator() : _it( U() ) {}
        normal_iterator( const normal_iterator &other ) : _it( other._it ) {}
        normal_iterator( const U &other ) : _it( other ) {}
        normal_iterator &operator=( const normal_iterator &other ) {
            _it = other._it;
            return *this;
        }

        normal_iterator &operator++() {
            _it++;
            return *this;
        }
        normal_iterator operator++( int ) { return _it++; }
        normal_iterator &operator--() {
            _it--;
            return *this;
        }
        normal_iterator operator--( int ) { return _it--; }


        reference operator*() { return *_it; }
        //typename normal_iterator< tree_const_iterator >::reference operator*() const {
        //    return *_it;
        //}

        pointer operator->() { return _it.operator->(); }
        //typename normal_iterator< tree_const_iterator >::pointer operator->() const {
        //    return _it.operator->();
        //}

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

        //operator U() const { return U( _it ); }
	};

	/*
        operator normal_iterator< tree_const_iterator >() const {
            return normal_iterator< tree_const_iterator >( _it );
        }
    };
	*/

	typedef BST<Key, T, Compare, Allocator> 			tree_type;

	//typedef typename BST<Key, T, Compare, Allocator> 	tree_type;

	typedef normal_iterator< tree_type >				iterator;
    typedef normal_iterator< const tree_type >			const_iterator;
    typedef ft::reverse_iterator< iterator >			reverse_iterator;
    typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;

	/*
    typedef normal_iterator< tree_iterator >			iterator;
    typedef normal_iterator< tree_const_iterator >		const_iterator;
    typedef ft::reverse_iterator< iterator >			reverse_iterator;
    typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;
	*/

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


	/* ----------------------------- Element access ----------------------------- */

	mapped_type& operator[] (const key_type& k);

	mapped_type& at (const key_type& k);
	const mapped_type& at (const key_type& k) const;

	/* -------------------------------- Capacity -------------------------------- */

	bool		empty () const {return _size == 0;}
	size_type	size () const { return _size;}
	size_type	max_size () const {return _allocator.max_size();}

	/* -------------------------------- Observers ------------------------------- */

    //key_compare   key_comp() const { return key_compare(); }
    //value_compare value_comp() const { return value_compare(); }


	/* -------------------------------- Destructor ------------------------------ */

	~map () {};
};

} //namespace ft

#endif
