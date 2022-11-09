/* GNU C++ version 10.2 - "g++ -std=c++17"
 * Benjamin Perraudin - 2021/08 - <Cont.hpp>
 * Exemple de conteneur (projet n°1)
 */
#ifndef _CONT_H_
#define _CONT_H_

#include  "Vect.hpp"
#include  "BST.hpp"
#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <utility>             // swap, move, forward...
#include  <exception>
#include  <stdexcept>           // standard exceptions
#include  <ostream>             // output streams

// Common output operator ====================================================

namespace _Cont_base {
    namespace {
        template <typename U>
        struct _Base {
            void _dsp (std::ostream& out) const
            {static_cast<const U*>(this)->_dsp(out);}
        };
    }
}

template <typename U>
std::ostream& operator<< (std::ostream& out, const _Cont_base::_Base<U>& b)
{b._dsp(out); return out;}

// Abstract base class =======================================================


template <typename T>
class Cont_base { // abstract
public:
    class Info;               // make class Info local
    class Ptr2Info;
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
    Cont_base& operator= (const Cont_base&);

public:
    // Getter
    std::size_t used () const  {return _used;};
    // Constructors & destructor
    Cont_base () : _used (0) {};
    Cont_base (const Cont_base&);
    virtual ~Cont_base ();
};

// Cont_base<T>
template <typename T>
const typename Cont_base<T>::Info Cont_base<T>::_EMPTY;     // Info _EMPTY attribute initialize

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
    //{out << (_ptr ? *_ptr : _EMPTY);}
	{out << (_ptr ? *_ptr : 0);}
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
namespace _Cont_base {
    template <typename> using _Base = void;   // "destroy" access to real _Base
}
*/

// Main class ================================================================

template <typename T>
class Cont : public BST<Info<T> >, public Vect<Ptr2Info<T> >{

public:

    // Constructors
    Cont();                                          // constructor without parameters
    explicit Cont(std::size_t t) : BST<Info<T> >(), Vect<Ptr2Info<T> >(t){}           // constructor with maximum size of Cont

    // Setters
    Ptr2Info<T>& operator[] (std::ptrdiff_t idx)  ;
    const Info<T>& insert(const T &v) ;
    bool erase(const T &v) ;
    // Getters
    const Info<T>& find(const T &v) const ;

    // Copies & transfers
    Cont(const Cont<T> &v) ;
    explicit Cont(const Vect<Ptr2Info<T> > &v) ;
    explicit Cont(const BST<Info<T> > &v) ;
    inline Cont<T>& operator= (const Cont&) ;


    // Output
    void _dsp (std::ostream &out) const  {BST<Info<T> >::_dsp(out);}
    // note : ne fonctionne pas pour un type déclaré Vect, problème : celui ci n'a pas de BST rempli et donc ne peut pas utiliser l'opérateur d'output de celui-ci
    // détecter le type déclaré (est-ce possible?) reviendrait à briser le principe de Substitution de Liskov...
    // Destructor
    ~Cont () {};
    // Associated function
    template <typename U>
    friend inline std::ostream& operator<< (std::ostream&, const Cont<U>&);
};

// Constructors ============================================================


// Setters =================================================================

template<typename T>
Ptr2Info<T>& Cont<T>::operator[](std::ptrdiff_t idx) {
    if (Vect<Ptr2Info<T> >::operator[](idx).isEmpty()){          // value are constant in Cont context, no change allowed for element
        return Vect<Ptr2Info<T> >::operator[](idx);
    }
    else throw std::domain_error("can't assign new value in a constant vect");
}

template<typename T>
const Info<T>& Cont<T>::insert(const T& v) {      // [-Wreturn-type] warning because no explicit return, prevents using insert two times
    std::ptrdiff_t idx = 2;
    if (idx == -1){                 // implicit conversion to Info with default index -1
        throw std::domain_error("no index specified");
    }
    if (std::size_t(idx) <= Vect<Ptr2Info<T> >::dim()){
        if(!BST<Info<T> >::exists(T(v))){                                // cast to T to find element without taking into account the index
            if (!Vect<Ptr2Info<T> >::operator[](idx).isEmpty()) {            // check if index is occupied, if yes erase it from the BST
                BST<Info<T> >::erase(Vect<Ptr2Info<T> >::operator[](idx));            // delete old Node at same position to update
            }
			const Info<T>& elem = BST<Info<T> >::insert(v);
            //Ptr2Info<T>::getPtr(Vect<Ptr2Info<T> >::operator[](idx)) = &BST<Info<T> >::insert(v);    // Vect[i] points to correct Node of BST
			Ptr2Info<T>::getPtr(Vect<Ptr2Info<T> >::operator[](idx)) = &elem;    // Vect[i] points to correct Node of BST
			return elem;
        }
        else{
            throw std::domain_error("element already in Container");
        }
    }
    else{
        throw std::out_of_range("index out of range");
    }
}

template<typename T>
bool Cont<T>::erase(const T &v) {
    std::ptrdiff_t idx = Cont_base<T>::_index(v);
    if (idx == -1){         // either no index specified but v in BST, or v not in BST
        if(BST<Info<T> >::erase(v)){
            Ptr2Info<T>::getPtr(Vect<Ptr2Info<T> >::operator[](Cont_base<T>::_index(BST<Info<T> >::find(v)))) = 0;  // delete pointer if v exist in BST
            return true;
        }
        else return false;
    }
    else {
        if(!(Vect<Ptr2Info<T> >::operator[](idx).isEmpty())){
            if(*Ptr2Info<T>::getPtr(Vect<Ptr2Info<T> >::operator[](idx)) == v){       // if index and value are the same
                Vect<Ptr2Info<T> >::operator[](idx) = Ptr2Info<T>() ;           // erase pointeur of Vect
                if(BST<Info<T> >::erase(v)){
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
const Info<T>& Cont<T>::find(const T &v) const {
    std::ptrdiff_t idx = Cont_base<T>::_index(v);
    if (idx == -1){
        return BST<Info<T> >::find(v);
    }
    else{
        if(!(Vect<Ptr2Info<T> >::operator[](idx).isEmpty())){
            if(*Cont_base<T>::_ptr(Vect<Ptr2Info<T> >::operator[](idx)) == v){    // if index and value are the same
                return BST<Info<T> >::find(v);
            }
            else return BST<Info<T> >::_NOT_FOUND;
        }
        else return BST<Info<T> >::_NOT_FOUND;  // no exception threw here because base virtual method is noexcept
    }
}

// Copies & transfers ========================================================

template<typename T>
Cont<T>::Cont (const Cont<T> &v) : BST<Info<T> >(), Vect<Ptr2Info<T> >(v.dim()){   // Cont_base<T> prevents warning
    for (std::ptrdiff_t i = 0; i < v.dim(); ++i){   // warning comparaison between std::ptrdiff_t='long int' from std::size_t='long unsigned int' is acceptable because i start at 0 (same for further into code)
        //if (!v.at(i).isEmpty()) Cont::insert({i,*Cont_base<T>::_ptr(v.at(i))});     // fill the BST
    }
}

// Associated function =======================================================

template<typename U>
inline std::ostream &operator<<(std::ostream &out, const Cont<U> &c){
    out << "[ "; c._dsp(out); out << ']'; return out;}


template<typename T>
Cont<T>& Cont<T>::operator=(const Cont &v)  {
    if (this != &v){
        Cont_base<T>::operator=(v);                 // explicit call to copy assignement operator of Cont_Base for _used
        BST<Info<T> >::operator=(v) ;                        // explicit call to copy assignement operator of BST
        Vect<Ptr2Info<T> >::operator=(v) ;                       // explicit call to copy assignement operator of Vect
    }
    return *this;
}

#endif // _CONT_H_
