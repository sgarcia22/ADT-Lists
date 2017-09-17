#ifndef SDAL_H
#define SDAL_H
#include "ADT.h"

#include <iostream>

namespace cop3530 {

template <class element>

class SDAL : public ADT<element>
{
    public:
        SDAL(size_t inputSize = 50);
        virtual ~SDAL();
        void insert(element object, int position) override;
        void push_back (element object) override;
        void push_front (element object) override;
        void replace (element object, int position) override;
        void remove (int position) override;
        element pop_back () override;
        element pop_front () override;
        element item_at (int position) override;
        element peek_back () override;
        element peek_front () override;
        bool is_empty () override;
        bool is_full () override;
        size_t length () override;
        void clear () override;
        void shitPrint(); ///ERASE
        bool contains (element object, bool (*equals_function) (element, element)) override;
        std::ostream& print (std::ostream& out) override;
        element * contents() override;
        void allocate_new();

    private:

        element * data;
        int tail;
        element * list;
        int max_size;
        //Keeps track of the initial size
        int initial_size;

};
}

template <class element>
//Constructor, initializes array
cop3530::SDAL<element>::SDAL(size_t inputSize) {

    max_size = inputSize;
    initial_size = inputSize;
    //Setting tail to -1 because it is accessed through index
    tail = -1;
    list = new element [max_size];
    data = list;

}
template <class element>
//Destructor, deallocates array and pointer
cop3530::SDAL<element>::~SDAL() {
    delete [] list;
    delete data;
}
template <class element>
//Inserts element at a certain position
void cop3530::SDAL<element>::insert(element object, int position) {
    if (is_full())
        allocate_new();
    if (position > max_size)
        throw std::runtime_error("Not a valid position.\n ");
    if (position > length()) {
        push_back(object);
        return;
    }
    if (position == 1) {
        push_front(object);
        return;
    }

    for (int i = length(); i > 0; --i) {
        if (i + 1 >= position) {
            list[i] = list[i - 1];
        }
    }
    list[position - 1] = object;
    ++tail;
}
template <class element>
//Inserts element at the back of the list
void cop3530::SDAL<element>::push_back (element object) {
    if (is_full())
        allocate_new();
    ++tail;
    list[tail] = object;
}
template <class element>
//Inserts element at the front of the list
void cop3530::SDAL<element>::push_front (element object) {
    if (is_full())
        allocate_new();
    if (!is_empty()) {
        for (int i = length(); i >= 0; --i) {
            list[i] = list[i - 1];
        }
    }
    list[0] = object;
    ++tail;
}
template <class element>
//Replaces an element at the specified index
void cop3530::SDAL<element>::replace (element object, int position) {
    if (position > max_size)
        throw std::runtime_error("Not a valid position.\n ");
    if (position - 1 > tail)
        throw std::runtime_error("No element at that position to replace.\n ");
    list[position - 1] = object;
}
template <class element>
//Removes an element at the specified position and moves all the succeeding elements up the list by one
void cop3530::SDAL<element>::remove (int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot remove an element.\n ");
    if (position > max_size)
        throw std::runtime_error("Not a valid position.\n ");
    if (position - 1 > tail)
        throw std::runtime_error("No element at that position to remove.\n ");
    for (int i = position - 1; i < length(); ++i)
        list[i] = list[i + 1];
    --tail;
    allocate_new();
}
template <class element>
//Removes and returns an element from the back of the list
element cop3530::SDAL<element>::pop_back () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop.\n ");
    element temp = list[tail];
    --tail;
    allocate_new();
    return temp;
}
template <class element>
//Removes and returns an element from the front of the list, moving all the succeeding element up the list by one
element cop3530::SDAL<element>::pop_front () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop.\n ");
    element temp = list[0];
    for (int i = 0; i < length(); ++i)
        list[i] = list[i + 1];
    tail--;
    allocate_new();
    return temp;

}
template <class element>
//Returns the item at the specified index
element cop3530::SDAL<element>::item_at (int position) {
    if (position > max_size)
        throw std::runtime_error("Not a valid position.\n ");
    if (position - 1 > tail)
        throw std::runtime_error("No element at that position.\n ");
    return list[position - 1];
}
template <class element>
//Returns the element at the back of the list
element cop3530::SDAL<element>::peek_back () {
    return list[tail];
}
template <class element>
//Returns the element at the front of the list
element cop3530::SDAL<element>::peek_front () {
    return list[0];
}
template <class element>
//Returns whether the list is empty
bool cop3530::SDAL<element>::is_empty () {
    return (tail == -1);
}
template <class element>
//Returns whether the list is full
bool cop3530::SDAL<element>::is_full () {
    return (tail + 1 == max_size);
}
template <class element>
//Returns the length of the elements in the list
size_t cop3530::SDAL<element>::length () {
    return tail + 1;
}
template <class element>
//Clears the array of all its values
void cop3530::SDAL<element>::clear () {
    tail = -1;
    delete [] list;
    list = new element [initial_size];
    data = list;
    max_size = initial_size;

}
///ERASE
template <class element>

void cop3530::SDAL<element>::shitPrint() {
    for (int i = 0; i < max_size; ++ i) {
        if (i + 1 > length())
            std::cout << 0 << "    ";
        else
            std::cout << list[i] << "   ";
    }
    std::cout << "TAIL: " << tail << std::endl;
    std::cout << "SIZE: " << max_size << std::endl;
}
template <class element>
//Returns whether the list contains the specified value
bool cop3530::SDAL<element>::contains (element object, bool (*equals_function) (element, element)) {
    if (is_empty())
        return false;
    for (int i = 0; i < length(); ++i) {
        if (equals_function(object, list[i]))
            return true;
    }
    return false;

}
template <class element>
//Prints out the contents of the list to the ostream
std::ostream& cop3530::SDAL<element>::print (std::ostream& out) {
    if (is_empty())
        out << "<empty list>";
    else {
        out << "<";
        for (int i = 0; i < length(); ++i) {
            if (i == length() - 1)
                out << list[i];
            else
                out << list[i] << ",";
        }
        out << ">";
    }
    return out;
}
template <class element>
//Returns the contents of the list
element * cop3530::SDAL<element>::contents() {
    if (is_empty())
        throw std::runtime_error("The list is empty, there are no elements.\n ");
    element * values = new element[length() - 1];
    for (int i = 0; i < length(); ++i)
        values[i] = list[i];
    return values;
}
template <class element>
//Allocate a new array is the current one is using too much or too little memory
void cop3530::SDAL<element>::allocate_new() {
    if (is_full()) {
        int new_size = int(max_size  * 1.5 + 0.5);
        element * temp = new element [new_size];
        for (int i = 0; i < max_size; ++i)
            temp[i] = list[i];
        delete [] list;
        list = temp;
        max_size = new_size;
    }
    if (max_size >= 100 && ((max_size / 2) > length())) {
        int new_size = int(max_size  * .75 + 0.5);
        element * temp = new element [new_size];
        for (int i = 0; i < new_size; ++i)
            temp[i] = list[i];
        delete [] list;
        list = temp;
        max_size = new_size;
    }
}


#endif // SDAL_H
