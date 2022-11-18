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
class Vector : public Vect<T> {

private:


public:

	Vector () : Vect<T>() {};

	explicit Vector (std::size_t d) : Vect<T>(d) {}

	typedef T* 			iterator;
	typedef const T*	const_iterator;

	iterator begin() { return &Vect<T>::_val[0]; }
	iterator end() { return &Vect<T>::_val[Vect<T>::_size]; }

};

#endif
