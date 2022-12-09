/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:51:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/09 15:34:39 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef map_H
#define map_H

#include  "Vect.hpp"
#include  "BST.hpp"
#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <utility>             // swap, move, forward...
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <ostream>             // output streams

// Common output operator ====================================================

namespace _map_base {
    namespace {
        template <typename U>
        struct _Base {
            void _dsp (std::ostream& out) const
            {static_cast<const U*>(this)->_dsp(out);}
        };
    }
}

template <typename U>
std::ostream& operator<< (std::ostream& out, const _map_base::_Base<U>& b)
{b._dsp(out); return out;}

// A_BSTract base class =======================================================


template <typename T>
class map_base { // a_BSTract
public:
    class Info;               // make class Info local
    class Ptr2_Info;
protected:
    static const Info _EMPTY;
    // Access methods
	/*
    static std::ptrdiff_t _index (const Info& i) {return i._index;}
    static std::ptrdiff_t& _index (Info& i) {return i._index;}
    static const Info* _ptr (const Ptr2Info& p) {return p._ptr;}
    static const Info*& _ptr (Ptr2Info& p) {return p._ptr;}
	*/
    // Implementation
    std::size_t _used;
    virtual void _dsp (std::ostream&) const = 0;
    // Non virtual assignations => protected
    map_base& operator= (const map_base&);

public:
    // Getter
    std::size_t used () const  {return _used;};
    // Constructors & destructor
    map_base () : _used (0) {};
    map_base (const map_base&);
    virtual ~map_base ();
};

// map_base<T>
template <typename T>
const typename map_base<T>::Info map_base<T>::_EMPTY;     // Info _EMPTY attribute initialize

// Embedded class Info =======================================================

template <typename T>
class Info  {
    std::ptrdiff_t _index;
    const T _data;
    void _dsp (std::ostream& out) const {out << _data;}
public:

	// Static method
	//static std::ptrdiff_t _index (const Info& i) {return i._index;}
    //static std::ptrdiff_t& _index (Info& i) {return i._index;}

    // Constructors & casts
    Info () : _index(-1), _data (0) {};
    Info (std::ptrdiff_t i, const T& v) : _index(i), _data(v) {};
    Info (const T& v) : _data(v) {} ;            	 // implicit cast
    operator const T& () const  {return _data;} 	 // implicit cast
    template <typename> friend bool operator< (const Info&, const Info&) ;
    template <typename> friend bool operator== (const Info&, const Info&) ;
    bool operator< (const Info& i) const
    {return _data < i._data;}
    bool operator== (const Info& i) const
    {return _data == i._data;}
}; // Info

// Embedded class Ptr2Info ===================================================

template <typename T>
class Ptr2Info {
    const Info<T> *_ptr;

    void _dsp (std::ostream& out) const
	{out << (_ptr ? *_ptr : 0);}
    //{out << (_ptr ? *_ptr : _EMPTY);}
public:
	// Static methods
	static const Info<T>* getPtr (const Ptr2Info& p) {return p._ptr;}
    static const Info<T>*& getPtr (Ptr2Info& p) {return p._ptr;}

    // Constructors & casts
	Ptr2Info () : _ptr (0) {};
    Ptr2Info(T i) : _ptr(new Info<T>(i))  {};       // implicit cast from T to Ptr2Info
	operator const Info<T>& () const {return *_ptr;}        // implicit cast
	//{return _ptr ? *_ptr : _EMPTY;}
    operator const T& () const {return *_ptr;}        // implicit cast from const T& to const *Info
    //{return _ptr ? *_ptr : _EMPTY;}
    // Getter
    bool isEmpty() const  {return !_ptr;}
    bool operator< (const Ptr2Info& i) const
    {return _ptr->_data < i._ptr->_data;}
    bool operator== (const Ptr2Info& i) const
    {return _ptr->_data == i._ptr->_data;}
}; // Ptr2Info

/*
namespace _map_base {
    template <typename> using _Base = void;   // "destroy" access to real _Base
}
*/

// Main class ================================================================


#include "Iterator.hpp"


template<
    class Key,														// map::key_type
    class T,														// map::mapped_type
    class Compare = std::less<Key>,									// map::key_compare
    class Allocator = std::allocator<std::pair<const Key, T> > >	// map::allocator_type
class map {
//class map : public BST<Info<T> >, public Vect<Ptr2Info<T> >{

	// iterator class
    template <typename U>
	class normal_iterator {
    public:
        typedef typename U::value_type        value_type;
        typedef typename U::reference         reference;
        typedef typename U::pointer           pointer;
        typedef typename U::difference_type   difference_type;
        typedef typename U::iterator_category iterator_category;

    private:
        U _it;

    public:
        normal_iterator() : _it( U() ) {}
        normal_iterator( const normal_iterator &other ) : _it( other._it ) {}
        normal_iterator( const U &other ) : _it( other ) {}
        normal_iterator &operator=( const normal_iterator &other ) {
            _it = other._it;
            return *this;
        }

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
        typename normal_iterator< tree_const_iterator >::reference operator*() const {
            return *_it;
        }

        pointer operator->() { return _it.operator->(); }
        typename normal_iterator< tree_const_iterator >::pointer operator->() const {
            return _it.operator->();
        }

        template < typename V >
        bool operator==( const normal_iterator< V > &other ) const {
            return U( *this ) == V( other );
        }
        bool operator==( const U &other ) const { return T( *this ) == other; }

        template < typename V >
        bool operator!=( const normal_iterator< V > &other ) const {
            return !( *this == other );
        }
        bool operator!=( const U &other ) const { return !( *this == other ); }

        //operator U() const { return U( _it ); }

        operator normal_iterator< tree_const_iterator >() const {
            return normal_iterator< tree_const_iterator >( _it );
        }
    };

    typedef normal_iterator< tree_iterator >              iterator;
    typedef normal_iterator< tree_const_iterator >        const_iterator;
    typedef ft::reverse_iterator< iterator >       reverse_iterator;
    typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;


public:

	// types:
	typedef Key											key_type;
	typedef T											mapped_type;
	typedef std::pair<const Key, T>						value_type;
	typedef Compare										key_compare;
	typedef Allocator									allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef	typename allocator_type::pointer			pointer;
	typedef	typename allocator_type::const_pointer		const_pointer;

	typedef std::ptrdiff_t							difference_type;
	typedef std::size_t								size_type;


	//typedef Vect<typename Allocator::value_type>	vector_type;


	typedef Vect<Ptr2Info<T> >	_Vect;
	typedef Ptr2Info<T> 		_Ptr2Info;
	typedef BST<Info<T>	>		_BST;
	typedef Info<T> 			_Info;



private:
	allocator_type		_alloc;
	size_type			_capacity;
	_Vect				_vector;

public:

	/* ------------------------------ Construction ------------------------------ */

	map();										// constructor without parameters
	explicit map(std::size_t t) {};			// constructor with maximum size of map

	/* ----------------------------- Element access ----------------------------- */

	mapped_type& operator[] (const key_type& k);

	mapped_type& at (const key_type& k);
	const mapped_type& at (const key_type& k) const;

	/* -------------------------------- Capacity -------------------------------- */

	bool		empty () const {return _vector._size == 0;}
	size_type	size () const { return _vector._size;}
	size_type	max_size () const {return _alloc.max_size();}


	// Setters
	_Ptr2Info& operator[] (std::ptrdiff_t idx)  ;
	const _Info& insert(const T &v) ;
	bool erase(const T &v) ;
	// Getters
	const _Info& find(const T &v) const ;

	// Copies & transfers

	~map () {};
};



#endif
