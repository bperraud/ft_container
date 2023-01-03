/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:51:50 by bperraud          #+#    #+#             */
/*   Updated: 2023/01/03 15:13:29 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
#define MAP_H

#include "BST.hpp"
#include "Iterator.hpp"
#include "pair.hpp"

namespace ft {

template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
class map {
public :
	typedef BST<Key, T, Compare, Allocator> 				tree_type;

	typedef const tree_type		const_tree_type;
	//typedef const BST<Key, const T, Compare, Allocator>		const_tree_type;

	// iterator class
    template <typename U>
	class normal_iterator {
    public:

        typedef typename U::value_type			value_type;
        typedef typename U::reference			reference;
        typedef typename U::pointer				pointer;
		typedef typename U::difference_type		difference_type;
        typedef typename U::iterator_category	iterator_category;


		typedef typename U::const_reference		const_reference;
		typedef	typename U::const_pointer		const_pointer;
		typedef typename U::node_pointer		node_pointer;

    private:
		node_pointer	_current_node;
		// const pointer ?

    public:

		normal_iterator() : _current_node() {}
		//normal_iterator( node_pointer node ) : _current_node( node ) {}
		normal_iterator( const node_pointer &node ) : _current_node( node ) {}
		normal_iterator( const normal_iterator &other ) : _current_node( other._current_node ) {}

		const node_pointer &get_node() const { return _current_node; }

		normal_iterator &operator=( const normal_iterator &other ) {
            _current_node = other.get_node();
            return *this;
        }
		normal_iterator &operator++() {
			_current_node = _current_node->next();
            return *this;
        }
        normal_iterator operator++( int ) {
			normal_iterator tmp = _current_node;
			_current_node = _current_node->next();
			return tmp;
		}
        normal_iterator &operator--() {
            _current_node = _current_node->previous();
            return *this;
        }
        normal_iterator operator--( int ) {
            normal_iterator tmp = _current_node;
			_current_node = _current_node->previous();
			return tmp;
		}

		pointer operator->() {
			return &_current_node->_info;
 		}

		typename normal_iterator< tree_type >::const_pointer operator->() const {
			return &_current_node->_info;
		}

		reference operator*() { return _current_node->_info; }
		typename normal_iterator< tree_type >::const_reference operator*() const {
			return _current_node->_info;
		}

		template < typename P >
		bool operator==( const normal_iterator< P > &other ) const {
			return _current_node == other.get_node();
		}
		template < typename P >
		bool operator!=( const normal_iterator< P > &other ) const {
			return !( *this == other );
		}

		operator U() const { return node_pointer( _current_node ); }

		operator normal_iterator< tree_type >() const {
            return ( normal_iterator< tree_type >( _current_node ) );
        }
	};

	// 	class const_iterator
    template <typename U>
	class const_normal_iterator {
    public:

		typedef typename U::value_type			value_type;
        typedef typename U::reference			reference;
        typedef typename U::pointer				pointer;
		typedef typename U::difference_type		difference_type;
        typedef typename U::iterator_category	iterator_category;

		typedef	typename U::node_pointer		node_pointer;
		typedef typename U::const_reference		const_reference;
        typedef typename U::const_pointer		const_pointer;

    private:
		node_pointer	_current_node;

    public:
		const_normal_iterator() : _current_node() {}

		template < typename P >
		const_normal_iterator( const normal_iterator< P > &other ) : _current_node( other.get_node() ) {}

		const_normal_iterator( const node_pointer &node ) : _current_node( node ) {}
		const_normal_iterator( const const_normal_iterator &other ) : _current_node( other._current_node ) {}

		const node_pointer &get_node() const { return _current_node; }

		const_normal_iterator &operator=( const const_normal_iterator &other ) {
            _current_node = other.get_node();
            return *this;
        }
		const_normal_iterator &operator++() {
			_current_node = _current_node->next();
            return *this;
        }
        const_normal_iterator operator++( int ) {
			const_normal_iterator tmp = _current_node;
			_current_node = _current_node->next();
			return tmp;
		}
        const_normal_iterator &operator--() {
            _current_node = _current_node->previous();
            return *this;
        }
        const_normal_iterator operator--( int ) {
            const_normal_iterator tmp = _current_node;
			_current_node = _current_node->previous();
			return tmp;
		}

		const_pointer operator->() {
			return &_current_node->_info;
 		}

		typename const_normal_iterator< const_tree_type >::const_pointer operator->() const {
			return &_current_node->_info;
		}

		const_reference operator*() { return _current_node->_info; }
		typename const_normal_iterator< const_tree_type >::const_reference operator*() const {
			return _current_node->_info;
		}

		template < typename P >
		bool operator==( const const_normal_iterator< P > &other ) const {
			return _current_node == other.get_node();
		}
		template < typename P >
		bool operator!=( const const_normal_iterator< P > &other ) const {
			return !( *this == other );
		}

		template < typename P >
		bool operator==( const normal_iterator< P > &other ) const {
			return _current_node == other.get_node();
		}
		template < typename P >
		bool operator!=( const normal_iterator< P > &other ) const {
			return !( *this == other );
		}

		operator U() const { return const_node_pointer( _current_node ); }

		//operator const_normal_iterator< const_tree_type >() const {
		//	std::cout << "conversion operator" << std::endl;
        //    return const_normal_iterator< const_tree_type >( _current_node );
        //}

	};

public :

	typedef normal_iterator< tree_type >					iterator;
	typedef const_normal_iterator< const_tree_type >		const_iterator;

	//typename map<Key, T, Compare, Allocator>::const_iterator map<Key, T, Compare, Allocator>::normal_iterator<BST<Key, T, Compare, Allocator> >::operator const_iterator() const {
	//	return const_iterator(_current_node);
	//}

    typedef ft::reverse_iterator< iterator >				reverse_iterator;
    //typedef ft::reverse_iterator< const_iterator >		const_reverse_iterator;
	typedef ft::const_reverse_iterator< const_iterator >	const_reverse_iterator;

public:

	typedef Key											key_type;
	typedef T											mapped_type;
	typedef ft::pair<const Key, T>						value_type;
	typedef Compare										key_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer		const_pointer;

	typedef std::ptrdiff_t								difference_type;
	typedef std::size_t									size_type;

	struct value_compare {
        bool operator()( const value_type &a, const value_type &b ) const {
            return key_compare()( a.first, b.first );
        }
    };


private:
	tree_type	_tree;

public:

	/* ------------------------------ Construction ------------------------------ */

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_tree( tree_type(comp, alloc)) {
	}

	template <class InputIterator>
	map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
	const allocator_type& alloc = allocator_type()) : _tree( tree_type(comp, alloc)) {
		insert(first, last);
	}

	/* -------------------------------- Iterators ------------------------------- */

	iterator 				begin() {return _tree.begin();}
	iterator 				end() { return _tree.end();}
	const_iterator 			begin() const {return const_iterator(_tree.begin()); }
	const_iterator 			end() const  { return _tree.end();}
	reverse_iterator 		rbegin() {return iterator(_tree.end());}
	reverse_iterator 		rend() { return iterator(_tree.begin());}
	const_reverse_iterator 	rbegin() const {return iterator(_tree.end());}
	const_reverse_iterator 	rend() const { return iterator(_tree.begin()); }
	const_iterator 			cbegin() const { return _tree.begin(); }
	const_iterator 			cend() const { return _tree.end();}
	const_reverse_iterator 	crbegin() const {return iterator(_tree.end());}
	const_reverse_iterator 	crend() const { return iterator(_tree.begin());}

	/* -------------------------------- Capacity -------------------------------- */

	bool		empty () const {return  _tree.size() == 0;}
	size_type	size () const { return _tree.size();}
	size_type	max_size () const {return _tree.max_size();}

	/* ----------------------------- Element access ----------------------------- */

	mapped_type& operator[] (const key_type& k) {
		return _tree.insert( value_type( k, mapped_type() ) ).first->_info.second;
	}

	mapped_type& at (const key_type& k);
	const mapped_type& at (const key_type& k) const;

	/* -------------------------------- Modifiers ------------------------------- */

	ft::pair<iterator, bool> insert( const value_type &val ) {
		return _tree.insert( val );
    }

	iterator insert( iterator position, const value_type &val ) {
		return _tree.insert( position.get_node(), val ).first;
    }

	template < class InputIterator >
    void insert( InputIterator first, InputIterator last ) {
		while (first != last) {
			insert (*first);
			first++;
		}
    }

	void erase (iterator position) {
		_tree.erase( position.get_node());
	}

	size_type erase (const key_type& k){
		if (_tree.exists(k)) {
			_tree.erase( _tree.find(k)) ;
			return 1;
		}
		return 0;
	}

    void erase (iterator first, iterator last){
		while (first != last) {
			iterator tmp = ++( iterator( first ) );
			_tree.erase( first.get_node());
			first = tmp;
		}
	}

	void printTree()
	{
		_tree.printTreeDiagram();
	}

	void clear() {
		_tree.clear();
	}

	/* -------------------------------- Observers ------------------------------- */

    key_compare   key_comp() const { return key_compare(); }
    value_compare value_comp() const { return value_compare(); }

	/* ------------------------------- Operations ------------------------------- */

	iterator find (const key_type& k) {
		return _tree.find(k);
	}

	const_iterator find (const key_type& k) const {
		return _tree.find(k);
	}

	size_type count (const key_type& k) const {
		return _tree.exists(k);
	}

	iterator lower_bound( const key_type &k ) { return _tree.lower_bound( k ); }
	const_iterator lower_bound( const key_type &k ) const {
		return _tree.lower_bound( k );
	}
	iterator upper_bound( const key_type &k ) { return _tree.upper_bound( k ); }
	const_iterator upper_bound( const key_type &k ) const {
		return _tree.upper_bound( k );
	}

	ft::pair< const_iterator, const_iterator >
	equal_range( const key_type &k ) const {
		return ft::pair< const_iterator, const_iterator >( lower_bound( k ), upper_bound( k ) );
	}
	ft::pair< iterator, iterator > equal_range( const key_type &k ) {
		return ft::pair< iterator, iterator >( lower_bound( k ), upper_bound( k ) );
	}

	/* -------------------------------- Allocator ------------------------------ */

	allocator_type get_allocator() const {
		return _tree.get_allocator();
	}

	void swap (map& x) {
		_tree.swap( x._tree);
	}

	/* -------------------------- Relational operators -------------------------- */

    bool operator==( const map &other ) const { return _tree == other._tree; }
    bool operator!=( const map &other ) const { return _tree != other._tree; }
    bool operator<( const map &other ) const { return _tree < other._tree; }
    bool operator<=( const map &other ) const { return _tree <= other._tree; }
    bool operator>( const map &other ) const { return _tree > other._tree; }
    bool operator>=( const map &other ) const { return _tree >= other._tree; }

	/* -------------------------------- Destructor ------------------------------ */

	~map () {};

private :

	bool _exists (const key_type &k) {
		return _tree.exists(k);
	}


};

	/* ---------------------------------- Swap ---------------------------------- */

template < class Key, class T, class Compare, class Alloc >
void swap( map< Key, T, Compare, Alloc > &x, map< Key, T, Compare, Alloc > &y ) {
	x.swap(y);
}

} //namespace ft


#endif
