/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:10:55 by bperraud          #+#    #+#             */
/*   Updated: 2022/11/18 13:10:55 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT_H
#define VECT_H

#include <iostream>

#include "Vect.hpp"
#include "Iterator.hpp"
#include "type_traits.hpp" // for enable_if
#include "utility.hpp" // for equal and lexicalcompare
#include <memory>
#include <algorithm>

namespace ft {

const int INIT_CAPA = 10;

template <typename T, typename Allocator = std::allocator<T> >
class vector {

	// iterator class
	template <typename U>
	class normal_iterator {
	private:
		U* _it;

	public:
		typedef U								value_type;
		typedef U&								reference;
		typedef U*								pointer;
		typedef std::ptrdiff_t					difference_type;
		typedef std::random_access_iterator_tag	iterator_category;

	public:
		normal_iterator() : _it(0) {}
		normal_iterator( pointer i ) : _it(i) {}
		normal_iterator( const normal_iterator &other ) : _it( other._it ) {}

		pointer base() const { return _it; }

		normal_iterator &operator=( const normal_iterator &other ) {
			_it = other._it;
			return *this;
		}
		difference_type operator-( const normal_iterator &other ) const { return _it - other._it; }
		difference_type operator+( const normal_iterator &other ) const { return _it + other._it; }

		friend normal_iterator operator+( difference_type n, const normal_iterator &other ) {
			return other + n;
		}

		normal_iterator operator+( difference_type n ) const { return _it + n; }
		normal_iterator operator-( difference_type n ) const { return _it - n; }
		normal_iterator& operator+=(difference_type n) { _it += n; return *this;}
		normal_iterator& operator-=(difference_type n) { _it -= n; return *this;}
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
		reference operator*() const { return *_it;}
		pointer operator->() { return _it; }
		pointer operator->() const { return _it ;};
		reference operator[]( difference_type i ) { return _it[i]; }
		reference operator[]( difference_type i ) const { return _it[i];}

		template < typename V >
		bool operator==( const normal_iterator< V > &other ) const {
			return ( _it == other.operator->() );
		};
	template < typename V >
		bool operator!=( const normal_iterator< V > &other ) const {
			return ( _it != other.operator->() );
		};
		template < typename V >
		bool operator>( const normal_iterator< V > &other ) const {
			return ( _it > other.operator->() );
		};
		template < typename V >
		bool operator<( const normal_iterator< V > &other ) const {
			return ( _it < other.operator->() );
		};
		template < typename V >
		bool operator>=( const normal_iterator< V > &other ) const {
			return ( _it >= other.operator->() );
		};
		template < typename V >
		bool operator<=( const normal_iterator< V > &other ) const {
			return ( _it <= other.operator->() );
		};

		// convert T to const T for non-const to const assignation
		operator normal_iterator< const U >() const {
            return ( normal_iterator< const U >( _it ) );
        }
	};

public:
	typedef T                                        value_type;

	typedef Allocator                                allocator_type;
	typedef typename allocator_type::reference       reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;

	typedef normal_iterator <T>						iterator;
	typedef normal_iterator <const T>				const_iterator;

	typedef ft::reverse_iterator< iterator >		reverse_iterator;
	typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
	typedef std::ptrdiff_t							difference_type;
	typedef std::size_t								size_type;

	typedef Vect<typename Allocator::value_type>	vector_type;

private:
	allocator_type			_allocator;
	size_type				_capacity;
	vector_type				_vector;

public:

	template <class U, class Alloc>
	friend std::ostream& operator<< (std::ostream& out, const vector<U,Alloc>& v);

	/* ------------------------------ Construction ------------------------------ */

	explicit vector (const allocator_type &alloc = allocator_type()) : _allocator(alloc), _capacity(INIT_CAPA), _vector() {
		_vector._data = _allocator.allocate(INIT_CAPA);
	}

	explicit vector( size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type() )
		: _allocator(alloc), _capacity(n), _vector() {
		if (n > max_size())
			throw std::length_error("vector");
		_vector._data = _allocator.allocate(n);
		_vector._size = n;
		for (size_type i = 0 ; i < n; ++i)
		{
			_allocator.construct(_vector._data + i, val);
		}
	}

	template < class InputIterator >
	vector( InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true)
		: _allocator(alloc), _capacity(INIT_CAPA), _vector() {
		_vector._data = _allocator.allocate(INIT_CAPA);
		assign( first, last );
	}

	vector( const vector &x ) : _allocator( x._allocator ), _capacity(x._capacity), _vector(){
		_vector._data = _allocator.allocate(x._capacity);
		*this = x;
    }

	vector &operator=( const vector &x ) {
		assign(x.begin(), x.end());
        return *this;
    }

	/* -------------------------------- Iterators ------------------------------- */

	iterator 				begin() {return _vector._data;}
	iterator 				end() { return _vector._data + _vector._size;}
	const_iterator 			begin() const { return _vector._data; }
	const_iterator 			end() const { return begin() + _vector._size;}
	reverse_iterator 		rbegin() { return begin() + _vector._size; }
	reverse_iterator 		rend() { return _vector._data; }
	const_reverse_iterator 	rbegin() const { return begin() + _vector._size; }
	const_reverse_iterator 	rend() const { return _vector._data; }
	const_iterator 			cbegin() const { return _vector._data; }
	const_iterator 			cend() const { return begin() + _vector._size;}
	const_reverse_iterator 	crbegin() const { return begin() + _vector._size;}
	const_reverse_iterator 	crend() const { return _vector._data ; }

	/* -------------------------------- Capacity -------------------------------- */

	size_type	size () const { return _vector._size;}
	size_type	max_size () const { return _allocator.max_size(); }
	bool		empty () const { return _vector._size == 0; }
	size_type	capacity() const { return _capacity; }

	void reserve (size_type n) {
		if (n > max_size())
			throw std::length_error("vector::reserve");
		if (n > _capacity)
			_reallocate(n);
	}

	void resize (size_type n, value_type val = value_type()) {
		if (n == _vector._size)
			return;
		reserve(n);
		if (n > max_size())
			throw std::length_error("vector::resize");
		if (n < _vector._size) {
			for (size_type i = n; i < _vector._size; ++i)
				_allocator.destroy(_vector._data + i);
		}
		else {
			for (size_type i = _vector._size; i < n; ++i)
				_allocator.construct(_vector._data + i, val);
		}
		_vector._size = n;
	}

	/* ----------------------------- Element access ----------------------------- */

	reference			operator[] (std::ptrdiff_t idx) { return _vector.operator[](idx);}
	const_reference		operator[] (std::ptrdiff_t idx) const { return _vector.operator[](idx);}
	reference			at (size_type n) {return _vector.at(n);}
	const_reference		at (size_type n) const {return _vector.at(n);}
	reference 			front() {return _vector.at(0);}
	const_reference 	front() const {return _vector.at(0);}
	reference 			back() {return _vector.at(_vector._size - 1);}
	const_reference		back() const {return _vector.at(_vector._size - 1);}
	value_type* 		data() {return _vector._data;}
	const value_type*	data() const {return _vector._data;}

	/* -------------------------------- Modifiers ------------------------------- */

	template <class InputIterator>
		struct ListNode {
			ListNode *node;
			ListNode *next;
			typename std::iterator_traits<InputIterator>::value_type val;
		};

	template <class InputIterator>
	void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {
		if (ft::is_same<typename std::iterator_traits<InputIterator>::iterator_category, std::random_access_iterator_tag>::value) {
			resize(std::distance(first, last));
			for (iterator it = begin() ; it != end() ; ++it) {
				*it = *first;
				first++;
			}
		} else {
			size_t size = 0;
			for (InputIterator input = first; input != last ; ++input) {
				if (size >= _vector._size)
					resize(size + 1);
				_vector._data[size] = *input;
				size++;
			}
			size_t s = size;
			while (s < _vector._size) {
				_allocator.destroy(_vector._data + s);
				s++;
			}
			_vector._size = size;
		}

		//ListNode<InputIterator> linked_list;
		//ListNode<InputIterator> head = &linked_list;

		//for (InputIterator input = first; input != last ; ++input) {
		//	linked_list.val = *input;
		//	ListNode<InputIterator> newNode;
		//	linked_list.next = newNode;

		//	size++;
		//}

	}

	void assign (size_type n, const value_type& val) {
		resize(n);
		for (iterator it = begin(); it != end(); ++it) {
			*it = val;
		}
	}

	void push_back (const value_type& val) {
		if (_capacity < _vector._size + 1)
			_reallocate(_increase_capacity(1));
		_vector._size += 1;
		_allocator.construct(_vector._data + _vector._size - 1, val);
	}

	void pop_back() {
		_allocator.destroy(_vector._data + _vector._size - 1);
		_vector._size -= 1;
	}

	iterator insert (iterator position, const value_type& val) {
		const size_type range = std::distance(begin(), position);
		insert(position, 1, val);
		return _vector._data + range;
	}

	void insert (iterator position, size_type n, const value_type& val) {
		size_type offset = position - _vector._data;
		reserve(_vector._size + n);
		iterator new_position = _vector._data + offset;
		if (new_position != end()) {
			for (size_type i = _vector._size; i < n + _vector._size; ++i)
				_allocator.construct(_vector._data + i, val);
			_vector.move_up(offset, n, _vector._size - offset);
			std::fill_n(new_position, n, val);
		}
		else {
			for (size_type i = offset; i < n + offset; ++i)
				_allocator.construct(_vector._data + i, val);
		}
		_vector._size += n;
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type = true) {
		const size_type n = std::distance(first, last);

		//for (size_type i = _vector._size; i < n + _vector._size; ++i)
		//	_allocator.construct(_vector._data + i, val);

		size_type offset = position - begin();
		if (_capacity < _vector._size + n)
			_reallocate(_increase_capacity(n));
		iterator new_position = begin() + offset;
		if (new_position != end())
			_vector.move_up(offset, n, _vector._size - offset);
		std::copy_backward(first, last, new_position + n);
		_vector._size += n;
	}

	iterator erase (iterator position) {
		return erase(position, position + 1);
	}

	iterator erase (iterator first, iterator last) {
		if (first > last)
			throw std::length_error("vector::erase");
		const size_type start = std::distance(begin(), first);
		const size_type range = std::distance(first, last);
		for (iterator it = end() - range; it != end(); ++it)
			_allocator.destroy(it.operator->());
		_vector.move_back(start, range, std::distance(last, end()));
		_vector._size -= range;
		return (begin() + start);
	}

	void swap (vector& x) {
		ft::swap(_capacity, x._capacity);
		ft::swap(_vector._size, x._vector._size);
		ft::swap(_allocator, x._allocator);
		ft::swap(_vector._data, x._vector._data);
	}

	void clear() {
		resize(0);
	}

	/* -------------------------------- Allocator ------------------------------- */

	allocator_type get_allocator() const { return _allocator;}

	virtual ~vector() {
		clear();
		_allocator.deallocate(_vector._data, _capacity);
	}

	/* -------------------------- Relational operators -------------------------- */

	bool operator==( const vector &other ) const {
		return size() == other.size() && ft::equal( begin(), end(), other.begin() );
	}
	bool operator!=( const vector &other ) const { return !( *this == other ); }
	bool operator<( const vector &other ) const {
		return ft::lexicographical_compare( begin(), end(), other.begin(), other.end() );
	}
	bool operator<=( const vector &other ) const { return *this == other || *this < other;}
	bool operator>( const vector &other ) const { return !( *this <= other ); }
	bool operator>=( const vector &other ) const { return !( *this < other ); }


private:

	/* ------------------------------ Private Method ---------------------------- */

	inline void	_reallocate(size_type n) {	// reallocate n _capacity
		if (n > max_size())
			throw std::length_error("vector::_reallocate");
		pointer ptr = _allocator.allocate(n);
		for (size_type i = 0; i < _vector._size; ++i)
			_allocator.construct(ptr + i, *(_vector._data + i));
		for (size_type i = 0; i < _vector._size; ++i)
			_allocator.destroy(_vector._data + i);
		_allocator.deallocate(_vector._data, _capacity);
		_vector._data = ptr;
		_capacity = n;
	}

	inline size_type _increase_capacity(size_type n) {	// increase capacity to add n element
		size_t new_capacity = _capacity;
		while (_vector._size + n > new_capacity && new_capacity < max_size())
			new_capacity *= 10;
		return new_capacity;
	}
};

template <class T, class Alloc>
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
	x.swap(y);
}


// Associated functions =========================================================

template <class T, class Alloc>
inline std::ostream& operator<< (std::ostream& out, const vector<T,Alloc>& v)
{
	out << v._vector ;
	return out;
}

} //namespace ft

#endif
