#include <iostream>
#include "BPlusTree.h"

int main()
{
    BPlusTree bPlusTree(3);

    bPlusTree.insert(10);
    bPlusTree.insert(20);
    bPlusTree.insert(5);
    bPlusTree.insert(6);
    bPlusTree.insert(12);
    bPlusTree.insert(30);
    bPlusTree.insert(7);
    bPlusTree.insert(17);

    Node *result = bPlusTree.search(bPlusTree.root, 6);
    cout << (result ? "Clave encontrada" : "Clave no encontrada") << endl;

    bPlusTree.remove(6);

    result = bPlusTree.search(bPlusTree.root, 6);
    cout << (result ? "Clave encontrada" : "Clave no encontrada") << endl;

    return 0;
}