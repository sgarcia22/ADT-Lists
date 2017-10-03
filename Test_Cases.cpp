#include "ADT.h"
#include "CDAL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "SSLL.h"

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

bool test_int_passed(cop3530::ADT<element> * test_case_1) {

    int index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        test_case_1->push_back(index);
    if (test_case_1->item_at(100) != 100 || test_case_1->item_at(1) != 1) return false;
    if (!(test_case_1->is_full()) || test_case_1->is_empty()) return false;
    if (test_case_1->length() != 100) return false;
    //Should through a runtime exception for all typenamees except CDAL and SDAL which allocates more memory
    if (dynamic_cast<cop3530::CDAL<element> *>(test_case_1) == nullptr && dynamic_cast<cop3530::SDAL<element> *>(test_case_1) == nullptr) {
        try {
            test_case_1->push_back(101);
            return false;
        }
        catch (const std::runtime_error e) {}
          try {
            test_case_1->push_front(0);
            return false;
        }
        catch (const std::runtime_error e) {}
    }
    else {
        test_case_1->push_back(101);
        test_case_1->push_front(0);
        if (test_case_1->length() != 102) return false;
        if (test_case_1->item_at(102) != 101 || test_case_1->item_at(1) != 0) return false;
    }

    test_case_1->clear();
    if (test_case_1->is_full()  || !(test_case_1->is_empty())) return false;

    index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        test_case_1->push_front(index);
    if (test_case_1->item_at(1) != 100 || test_case_1->item_at(100) != 1) return false;
    if (!(test_case_1->is_full()) || test_case_1->is_empty()) return false;
    if (test_case_1->length() != 100) return false;
    //Testing the insert function
    if (dynamic_cast<cop3530::CDAL<element> *>(test_case_1) == nullptr && dynamic_cast<cop3530::SDAL<element> *>(test_case_1) == nullptr) {
        //Should through a runtime_error exception
        try {
            test_case_1->insert(30, 50);
            return false;
        }
        catch (const std::runtime_error e) {}
          try {
            test_case_1->insert(30, 100);
            return false;
        }
        catch (const std::runtime_error e) {}
    }
    else {
        test_case_1->insert(30, 51);
        //Will push to front of CDAL or SDAL List
        test_case_1->insert(79, 1);
        if (test_case_1->length() != 102) return false;
        //If we passed in the SDAL class
        if (dynamic_cast<cop3530::SDAL<element> *>(test_case_1) != nullptr || dynamic_cast<cop3530::CDAL<element> *>(test_case_1) != nullptr ) {
            if (test_case_1->item_at(52) != 30) return false;
            if (test_case_1->item_at(102) != 1) return false;
        }

        //Remove inserted elements
        test_case_1->remove(1);
        test_case_1->remove(51);
        if (test_case_1->item_at(1) != 100) return false;
        if (test_case_1->item_at(51) != 50) return false;

    }

    test_case_1->replace(40, 10);
    if (test_case_1->item_at(10) != 40) return false;

    if (test_case_1->peek_back() != 1) return false;
    test_case_1->pop_back();
    if (test_case_1->peek_back() != 2) return false;
    if (test_case_1->length() != 99) return false;


    if (test_case_1->peek_front() != 100) return false;
    test_case_1->pop_front();

    if (test_case_1->item_at(1) != 99) return false;
    if (test_case_1->length() != 98) return false;


    test_case_1->remove(9);
    if (test_case_1->length() != 97) return false;
    if (test_case_1->item_at(9) != 90) return false;

    //Checking Print Function
    test_case_1->clear();
    //Should print out <empty list>
    std::ofstream out_file("test_case_1.txt");
    test_case_1->print(out_file);

    for (int i = 1; i < 6; ++i)
        test_case_1->push_back(i);

    std::ofstream out_file_2("test_case_2.txt");
    test_case_1->print(out_file_2);

    std::string first_file_content;

    std::ifstream in_file_1 ("test_case_1.txt");
    if (!in_file_1) return false;

    std::ifstream in_file_2 ("test_case_2.txt");
    if (!in_file_2) return false;

    ///CHECK PRINT CONTENTS?
   /* std::string output;

    in_file_1.open("test_case_1.txt");
    if (in_file_1.is_open()) {
        while(std::getline(in_file_1, output))
            std::cout << output;
    }
*/
    //Checking contents Function
    element true_contents [5] = {1, 2, 3, 4, 5};
    element * list_contents = test_case_1->contents();
    for (int i = 0; i < 5; ++i) {
        if (true_contents[i] != list_contents[i]) return false;
    }
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

int main () {

    bool all_passed = true;

    cop3530::SSLL<int> * ssll_list = new cop3530::SSLL<int> (100);
    cop3530::PSLL<int> * psll_list = new cop3530::PSLL<int> (100);
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

    std::cout << (all_passed ? "ALL TEST CASES PASSED\n" : "AT LEAST ONE TEST CASE FAILED\n");



    return 0;
}
