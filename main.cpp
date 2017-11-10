#include "ADT.h"
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace cop3530;

template <typename element>
//For the contains function
bool equals(element a, element b) {
    return a == b;
}

int main()
{
     /*cout << "\n--------------SDAL ----------------\n";
    ///SDAL
    cop3530::SDAL<int> * list4 = new cop3530::SDAL<int> (101);
    for (int i = 1 ; i <= 101; ++i)
        list4->push_back(i);

    int index4 = 0;
    for (cop3530::SDAL<int>::iterator i = list4->begin(); i != list4->end(); ++i) {
        std::cout << *i << "  ";
        index4++;
    }
    cout << "\n INDEX: " << index4 << endl;
    ///CONTENT
//    cop3530::SSLL<int> * ssll = new cop3530::SSLL<int> (100);
//ssll->push_back(5);
   // cout << ssll->contains(5);
  cout << "\n--------------SSLL ----------------\n";

    ///SSLL
    cop3530::SSLL<int> * list = new cop3530::SSLL<int> (101);
    ///ERROR --- FIX
    for (int i = 1 ; i <= 101; ++i)
        list->push_back(i);

   int index = 0;
   // cop3530::SSLL<int>::iterator i = list->begin();
//    cout << *i << endl;
    for (cop3530::SSLL<int>::iterator i = list->begin(); i != list->end(); ++i) {
        std::cout << *i << "  ";
        index++;
    }
    cout << "\n INDEX: " << index << endl;
*/
   /*   ///PSLL
      cout << "\n--------------PSLL ----------------\n";
    cop3530::PSLL<int> * list2 = new cop3530::PSLL<int> (250);
    for (int i = 1 ; i <= 200; ++i)
        list2->push_front(i);
    list2->shitPrint();
    list2->poolPrint();

     for (int i = 1 ; i <= 20; ++i)
        list2->pop_back();
     list2->shitPrint();
     list2->poolPrint();*/
  /*  for (int i = 1 ; i <= 10; ++i)
        list2->push_front(i);
    list2->shitPrint();
    list2->insert(5, 5);
   list2->shitPrint();
    list2->replace(4, 5);
    list2->shitPrint();
        list2->poolPrint();
    list2->remove(4);
  list2->shitPrint();
    list2->poolPrint();
    list2->push_front(9);
   list2->shitPrint();
    list2->poolPrint(); ///FIX THE POOL -> PUSH FRONT AINT WORKING */

   //  list2->shitPrint();
   //  list2->poolPrint();

  //   list2->shitPrint();
  //  list2->poolPrint();

   //  list2->shitPrint();
   //  list2->poolPrint();
   /* for (int i = 1 ; i <= 101; ++i)
        list2->push_back(i);

   int index2 = 0;

    for (cop3530::PSLL<int>::iterator i = list2->begin(); i != list2->end(); ++i) {
        std::cout << *i << "  ";
        index2++;
    }
    cout << "\n INDEX: " << index2 << endl;*/
/*
    ///CDAL
      cout << "\n--------------CDAL ----------------\n";
    cop3530::CDAL<int> * list3 = new cop3530::CDAL<int> ();
       for (int i = 1 ; i <= 101; ++i)
        list3->push_back(i);

   int index3 = 0;

    cop3530::CDAL<int>::iterator i = list3->begin();
    for (; index3 < 101; ++index3, ++i) {
         std::cout << *i << "  ";
    }
    for (cop3530::CDAL<int>::iterator i = list3->begin(); i != list3->end(); ++i) {
        std::cout << *i << "  ";
        index3++;
    }
   cout << "\n INDEX: " << index3 << endl; */


   // list->test = &(list->equals);
  //  list->contains(5, list->test);
    //list->a_pointer = &(list->equals());
    //(list->contains(5, list->*equals)(5, 6));
 /*
    cop3530::SSLL<string> * list = new cop3530::SSLL<string> (5);
    list->push_back("hi");
    list->push_back("name");
    list->push_front("sam");
    cout << "PEEK FRONT: " << list->peek_front() << endl;
    cout << "PEEK BACK: " << list->peek_back() << endl;
    list->shitPrint();
    cout << "POP FRONT: " << list->pop_front() << endl;
        list->shitPrint();
    cout << "POP back: " << list->pop_back() << endl;
        list->shitPrint();
      cout << "length: " << list->length() << endl;
      cout << "item at: " << list->item_at(0) << endl;
    list->remove(0);
     list->shitPrint();

      list->push_back("hi");
    list->push_back("name");
    list->push_front("sam");
    list->clear();
     list->shitPrint();


      list->push_back("hi");
    list->push_back("name");
    list->push_front("sam");
 list->shitPrint();
    list->remove(1);
    cout << endl;
    list->shitPrint();

    list->remove(1);
    list->shitPrint();

    list->replace("fuck" ,0);
     list->shitPrint();

      list->push_back("hi");
    list->push_back("name");
    list->push_front("sam");
     list->shitPrint();
    list->replace("shitt",3);
         list->shitPrint();

         list->insert("want", 1);
             list->shitPrint();


         list->insert("shit", 3);
             list->shitPrint();

    string * aray = new string [list->length()];
    aray = list->contents();
    cout << aray[0] << aray[1] << aray[2];

    std::ofstream outFile("shit.txt");
    list->print(outFile);

    list->clear();
    std::ofstream outi("test.txt");
    list->print(outi);

      list->push_back("hi");
    cout << list->contains("hi", typeid("sam")); */
    ///PSAL
/*
   cop3530::PSLL<string> * list = new cop3530::PSLL<string> (300);
    list->poolPrint();
    for (int i = 0; i < 100; ++i)
        list->push_front("why");
 list->poolPrint();
 list->shitPrint(); */
  /*  list->push_front("why");

    list->push_front("why");

    list->shitPrint();
    list->poolPrint();

    cout << "Popping Back: " << list->pop_front() << endl;

    list->shitPrint();
    list->poolPrint(); */

  // cout << list->is_empty() << endl;
   // cout << list->is_full() << endl;
  /* list->push_front("hi");
  // cout << list->is_empty() << endl;
  //  cout << list->is_full() << endl;
   list->push_front("why");
    list->push_back("ayas");
    cout << "Inserting : 0\n";
   list->insert("inserting", 0);
   list->replace("not inserting", 0);
     list->shitPrint();
   list->remove(3);
  list->poolPrint();
  cout << endl;
    cout << list->item_at(3) << endl;;
  list->shitPrint(); */
   /* cop3530::SSLL<int> * ssll = new cop3530::SSLL<int> (100);
   cop3530::SDAL<int> * sdal = new cop3530::SDAL<int>(100);
   cop3530::PSLL<int> * psll = new cop3530::PSLL<int> (100);
   for (int i = 0; i < 100; ++i) {
        ssll->push_back(i);
    sdal->push_back(i);
    psll->push_back(i);
   }
   sdal->remove(10);
   psll->remove(10);
   ssll->remove(10);
   sdal->shitPrint();
   psll->shitPrint();
    ssll->shitPrint();
  ///SDAL
 /* cop3530::SDAL<int> * list = new cop3530::SDAL<int>(100);

    list->shitPrint();
   list->push_back(4);
      list->shitPrint();
    list->push_front(5);
     list->push_front(3);
      list->push_front(1);
        list->push_front(1);

        list->shitPrint();
        cout << endl;
        list->allocate_new();*?

      //  list->shitPrint();
    /*  std::ofstream outFile("SDALTest.txt");
      list->print(outFile);
      int * arrayy = list->contents();
      cout << arrayy[3] << endl; */
      /* list->shitPrint();
       list->pop_back();
            list->shitPrint();
            list->pop_front();
            list->shitPrint();
        cout << "item at: 2 " << list->item_at(2) << endl;
           cout << "peek front" << list->peek_front() << endl;
             cout << "peek back" << list->peek_back() << endl;
               list->pop_back();
        list->clear();
 list->shitPrint(); */
/*  list->push_front(5);
  list->push_front(3);
 list->push_back(5);
 list->shitPrint();
list->insert(50, 2);
list->insert(50, 5);
list->replace(45, 5);
list->replace(5, 1);
list->replace(10, 3);
cout << endl;
 list->shitPrint();
 list->remove(5);
 cout << endl;
 list->shitPrint();*/
/*
 ///CDAL
    cop3530::CDAL<int> * list = new cop3530::CDAL<int>();
    for (int i = 1; i<= 100; ++i)
        list->push_back(i);

       // list.functor;
       // bool yes = functor(5, 5);

 // int * p = &list->equals;
  list->contains(4, (list->*equals()));
  /*  list->insert(30, 51);
    list->insert(79, 1);
  //  list->shitPrint();
  //  cout << list->item_at(51) << endl;
    list->remove(1);
  //   list->shitPrint();
     list->remove(51);
   //   list->shitPrint();
   // cout << list->length();
   // cout << endl;
 /*   for (int i = 1; i<=100; ++i)
        list->pop_front();
    list->shitPrint();
    list->deallocate_old();
    list->shitPrint();*/
   // cout << endl;
  //  cout << list->length();
  /*  int * arr = list->contents();
    for (int i = 0; i< list->length(); ++i)
        cout << arr[i] << "    ";
    cout << endl;
   std::ofstream outFile("CDALTest.txt");
      list->print(outFile); */
  //   cout<< list->length() << endl;;
 //   list->deallocate_old();

  /*  list->shitPrint();
    list->insert(30,51);
    list->insert(79,1);
    list->shitPrint();
    cout << endl;
    cout << list->length() << endl;
    cout << endl;
    cout << list->item_at(52) << "   " << list->item_at(102);
    list->remove(1);
     cout << list->length() << endl;
    list->shitPrint();
    list->remove(51);
     cout << list->length() << endl;
    list->shitPrint(); */

 /*   list->length();
    list->allocate_new();
    cout << endl;
    list->length();
    list->allocate_new();
    cout << endl;
    list->length();
    cout << endl;
    list->shitPrint(); */

   // cout << endl;
 /*   int number = 1;
    for (int i = 0; i < 150; ++i, ++number)
        list->push_back(number);

    //list->push_back(5);
  //  list->replace(6, 101);
    list->shitPrint();
    cout << endl;
    list->length();

    list->remove(51);
   // list->pop_front();

    list->shitPrint();
    cout << endl;
    list->length();

    std::ofstream outFile("CDALTest.txt");
      list->print(outFile);

      int * shit = list->contents();
       cout << shit[148]; */
  //  list->push_front(number);

/*    cout << endl;
    list->shitPrint();
    cout << endl;
    list->length();*/
  /*  list->pop_back();
    list->shitPrint();
    cout << endl;
    list->length();


    list->pop_front();
    list->shitPrint();
    cout << endl;
    list->length();*/

   // cout << endl;
  //  list->pop_front();
 //   list->shitPrint();
    //cout << list->peek_front();

/*    ///SDAL CHANGES
    cout << "\n--------------SDAL ----------------\n";

    cop3530::SDAL<int> * sdal_test = new cop3530::SDAL<int> (50);
    for (int i = 0; i < 100; ++i)
        sdal_test->push_front(i);
    sdal_test->shitPrint();

    for (int i = 0; i < 50; ++i)
        sdal_test->pop_back();
    sdal_test->shitPrint();
   /* sdal_test->pop_back();
    sdal_test->shitPrint();

    sdal_test->pop_front();
    sdal_test->shitPrint();*/

    cout << "\n--------------CDAL ----------------\n";

    int size = 0;

    cop3530::CDAL<int> * cdal_test = new cop3530::CDAL<int> ();
    for (int i = 0; i < 100; ++i)
        cdal_test->push_front(i + 5);

    for (cop3530::CDAL<int>::iterator it = cdal_test->begin(); it != cdal_test->end(); ++it) {
        std::cout << *it << "  ";
        ++size;
        if (!(size % 50))
            cout << endl;
    }
    cout<<endl;

    //cdal_test->shitPrint();

   /* cdal_test->insert(5, 100);
    //cdal_test->shitPrint();

    size = 0;
    for (cop3530::CDAL<int>::iterator it = cdal_test->begin(); it != cdal_test->end(); ++it) {
        std::cout << *it << "  ";
        ++size;
        if (!(size % 50))
            cout << endl;
    }
    cout<<endl;
    cdal_test->pop_back();
    //cdal_test->shitPrint();
*/

/*
 cdal_test->pop_back();
//For the contains function
bool equals(element a, element b) {
    return a == b;
}
    std::cout << "\nTAIL: " << cdal_test->tail << "\n";

    size = 0;
    for (cop3530::CDAL<int>::iterator it = cdal_test->begin(); it != cdal_test->end(); ++it) {
        std::cout << *it << "  ";
        ++size;
        if (!(size % 50))
            cout << endl;
    }
    cout<<endl;*/
    cout << "\n" << cdal_test->length() << endl;

    cdal_test->pop_back();

    std::cout << "\nTAIL: " << cdal_test->tail << "\n";

    size = 0;
    for (cop3530::CDAL<int>::iterator it = cdal_test->begin(); it != cdal_test->end(); ++it) {
        std::cout << *it << "  ";
        ++size;
        if (!(size % 50))
            cout << endl;
    }
    cout<<endl;

    cout << "\nUNUSED ARRAYS: " << cdal_test->unused_arrays << "\n";


 for (int i = 0; i < 10; ++i)
        cdal_test->push_front(i + 5);

    size = 0;
    for (cop3530::CDAL<int>::iterator it = cdal_test->begin(); it != cdal_test->end(); ++it) {
        std::cout << *it << "  ";
        ++size;
        if (!(size % 50))
            cout << endl;
    }
    cout<<endl;

    cdal_test->pop_front();
 size = 0;
    for (cop3530::CDAL<int>::iterator it = cdal_test->begin(); it != cdal_test->end(); ++it) {
        std::cout << *it << "  ";
        ++size;
        if (!(size % 50))
            cout << endl;
    }
    cout<<endl;

    cout<< endl;
    cout << cdal_test->peek_front() <<   endl;

    cout << cdal_test->contains(5005, &equals) << endl;



    cdal_test->remove(2);
     size = 0;
    for (cop3530::CDAL<int>::iterator it = cdal_test->begin(); it != cdal_test->end(); ++it) {
        std::cout << *it << "  ";
        ++size;
        if (!(size % 50))
            cout << endl;
    }

    return 0;
}
