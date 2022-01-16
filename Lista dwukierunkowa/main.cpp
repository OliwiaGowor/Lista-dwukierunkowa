#include <iostream>
#include <functional>


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
        const_iterator(Node<T>* current_node) : current_node(current_node) {
        }

        const_iterator& operator++() {
            if (current_node) {
                current_node = current_node->pNext;
            }
            return *this;
        }

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
           return it.current_node != this ->current_node;
        }

    };

    class iterator: public const_iterator
    {
        friend class List;
        using const_iterator::current_node;
    public:
        iterator(Node<T>* current_node): const_iterator(current_node) {
        }

        iterator& operator++() {
            if(current_node){
            (this->current_node = current_node->pNext);
            }
            return *this;
        }

        iterator operator++(int) {
            iterator it = *this;
            ++* this;
            return it;
        }

        iterator& operator--() {
            if (current_node) {
                (this->current_node = current_node->pPrevious);
            }
            return *this;
        }

        iterator operator--(int) {
            iterator it = *this;
            --* this;
            return it;
        }

       T& operator *() {
           return this->current_node->data;
       }

        T* operator -> () {
            return this->current_node;
        }
    };

public:
    List<T>() : pHead(nullptr), pTail(nullptr) {
    }

    List<T>(const size_t size, const std::function<T(const size_t i)> &f) {
        for (int i = 0; i < size; ++i) {
            push_back(f(i));
        }
    }

    List<T>(const std::size_t size, T data) {
        for (int i = 0; i < size; ++i) {
            push_back(data);
        }
    }

    ~List<T>() noexcept {
        while (pHead) {
            auto tmp = pHead->pNext;
            delete pHead;
            pHead = tmp;
        }
        //delete pTail;
    }

    size_t size() const noexcept {
        Node<T>* ptr = pHead;
        size_t tmp = 0;
        while (ptr) {
            tmp++;
            ptr = ptr->pNext;
        }
        return tmp;
    }

    void push_back(T new_data) {
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


    void insert(iterator it, T new_data)
    {
        if (pHead) {
            if (it.current_node == pHead) {
                Node<T> *new_node = new Node<T>;
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
            Node<T> *new_node = new Node<T>;
            new_node->data = new_data;
            pHead = pTail = new_node;
        }
    }

    void erase(iterator it) {
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

    void clear() {
        while (pHead) {
            auto tmp = pHead->pNext;
            delete pHead;
            pHead = tmp;
        }
        pHead = pTail = nullptr;
    }

    Node<T>* find(const T to_find) {
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

    const_iterator begin() const {
        return const_iterator(pHead);
    }

    const_iterator end() const {
        return const_iterator(nullptr);
    }

    iterator begin() {
        return iterator(pHead);
    }

    iterator end() {
        return iterator(nullptr);
    }

    Node<T>* front() {
        return this->pHead;
    }

    Node<T>* back() {
        return this->pTail;
    }

    friend std::ostream& operator << (std::ostream& out, const List<T>& l)
    {
        Node<T>* ptr = l.pHead;
        while (ptr) {
            out << ptr->data << std::endl;
            ptr = ptr->pNext;
        }
        return out;
    }

};

int main() {
     List<double> lista(4, [](const size_t i) { return 1.0 + i; });
    for (const auto& el : lista) std::cout << el << std::endl;
    std::cout << "Test 1" << std::endl;
    for (auto& el : lista) el *= 2.0;
    for (auto it = lista.begin(); it != lista.end(); ++it) std::cout << *it << std::endl;
    std::cout << "Test 2" << std::endl;
    lista.erase(lista.begin());
    for (const auto& el : lista) std::cout << el << std::endl;
    std::cout << "Test 3" << std::endl;
    lista.erase(lista.end());
    for (const auto& el : lista) std::cout << el << std::endl;
    std::cout << "Test 4" << std::endl;
    lista.push_back(13.3);
    for (const auto& el : lista) std::cout << el << std::endl;
    std::cout << "Test 5" << std::endl;
    lista.insert(++(lista.begin()), 16.6);
    for (const auto& el : lista) std::cout << el << std::endl;
    std::cout << "Test 6" << std::endl;

    std::cout << "Znalezione: " << lista.find(6)->data << std::endl;

    std::cout << "Pierwszy element: " << lista.front()->data << std::endl;
    std::cout << "Ostatni element: " << lista.back()->data << std::endl;

    lista.clear();

    std::cout << "Znalezione: " << lista.find(6) << std::endl;

    for (const auto& el : lista) std::cout << el << std::endl;
    std::cout << "Test 7" << std::endl;

    return 0;
}
