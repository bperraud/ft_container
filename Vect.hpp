/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:24:23 by bperraud          #+#    #+#             */
/*   Updated: 2022/11/22 13:42:58 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECT_H_
#define _VECT_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <ostream>             // output streams

template <typename T, typename Allocator = std::allocator<T> >
class Vect {
protected:
    std::size_t _size;
    T *_val;
	Allocator	_alloc;
    inline static T* _cp (const Vect&);
protected:
    //virtual void _dsp (std::ostream& out) const {out << *_val ;} ;
public:
    // Constructors
    Vect ();   // Tableau vide
    explicit Vect (std::size_t d) : _size(d), _val(new T[d]) {}
	explicit Vect (std::size_t d, Allocator alloc) : _size(d), _val(alloc.allocate(d)) {}


    // Getters
    std::size_t dim () const {return _size;}
    const T& operator[] (std::ptrdiff_t) const;
    inline const T& at(std::ptrdiff_t) const;
    // Setters
    virtual T& operator[] (std::ptrdiff_t);
    // Copies & transfers
    Vect (const Vect& v) : _size(v._size), _val(_cp(v)) {}
    inline Vect& operator= (const Vect&);
    // Destructor
    virtual ~Vect ()  {delete[] _val;}
    // Associated function
    template <typename U, typename A>
    friend inline std::ostream& operator<< (std::ostream&, const Vect<U, A>&);
}; // Vect<T>

// Constructors ============================================================

template <typename T, typename Allocator>
Vect<T, Allocator>::Vect () : _size(0), _val(0) {

}

// Getters ===================================================================

template <typename T, typename Allocator>
const T& Vect<T, Allocator>::operator[] (std::ptrdiff_t idx) const {
    return _val[idx];
}

template <typename T, typename Allocator>
const T &Vect<T, Allocator>::at(std::ptrdiff_t idx) const {
    if (std::size_t(idx) >= _size)
        throw std::domain_error("Vect::at(i): index out of range");
    return _val[idx];
}

// Setters ===================================================================

template <typename T, typename Allocator>
T& Vect<T, Allocator>::operator[] (std::ptrdiff_t idx) {
    if (std::size_t(idx) >= _size)
		throw std::domain_error("Vect::op[]: index out of range");
    return _val[idx];
}

// Copies & transfers ========================================================

template <typename T, typename Allocator>
T* Vect<T, Allocator>::_cp (const Vect<T, Allocator>& v) {
    T *res = new T[v._size];
    for (std::size_t i = 0; i < v._size; ++i) res[i] = v._val[i];
    return res;
}

template <typename T, typename Allocator>
Vect<T, Allocator>& Vect<T, Allocator>::operator= (const Vect& v) {
    if (this != &v) {delete[] _val; _size = v._size; _val = _cp(v);}
    return *this;
}

// Associated functions =========================================================

template <typename T, typename Allocator>
inline std::ostream& operator<< (std::ostream& out, const Vect<T, Allocator>& v)
{
	out << "vect output ";
	out << "[ "; v._dsp(out); out << ']'; return out;
}


#endif // _VECT_H_





