/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 12:55:32 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/29 12:55:32 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_H
#define PAIR_H

namespace ft {

template<class T1, class T2>
struct pair {
	typedef T1 first_type;
	typedef T2 second_type;

	T1 first;
	T2 second;

	pair()										: first(), second() {}
	pair(const T1& pFirst, const T2& pSecond)	: first(pFirst), second(pSecond) {}
	pair(const pair<T1,T2>& other)				: first(other.first), second(other.second) {}
	template <class U1, class U2>
	pair(const pair<U1, U2>& p)				: first(p.first), second(p.second) {};

	pair&	operator=(const pair& other)
	{
		if (this == &other)
			return *this;
		first=other.first;
		second=other.second;
		return *this;
	}
	~pair() {}

	bool operator==( const pair &other ) const {
		return ( first == other.first && second == other.second );
	}
	bool operator<( const pair &other ) const {
		return first < other.first || ( !( first < other.first ) && second < other.second );
	}
	bool operator!=( const pair &other ) const { return !( *this == other ); }
	bool operator<=( const pair &other ) const { return !( *this < other ); }
	bool operator>( const pair &other ) const { return ( other < *this ); }
	bool operator>=( const pair &other ) const { return !( *this < other ); }
};

template< class T1, class T2 >
inline void swap( pair<T1,T2>& x, pair<T1,T2>& y ) throw() { x.swap(y); }

template< class T1, class T2 >
pair<T1,T2> make_pair(T1 first, T2 second ) { return pair<T1, T2>(first, second);}

} //namespace ft

#endif
