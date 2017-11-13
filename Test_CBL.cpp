//Include CATCH Framework
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ADT.h"
#include "CBL.h"
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"

using Catch::EndsWith;
using Catch::StartsWith;

template <typename element>
//For the Contains function
bool equals(element a, element b) {
    return a == b;
}

TEST_CASE( "CBL List Test Case" ) {

    cop3530::CBL<int> * cbl_list = new cop3530::CBL<int> (100);

    int index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        cbl_list->push_back(index);

    REQUIRE( cbl_list->item_at(99) == 100 );
    REQUIRE( cbl_list->item_at(0) == 1 );
    REQUIRE( !(cbl_list->is_empty()) );
    REQUIRE( cbl_list->length() == 100 );

    cbl_list->push_back(101);
    cbl_list->push_front(0);

    REQUIRE( cbl_list->length() == 102 );
    REQUIRE( cbl_list->item_at(101) == 101 );
    REQUIRE( cbl_list->item_at(0) == 0 );

    cbl_list->clear();

    REQUIRE( !(cbl_list->is_full()) );
    REQUIRE( cbl_list->is_empty() );

    index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        cbl_list->push_front(index);

    REQUIRE ( cbl_list->item_at(0) == 100 );
    REQUIRE ( cbl_list->item_at(99) == 1 );
    REQUIRE ( !(cbl_list->is_empty()) );
    REQUIRE ( cbl_list->length() == 100 );

    cbl_list->insert(30, 50);
    cbl_list->insert(79, 0);

    REQUIRE ( cbl_list->length() == 102 );
    REQUIRE ( cbl_list->item_at(51) == 30 );
    REQUIRE ( cbl_list->item_at(101) == 1 );

    cbl_list->remove(0);
    cbl_list->remove(50);

    REQUIRE ( cbl_list->item_at(0) == 100 );
    REQUIRE ( cbl_list->item_at(50) == 50 );

    cbl_list->replace(40, 9);

    REQUIRE ( cbl_list->item_at(9) == 40 );

    REQUIRE ( cbl_list->peek_back() == 1 );

    cbl_list->pop_back();

    REQUIRE ( cbl_list->peek_back() == 2 );
    REQUIRE ( cbl_list->length() == 99 );
    REQUIRE ( cbl_list->peek_front() == 100 );

    cbl_list->pop_front();

    REQUIRE ( cbl_list->item_at(0) == 99 );
    REQUIRE ( cbl_list->length() == 98 );

    cbl_list->remove(8);

    REQUIRE ( cbl_list->length() == 97 );
    REQUIRE ( cbl_list->item_at(8) == 90 );

    cbl_list->clear();

    std::ofstream out_file("cbl_list.txt");
    cbl_list->print(out_file);

    for (int i = 1; i < 6; ++i)
        cbl_list->push_back(i);

    std::ofstream out_file_2("test_case_2.txt");
    cbl_list->print(out_file_2);
    std::ifstream in_file_1 ("cbl_list.txt");

    std::ifstream in_file_2 ("test_case_2.txt");

    REQUIRE ( in_file_1 );
    REQUIRE ( in_file_2 );

    ///TODO
   // REQUIRE (  )

    int true_contents [5] = {1, 2, 3, 4, 5};
    int * list_contents = cbl_list->contents();
    for (int i = 0; i < 5; ++i)
        REQUIRE ( true_contents[i] == list_contents[i] );

    //Check Contains Function
    REQUIRE ( cbl_list->contains(5, &equals) );
    REQUIRE ( !(cbl_list->contains(7, &equals)) );

    cbl_list->clear();

    index = 1;
    for (int i = 0; i < 100; ++i, ++index)
        cbl_list->push_back(index);


    REQUIRE ( cbl_list->contains(59, &equals) );
    REQUIRE ( cbl_list->contains(1, &equals) );
    REQUIRE ( cbl_list->contains(100, &equals) );
    REQUIRE ( !(cbl_list->contains(101, &equals)) );

}

TEST_CASE( "CBL Iterator" ) {

    cop3530::CBL<int> * cbl_list_iter = new cop3530::CBL<int> (100);

     for (int i = 1; i <= 100; ++i)
        cbl_list_iter->push_back(i);

    int * temp_contents = cbl_list_iter->contents();
    int index = 0;

    for (cop3530::CBL<int>::iterator it = cbl_list_iter->begin(); it != cbl_list_iter->end(); ++it, ++index) {
        if (temp_contents[index] != *it) {
            std::cout << temp_contents[index] << "  " << *it << "  " << index << std::endl;
          REQUIRE ( temp_contents[index] == *it );

        }
    }

    cbl_list_iter->insert(30, 50);
    cbl_list_iter->remove(8);
    cbl_list_iter->pop_back();
    cbl_list_iter->pop_front();

    temp_contents = cbl_list_iter->contents();
    index = 0;

    for (cop3530::CBL<int>::iterator it = cbl_list_iter->begin(); it != cbl_list_iter->end(); ++it) {

        REQUIRE ( temp_contents[index] == *it );

        ++index;
    }

    cop3530::CBL<int> const * cbl_list_const_iter = cbl_list_iter;

    index = 0;
    for (cop3530::CBL<int>::const_iterator it = cbl_list_const_iter->begin(); it != cbl_list_const_iter->end(); ++it) {

        REQUIRE ( temp_contents[index] == *it );

        ++index;
    }

}

