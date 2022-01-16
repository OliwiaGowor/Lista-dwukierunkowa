#pragma once
#include <iostream>
#include <functional>
#include "const_iterator.h"


template <class T>
struct Node {
    T data;
    Node<T>* pNext;
    Node<T>* pPrevious;
};


template <class T>
class List {
private:
    Node<T>* pHead;
    Node<T>* pTail;

public:
    class const_iterator {
    protected:
        friend class List;
        Node<T>* current_node;

    public:
        const_iterator(Node<T>* current_node) : current_node(current_node);
        const_iterator& operator++();
        const_iterator& operator++(int);
        const_iterator& operator--();
        const_iterator& operator--(int);
        const T& operator *() const;
        const T* operator -> () const;
        bool operator != (const const_iterator& it) const;

    };

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

    List<T>();
    List<T>(const size_t size, const std::function<T(const size_t i)>& f);
    List<T>(const size_t size, T data);
    ~List<T>() noexcept;
    size_t size() const noexcept;
    void push_back(T new_data);
    void insert(iterator it, T new_data);
    void erase(iterator it);
    void clear();
    Node<T>* find(const T to_find);
    const_iterator cbegin() const;
    const_iterator cend() const;
    iterator begin();
    iterator end();
    Node<T>* front();
    Node<T>* back();
    friend std::ostream& operator<< (std::ostream& out, const List<T>& l);

};

