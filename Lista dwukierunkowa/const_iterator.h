#pragma once


template <class T>
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

