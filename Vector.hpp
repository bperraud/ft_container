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

		//explicit value_type( normal_iterator o) { return *o._it; }

		// bizarre ça non ?
		explicit normal_iterator( U &i ) : _it( &i ) {}

		normal_iterator &operator=( const normal_iterator &other ) {
			_it = other._it;
			return *this;
		}

		//normal_iterator operator-( const normal_iterator &other ) const { return _it - other._it; }
		//normal_iterator operator+( const normal_iterator &other ) const { return _it + other._it; }

		difference_type operator-( const normal_iterator &other ) const { return _it - other._it; }
		difference_type operator+( const normal_iterator &other ) const { return _it + other._it; }

		// util ?
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

private:
	allocator_type			_alloc;
	size_type				_capacity;
	vector_type				_vector;


	void	reallocate(size_type n) {
		pointer ptr = _alloc.allocate(n);
		_vector.cp(ptr);
		_alloc.deallocate(_vector.getData(), _capacity);
		_vector.setVal(ptr);
		_capacity = n;
	}

	void	reallocate(size_type n, std::ptrdiff_t start, std::size_t range, const value_type& val) {
		pointer ptr = _alloc.allocate(n);
		_vector.cp_and_move(ptr, start, range, val);
		_alloc.deallocate(_vector.getData(), _capacity);
		_vector.setVal(ptr);
		_capacity = n;
	}

	void	increase_capacity(size_type n) {
		while (_capacity < n)
			_capacity *= 2;
	}

public:
	vector () : _capacity(10), _vector(){
		//_alloc = new Allocator() ;
	};

	explicit vector (std::size_t d) : _capacity(d), _vector(d) {
		_alloc = allocator_type();
		_vector.setVal(_alloc.allocate(d));
		//reserve(d);
	}

	vector( const vector &other ) {
        *this = other;
    }

	// operators
	vector &operator=( const vector &other ) {
        return *this;
    }

	iterator begin() {return iterator(data()); }
	iterator end() { return iterator(data() + _vector.dim()); }
	const_iterator begin() const { return const_iterator(data()); }
	const_iterator end() const  { return const_iterator(begin() + _vector.dim()); }

	reverse_iterator rbegin() {return reverse_iterator(begin() + _vector.dim() - 1);}
	reverse_iterator rend() { return reverse_iterator(data() - 1); }
	const_reverse_iterator rbegin() const {return const_reverse_iterator(begin() + _vector.dim() - 1);}
	const_reverse_iterator rend() const { return const_reverse_iterator(data() - 1); }

	const_iterator cbegin() const { return const_iterator(data());}
    const_iterator cend() const { return const_iterator(begin() + _vector.dim()); }
    const_reverse_iterator crbegin() const {return const_reverse_iterator(begin() + _vector.dim() - 1);}
    const_reverse_iterator crend() const { return const_reverse_iterator(data() - 1); }


	// Capacity
	size_type	size () const { return _vector.dim();}
	bool		empty () const {return _vector.dim() == 0;}
	size_type	capacity() const { return _capacity; }
	size_type	max_size () const {return _alloc.max_size();}

	void		reserve (size_type n) {
		if (n > _capacity)
		{
			pointer ptr = _alloc.allocate(n);
			_vector.cp(ptr);
			_vector.setVal(ptr);
			_capacity = n;
		}
	}

	void resize (size_type n, value_type val = value_type()) {
		pointer data = _vector.getData();
		if (n < _vector.dim())
		{
			for (std::size_t i = n; i < _vector.dim(); ++i)
				_alloc.destroy(data + i);
		}
		else if (n > _capacity)
		{
			reallocate(n);
			_vector.fill(n, _capacity, val);
		}
		else if (n > _vector.dim())
		{
			for (std::size_t i = _vector.dim(); i < n; ++i)
				data[i] = val;
		}
		_vector.setDim(n);
	}

	//Element access
	reference			operator[] (std::ptrdiff_t idx) { return _vector.operator[](idx);}
	reference			at (size_type n) {return _vector.at(n);}
	const_reference		at (size_type n) const {return _vector.at(n);}
	value_type* 		data() {return _vector.getData();}
	const value_type*	data() const {return _vector.getData();}
	reference 			front() {return _vector.at(0);}
	const_reference 	front() const {return _vector.at(0);}
	reference 			back() {return _vector.at(_vector.dim() - 1);}
	const_reference		back() const {return _vector.at(_vector.dim() - 1);}

	//Modifiers


	template <class InputIterator>
	void assign (InputIterator first, InputIterator last) {
		pointer data = _vector.getData();
		typename iterator::difference_type range = last - first;
		resize(range);
		for (std::size_t i = 0; i < _vector.dim(); ++i)
		{
			_alloc.destroy(data + i);
			data[i] = *(first + i);
		}
	}


	void assign (size_type n, const value_type& val) {
		resize(n);
		pointer data = _vector.getData();
		for (std::size_t i = 0; i < _vector.dim(); ++i)
		{
			_alloc.destroy(data + i);
			data[i] = val;
		}
	}

	void push_back (const value_type& val) {
		if (_capacity < _vector.dim() + 1)
		{
			increase_capacity(_vector.dim() + 1);
			reallocate(_capacity);
		}
		_vector.setDim(_vector.dim() + 1);
		_vector.operator[](_vector.dim() - 1) = val;
	}

	void pop_back() {
		if (!empty())
		{
			_alloc.destroy(_vector.getLast());
			_vector.setDim(_vector.dim() - 1);
		}
	}

	// manque gestion d'erreur !

	iterator insert (iterator position, const value_type& val) {
		typename iterator::difference_type i = position - begin();
		if (_capacity < _vector.dim() + 1)
			increase_capacity(_vector.dim() + 1);
		reallocate(_capacity, i, 1, val);	// reallocate and copy until position
		return begin() + i;
	}


    void insert (iterator position, size_type n, const value_type& val) {
		// test pour n > 0
		typename iterator::difference_type i = position - begin();
		if (_vector.dim() + n > _capacity)
			increase_capacity(_vector.dim() + n);
		reallocate(_capacity, i, n, val);
	}

	/*
	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last) {
		std::cout << "PAS LE BON" << std::endl;
		typename iterator::difference_type i = position - begin();
		//size_type n = std::distance( first, last );
		(void) i;
		(void) first;
		(void) last;
		//cp_and_move ()
	}
	*/

	void clear() {
		resize(0);
	}

	iterator erase (iterator position) {
		typename iterator::difference_type start = position - begin();
		erase(position , position + 1);
		return begin() + start;
	}

	iterator erase (iterator first, iterator last) {
		pointer data = _vector.getData();
		typename iterator::difference_type start = first - begin();
		for (typename iterator::difference_type i = start; i < last - begin(); ++i)
			_alloc.destroy(data + i);
		_vector.move_back(start, last - first);
		return begin() + start;
	}

	//Allocator
	allocator_type get_allocator() const { return _alloc;}

	virtual ~vector() { _alloc.deallocate(_vector.getData(), _capacity);}

};

#endif
