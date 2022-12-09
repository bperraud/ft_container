/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:51:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/09 01:38:52 by bperraud         ###   ########.fr       */
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


	typedef Vect<Ptr2Info<T> >	_Vect;
	typedef Ptr2Info<T> 		_Ptr2Info;
	typedef BST<Info<T>	>		_BST;
	typedef Info<T> 			_Info;

private:

public:

	// Constructors
	map();										// constructor without parameters
	explicit map(std::size_t t) : {}			// constructor with maximum size of map

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
