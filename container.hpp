/*
#include <iostream>
#include "container.h"
#include "errors.h"

using namespace std;

template <typename T>
List<T>::List()
{
    head = nullptr;
    count = 0;
}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
List<T>::List(size_t len, const T *arr)
{
    head = nullptr;
    count = 0;
    for (size_t i = 0; i < len; i++){
        push_back(arr[i]);
    }
}

template <typename T>
List<T>::List(const initializer_list<T> &list)
{
    head = nullptr;
    count = 0;
    for (const auto &elem : list){
        push_back(elem);
    }
}

template <typename T>
List<T>::List(const List<T> &list)
{
    copy(*this, list);
}

template <typename T>
void List<T>::pop_front()
{
    del(0);
}

template <typename T>
void List<T>::pop_back()
{
    del(count - 1);
}

template <typename T>
void List<T>::push_front(const T &data)
{
    insert(0, data);
}

template <typename T>
void List<T>::push_back(const T &data)
{
    insert(count, data);
}

template <typename T>
Iterator<T> List<T>::begin() const
{
    return Iterator<T>(head);
}

template <typename T>
Iterator<T> List<T>::end() const
{
    return Iterator<T>(nullptr);
}

template <typename T>
void List<T>::push_elems_back(const List<T> &list)
{
    merge(*this, list);
}

template <typename T>
void List<T>::push_elems_front(const List<T> &list)
{
    for (Iterator<T> it = list.begin(); it != list.end(); it++){
        push_front(*it);
    }
}

template <typename T>
void List<T>::push_elems_back(const initializer_list<T> &list)
{
    for (auto &elem : list){
        push_back(elem);
    }
}

template <typename T>
void List<T>::push_elems_front(const initializer_list<T> &list)
{
    for (auto &elem : list){
        push_front(elem);
    }
}

template <typename T>
T& List<T>::get_elem(size_t index) const
{
    if (index < 0 || index >= count)
        throw(RangeError());

    Iterator<T> it;
    for (it = begin(); index != 0; it++, index--);
    return (*it);
}

template <typename T>
void List<T>::set_elem(size_t index, const T &data)
{
    if (index < 0 || index >= count)
        throw(RangeError());

    Iterator<T> it;
    for (it = begin(); index != 0; it++, index--);
    *it = data;
}

template <typename T>
List<T>& List<T>::operator=(const List<T> &list)
{
    clear();
    for (Iterator<T> it = list.begin(); it != list.end(); it++){
        push_back(*it);
    }
    return (*this);
}

template <typename T>
List<T> List<T>::operator+(const List<T> &list)
{
    List<T> newlist(*this);
    merge(newlist, list);
    return newlist;
}

template <typename T>
List<T>& List<T>::operator+=(const List<T> &list)
{
    merge(*this, list);
    return (*this);
}

template <typename T>
List<T> List<T>::operator+(const T &data)
{
    List<T> newlist(*this);
    newlist.push_back(data);
    return newlist;
}

template <typename T>
List<T>& List<T>::operator+=(const T &data)
{
    this->push_back(data);
    return (*this);
}

template <typename T>
bool List<T>::operator==(const List<T> &list) const
{
    return equal(list);
}

template <typename T>
bool List<T>::operator!=(const List<T> &list) const
{
    return !equal(list);
}

template <typename T>
void List<T>::del(size_t i)
{
    if (empty())
        throw(EmptyError());
    if (i < 0 || i >= count)
        throw(RangeError());

    --count;
    if (i == 0){
        head = head->next;
        return;
    }
    Iterator<T> it;
    for (it = begin(); i > 1; i--, it++);
    shared_ptr< Node<T> > n = it.node.lock();
    n->next = n->next->next;
}

template <typename T>
void List<T>::insert(size_t i, const T &data)
{
    if (i < 0 || i > count)
        throw(RangeError());

    auto n = make_shared< Node<T> >(data);
    if (!n)
        throw(MemoryError());

    ++count;
    if (i == 0){
        n->set_next(head);
        head = n;
        return;
    }

    Iterator<T> it;
    for (it = begin(); i > 1; it++, i--);
    Iterator<T> it_prev = it++;
    n->set_next(it.node.lock());
    it_prev.node.lock()->set_next(n);
    return;
}

template <typename T>
void List<T>::clear()
{
    while (count)
        pop_front();
}

template <typename T>
bool List<T>::empty()
{
    return (begin() == end());
}

template <typename T>
void List<T>::copy(List<T> &list, const List<T> &other)
{
    list.count = 0;
    for (Iterator<T> it = other.begin(); it != other.end(); it++){
        list.push_back(*it);
    }
}

template <typename T>
void List<T>::merge(List<T> &list1, const List<T> &list2)
{
    for (Iterator<T> it = list2.begin(); it != list2.end(); it++){
        list1.push_back(*it);
    }
}

template <typename T>
bool List<T>::equal(const List<T> &other) const
{
    if (count != other.len())
        return false;

    Iterator<T> it = begin();
    Iterator<T> it_other = other.begin();
    while (it != end()){
        if (*it != *it_other)
            return false;
        it++;
        it_other++;
    }
    return true;
}

*/
