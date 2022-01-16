#include "const_iterator.h"

template <class T>
    const_iterator::const_iterator(Node<T>* current_node) : current_node(current_node) {
    }

    const_iterator& operator++() {
        if (current_node) {
            current_node = current_node->pNext;
        }
        return *this;
    }

    template <class T>
    const_iterator& operator++(int) {
        Node<T>* tmp = current_node;
        ++* this;
        return const_iterator(tmp);
    }

    const_iterator& operator--() {
        if (current_node) {
            current_node = current_node->pPrevious;
        }
        return *this;
    }

    template <class T>
    const_iterator& operator--(int) {
        Node<T>* tmp = current_node;
        --* this;
        return const_iterator(tmp);
    }

    const T& operator *() const {
        return current_node->data;
    }

    const T* operator -> () const {
        return current_node;
    }

    bool operator != (const const_iterator& it) const {
        return it.current_node != this->current_node;
    }

