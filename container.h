#ifndef CONTAINER_H
#define CONTAINER_H
// ins rem(it), it1..it2
// cbegin cend
// методы
#include <iostream>
#include <memory>
#include <iterator>
#include <initializer_list>
#include "base.h"
#include "myiterator.h"
#include "node.h"

using namespace std;

template <typename T>
class List : public Base
{
public:
    List();
    ~List() override;
    List(const initializer_list<T> &list);
    List(const T *arr, size_t len);
    explicit List(const List<T> &list);
    List(Iterator<T> &it1, Iterator<T> &it2);
    List(List<T> &&list);
    List<T>& operator=(const List<T> &list);
    List<T>& operator=(List<T> &&list);

    void pop_front();
    void pop_back();
    void remove(Iterator<T> &pos);
    void remove_elems(Iterator<T> &it1, Iterator<T> &it2);

    void push_front(const T &data);
    void push_back(const T &data);
    void push_elems_back(const List<T> &list);
    void push_elems_front(const List<T> &list);
    void push_elems_back(initializer_list<T> &list);
    void push_elems_front(initializer_list<T> &list);
    void insert_after(Iterator<T> &pos, const T &elem);
    void insert_before(Iterator<T> &pos, const T &elem);
    void insert_elems_after(Iterator<T> &pos, const T *arr, size_t len);
    void insert_elems_before(Iterator<T> &pos, const T *arr, size_t len);

    Iterator<T> begin() const;
    Iterator<T> end() const;
    Const_Iterator<T> cbegin() const;
    Const_Iterator<T> cend() const;
    size_t len() const override { return count; }
    T* to_array();

    bool empty();
    List<T>& combine(const List<T>& list);
    bool equal(const List<T> &other) const;

    operator bool() override { return count != 0; }
    List<T> operator+(const List<T> &list);
    List<T>& operator+=(const List<T> &list);
    List<T> operator+(const T &data);
    List<T>& operator+=(const T &data);
    bool operator==(const List<T> &list) const;
    bool operator!=(const List<T> &list) const;

    friend std::ostream& operator<<(std::ostream& os, const List<T>& list)
    {
        for (Iterator<T> it = list.begin(); it != list.end(); it++)
            os << (*it) << " ";
        os << endl << endl;
        return os;
    }

private:
    shared_ptr< Node<T> > head;
    size_t count;

    void del(size_t i);
    void insert(size_t i, const T &data);
    void clear();
    void copy(List<T> &list, const List<T> &other);
    void merge(List<T> &list1, const List<T> &list2);
};

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
List<T>::List(const initializer_list<T> &list)
{
    head = nullptr;
    count = 0;
    for (const auto &elem : list){
        push_back(elem);
    }
}

template <typename T>
List<T>::List(const T *arr, size_t len)
{
    head = nullptr;
    count = 0;
    for (size_t i = 0; i < len; i++){
        push_back(arr[i]);
    }
}

template <typename T>
List<T>::List(const List<T> &list)
{
    copy(*this, list);
}

template <typename T>
List<T>::List(Iterator<T> &it1, Iterator<T> &it2)
{
    head = nullptr;
    count = 0;
    for (Iterator<T> it = it1; it != it2; it++){
        push_back(*it);
    }
}

template <typename T>
List<T>::List(List<T> &&list)
{
    head = list.head;
    count = list.count;
    list.head = nullptr;
    list.count = 0;
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
Const_Iterator<T> List<T>::cbegin() const
{
    return Const_Iterator<T>(head);
}

template <typename T>
Const_Iterator<T> List<T>::cend() const
{
    return Const_Iterator<T>(nullptr);
}

template <typename T>
T* List<T>::to_array()
{
    T *arr = new T[count];
    if (!arr)
        throw(MemoryError());
    int i = 0;
    for (Iterator<T> it = begin(); it != end(); it++, i++){
        arr[i] = *it;
    }
    return arr;
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
void List<T>::push_elems_back(initializer_list<T> &list)
{
    for (auto &elem : list){
        push_back(elem);
    }
}

template <typename T>
void List<T>::push_elems_front(initializer_list<T> &list)
{
    for (auto &elem : list){
        push_front(elem);
    }
}

template <typename T>
void List<T>::insert_after(Iterator<T> &it, const T &data)
{
    if (!it)
        throw(IteratorError());
    auto new_n = make_shared< Node<T> >(data);
    if (!new_n)
        throw(MemoryError());
    shared_ptr< Node<T> > n = it.node.lock();
    new_n->next = n->next;
    n->next = new_n;
    count++;
}

template <typename T>
void List<T>::insert_before(Iterator<T> &pos, const T &data)
{
    if (pos == begin()){
        push_front(data);
        return;
    }

    Iterator<T> prev = begin();
    Iterator<T> it = begin();
    it++;
    while (it != pos){
        prev++;
        it++;
    }
    insert_after(prev, data);
}

template <typename T>
void List<T>::insert_elems_after(Iterator<T> &pos, const T *arr, size_t len)
{
    Iterator<T> it = pos;
    for (size_t i = 0; i < len; i++){
        insert_after(it, arr[i]);
        it++;
    }
}

template <typename T>
void List<T>::insert_elems_before(Iterator<T> &pos, const T *arr, size_t len)
{
    if (pos == begin()){
        for (size_t i = 0; i < len; i++)
            push_front(arr[i]);
        return;
    }

    Iterator<T> prev = begin();
    Iterator<T> it = begin();
    it++;
    while (it != pos){
        prev++;
        it++;
    }
    insert_elems_after(prev, arr, len);
}

template <typename T>
void List<T>::remove(Iterator<T> &pos)
{
    if (empty())
        throw(EmptyError());

    if (pos == begin())
        pop_front();

    Iterator<T> prev = begin();
    Iterator<T> it = begin();
    it++;
    while (it != pos){
        prev++;
        it++;
    }
    shared_ptr< Node<T> > n = prev.node.lock();
    n->next = n->next->next;
    count++;
}

template <typename T>
void List<T>::remove_elems(Iterator<T> &it1, Iterator<T> &it2)
{
    if (empty())
        throw(EmptyError());


    for (Iterator<T> it = it1; it != it2; it++)
        count--;

    shared_ptr< Node<T> > n2 = it2.node.lock();
    if (it1 == begin()){
        head = n2;
        return;
    }
    Iterator<T> prev = begin();
    Iterator<T> it = begin();
    it++;
    while (it != it1){
        prev++;
        it++;
    }
    shared_ptr< Node<T> > n1 = prev.node.lock();
    n1->next = n2;
}

template <typename T>
List<T>& List<T>::operator=(const List<T> &list)
{
    clear();
    copy(*this, list);
    return (*this);
}

template <typename T>
List<T>& List<T>::operator=(List<T> &&list)
{
    clear();
    head = list.head;
    count = list.count;
    list.head = nullptr;
    list.count = 0;
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

    auto new_n = make_shared< Node<T> >(data);
    if (!new_n)
        throw(MemoryError());

    ++count;
    if (i == 0){
        new_n->set_next(head);
        head = new_n;
        return;
    }

    Iterator<T> it;
    for (it = begin(); i > 1; it++, i--);
    shared_ptr< Node<T> > n = it.node.lock();
    new_n->set_next(n->get_next());
    n->set_next(new_n);
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

template <typename T>
List<T>& List<T>::combine(const List<T>& list)
{
    merge(*this, list);
    return (*this);
}

#endif // CONTAINER_H
