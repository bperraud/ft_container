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

#include "Vect.hpp"
#include "Iterator.hpp"


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
		normal_iterator() : _it(U()) {}
		normal_iterator( pointer i ) : _it(i) {}
		normal_iterator( const normal_iterator &other ) : _it( other._it ) {}
		normal_iterator( U &i ) : _it( &i ) {}

		normal_iterator &operator=( const normal_iterator &other ) {
			_it = other._it;
			return *this;
		}
		normal_iterator operator+( difference_type n ) const { return _it + n; }
		/*
		iterator operator+(difference_type lhs, const iterator &other) {
			return lhs + other;
		}
		*/
		normal_iterator operator-( difference_type n ) const { return _it - n; }
		/*
		difference_type operator-( const Iterator &other ) const {
			return _p - other._p;
		}
		*/

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


        bool operator>( const normal_iterator &other ) const { return (_it > other.operator->()); };
        bool operator<( const normal_iterator &other ) const { return (_it < other.operator->()); };
		bool operator>=( const normal_iterator &other ) const { return (_it >= other.operator->()); };
		bool operator<=( const normal_iterator &other ) const { return (_it <= other.operator->()); };
		bool operator==( const normal_iterator& other ) const { return _it == other._it; }
		bool operator!=( const normal_iterator& other ) const { return _it != other._it; }

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

	//typedef typename Vect<T>::_size						_size;

private:
	allocator_type			_alloc;
	size_type				_capacity;
	vector_type				_vector;

public:
	vector () : Vect<T>() , _capacity(0){
		//_alloc = new Allocator() ;
	};
	explicit vector (std::size_t d) : _capacity(0), _vector(d) {
		_alloc = allocator_type();
		reserve(d);
	}

	vector( const vector &other ) {
        *this = other;
    }

	// operators
	vector &operator=( const vector &other ) {
        return *this;
    }

	T& operator[] (std::ptrdiff_t idx) { return _vector.operator[](idx);}

	iterator begin() {return iterator(this->operator[](0)); }
	iterator end() { return begin() + _vector.dim(); }

	reverse_iterator rbegin() {return reverse_iterator(begin() + _vector.dim() - 1);}
	reverse_iterator rend() { return reverse_iterator(this->operator[](0)) + 1; }

	const_iterator begin() const { return const_iterator(this->operator[](0)); }
	const_iterator end() const  { return const_iterator(begin() + _vector.dim()); }

	// Capacity
	size_type	size () const { return _vector.dim();}
	bool		empty () const {return _vector.dim() == 0;}
	size_type	capacity() const { return _capacity; }
	size_type	max_size () const {return _alloc.max_size();}

	void		reserve (size_type n) {
		if (n > _capacity)
		{
			_vector.setVal(_alloc.allocate(n));
			_capacity = n;
		}
	}

	void resize (size_type n, value_type val = value_type()) {
		if (n < _vector.dim())
		{
			for (std::size_t i = 0; i <  _vector.dim(); ++i)
				//_alloc.destroy()
				;
		}
		if (n > _capacity)
		{
			pointer ptr = _alloc.allocate(n);
			_vector.cp(ptr, val, n);
			_alloc.deallocate(_vector.getVal(), _capacity);
			_vector.setVal(ptr);
			_capacity = n;
		}
	}

	virtual ~vector() { _alloc.deallocate(_vector.getVal(), _capacity);}

};

#endif
