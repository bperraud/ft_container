/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:09:19 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/07 15:09:19 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
#define STACK_H

#include "vector.hpp"
#include "Iterator.hpp"
#include "type_traits.hpp" // for enable_if

namespace ft {

template <class T, class Container = ft::vector<T> >
class stack {

public:
	typedef T			value_type;
	typedef Container	container_type;
	typedef std::size_t	size_type;

protected :
	container_type _container;

public:

	/* ------------------------------ Construction ------------------------------ */

	explicit stack (const container_type& ctnr = container_type()) : _container(ctnr) {}

	/* ---------------------------- Member functions ---------------------------- */

	bool empty() const {
		return _container.empty();
	}

	size_type size() const {
		return _container.size();
	}

	value_type& top() {
		return _container.back();
	}

	const value_type& top() const {
		return _container.back();
	}

	void push (const value_type& val) {
		_container.push_back(val);
	}

	void pop() {
		_container.pop_back();
	}

	void swap (stack& x) {
		_container.swap(x);
	}

	/* -------------------------- Relational operators -------------------------- */

	bool operator==( const stack &other ) const { return _container == other._container; }
    bool operator!=( const stack &other ) const { return _container != other._container; }
    bool operator<( const stack &other ) const { return _container < other._container; }
    bool operator<=( const stack &other ) const { return _container <= other._container; }
    bool operator>( const stack &other ) const { return _container > other._container; }
    bool operator>=( const stack &other ) const { return _container >= other._container; }

};

} // namespace ft

#endif
