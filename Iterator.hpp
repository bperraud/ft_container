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

//#include <iterator>

namespace fte {

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
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef T *                             pointer;
		typedef T &                             reference;
		typedef std::ptrdiff_t                  difference_type;
	};

	template < typename T >
	struct iterator_traits< const T * > {
		typedef std::random_access_iterator_tag iterator_category;
		typedef T                               value_type;
		typedef const T *                       pointer;
		typedef const T &                       reference;
		typedef std::ptrdiff_t                  difference_type;
	};


/*
template <class Category, class T, class Distance = std::ptrdiff_t,
          class Pointer = T*, class Reference = T&>
  struct iterator {
    typedef T         value_type;
    typedef Distance  difference_type;
    typedef Pointer   pointer;
    typedef Reference reference;
    typedef Category  iterator_category;
  };
*/

template <typename It>
class reverse_iterator {

public:
	/*
    typedef typename T::value_type        value_type;
    typedef typename T::reference         reference;
    typedef typename T::pointer           pointer;
    typedef typename T::difference_type   difference_type;
    typedef typename T::iterator_category iterator_category;
	*/

	typedef It												iterator_type;
	typedef typename iterator_traits<It>::value_type		value_type;
    typedef typename iterator_traits<It>::difference_type	difference_type;
    typedef typename iterator_traits<It>::reference			reference;
    typedef typename iterator_traits<It>::pointer			pointer;

protected:
    It current;

public:
	reverse_iterator();
    explicit reverse_iterator(It itr) : current(itr) {}

	template <typename U>
    explicit reverse_iterator(const U& other) : current(other.base()) {}

    reverse_iterator& operator++() { --current; return *this; }
    reverse_iterator operator++(int) { It tmp = *this; ++(*this); return tmp; }

    reverse_iterator& operator--() { ++current; return *this; }
    reverse_iterator operator--(int) { It tmp = *this; --(*this); return tmp; }

    It base() const { return current; }

    // Other member functions, friend functions, and member typedefs are not shown here.
};


template <typename T>
class normal_iterator
{

protected:
	typedef iterator_traits<T>		__traits_type;
	T _it;

public:
	typedef T                               value_type;
	typedef T &                    			reference;
	typedef T *                    			pointer;
	typedef std::ptrdiff_t                  difference_type;
	typedef std::random_access_iterator_tag iterator_category;

public:
	normal_iterator() : _it( T() ) {}
	normal_iterator( const normal_iterator &other ) : _it( other._it ) {}
	normal_iterator( const T &other ) : _it( other ) {}

	T base() const { return _it; }

	normal_iterator &operator=( const normal_iterator &other ) {
		_it = other._it;
		return *this;
	}

	normal_iterator &operator++() {
		_it++;
		return *this;
	}
	normal_iterator  operator++( int ) { return _it++; }
	normal_iterator &operator--() {
		_it--;
		return *this;
	}
	normal_iterator operator--( int ) { return _it--; }


	reference operator*() { return *_it; }
	pointer operator->() { return _it; }

	template < typename U >
	bool operator==( const normal_iterator< U > &other ) const {
		return T( *this ) == U( other );
	}
	bool operator==( const T &other ) const { return T( *this ) == other; }

	template < typename U >
	bool operator!=( const normal_iterator< U > &other ) const {
		return !( *this == other );
	}
	bool operator!=( const T &other ) const { return !( *this == other ); }

};

} // namespace ft

#endif
