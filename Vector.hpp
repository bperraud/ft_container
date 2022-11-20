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

private:

	class iterator;               // make iterator local

	iterator	it;

public:

	vector () : Vect<T>() {};

	explicit vector (std::size_t d) : Vect<T>(d) {}

	// possible de definir un iterator comme ça ?
	//typedef T* 			iterator;
	//typedef const T*	const_iterator;

	iterator begin() { return &Vect<T>::_val[0]; }
	iterator end() { return &Vect<T>::_val[Vect<T>::_size]; }

};


template <typename T>
class vector<T>::iterator {
protected:
	T _it;

public:
	typedef T                               value_type;
	typedef T &                    			reference;
	typedef T *                    			pointer;
	typedef std::ptrdiff_t                  difference_type;
	typedef std::random_access_iterator_tag iterator_category;

public:
	iterator() : _it( T() ) {}
	iterator( const iterator &other ) : _it( other._it ) {}
	iterator( const T &other ) : _it( other ) {}

	T base() const { return _it; }

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


	bool operator==( const T &other ) const { return T( *this ) == other; }

	bool operator!=( const T &other ) const { return !( *this == other ); }

};


#endif
