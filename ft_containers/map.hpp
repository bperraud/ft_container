/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:51:50 by bperraud          #+#    #+#             */
/*   Updated: 2022/12/03 15:28:22 by bperraud         ###   ########.fr       */
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


template <typename T>
class map : public BST<Info<T> >, public Vect<Ptr2Info<T> >{


public:
	//Iterator	const_iterator;

public:

	typedef Vect<Ptr2Info<T> >	_Vect;
	typedef Ptr2Info<T> 		_Ptr2Info;
	typedef BST<Info<T>	>		_BST;
	typedef Info<T> 			_Info;


    // Constructors
    map();                                          // constructor without parameters
    explicit map(std::size_t t) : _BST(), _Vect(t){}           // constructor with maximum size of map

    // Setters
    _Ptr2Info& operator[] (std::ptrdiff_t idx)  ;
    const _Info& insert(const T &v) ;
    bool erase(const T &v) ;
    // Getters
    const _Info& find(const T &v) const ;

    // Copies & transfers
    map(const map<T> &v) ;
    explicit map(const _Vect &v) ;
    explicit map(const _BST &v) ;
    inline map<T>& operator= (const map&) ;


    // Output
    void _dsp (std::ostream &out) const  {_BST::_dsp(out);}
    // note : ne fonctionne pas pour un type déclaré _Vect, problème : celui ci n'a pas de _BST rempli et donc ne peut pas utiliser l'opérateur d'output de celui-ci
    // détecter le type déclaré (est-ce possible?) reviendrait à briser le principe de Su_BSTitution de Liskov...
    // Destructor
    ~map () {};
    // Associated function
    template <typename U>
    friend inline std::ostream& operator<< (std::ostream&, const map<U>&);
};

// Constructors ============================================================


// Setters =================================================================

template<typename T>
Ptr2Info<T>& map<T>::operator[](std::ptrdiff_t idx) {
    if (_Vect::operator[](idx).isEmpty()){          // value are constant in map mapext, no change allowed for element
        return _Vect::operator[](idx);
    }
    else throw std::domain_error("can't assign new value in a constant _Vect");
}

template<typename T>
const Info<T>& map<T>::insert(const T& v) {      // [-Wreturn-type] warning because no explicit return, prevents using insert two times
    std::ptrdiff_t idx = 0;
    if (idx == -1){                 // implicit conversion to _Info with default index -1
        throw std::domain_error("no index specified");
    }
    if (std::size_t(idx) <= _Vect::dim()){
        if(!_BST::exists(T(v))){                                // cast to T to find element without taking into account the index
            if (!_Vect::operator[](idx).isEmpty()) {            // check if index is occupied, if yes erase it from the _BST
                _BST::erase(_Vect::operator[](idx));            // delete old Node at same position to update
            }
			const _Info& elem = _BST::insert(v);
            //_Ptr2Info<T>::getPtr(_Vect::operator[](idx)) = &_BST<_Info<T> >::insert(v);    // _Vect[i] points to correct Node of _BST
			_Ptr2Info::getPtr(_Vect::operator[](idx)) = &elem;    // _Vect[i] points to correct Node of _BST
			return elem;
        }
        else{
            throw std::domain_error("element already in mapainer");
        }
    }
    else{
        throw std::out_of_range("index out of range");
    }
}

template<typename T>
bool map<T>::erase(const T &v) {
    std::ptrdiff_t idx = map_base<T>::_index(v);
    if (idx == -1){         // either no index specified but v in _BST, or v not in _BST
        if(_BST::erase(v)){
            _Ptr2Info::getPtr(_Vect::operator[](map_base<T>::_index(_BST::find(v)))) = 0;  // delete pointer if v exist in _BST
            return true;
        }
        else return false;
    }
    else {
        if(!(_Vect::operator[](idx).isEmpty())){
            if(*_Ptr2Info::getPtr(_Vect::operator[](idx)) == v){       // if index and value are the same
                _Vect::operator[](idx) = _Ptr2Info() ;           // erase pointeur of _Vect
                if(_BST::erase(v)){
                    return true;
                }
                else return false;
            }
        }
        else{
            throw std::domain_error("element not found at this position");
        }
    }
}

// Getters ===================================================================

template<typename T>
const Info<T>& map<T>::find(const T &v) const {
    std::ptrdiff_t idx = map_base<T>::_index(v);
    if (idx == -1){
        return _BST::find(v);
    }
    else{
        if(!(_Vect::operator[](idx).isEmpty())){
            if(*map_base<T>::_ptr(_Vect::operator[](idx)) == v){    // if index and value are the same
                return _BST::find(v);
            }
            else return _BST::_NOT_FOUND;
        }
        else return _BST::_NOT_FOUND;  // no exception threw here because base virtual method is noexcept
    }
}

// Copies & transfers ========================================================

template<typename T>
map<T>::map (const map<T> &v) : _BST(), _Vect(v.dim()){   // map_base<T> prevents warning
    for (std::ptrdiff_t i = 0; i < v.dim(); ++i){   // warning comparaison between std::ptrdiff_t='long int' from std::size_t='long unsigned int' is acceptable because i start at 0 (same for further into code)
        //if (!v.at(i).isEmpty()) map::insert({i,*map_base<T>::_ptr(v.at(i))});     // fill the _BST
    }
}

// Associated function =======================================================

template<typename U>
inline std::ostream &operator<<(std::ostream &out, const map<U> &c){
	out << "mapainer output ";
    out << "[ "; c._dsp(out); out << ']'; return out;
}


template<typename T>
map<T>& map<T>::operator=(const map &v)  {
    if (this != &v){
        map::operator=(v);                 // explicit call to copy assignement operator of map_Base for _used
        _BST::operator=(v) ;                        // explicit call to copy assignement operator of _BST
        _Vect::operator=(v) ;                       // explicit call to copy assignement operator of _Vect
    }
    return *this;
}

#endif
