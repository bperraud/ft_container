/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:41:01 by bperraud          #+#    #+#             */
/*   Updated: 2023/01/03 17:41:01 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_H
#define UTILITY_H

namespace ft {

template <typename T>
void swap(T &a, T &b) {
	T tmp( a );
	a = b;
	b = tmp;
}

template <typename Iterator>
bool equal(Iterator first, Iterator last, Iterator b)
{
	while (first != last){
		if ( *first != *b ) {
			return false;
		}
		first++;
		b++;
	}
	return true;
}

template <typename Iterator>
bool lexicographical_compare(Iterator first, Iterator last, Iterator bfirst, Iterator blast)
{
	while ( first != last ) {
		if ( bfirst == blast || *bfirst < *first ) {
			return false;
		}
		else if ( *first < *bfirst ) {
			return true;
		}
		first++;
		bfirst++;
	}
	return bfirst != blast;
}

} //namespace ft

#endif
