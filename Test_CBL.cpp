//Include CATCH Framework
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "List.h"
#include "CBL.h"
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"

using Catch::EndsWith;
using Catch::StartsWith;

/*TODO Test
 * Change functions return values to by reference (not remove, pop_front, nor pop_back)
 * Copy, Move Constructors
 * Undefined Behavior Errors
 * String SDAL & CDAL -> Push front not working well
 * Test String and Char with CBL
 * */

template <typename element>
//For the Contains function
bool equals(element a, element b) {
    return a == b;
}

TEST_CASE( "CBL List Test Case" ) {

    cop3530::CBL<int> * cbl_list = new cop3530::CBL<int> ();

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
    REQUIRE ( cbl_list->item_at(50) == 30 );

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

	std::ostringstream out_file_1;
	cbl_list->print(out_file_1);
	std::string in_file_1 = out_file_1.str();

	REQUIRE_THAT ( in_file_1 , EndsWith("<empty list>") );

    for (int i = 1; i < 6; ++i)
        cbl_list->push_back(i);

	std::ostringstream out_file_2;
	cbl_list->print(out_file_2);
	std::string in_file_2 = out_file_2.str();

	REQUIRE_THAT ( in_file_2 , EndsWith("<1,2,3,4,5>") );

    int true_contents [5] = {1, 2, 3, 4, 5};
    int * list_contents = cbl_list->contents();
    for (int i = 0; i < 5; ++i)
        REQUIRE ( true_contents[i] == list_contents[i] );
    delete [] list_contents;

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

    delete cbl_list;

}

TEST_CASE( "CBL Iterator" ) {

    cop3530::CBL<int> * cbl_list_iter = new cop3530::CBL<int> ();

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

	delete [] temp_contents;
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

    delete [] temp_contents;
    delete cbl_list_iter;

}

TEST_CASE ( "SSLL Print" ) {

	cop3530::SSLL<int> * ssll_list = new cop3530::SSLL<int> ();

	std::ostringstream out_file_1;
	ssll_list->print(out_file_1);
	std::string in_file_1 = out_file_1.str();

	REQUIRE_THAT ( in_file_1 , EndsWith("<empty list>") );

	for (int i = 0; i < 100; ++i)
        ssll_list->push_front(i + 1);

    std::ostringstream out_file_2;
    ssll_list->print(out_file_2);
	std::string in_file_2 = out_file_2.str();

    REQUIRE_THAT ( in_file_2 , EndsWith("5,4,3,2,1>") );

	ssll_list->pop_back();
	ssll_list->pop_front();

	std::ostringstream out_file_3;
    ssll_list->print(out_file_3);
	std::string in_file_3 = out_file_3.str();

	 REQUIRE_THAT ( in_file_3 , StartsWith("<99,98,97,96,95,94") );

	 delete ssll_list;

}

TEST_CASE ( "PSLL Print" ) {

	cop3530::PSLL<int> * psll_list = new cop3530::PSLL<int> ();

	std::ostringstream out_file_1;
	psll_list->print(out_file_1);
	std::string in_file_1 = out_file_1.str();

	REQUIRE_THAT ( in_file_1 , EndsWith("<empty list>") );

	for (int i = 0; i < 100; ++i)
        psll_list->push_front(i + 1);

    std::ostringstream out_file_2;
    psll_list->print(out_file_2);
	std::string in_file_2 = out_file_2.str();

    REQUIRE_THAT ( in_file_2 , EndsWith("5,4,3,2,1>") );

	psll_list->pop_back();
	psll_list->pop_front();

	std::ostringstream out_file_3;
    psll_list->print(out_file_3);
	std::string in_file_3 = out_file_3.str();

	 REQUIRE_THAT ( in_file_3 , StartsWith("<99,98,97,96,95,94") );

	 delete psll_list;

}

TEST_CASE ( "SDAL Print" ) {

	cop3530::SDAL<int> * sdal_list = new cop3530::SDAL<int> (100);

	std::ostringstream out_file_1;
	sdal_list->print(out_file_1);
	std::string in_file_1 = out_file_1.str();

	REQUIRE_THAT ( in_file_1 , EndsWith("<empty list>") );

	for (int i = 0; i < 100; ++i)
        sdal_list->push_front(i + 1);

    std::ostringstream out_file_2;
    sdal_list->print(out_file_2);
	std::string in_file_2 = out_file_2.str();

    REQUIRE_THAT ( in_file_2 , EndsWith("5,4,3,2,1>") );

	sdal_list->pop_back();
	sdal_list->pop_front();

	std::ostringstream out_file_3;
    sdal_list->print(out_file_3);
	std::string in_file_3 = out_file_3.str();

	 REQUIRE_THAT ( in_file_3 , StartsWith("<99,98,97,96,95,94") );

	 delete sdal_list;

}

TEST_CASE ( "CDAL Print" ) {

	cop3530::CDAL<int> * cdal_list = new cop3530::CDAL<int> ();

	std::ostringstream out_file_1;
	cdal_list->print(out_file_1);
	std::string in_file_1 = out_file_1.str();

	REQUIRE_THAT ( in_file_1 , EndsWith("<empty list>") );

	for (int i = 0; i < 100; ++i)
        cdal_list->push_front(i + 1);

    std::ostringstream out_file_2;
    cdal_list->print(out_file_2);
	std::string in_file_2 = out_file_2.str();

    REQUIRE_THAT ( in_file_2 , EndsWith("5,4,3,2,1>") );

	cdal_list->pop_back();
	cdal_list->pop_front();

	std::ostringstream out_file_3;
    cdal_list->print(out_file_3);
	std::string in_file_3 = out_file_3.str();

	REQUIRE_THAT ( in_file_3 , StartsWith("<99,98,97,96,95,94") );

	delete cdal_list;

}


TEST_CASE( "CBL CHAR" ) {

    cop3530::CBL<char> * cbl_list = new cop3530::CBL<char> ();

	cbl_list->push_back ('a');
	cbl_list->push_back ('b');
	cbl_list->push_back ('c');
	cbl_list->push_back ('d');
	cbl_list->push_back ('e');
	cbl_list->push_back ('f');
	cbl_list->push_back ('g');
	cbl_list->push_back ('h');
	cbl_list->push_back ('i');
	cbl_list->push_back ('j');

	REQUIRE (cbl_list->item_at(0) == 'a');
	REQUIRE (cbl_list->item_at(5) == 'f');
	REQUIRE (cbl_list->length() == 10);

	REQUIRE (cbl_list->remove(8) == 'i');
	REQUIRE (cbl_list->item_at(8) == 'j');
	try {
		cbl_list->remove(9);
	}
	catch (std::runtime_error e) {}

	cbl_list->push_front('z');
	REQUIRE (cbl_list->peek_front() == 'z');

	REQUIRE (!(cbl_list->contains('m', &equals)));
	REQUIRE (cbl_list->contains('a', &equals));

	char * temp_contents = cbl_list->contents();

	REQUIRE (temp_contents[0] == 'z');
	REQUIRE (temp_contents[0] == cbl_list->peek_front());
	REQUIRE (temp_contents[5] == cbl_list->item_at(5));

	delete [] temp_contents;
    delete cbl_list;

}

TEST_CASE ( "CBL COPY" ) {

    cop3530::CBL<int> * cbl_list = new cop3530::CBL<int> ();
    cbl_list->push_back (1);
	cbl_list->push_back (2);
	cbl_list->push_back (3);
	cbl_list->push_back (4);
	cbl_list->push_back (5);

    cop3530::CBL<int> * cbl_list_2 = cbl_list;

    for (int i = 0; i < cbl_list->length(); ++i)
        REQUIRE (cbl_list == cbl_list_2);

    delete cbl_list_2;

}

TEST_CASE ( "SSLL COPY" ) {

    cop3530::SSLL<int> * ssll_list = new cop3530::SSLL<int> ();
    ssll_list->push_back (1);
	ssll_list->push_back (2);
	ssll_list->push_back (3);
	ssll_list->push_back (4);
	ssll_list->push_back (5);

    cop3530::SSLL<int> * ssll_list_2 = ssll_list;

    for (int i = 0; i < ssll_list->length(); ++i)
        REQUIRE (ssll_list == ssll_list_2);

    delete ssll_list_2;

}

TEST_CASE ( "PSLL COPY" ) {

    cop3530::PSLL<int> * psll_list = new cop3530::PSLL<int> ();
    psll_list->push_back (1);
	psll_list->push_back (2);
	psll_list->push_back (3);
	psll_list->push_back (4);
	psll_list->push_back (5);

    cop3530::PSLL<int> * psll_list_2 = psll_list;

    for (int i = 0; i < psll_list->length(); ++i)
        REQUIRE (psll_list == psll_list_2);

    delete psll_list_2;

}

TEST_CASE ( "SDAL COPY" ) {

    cop3530::SDAL<int> * sdal_list = new cop3530::SDAL<int> ();
    sdal_list->push_back (1);
	sdal_list->push_back (2);
	sdal_list->push_back (3);
	sdal_list->push_back (4);
	sdal_list->push_back (5);

    cop3530::SDAL<int> * sdal_list_2 = sdal_list;

    for (int i = 0; i < sdal_list->length(); ++i)
        REQUIRE (sdal_list == sdal_list_2);

    delete sdal_list_2;

}

TEST_CASE ( "CDAL COPY" ) {

    cop3530::CDAL<int> * cdal_list = new cop3530::CDAL<int> ();
    cdal_list->push_back (1);
	cdal_list->push_back (2);
	cdal_list->push_back (3);
	cdal_list->push_back (4);
	cdal_list->push_back (5);

    cop3530::CDAL<int> * cdal_list_2 = cdal_list;

    for (int i = 0; i < cdal_list->length(); ++i)
        REQUIRE (cdal_list == cdal_list_2);

    delete cdal_list_2;

}

