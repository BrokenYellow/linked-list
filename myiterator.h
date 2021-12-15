#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>
#include <iostream>
#include <memory>
#include "node.h"
#include "errors.h"

using namespace std;

template <typename T>
class Iterator: public iterator<input_iterator_tag, T>
{
    friend class List<T>;
public:
    Iterator() {}
    Iterator(const shared_ptr< Node<T> > node): node(node) {}
    Iterator(const Iterator &it){
        node = it.node;
    }

    bool operator!=(const Iterator<T> &other) const{
        return node.lock() != other.node.lock();
    }

    bool operator==(const Iterator<T> &other) const{
        return node.lock() == other.node.lock();
    }

    const T& operator*() const{
        return this->get_data();
    }

    T& operator*(){
        return this->get_data();
    }

    const T* operator->() const{
        return &(this->get_data());
    }

    T* operator->(){
        return &(this->get_data());
    }

    Iterator<T>& operator++(){
        shared_ptr< Node<T> > n = node.lock();
        if (!n)
            throw(IteratorError());
        node = n->next;
        return *this;
    }

    Iterator<T> operator++(int){ // x++
        Iterator<T> it(*this);
        ++(*this);
        return it;
    }

    operator bool() const{
        return (node.lock() != nullptr);
    }

    Iterator<T>& operator=(const Iterator<T> &it){
        if (*this != it){
            node = it.node;
        }
        return *this;
    }

private:
    weak_ptr< Node<T> > node;

    T& get_data() const{
        if (!node.expired())
            throw(IteratorError());

        shared_ptr< Node<T> > n(node);
        return n->get_data();
    }
};

////// Const Iterator ///////////////////////////////////////////

template <typename T>
class Const_Iterator: public iterator<input_iterator_tag, T>
{
    friend class List<T>;
public:
    Const_Iterator() {}
    Const_Iterator(const shared_ptr< Node<T> > node): node(node) {}
    Const_Iterator(const Const_Iterator &it){
        node = it.node;
    }

    bool operator!=(const Const_Iterator<T> &other) const{
        return node.lock() != other.node.lock();
    }

    bool operator==(const Const_Iterator<T> &other) const{
        return node.lock() == other.node.lock();
    }

    const T& operator*() const{
        return this->get_data();
    }

    const T* operator->() const{
        return &(this->get_data());
    }

    Const_Iterator<T>& operator++(){
        shared_ptr< Node<T> > n = node.lock();
        if (!n)
            throw(IteratorError());
        node = n->next;
        return *this;
    }

    Const_Iterator<T> operator++(int){ // x++
        Const_Iterator<T> it(*this);
        ++(*this);
        return it;
    }

    operator bool() const{
        return (node.lock() != nullptr);
    }

    Const_Iterator<T>& operator=(const Const_Iterator<T> &it){
        if (*this != it){
            node = it.node;
        }
        return *this;
    }

private:
    weak_ptr< Node<T> > node;

    T& get_data() const{
        shared_ptr< Node<T> > n(node);
        if (!n)
            throw(IteratorError());
        return n->get_data();
    }
};

#endif // ITERATOR_H
