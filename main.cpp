#include "List.h"
#include "SSLL.h"
#include "PSLL.h"
#include "CBL.h"
#include "SDAL.h"
#include "CDAL.h"
#include <iostream>

using namespace std;

bool equals(const char& a, const char& b) {
	return a == b;
}

int main () {

	cop3530::SDAL<std::string> * list  = new cop3530::SDAL<std::string>();

	list->push_back ("Testing the ");
	list->push_back ("string template.");
	list->push_back ("Henri");
	list->push_back ("in HenriLeChatNoir ");
	list->push_back ("is my spirit animal.");
	list->push_back ("9000");
	list->push_back ("COP3530");
	list->push_back ("!.!.!");
	list->push_back ("Hello++");
	list->push_back ("World..");
	list->remove(8);

    try {
		list->remove(9);
	}
	catch (std::runtime_error e) {std::cout << "DIDNT WORK";}
    list->push_front("Hello from the other side.");

    std::string * temp = list->contents ();

	for (int i = 0; i < list->length (); ++i)
        cout << temp[i] << "   ";
    cout << endl;

	/*cout << (list->item_at(0)) << endl;
	cout << (list->item_at(5)) << endl;
	cout << (list->length()) << endl;

	std::string * temp = list->contents ();

	for (int i = 0; i < list->length (); ++i)
        cout << temp[i] << "   ";
    cout << endl;

	cout << (list->remove(8)) << endl;
	cout << (list->item_at(8)) << endl;

	temp = list->contents ();

	for (int i = 0; i < list->length (); ++i)
        cout << temp[i] << "   ";
    cout << endl;


	try {
		list->remove(9);
	}
	catch (std::runtime_error e) {}


    list->push_front("Hello from the other side.");
    cout << (list->peek_front()) << endl;

     list->push_front("Hello from the other side.");
    cout << (list->peek_front()) << endl;
     list->push_front("Hello from the other side.");
    cout << (list->peek_front()) << endl;
     list->push_front("Hello from the other side.");
    cout << (list->peek_front()) << endl;

    	temp = list->contents ();

	for (int i = 0; i < list->length (); ++i)
        cout << temp[i] << "   ";
    cout << endl;
*/


	return 0;
}
