/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/19 17:04:50 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BST_H_
#define _BST_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <ostream>             // output streams

template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<std::pair<const Key, T> > >	// map::allocator_type
class BST {


public :
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef std::pair<const Key, T>						value_type;
	typedef Compare										key_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer		const_pointer;

	typedef std::ptrdiff_t								difference_type;
	typedef std::size_t									size_type;


private:
    // Implementation
	struct _Node {
		const value_type _info;
		BST left, right;
		explicit _Node (const value_type& v) : _info(v), left(), right() {}
	};

    _Node *				_root;
	allocator_type		_allocator;
	key_compare			_key_compare;

protected:
    //static const value_type _NOT_FOUND = 0;                      // "not found" element

public:

    /* ------------------------------ Construction ------------------------------ */

	BST( const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type() )
		:_root( 0 ), _allocator( alloc ), _key_compare(comp) {
	}


	/* -------------------------------- Observers ------------------------------- */

    //virtual BST& operator= (const BST&);
    // Destructor
    virtual ~BST () {delete _root;}  // recursive
    // Associated function
    //template <typename U>
    //friend inline std::ostream& operator<< (std::ostream&, const BST<U>&);

	// Operator
	BST &operator++() ;
	BST operator++( int ) ;
	BST &operator--() ;
	BST operator--( int ) ;

}; // BST<T>

//template <typename T>
//const T BST<T>::_NOT_FOUND = 0;


//template <typename T>
//BST<T>::BST( const key_compare &comp = key_compare(), const allocator_type &alloc = node_allocator_type() )
//	:_root( _end ), _allocator( alloc ),_key_compare( extended_key_compare( _end, comp ) ) {
//}


#endif // _BST_H_
