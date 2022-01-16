#include "List.h"

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