#ifndef GITHUB_PARCIAL_AED_ITERATORS_H
#define GITHUB_PARCIAL_AED_ITERATORS_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;

void iterate_vector() {
    vector<int> vec = {1, 2, 3, 4, 5};
    vector<int>::iterator it;

    cout << "Elementos del vector: ";
    for (it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void iterate_list() {
    list<int> li = {10, 20, 30, 40, 50};
    list<int>::iterator it;

    cout << "Elementos de la lista: ";
    for (it = li.begin(); it != li.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;


#endif //GITHUB_PARCIAL_AED_ITERATORS_H
