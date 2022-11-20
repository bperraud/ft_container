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

template <typename T>
class vector : public Vect<T> {

public:
	class iterator;               // make iterator local
	iterator	it;

public:

	vector () : Vect<T>() {};

	explicit vector (std::size_t d) : Vect<T>(d) {}


	//const T& operator[] (std::ptrdiff_t idx)  ;

	// possible de definir un iterator comme ça ?
	//typedef T* 			iterator;
	//typedef const T*	const_iterator;

	//iterator begin() { return &Vect<T>::_val[0]; }
	//iterator end() { return &Vect<T>::_val[Vect<T>::_size]; }

	iterator begin() { return this->operator[](0) ;}
	iterator end() { return this->operator[](Vect<T>::_size-1) ;}
};


template <typename T>
class vector<T>::iterator {
protected:
	T* _it;

public:
	typedef T								value_type;
	typedef T&								reference;
	typedef T*								pointer;
	typedef std::ptrdiff_t					difference_type;
	typedef std::random_access_iterator_tag	iterator_category;

public:
	iterator() : _it(T()) {}
	iterator(const iterator &other) : _it(other._it) {}
	iterator(pointer i) : _it( i ) {}
	iterator(T &i) : _it(&i) {}

	//conversion
	explicit iterator(const T &i) : _it(&i) {}



	T base() const { return _it; }

	iterator operator+(difference_type n) const {return _it + n;}
	/*
	iterator operator+(difference_type lhs, const iterator &other) {
		return lhs + other;
	}
	*/

	iterator operator-(difference_type n) const { return _it - n; }

	/*
	difference_type operator-( const Iterator &other ) const {
		return _p - other._p;
	}
	*/

	iterator &operator=( const iterator &other ) {
		_it = other._it;
		return *this;
	}
	iterator &operator++() {
		_it++;
		return *this;
	}
	iterator  operator++( int ) { return _it++; }
	iterator &operator--() {
		_it--;
		return *this;
	}
	iterator operator--( int ) { return _it--; }

	reference operator*() { return *_it; }
	pointer operator->() { return _it; }

	bool operator==( const reference other ) const { return _it == other._it; }
	bool operator!=( const reference other ) const { return _it != other._it; }
	bool operator==( iterator other ) const { return _it == other._it; }
	bool operator!=( iterator other ) const { return _it != other._it; }
};


#endif
