#include "ADT.h"
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CDAL.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace cop3530;

int main()
{
    ///CONTENT
//    cop3530::SSLL<int> * ssll = new cop3530::SSLL<int> (100);
//ssll->push_back(5);
   // cout << ssll->contains(5);


    ///SSAL
    cop3530::SSLL<int> * list = new cop3530::SSLL<int> (5);
    list->push_back(5);
    list->push_back(3);
    list->push_front(4);
    list->shitPrint();
    cout << list->contains(70);
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

    return 0;
}
