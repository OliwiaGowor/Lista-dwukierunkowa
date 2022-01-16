#pragma once
#include "const_iterator.h"

template <class T>
class iterator : public const_iterator
{
    friend class List;
    const_iterator::current_node;
public:
    iterator(Node<T>* current_node) : const_iterator(current_node);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    T& operator *();
    T* operator -> ();
};
