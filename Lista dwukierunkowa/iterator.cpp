#include "iterator.h"

    template <class T>
    iterator::iterator(Node<T>* current_node) : const_iterator(current_node) {
    }

    template <class T>
    iterator& iterator::operator++() {
        if (current_node) {
            (this->current_node = current_node->pNext);
        }
        return *this;
    }

    template <class T>
    iterator iterator::operator++(int) {
        iterator it = *this;
        ++* this;
        return it;
    }

    iterator& iterator::operator--() {
        if (current_node) {
            (this->current_node = current_node->pPrevious);
        }
        return *this;
    }

    iterator iterator::operator--(int) {
        iterator it = *this;
        --* this;
        return it;
    }

    T& iterator::operator *() {
        return this->current_node->data;
    }

    T* iterator::operator -> () {
        return this->current_node;
    }
