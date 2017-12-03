#include "List.h"
#include "CDAL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "SSLL.h"
#include "CBL.h"

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <limits>

template <typename element>

//For the contains function
bool equals(element a, element b) {
    return a == b;
}

template <typename element>

bool test_int_passed(cop3530::List<element> * test_case_1) {

    int index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        test_case_1->push_back(index);
    if (test_case_1->item_at(99) != 100 || test_case_1->item_at(0) != 1) return false;
    if (test_case_1->is_empty()) return false;
    if (test_case_1->length() != 100) return false;
    //Should through a runtime exception for all typenames except CDAL and SDAL which allocates more memory

	test_case_1->push_back(101);
	test_case_1->push_front(0);
	if (test_case_1->length() != 102) return false;
	if (test_case_1->item_at(101) != 101 || test_case_1->item_at(0) != 0) return false;


    test_case_1->clear();
    if (test_case_1->is_full()  || !(test_case_1->is_empty())) return false;

    index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        test_case_1->push_front(index);
    if (test_case_1->item_at(0) != 100 || test_case_1->item_at(99) != 1) return false;
    if (test_case_1->is_empty()) return false;
    if (test_case_1->length() != 100) return false;
    //Testing the insert function

	test_case_1->insert(30, 50);
	//Will push to front of CDAL or SDAL List
	test_case_1->insert(79, 0);
	if (test_case_1->length() != 102) return false;

	if (test_case_1->item_at(51) != 30) return false;
	if (test_case_1->item_at(101) != 1) return false;

	//Remove inserted elements
	if (test_case_1->remove(0) != 79) return false;
	test_case_1->remove(50);
	if (test_case_1->item_at(0) != 100) return false;
	if (test_case_1->item_at(50) != 50) return false;

    test_case_1->replace(40, 9);
    if (test_case_1->item_at(9) != 40) return false;

    if (test_case_1->peek_back() != 1) return false;
    test_case_1->pop_back();
    if (test_case_1->peek_back() != 2) return false;
    if (test_case_1->length() != 99) return false;

    if (test_case_1->peek_front() != 100) return false;
    test_case_1->pop_front();

    if (test_case_1->item_at(0) != 99) return false;
    if (test_case_1->length() != 98) return false;

    test_case_1->remove(8);
    if (test_case_1->length() != 97) return false;
    if (test_case_1->item_at(8) != 90) return false;

    test_case_1->clear();

    for (int i = 1; i < 6; ++i)
        test_case_1->push_back(i);

    //Checking contents Function
    element true_contents [5] = {1, 2, 3, 4, 5};
    element * list_contents = test_case_1->contents();
    for (int i = 0; i < 5; ++i)
        if (true_contents[i] != list_contents[i]) return false;
    delete [] list_contents;
    //Print function file matches contents

    //Check contains functions
    if (!test_case_1->contains(5, &equals)) return false;
    if (test_case_1->contains(7, &equals)) return false;

    test_case_1->clear();

    index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        test_case_1->push_back(index);

    if (!test_case_1->contains(59, &equals)) return false;
    if (!test_case_1->contains(1, &equals)) return false;
    if (!test_case_1->contains(100, &equals)) return false;
    if (test_case_1->contains(101, &equals)) return false;


    return true;
}

template <typename element>

bool test_char_passed(cop3530::List<element> * test_case_2) {

	test_case_2->push_back ('a');
	test_case_2->push_back ('b');
	test_case_2->push_back ('c');
	test_case_2->push_back ('d');
	test_case_2->push_back ('e');
	test_case_2->push_back ('f');
	test_case_2->push_back ('g');
	test_case_2->push_back ('h');
	test_case_2->push_back ('i');
	test_case_2->push_back ('j');

	if (test_case_2->item_at(0) != 'a') return false;
	if (test_case_2->item_at(5) != 'f') return false;
	if (test_case_2->length() != 10) return false;

	if (test_case_2->remove(8) != 'i') return false;
	if (test_case_2->item_at(8) != 'j') return false;
	try {
		test_case_2->remove(9);
	}
	catch (std::runtime_error e) {}

	test_case_2->push_front('z');
	if (test_case_2->peek_front() != 'z') return false;

	if (test_case_2->contains('m', &equals)) return false;
	if (!test_case_2->contains('a', &equals)) return false;

	element * temp_contents = test_case_2->contents();

	if (temp_contents[0] != 'z' || temp_contents[0] != test_case_2->peek_front()) return false;
	if (temp_contents[5] != test_case_2->item_at(5)) return false;

	delete [] temp_contents;

	return true;
}

bool test_ssll_iterator () {

    cop3530::SSLL<int> * ssll_list = new cop3530::SSLL<int> ();
    for (int i = 1; i <= 100; ++i)
        ssll_list->push_back(i);

    int * temp_contents = ssll_list->contents();
    int index = 0;

    for (cop3530::SSLL<int>::iterator i = ssll_list->begin(); i != ssll_list->end(); ++i) {
        if (temp_contents[index] != *i) return false;
        ++index;
    }

    ssll_list->remove(8);
    ssll_list->insert(30, 50);
    ssll_list->pop_back();
    ssll_list->pop_front();

	delete [] temp_contents;

    temp_contents = ssll_list->contents();
    index = 0;

    for (cop3530::SSLL<int>::iterator it = ssll_list->begin(); it != ssll_list->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }

    cop3530::SSLL<int> const * ssll_list_const_iter = ssll_list;

    index = 0;
    for (cop3530::SSLL<int>::const_iterator it = ssll_list_const_iter->begin(); it != ssll_list_const_iter->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }

    delete [] temp_contents;
	delete ssll_list;

    return true;
}

bool test_psll_iterator () {

    cop3530::PSLL<int> * psll_list = new cop3530::PSLL<int> ();
    for (int i = 1; i <= 100; ++i)
        psll_list->push_back(i);

    int * temp_contents = psll_list->contents();
    int index = 0;

    for (cop3530::PSLL<int>::iterator i = psll_list->begin(); i != psll_list->end(); ++i) {
        if (temp_contents[index] != *i) return false;
        ++index;
    }

    psll_list->remove(8);
    psll_list->insert(30, 50);
    psll_list->pop_back();
    psll_list->pop_front();

	delete [] temp_contents;
    temp_contents = psll_list->contents();
    index = 0;

    for (cop3530::PSLL<int>::iterator it = psll_list->begin(); it != psll_list->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }

    cop3530::PSLL<int> const * psll_list_const_iter = psll_list;

    index = 0;
    for (cop3530::PSLL<int>::const_iterator it = psll_list_const_iter->begin(); it != psll_list_const_iter->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }

    delete [] temp_contents;
	delete psll_list;

    return true;
}

bool test_sdal_iterator () {

    cop3530::SDAL<int> * sdal_list = new cop3530::SDAL<int> (100);
    for (int i = 1; i <= 100; ++i)
        sdal_list->push_back(i);

    int * temp_contents = sdal_list->contents();
    int index = 0;

    for (cop3530::SDAL<int>::iterator i = sdal_list->begin(); i != sdal_list->end(); ++i) {
        if (temp_contents[index] != *i) return false;
        ++index;
    }

    sdal_list->insert(30, 50);
    sdal_list->remove(8);
    sdal_list->pop_back();
    sdal_list->pop_front();

	delete [] temp_contents;
    temp_contents = sdal_list->contents();
    index = 0;

    for (cop3530::SDAL<int>::iterator it = sdal_list->begin(); it != sdal_list->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }

    cop3530::SDAL<int> const * sdal_list_const_iter = sdal_list;

    index = 0;
    for (cop3530::SDAL<int>::const_iterator it = sdal_list_const_iter->begin(); it != sdal_list_const_iter->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }

    delete [] temp_contents;
	delete sdal_list;

    return true;
}

bool test_cdal_iterator () {

   cop3530::CDAL<int> * cdal_list = new cop3530::CDAL<int> ();
   for (int i = 1; i <= 100; ++i)
        cdal_list->push_back(i);

    cdal_list->remove(8);
    cdal_list->pop_back();
    cdal_list->pop_front();
    cdal_list->insert(30, 50);

    int * temp_contents = cdal_list->contents();
    int  index = 0;

    for (cop3530::CDAL<int>::iterator it = cdal_list->begin(); it != cdal_list->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }


    cop3530::CDAL<int> const * cdal_list_const_iter = cdal_list;

    index = 0;
    for (cop3530::CDAL<int>::const_iterator it = cdal_list_const_iter->begin(); it != cdal_list_const_iter->end(); ++it) {
        if (temp_contents[index] != *it) return false;
        ++index;
    }

    delete [] temp_contents;
    delete cdal_list;

    return true;
}

int main () {

    bool all_passed = true;

    cop3530::SSLL<int> * ssll_list = new cop3530::SSLL<int> ();
    cop3530::PSLL<int> * psll_list = new cop3530::PSLL<int> ();
    cop3530::SDAL<int> * sdal_list = new cop3530::SDAL<int> (100);
    cop3530::CDAL<int> * cdal_list = new cop3530::CDAL<int> ();

    std::cout << "--------------- TEST CASES ---------------\n";
    std::cout << "\t     --- INT LIST ---\n";

    if (test_int_passed(ssll_list))
        std::cout << "SSLL TEST CASE: PASSED\n";
    else {
        std::cout << "SSLL TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_int_passed(psll_list))
        std::cout << "PSLL TEST CASE: PASSED\n";
    else {
        std::cout << "PSLL TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_int_passed(sdal_list))
        std::cout << "SDAL TEST CASE: PASSED\n";
    else {
        std::cout << "SDAL TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_int_passed(cdal_list))
        std::cout << "CDAL TEST CASE: PASSED\n";
    else {
        std::cout << "CDAL TEST CASE: FAILED\n" ;
        all_passed = false;
    }

    cop3530::SSLL<char> * ssll_list_char = new cop3530::SSLL<char> ();
    cop3530::PSLL<char> * psll_list_char = new cop3530::PSLL<char> ();
    cop3530::SDAL<char> * sdal_list_char = new cop3530::SDAL<char> ();
    cop3530::CDAL<char> * cdal_list_char = new cop3530::CDAL<char> ();

    std::cout << "\n\t    --- CHAR LIST ---\n";

    if (test_char_passed(ssll_list_char))
        std::cout << "SSLL TEST CASE: PASSED\n";
    else {
        std::cout << "SSLL TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_char_passed(psll_list_char))
        std::cout << "PSLL TEST CASE: PASSED\n";
    else {
        std::cout << "PSLL TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_char_passed(sdal_list_char))
        std::cout << "SDAL TEST CASE: PASSED\n";
    else {
        std::cout << "SDAL TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_char_passed(cdal_list_char))
        std::cout << "CDAL TEST CASE: PASSED\n";
    else {
        std::cout << "CDAL TEST CASE: FAILED\n" ;
        all_passed = false;
    }

    std::cout << "\n\t   --- ITERATOR LIST ---\n";

    if (test_ssll_iterator())
        std::cout << "SSLL ITERATOR TEST CASE: PASSED\n";
    else {
        std::cout << "SSLL ITERATOR TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_psll_iterator())
        std::cout << "PSLL ITERATOR TEST CASE: PASSED\n";
    else {
        std::cout << "PSLL ITERATOR TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_sdal_iterator())
        std::cout << "SDAL ITERATOR TEST CASE: PASSED\n";
    else {
        std::cout << "SDAL ITERATOR TEST CASE: FAILED\n" ;
        all_passed = false;
    }
    if (test_cdal_iterator())
        std::cout << "CDAL ITERATOR TEST CASE: PASSED\n";
    else {
        std::cout << "CDAL ITERATOR TEST CASE: FAILED\n" ;
        all_passed = false;
    }

    std::cout << (all_passed ? "\nALL TEST CASES PASSED\n" : "\nAT LEAST ONE TEST CASE FAILED\n");


	delete ssll_list;
	delete psll_list;
	delete sdal_list;
	delete cdal_list;

	delete ssll_list_char;
	delete psll_list_char;
	delete sdal_list_char;
	delete cdal_list_char;

    return 0;
}
