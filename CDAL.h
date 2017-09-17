#ifndef CDAL_H
#define CDAL_H
#include "ADT.h"

#include <iostream>

namespace cop3530 {

template <class element>

class CDAL : public ADT<element>
{
    public:
        CDAL();
        virtual ~CDAL();
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
        //Will allocate a new array if full
        void allocate_new();
        //Will deallocate memory when more than half of the arrays are unused
        void deallocate_old();
        //Determines if two elements are equal
        bool equals(element a, element b);

    private:

        struct Node {
            element * list;
            Node * next;
        };
        //Keeps track of the tail in any array
        int tail;
        Node * data;
        const int array_size = 50;
        //Keeps track of the number of unused arrays
        int unused_arrays = 0;

};
}

template <class element>
//Constructor, initializes one node and its array with 50 slots
cop3530::CDAL<element>::CDAL() {
    data = new Node();
    data->list = new element[array_size];
    tail = -1;
    data->next = NULL;
}
template <class element>
//Destructor, traverses through each node and deletes its array
cop3530::CDAL<element>::~CDAL() {
    //Delete each array in each Node and it's respective Node
    Node * temp = data;
    while (temp) {
        delete [] data->list;
        data = temp->next;
        temp = temp->next;
    }
    delete temp;
    delete data;
}
template <class element>
//Inserts element at a certain position
void cop3530::CDAL<element>::insert(element object, int position) {
  //If the list is full allocate a new Node with an array that fits 50 items
    if (position > length())
         throw std::runtime_error ("Not a valid position.\n ");

    //This will be the new array with the added elements
    element * values = new element[length() + 1];
    //Get old array
    element * curr = contents();
    //Copy values from current into new array and insert the new value
    for (int i = 0; i < length() + 1; ++i) {
        if (i < position - 1)
            values[i] = curr[i];
        else if (i == position - 1)
            values[i] = object;
        else
            values[i] = curr[i - 1];
    }

    size_t size = length() + 1;
    //Push back all of the new elements into the new list
    clear();
    for (int i = 0; i < size; ++i) {
       push_back(values[i]);
    }

}
template <class element>
//Inserts element at the back of the list
void cop3530::CDAL<element>::push_back (element object) {
    //If the list is full allocate a new Node with an array that fits 50 items
    if (is_full())
        allocate_new();
    //Move tail pointer to correct new index
    if (tail == 49) {
        tail = 0;
        if (unused_arrays > 0)
            --unused_arrays;
    }
    else
        ++tail;

    Node * temp = data;
    while (temp) {
        if (!(temp->next)) {
            temp->list[tail] = object;
        }
        temp = temp->next;
    }

}
template <class element>
//Inserts element at the front of the list
void cop3530::CDAL<element>::push_front (element object) {
    //If the list is full allocate a new Node with an array that fits 50 items
    if (is_full()) {
        allocate_new();
    }
    Node * curr = data;
    //Will keep track of the last index in the previous array
    element temp;
    //Will keep track of the last index in the current array
    element last_temp;
    if (tail == 49) {
        tail = 0;
        if (unused_arrays > 0)
            --unused_arrays;
    }
    else
        ++tail;
    while (curr) {

        if (!(curr->next)) {

             for (int i = tail; i >= 0; --i) {
                 curr->list[i] = curr->list[i - 1];
             }
             if (curr == data)
                curr->list[0] = object;
             else
                curr->list[0] = temp;
            curr = curr->next;
        }
        else {
            if (data == curr) {
                temp = curr->list[array_size - 1];
                for (int i = array_size - 1; i >= 0; --i)
                    curr->list[i] = curr->list[i - 1];
                curr->list[0] = object;
            }
            else {
                for (int i = array_size - 1; i >= 0; --i) {
                    //Save the last element so we can later replace the first index with temp and
                    //fill temp with this new last_temp
                    if (i == array_size - 1)
                        last_temp = curr->list[i];
                    curr->list[i] = curr->list[i - 1];
                }
                curr->list[0] = temp;
                temp = last_temp;
            }
            curr = curr->next;
        }
    }

}
template <class element>
//Replaces an element at the specified index
void cop3530::CDAL<element>::replace (element object, int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot replace.\n ");
    if (position > length())
         throw std::runtime_error ("Not a valid position.\n ");
    Node * temp = data;
    while (temp) {
        //If the desired element is in another node, go to the next node and decrease the position index
        //to match the appropriate node array index
        if (position > 50) {
            temp = temp->next;
            position -=50;
        }
        else {
            temp->list[position - 1] = object;
            break;
        }
    }
}
template <class element>
//Removes an element at the specified position and moves all the succeeding elements up the list by one
void cop3530::CDAL<element>::remove (int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot replace.\n ");
    if (position > length())
         throw std::runtime_error ("Not a valid position.\n ");

    if (position == length()) {
        pop_back();
        return;
    }
    if (position == 1) {
        pop_front();
        return;
    }
    //Increase the number of unused arrays
    if (!tail)
        ++unused_arrays;
    size_t temp_unused = unused_arrays;
    //This will be the new array with the added elements
    element * values = new element[length() - 1];
    //Get old array

    element * curr = contents();
    //Copy values from current into new array and insert the new value
    for (int i = 0; i < length() - 1; ++i) {
        if (i < position - 1)
            values[i] = curr[i];
        else if (i >= position - 1)
            values[i] = curr[i + 1];
    }

    size_t size = length() - 1;
    //Push back all of the new elements into the new list
    clear();
    for (int i = 0; i < size; ++i) {
       push_back(values[i]);
    }

    //Deallocate unused arrays if condition holds
    deallocate_old();
}
template <class element>
//Removes and returns an element from the back of the list
element cop3530::CDAL<element>::pop_back () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop at the back.\n ");
    Node * temp = data;
    element last;
    while (temp) {
        if (!(temp->next)) {
            last = temp->list[tail];
            if (tail || temp == data) {
                --tail;
                break;
            }
            else {
                tail = 49;
                ++unused_arrays;
                temp = NULL;
                break;
            }
        }
        temp = temp->next;
    }
    //Deallocate unused arrays if condition holds
    deallocate_old();
    return last;

}
template <class element>
//Removes and returns an element from the front of the list, moving all the succeeding element up the list by one
element cop3530::CDAL<element>::pop_front () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop at the front.\n ");
    element front = data->list[0];
    Node * temp;
    Node * curr = data;
    while (curr) {
        if (curr == data) {
            for (int i = 0; i < array_size; ++i) {
                curr->list[i] = curr->list[i + 1];
            }
            temp = data;
            curr = curr->next;
        }
        else {
            temp->list[array_size - 1] = curr->list[0];
            for (int i = 0; i < array_size; ++i) {
                curr->list[i] = curr->list[i + 1];
            }
            temp = curr;
            curr = curr->next;
        }
    }
    if (tail == 0) {
        tail = array_size - 1;
        ++unused_arrays;
    }
    else
        --tail;
    //Deallocate unused arrays if condition holds
    deallocate_old();
    return front;
}
template <class element>
//Returns the item at the specified index
element cop3530::CDAL<element>::item_at (int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, there are no elements.\n ");
    if (position - 1 < 0 || position > length())
        throw std::runtime_error ("Not a valid position.\n ");
    int current_index = 0;
    Node * temp = data;
    while (temp) {
        if (position > array_size) {
            temp = temp->next;
            position -= 50;
        }
        else {
            return temp->list[position - 1];
        }
    }

}
template <class element>
//Returns the element at the back of the list
element cop3530::CDAL<element>::peek_back () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot peek back.\n ");
    Node * temp = data;
    while (temp) {
        if (!(temp->next)) {
            return temp->list[tail];
        }
        temp = temp->next;
    }
}
template <class element>
//Returns the element at the front of the list
element cop3530::CDAL<element>::peek_front () {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek front.\n ");
    return data->list[0];
}
template <class element>
//Returns whether the list is empty
bool cop3530::CDAL<element>::is_empty () {
    return (tail == -1 && !(data->next));
}
template <class element>
//Returns whether the list is full
bool cop3530::CDAL<element>::is_full () {
    return (tail + 1 == array_size);
}
template <class element>
//Returns the length of the elements in the list
size_t cop3530::CDAL<element>::length () {
    int len = 0;
    Node * temp = data;
    while (temp) {
        if (!(temp->next)) {
            len += tail + 1;
            break;
        }
        temp = temp->next;
        len += 50;
    }
/*    if (unused_arrays) {
        int temp_unused = unused_arrays;
        while (temp_unused > 0) {
            len -= 50;
            --temp_unused;
        }
    } */
    return len;
}
template <class element>
//Clears the array of all its values
void cop3530::CDAL<element>::clear () {
    //Delete each array in each Node and it's respective Node
    delete [] data;
    data = NULL;
    //Make a new list with data pointing to it
    data = new Node();
    data->list = new element[array_size];
    tail = -1;
    data->next = NULL;
    unused_arrays = 0;
}
///ERASE
template <class element>

void cop3530::CDAL<element>::shitPrint() {
    Node * temp = data;
    int index = 1;
    while (temp) {
        std::cout << "\n----------- NODE " << index << " --------------\n" << std::endl;
        for (int i = 0; i < array_size; ++i)
            std::cout << temp->list[i] << "    ";
        ++index;
        temp = temp->next;
    }
    std::cout << std::endl;
}
template <class element>
//Returns whether the list contains the specified value
bool cop3530::CDAL<element>::contains (element object, bool (*equals_function) (element, element)) {
    if (is_empty())
        return false;
    Node * temp = data;
    while (temp) {
        //If the last node
        if (!(temp->next)) {
            for (int i = 0; i < tail - 1; ++i)
                if (equals_function(object, temp->list[i])) return true;
        }
        else {
            for (int i = 0; i < array_size; ++i)
                if (equals_function(object, temp->list[i])) return true;
        }
        temp = temp->next;
    }
    return false;
}
template <class element>
//Returns whether two elements are equal
bool cop3530::CDAL<element>::equals(element a, element b) {
    return (a == b ? true : false);
}

template <class element>
//Prints out the contents of the list to the ostream
std::ostream& cop3530::CDAL<element>::print (std::ostream& out) {
    if (is_empty())
        out << "<empty list>";
    else {
        out << "<";
        //Copy contents of array
        element * arr = contents();
        for (int i = 0; i < length(); ++i) {
            if (i == length() - 1)
                out << arr[i];
            else
                out << arr[i] << ",";
        }
        out << ">";
    }
    return out;
}
template <class element>
//Returns the contents of the list
element * cop3530::CDAL<element>::contents() {
    if (is_empty())
        throw std::runtime_error("The list is empty, there are no elements.\n ");
    element * values = new element[length()];
    int current_index = 0;
    Node * curr = data;
    while (curr) {
        if (!(curr->next)) {
            for (int i = 0; i <= tail; ++i, ++current_index)
                values[current_index] = curr->list[i];
            break;
        }
        else {
            for (int i = 0; i < array_size; ++i, ++current_index)
                values[current_index] = curr->list[i];
        }
        curr = curr->next;
    }
    return values;
}
template <class element>
//Allocates a new array is full
void cop3530::CDAL<element>::allocate_new(){
    Node * new_node = new Node();
    new_node->list = new element[array_size];
    Node * curr = data;
    while (curr) {
        if (!(curr->next)) {
            curr->next = new_node;
            break;
        }
        curr = curr->next;
    }
}
template <class element>
//Deallocated half the arrays when more than half are unused
void cop3530::CDAL<element>::deallocate_old() {
    size_t total_arrays = 0;
    Node * temp = data;
    //Get the total number of arrays
    while (temp) {
        ++total_arrays;
        temp = temp->next;
    }
    size_t half_total = size_t(total_arrays / 2 + 0.5);
    size_t to_deallocate = size_t(unused_arrays / 2 + 0.5);
    size_t temp_length = length();

    //See if more than half of the arrays are unused
    if (half_total < unused_arrays) {
        element * temp = contents();
        //Clear the current list to make a new one
        clear();
        for (int i = 0; i < temp_length; ++i)
            push_back(temp[i]);
        //Deallocate half of unused arrays
        while (to_deallocate > 0) {
            allocate_new();
            --to_deallocate;
        }
    }
}

#endif // CDAL_H