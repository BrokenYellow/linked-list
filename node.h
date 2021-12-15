#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>

using namespace std;

template <typename T>
class List;

template <typename T>
class Iterator;

template <typename T>
class Node
{
    friend class Iterator<T>;
    friend class List<T>;
public:
    Node() : data(0), next(nullptr) {}

    ~Node(){
        data = 0;
        next = nullptr;
    }

    Node(const T &d) : data(d), next(nullptr) {}

    Node(const Node<T>& n){
        copy(*this, n);
    }

    Node<T>& operator=(const Node &n){
        copy(*this, n);
    }

    void set_data(const T &data){
        this->data = data;
    }

    void set_next(shared_ptr< Node<T> > next){
        this->next = next;
    }

    T& get_data(){
        return data;
    }

    shared_ptr< Node<T> > get_next(){
        return next;
    }

private:
    T data;
    shared_ptr< Node<T> > next;

    void copy(Node<T> &n, const Node<T> &other){
        n.data = other.data;
        n.next = other.next;
    }
};

#endif // NODE_H
