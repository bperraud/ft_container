/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bperraud <bperraud@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:11:31 by bperraud          #+#    #+#             */
/*   Updated: 2022/11/07 01:06:32 by bperraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _BST_H_
#define _BST_H_

#include  <cstddef>             // nullptr_t, size_t, ptrdiff_t, byte...
#include  <ostream>             // output streams

template <typename T>
class BST {
private:
    // Implementation
    struct _Node;
    _Node *_root;
    // Utilities
    inline _Node*& _findNode (const T&) ;   // ready for insert or erase
    inline _Node*& _nextLeaf (const T&) ;   // always null (for insert)
    static inline _Node* _erase (_Node*&) ; // ready for delete
    static _Node* _cp (const _Node* r)      // recursive
    {return r ? new _Node(*r) : 0;}
protected:
    static const T _NOT_FOUND;                      // "not found" element
    virtual void _dsp (std::ostream&) const;        // recursive
public:
    // Constructors
    BST ();            // empty tree
    // Getters
    static bool isNotFound (const T& v) {return &v == &_NOT_FOUND;}
    bool isEmpty () const  {return !_root;}
    virtual const T& find (const T&) const ;
    bool exists (const T& v) const {return !isNotFound(find(v));}
    // Setters
    virtual const T& insert (const T& v) {return (_nextLeaf(v) = new _Node(v))->info;} 			 // always add
    virtual bool erase (const T& v) {_Node *res = _erase(_findNode(v)); delete res; return res;} // false if doesn't exist
    // Copies & transfers
    BST (const BST& t) : _root(_cp(t._root)) {}
    virtual BST& operator= (const BST&);
    // Destructor
    virtual ~BST () {delete _root;}  // recursive
    // Associated function
    template <typename U>
    friend inline std::ostream& operator<< (std::ostream&, const BST<U>&);
}; // BST<T>

template <typename T>
const T BST<T>::_NOT_FOUND = 0;

// Embedded class _Node ======================================================

template <typename T>
struct BST<T>::_Node {
    const T info;
    //BST left{}, right{};
	BST left, right;
    explicit _Node (const T& v) : info(v) {}
};

//Constructor
template <typename T>
BST<T>::BST() : _root(0) {

}

// Getters ===================================================================


template <typename T>
void BST<T>::_dsp (std::ostream& out) const {
    if (_root) {
        out << '('; _root->left._dsp(out);
        out << _root->info;
        _root->right._dsp(out); out << ')';
    }
}

template <typename T>
const T& BST<T>::find (const T& v) const {
    const _Node *const res = const_cast<BST*>(this)->_findNode(v);
    return res ? res->info : _NOT_FOUND;
}

// Setters ===================================================================

template <typename T>
typename BST<T>::_Node*& BST<T>::_findNode (const T& v) {
    _Node **res = &_root;
    while (*res)
	{
		if (v == (*res)->info)
			break;
		else
			res = v < (*res)->info ? &(*res)->left._root : &(*res)->right._root;
	}
	return *res; // pointer to place where v is or should be
}

template <typename T>
typename BST<T>::_Node*& BST<T>::_nextLeaf (const T& v) {
    _Node **res = &_root;
    while (*res)
        res = v < (*res)->info ? &(*res)->left._root : &(*res)->right._root;
    return *res;
}

template <typename T>
typename BST<T>::_Node* BST<T>::_erase (_Node*& target) {
    _Node *const res = target; // saved
    if (target) {
        _Node *subst = target->right._root;
        if (subst) {
            _Node *father = 0;
            while (subst->left._root) {father = subst; subst = subst->left._root;}
            if (father) {
                father->left._root = subst->right._root;
                subst->right._root = target->right._root;
            }
            subst->left._root  = target->left._root;
        } else subst = target->left._root;
        target->left._root = 0; target->right._root = 0;
        target = subst;
    }
    return res;   // old isolated _Node (not yet deleted)
}

// Copies & transfers ========================================================

template <typename T>
BST<T>& BST<T>::operator= (const BST& t) {
    if (this != &t) {delete _root; _root = _cp(t._root);}
    return *this;
}

// Associated function =======================================================

template <typename T>
inline std::ostream& operator<< (std::ostream& out, const BST<T>& t)
{out << "[ "; t._dsp(out); out << ']'; return out;}

#endif // _BST_H_
