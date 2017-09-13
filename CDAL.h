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
        bool contains (element object, const std::type_info& type) override;
        std::ostream& print (std::ostream& out) override;
        element * contents() override;
        //Will allocate a new array if full
        void allocate_new();
    private:

        struct Node {
            element * list;
            Node * next;
        };
        //Keeps track of the tail in any array
        int tail;
        Node * data;
        const int array_size = 50;

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
        delete data;
        data = temp->next;
    }
    delete temp;
}
template <class element>
//Inserts element at a certain position
void cop3530::CDAL<element>::insert(element object, int position) {
}
template <class element>
//Inserts element at the back of the list
void cop3530::CDAL<element>::push_back (element object) {
    //If the list is full allocate a new Node with an array that fits 50 items
    if (is_full()) {
        allocate_new();
    }
    //Move tail pointer to correct new index
    if (tail == 49)
        tail = 0;
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
    if (tail == 49)
        tail = 0;
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

    //Keeps track of the current Node
    Node * curr = data;
    //Keeps track of the previous Node
    Node * temp;
    element last_temp;

    if (position > 50) {
        while (position > 50) {
            curr = curr->next;
            position -=50;
        }
    }
    while (curr) {
        //Move all the elements up by one
        if (curr == data) {
            for (int i = position - 1; i < array_size; ++i) {
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
    --tail;
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
                temp = NULL;
                break;
            }
        }
        temp = temp->next;
    }
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
    if (tail == 0)
        tail = array_size - 1;
    else
        --tail;
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
    std::cout << "LENGTH: " << len << std::endl;
    return len;
}
template <class element>
//Clears the array of all its values
void cop3530::CDAL<element>::clear () {
    //Delete each array in each Node and it's respective Node
    Node * temp = data;
    while (temp) {
        delete [] data->list;
        delete data;
        data = temp->next;
    }
    delete temp;
    CDAL();
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
template <class element> ///DO THIS FOR ALL
//Returns whether the list contains the specified value
bool cop3530::CDAL<element>::contains (element object, const std::type_info& type) {
}
template <class element>
//Prints out the contents of the list to the ostream
std::ostream& cop3530::CDAL<element>::print (std::ostream& out) {
    if (is_empty())
        out << "<empty list>";

    out << "<";
    Node * temp = data;
    while (temp) {
        if (!(temp->next)) {
            for (int i = 0; i <= tail; ++i) {
                if (i == tail)
                    out << temp->list[i];
                else
                    out << temp->list[i] << ",";
            }
            break;
        }
        else {
            for (int i = 0; i < array_size; ++i) {
                out << temp->list[i] << ",";
        }
    }
    temp = temp->next;
    }
    out << ">";
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

#endif // CDAL_H
