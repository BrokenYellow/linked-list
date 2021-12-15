#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include "container.h"
#include "myiterator.h"
#include "node.h"
#include <memory>
//QTextStream cout(stdout);

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    QCoreApplication a(argc, argv);

    List<int> li({1, 2, 3});
    std::cout << "Constructor li\n" << li;

    li.push_back(4);
    std::cout << "push_back(4)\n" << li;

    li.push_front(0);
    std::cout << "push_front(0)\n" << li;

    li.pop_back();
    std::cout << "pop_back()\n" << li;

    li.pop_front();
    std::cout << "pop_front()\n" << li;

    /////////////////////////////////////

    List<int> l1({1, 2, 3}), l2({4, 5}), l3;
    std::cout << "l1\n" << l1;
    std::cout << "l2\n" << l2;

    l3 = l1 + l2;
    cout << "l3 = l1 + l2\n" << l3;

    l1 += l2;
    cout << "l1 += l2\n" << l1;

    l1 += 10;
    cout << "l1 += 10\n" << l1;

    l1 = l2;
    cout << "l1 = l2\n" << l1 << " = " << l2;

    cout << "l1 == l2? " << (l1 == l2) << endl;

    cout << "l1 != l3? " << (l1 != l3) << endl;

    List<int> l4;
    cout << "l4.empty() " << l4.empty() << endl;

    List<int> l5({0, 1, 2, 3, 4, 5});
    Iterator<int> it;
    int i = 0;
    int arr[] = {30, 31};
    for (it = l5.begin(); i < 1; it++, i++);
    Iterator<int> e = l5.end();
    l5.insert_elems_before(e, arr, 2);
    cout << "l5 " << l5 << endl;
    l5.remove_elems(it, e);
    cout << "l5 " << l5 << endl;

    return a.exec();
}
