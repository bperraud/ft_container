/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vect.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:24:23 by bperraud          #+#    #+#             */
/*   Updated: 2022/11/28 18:15:10 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VECT_H_
#define _VECT_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <ostream>             // output streams

template <typename T>
class Vect {
protected:
    std::size_t _size;
    T *_data;
    inline static T* _cp (const Vect&);
protected:
    //virtual void _dsp (std::ostream& out) const {out << *_data ;} ;
public:

	T* cp (T *alloc);


	//T* cp_and_move (T *alloc, std::ptrdiff_t start, std::size_t range, const &T val) {
	T* cp_and_move (T *alloc, std::ptrdiff_t start, std::size_t range, T val) {
		for (unsigned int i = 0; i < start; ++i) alloc[i] = _data[i];			// copy until start
		for (unsigned int u = start; u < start + range; ++u) {
			alloc[u] = val;	// insert new val
			_size += 1;
		}
		for (std::size_t n = start + range; n < _size + range; ++n)				// decallage du reste
		{
			alloc[n] = _data[n - range];
		}
		return _data;
	}

	T* cp_and_move (T *alloc, std::ptrdiff_t start, std::size_t range, T* val) {
		for (unsigned int i = 0; i < start; ++i) alloc[i] = _data[i];			// copy until start
		for (unsigned int u = start; u < start + range; ++u) {
			alloc[u] = val[u];	// insert new val
			_size += 1;
		}
		for (std::size_t n = start + range; n < _size + range; ++n)				// decallage du reste
		{
			alloc[n] = _data[n - range];
		}
		return _data;
	}

	void move_back (std::ptrdiff_t start, std::size_t range) {
		std::cout << "start : " << start << std::endl;
		std::cout << "range : " << range << std::endl;
		//for (std::size_t n = start; n < start + range; ++n){
		for (std::size_t n = start; n < start + _size ; ++n){
			_data[n] = _data[n + range];
		}
		_size -= range;
	}


	void	fill(std::ptrdiff_t, std::size_t n, T val);
    // Constructors
    Vect ();   // Tableau vide
    explicit Vect (std::size_t d) : _size(d), _data(0) {}
    // Getters
    std::size_t dim () const {return _size;}
	T* getData() { return _data;}
	T* getData() const { return _data;}
	//const T* getData() const { return _data;}
    const T& operator[] (std::ptrdiff_t) const;
	T* getLast() const { return _data + _size - 1;}
	inline T& at(std::ptrdiff_t) ;
    inline const T& at(std::ptrdiff_t) const;
    // Setters
    virtual T& operator[] (std::ptrdiff_t);
	void setVal(T *alloc) {_data = alloc;};
	void setDim(std::size_t d) {_size = d;};
    // Copies & transfers
    Vect (const Vect& v) : _size(v._size), _data(_cp(v)) {}
    inline Vect& operator= (const Vect&);
    // Destructor
    //virtual ~Vect ()  {delete[] _data;}
    // Associated function
    template <typename U>
    friend inline std::ostream& operator<< (std::ostream&, const Vect<U>&);
}; // Vect<T>

// Constructors ============================================================

template <typename T>
Vect<T>::Vect () : _size(0), _data(0) {

}

// Getters ===================================================================

template <typename T>
const T& Vect<T>::operator[] (std::ptrdiff_t idx) const {
    return _data[idx];
}

template<typename T>
const T &Vect<T>::at(std::ptrdiff_t idx) const {
	std::cout << "at" << std::endl;
    if (std::size_t(idx) >= _size)
        throw std::domain_error("Vect::at(i): index out of range");
    return _data[idx];
}

template<typename T>
T &Vect<T>::at(std::ptrdiff_t idx) {
    if (std::size_t(idx) >= _size)
        throw std::domain_error("Vect::at(i): index out of range");
    return _data[idx];
}

// Setters ===================================================================

template <typename T>
T& Vect<T>::operator[] (std::ptrdiff_t idx) {
    if (std::size_t(idx) >= _size)
		throw std::domain_error("Vect::op[]: index out of range");
    return _data[idx];
}

// Copies & transfers ========================================================


// utile ?
template <typename T>
T* Vect<T>::_cp (const Vect<T>& v) {
	T *res = new T[v._size];
    for (std::size_t i = 0; i < v._size; ++i) res[i] = v._data[i];
    return res;
}

template <typename T>
T* Vect<T>::cp (T *alloc) {
    for (unsigned int i = 0; i < _size; ++i) alloc[i] = _data[i];
    return _data;
}

template <typename T>
void Vect<T>::fill(std::ptrdiff_t pos, std::size_t n, T val) {
	for (std::size_t i = pos; i < n; ++i)
		_data[i] = val;
}

template <typename T>
Vect<T>& Vect<T>::operator= (const Vect& v) {
    if (this != &v) {delete[] _data; _size = v._size; _data = _cp(v);}
    return *this;
}

// Associated functions =========================================================

template <typename T>
inline std::ostream& operator<< (std::ostream& out, const Vect<T>& v)
{
	out << "vect output ";
	out << "[ "; v._dsp(out); out << ']'; return out;
}


#endif // _VECT_H_
