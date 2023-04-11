/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:53:29 by bperraud          #+#    #+#             */
/*   Updated: 2022/11/09 21:53:29 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef> // ptrdiff_t
#include <iterator> // iterator_traits

namespace ft {

/*
   *  @defgroup iterator_tags Iterator Tags
   *  These are empty types, used to distinguish different iterators.  The
   *  distinction is not made by what they contain, but simply by what they
   *  are.  Different underlying algorithms can then be used based on the
   *  different operations supported by different iterator types.
*/

///  Marking input iterators.
struct input_iterator_tag {};
///  Marking output iterators.
struct output_iterator_tag {};
/// Forward iterators support a superset of input iterator operations.
struct forward_iterator_tag : public input_iterator_tag {};
/// Bidirectional iterators support a superset of forward iterator
/// operations.
struct bidirectional_iterator_tag : public forward_iterator_tag {};
/// Random-access iterators support a superset of bidirectional iterator
/// operations.
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template < typename I >
struct iterator_traits {
	typedef typename I::iterator_category iterator_category;
	typedef typename I::value_type        value_type;
	typedef typename I::difference_type   difference_type;
	typedef typename I::pointer           pointer;
	typedef typename I::reference         reference;
};

template < typename T >
struct iterator_traits< T * > {
	typedef random_access_iterator_tag iterator_category;
	typedef T                               value_type;
	typedef T *                             pointer;
	typedef T &                             reference;
	typedef std::ptrdiff_t                  difference_type;
};

template < typename T >
struct iterator_traits< const T * > {
	typedef random_access_iterator_tag iterator_category;
	typedef T                               value_type;
	typedef const T *                       pointer;
	typedef const T &                       reference;
	typedef std::ptrdiff_t                  difference_type;
};


template <typename _It>
class reverse_iterator {

private:
	_It _it;

public:
	typedef typename _It::value_type        value_type;
    typedef typename _It::reference         reference;
    typedef typename _It::pointer           pointer;
    typedef typename _It::difference_type   difference_type;
    typedef typename _It::iterator_category iterator_category;

public:
	reverse_iterator() {}
	reverse_iterator( pointer p ) : _it( _It( p ) ) {}
	reverse_iterator( const _It &other ) : _it( other ) {}
	reverse_iterator( const reverse_iterator &other ) : _it( other._it ) {}
	template < typename U >
    reverse_iterator( const reverse_iterator< U > &other ) : _it( other.base() ) {}

	_It base() const { return _it; }

	template < typename U >
    reverse_iterator &operator=( const reverse_iterator< U > &other ) {
        _it = other.base();
        return *this;
    }

	reverse_iterator operator+( difference_type n ) const { return _it - n; }
    friend reverse_iterator operator+( difference_type n, const reverse_iterator &other ) {
		return other + n;
	};
    reverse_iterator operator-( difference_type n ) const { return _it + n; }
    difference_type  operator-( const reverse_iterator &other ) const {
        return other.base() - _it;
    }

    reverse_iterator operator++() { return --_it; }
    reverse_iterator operator--() { return ++_it; }
    reverse_iterator operator++( int ) { return _it--; }
    reverse_iterator operator--( int ) { return _it++; }

    reverse_iterator &operator+=( difference_type n ) {
        _it -= n;
        return *this;
    };
    reverse_iterator &operator-=( difference_type n ) {
        _it += n;
        return *this;
    };

	reference		operator*() { return (--_It( _it )).operator*(); }
	const reference	operator*() const { return (--_It( _it )).operator*(); }
	pointer			operator->() { return (--_It( _it )).operator->(); }
	const pointer	operator->() const { return (--_It( _it )).operator->(); }
	reference       operator[]( difference_type i ) { return *operator+( i ); }
    const reference operator[]( difference_type i ) const { return *operator+( i );}

	template < typename U >
    bool operator==( const reverse_iterator< U > &other ) const {
        return ( _it == other.base() );
    };
    template < typename U >
    bool operator!=( const reverse_iterator< U > &other ) const {
        return ( _it != other.base() );
    };
    template < typename U >
    bool operator>( const reverse_iterator< U > &other ) const {
        return ( _it < other.base() );
    };
    template < typename U >
    bool operator<( const reverse_iterator< U > &other ) const {
        return ( _it > other.base() );
    };
    template < typename U >
    bool operator>=( const reverse_iterator< U > &other ) const {
        return ( _it <= other.base() );
    };
    template < typename U >
    bool operator<=( const reverse_iterator< U > &other ) const {
        return ( _it >= other.base() );
    };

};

template <typename _It>
class const_reverse_iterator {

private:
	_It _it;

public:
	typedef typename _It::value_type        value_type;
    typedef typename _It::const_reference         const_reference;
    typedef typename _It::const_pointer           const_pointer;
    typedef typename _It::difference_type   difference_type;
    typedef typename _It::iterator_category iterator_category;

public:
	const_reverse_iterator() {}
	const_reverse_iterator( const_pointer p ) : _it( _It( p ) ) {}
	const_reverse_iterator( const _It &other ) : _it( other ) {}
	template < typename P >
	const_reverse_iterator( const reverse_iterator< P> &other ) : _it( other.base() ) {}
	const_reverse_iterator( const const_reverse_iterator &other ) : _it( other._it ) {}
	template < typename U >
    const_reverse_iterator( const const_reverse_iterator< U > &other ) : _it( other.base() ) {}

	_It base() const { return _it; }

	template < typename U >
    const_reverse_iterator &operator=( const const_reverse_iterator< U > &other ) {
        _it = other.base();
        return *this;
    }

	const_reverse_iterator operator+( difference_type n ) const { return _it - n; }
    friend const_reverse_iterator operator+( difference_type n, const const_reverse_iterator &other ) {
		return other + n;
	};
    const_reverse_iterator operator-( difference_type n ) const { return _it + n; }
    difference_type  operator-( const const_reverse_iterator &other ) const {
        return other.base() - _it;
    }

    const_reverse_iterator operator++() { return --_it; }
    const_reverse_iterator operator--() { return ++_it; }
    const_reverse_iterator operator++( int ) { return _it--; }
    const_reverse_iterator operator--( int ) { return _it++; }

    const_reverse_iterator &operator+=( difference_type n ) {
        _it -= n;
        return *this;
    };
    const_reverse_iterator &operator-=( difference_type n ) {
        _it += n;
        return *this;
    };

	const_reference			operator*() { return (--_It( _it )).operator*(); }
	const const_reference	operator*() const { return (--_It( _it )).operator*(); }
	const_pointer					operator->() { return (--_It( _it )).operator->(); }
	const const_pointer			operator->() const { return (--_It( _it )).operator->(); }
	const_reference			operator[]( difference_type i ) { return *operator+( i ); }
    const const_reference	operator[]( difference_type i ) const { return *operator+( i );}

	template < typename U >
    bool operator==( const const_reverse_iterator< U > &other ) const {
        return ( _it == other.base() );
    };
    template < typename U >
    bool operator!=( const const_reverse_iterator< U > &other ) const {
        return ( _it != other.base() );
    };
    template < typename U >
    bool operator>( const const_reverse_iterator< U > &other ) const {
        return ( _it < other.base() );
    };
    template < typename U >
    bool operator<( const const_reverse_iterator< U > &other ) const {
        return ( _it > other.base() );
    };
    template < typename U >
    bool operator>=( const const_reverse_iterator< U > &other ) const {
        return ( _it <= other.base() );
    };
    template < typename U >
    bool operator<=( const const_reverse_iterator< U > &other ) const {
        return ( _it >= other.base() );
    };

};


} // namespace ft

#endif
