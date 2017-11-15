#include "List.h"
#include "SSLL.h"
#include "PSLL.h"
#include "CBL.h"
#include <iostream>

using namespace std;

int main () {
	cop3530::SSLL<int> * list = new cop3530::SSLL<int> ();
    ///Testing Constructors and Destructors
    for (int i = 0; i < 10; ++i)
        list->push_back(i + 1);
    for (cop3530::SSLL<int>::iterator i = list->begin(); i != list->end(); ++i)
       cout << *i << "  ";
    cout << endl;
    cop3530::SSLL<int> * list2 = new cop3530::SSLL<int> ();
    ///Testing Constructors and Destructors
    for (int i = 9; i < 19; ++i)
        list2->push_back(i + 1);
    for (cop3530::SSLL<int>::iterator i = list2->begin(); i != list2->end(); ++i)
       cout << *i << "  ";

    cout << "list:" << endl << list << endl;
    cout << "list2:" << endl << list2 << endl;
    list = list2;
    cout << "list:" << endl;
    cout << list << endl;
    cout << "list2:" << endl;
    cout << list2 << endl;

     for (cop3530::SSLL<int>::iterator i = list->begin(); i != list->end(); ++i)
       cout << *i << "  ";

    cout << endl;

    for (cop3530::SSLL<int>::iterator i = list2->begin(); i != list2->end(); ++i)
       cout << *i << "  ";

	return 0;
}
