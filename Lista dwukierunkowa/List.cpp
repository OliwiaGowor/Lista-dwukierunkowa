#include "List.h"
 



    template<class T>
    List<T>::List<T>() : pHead(nullptr), pTail(nullptr) {
    }

    template<class T>
    List<T>::List<T>(const size_t size, const std::function<T(const size_t i)>& f) {
        for (int i = 0; i < size; ++i) {
            push_back(f(i));
        }
    }

    template<class T>
    List<T>::List<T>(const size_t size, T data) {
        for (int i = 0; i < size; ++i) {
            push_back(T);
        }
    }

    template<class T>
    List<T>::~List<T>() noexcept {
        while (pHead) {
            auto tmp = pHead->pNext;
            delete pHead;
            pHead = tmp;
        }
        delete pTail;
    }

    template<class T>
    size_t List<T>::size() const noexcept {
        Node<T>* ptr = pHead;
        size_t tmp = 0;
        while (ptr) {
            tmp++;
            ptr = ptr->pNext;
        }
        return tmp;
    }

    template<class T>
    void List<T>::push_back(T new_data) {
        Node<T>* new_node = new Node<T>{ new_data, nullptr, nullptr };
        if (!pHead) {
            pHead = new_node;
        }
        else {
            new_node->pPrevious = pTail;
            pTail->pNext = new_node;
        }
        pTail = new_node;
    }

    template<class T>
    void List<T>::insert(iterator it, T new_data)
    {
        if (pHead) {
            if (it.current_node == pHead) {
                Node<T>* new_node = new Node<T>;
                new_node->data = new_data;
                new_node->pNext = it.current_node;
                pHead = new_node;
            }
            else {
                Node<T>* tmp = new Node<T>;
                tmp->data = it.current_node->data;
                it.current_node->data = new_data;
                tmp->pNext = it.current_node->pNext;
                tmp->pPrevious = it.current_node;
                it.current_node->pNext = tmp;

            }
        }
        else {
            Node<T>* new_node = new Node<T>;
            new_node->data = new_data;
            pHead = pTail = new_node;
        }
    }

    template<class T>
    void List<T>::erase(iterator it) {
        if (pHead) {
            if (it != end()) {
                if (it != begin()) {
                    Node<T>* tmp = it.current_node->pNext;
                    if (it.current_node->pNext == nullptr) {
                        it.current_node->pNext = nullptr;
                        delete tmp;
                        return;
                    }
                    it.current_node->data = tmp->data;
                    it.current_node->pNext = tmp->pNext;
                    it.current_node->pPrevious = tmp->pPrevious;
                    delete tmp;
                }
                else {
                    pHead = it.current_node->pNext;
                    pHead->pPrevious = nullptr;
                    delete it.current_node;
                }
            }
            else
                std::cout << "Iterator poza zakresem listy!" << std::endl;
        }
        else
            std::cout << "Brak elementow do usuniecia" << std::endl;
    }

    template<class T>
    void List<T>::clear() {
        while (pHead) {
            auto tmp = pHead->pNext;
            delete pHead;
            pHead = tmp;
        }
        pHead = pTail = nullptr;
    }

    template<class T>
    Node<T>* List<T>::find(const T to_find) {
        auto tmp = pHead;
        if (tmp) {
            while (tmp) {
                if (tmp->data == to_find) {
                    return tmp;
                }
                tmp = tmp->pNext;
            }
        }
        else {
            return nullptr;
        }
    }

    template<class T>
    const_iterator List<T>::cbegin() const {
        return const_iterator(pHead);
    }

    template<class T>
    const_iterator List<T>::cend() const {
        return const_iterator(nullptr);
    }

    template<class T>
    iterator List<T>::begin() {
        return iterator(pHead);
    }

    template<class T>
    iterator List<T>::end() {
        return iterator(nullptr);
    }

    template<class T>
    Node<T>* List<T>::front() {
        return this->pHead;
    }

    template<class T>
    Node<T>* List<T>::back() {
        return this->pTail;
    }

    template<class T>
    std::ostream& operator<< (std::ostream& out, const List<T>& l)
    {
        Node<T>* ptr = l.pHead;
        while (ptr) {
            out << ptr->data << std::endl;
            ptr = ptr->pNext;
        }
        return out;
    }