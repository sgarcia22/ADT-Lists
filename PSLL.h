#ifndef PSLL_H
#define PSLL_H

#include <iostream>
#include <typeinfo>
///DEALLOCATE SHIT
namespace cop3530 {

template <class element>

class PSLL : public ADT<element>
{

    public:
        PSLL(size_t size);
        ~PSLL();
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
        void poolPrint(); ///ERASE
        bool contains (element object, const std::type_info& type) override;
        std::ostream& print (std::ostream& out) override;
        element * contents() override;
        //Function that will deallocate the free Nodes that are not being used
        void deallocateNodes();

    private:
        struct Node {
            element data;
            Node * next;
        };
        Node * head;
        Node * tail;
        Node ** pool;
        Node * poolHead;
        size_t pool_size;

};
}

template <class element>
//Constructor, initialize Nodes
cop3530::PSLL<element>::PSLL(size_t size) {
    //Set head and tail equal to null

    if (!size)
        throw std::runtime_error("List cannot have a zero size. ");

    head = NULL;
    tail = NULL;
    pool = new Node* [size];
    pool_size = size;

    Node * temp;
    //Allocate all of the free nodes
    for (int i = 0; i < pool_size; ++i) {
        pool[i] = new Node();
        if (i == 0) {
            poolHead = pool[i];
            temp = poolHead;
        }
        else {
            temp->next = pool[i];
            temp = temp->next;
        }
        if (i == pool_size - 1) {
            temp->next = NULL;
        }
    }

}

template <class element>
//Deallocate free Nodes
cop3530::PSLL<element>::~PSLL() {
     for (int i = 0; i < pool_size; ++i) {
        delete pool[i];
     }
     delete [] pool;
     delete poolHead;
     delete head;
     delete tail;

}

template <class element>
//Pushes an element to the front
void cop3530::PSLL<element>::push_front(element object) {

    if (!is_full()) {
        if (is_empty()) {
            Node * temp = new Node();
            temp = poolHead -> next;
            poolHead->data = object;
            poolHead->next = NULL;
            head = poolHead;
            tail = head;
            poolHead = temp;
        }
        else {
            Node * temp = new Node();
            temp = poolHead -> next;
            poolHead->data = object;
            poolHead->next = head;
            head = poolHead;
            poolHead = temp;
        }
    }
    else
        throw std::runtime_error("The List is full, cannot push to the front.\n ");

    deallocateNodes();

}

template <class element>
//Pushes an element to the back
void cop3530::PSLL<element>::push_back(element object) {

    if (!is_full()) {
        Node * temp = new Node();
        temp = poolHead -> next;
        poolHead->data = object;
        poolHead->next = NULL;
        //If there is no current head pointer
        if (!head) {
            //Since there are no more elements the head and tail pointers equal the same thing
            head = poolHead;
            tail = poolHead;
        }
        else {
            //Make the next element in the list equal the current Node
            tail->next = poolHead;
            tail = tail->next;
        }
        poolHead = temp;
    }
    else
        throw std::runtime_error("The List is full, cannot push back.\n ");

    deallocateNodes();

}

template <class element>
//Inserts an element at the specified position
void cop3530::PSLL<element>::insert(element object, int position) {
    if (is_empty() && position != 0)
        throw std::runtime_error("The list is empty, cannot insert.\n ");
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position == 0) {
        push_front(object);
        return;
    }
    if (position == length()) {
        push_back(object);
        return;
    }
    Node * temp = new Node();
    Node * curr = head;
    int index = 0;
    while (curr) {
        if (index + 1 == position) {
            temp = poolHead->next;
            poolHead->data = object;
            poolHead->next = curr->next;
            curr->next = poolHead;
            poolHead = temp;
            break;
        }
        curr = curr->next;
        ++index;
    }

    deallocateNodes();
}

template <class element>
//Replaces an element at the specified position
void cop3530::PSLL<element>::replace(element object, int position) {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot replace.\n ");
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    Node * curr = head;
    int index = 0;
    while (curr) {
        if (index == position) {
            curr->data = object;
            break;
        }
        curr = curr->next;
        ++index;
    }
}

template <class element>
//Removes an element at the specified position and adds that removed node to the pool list
void cop3530::PSLL<element>::remove(int position) {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot replace.\n ");
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position == 0) {
        pop_front();
        return;
    }
    if (position == length()) {
        pop_back();
        return;
    }
    Node * curr = head;
    int index = 0;
    while (curr) {
        if (index + 1 == position) {
            Node * temp = curr->next;
            curr->next = curr->next->next;
            temp->next = poolHead->next;
            poolHead = temp;
            break;
        }
        curr = curr->next;
        ++index;
    }
}

template <class element>
//Returns the item at a specified position
element cop3530::PSLL<element>::item_at(int position) {
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");

    Node * temp = head;
    int index = 0;
    while (temp) {
        if (index + 1 == position) {
            return temp->data;
        }
        temp = temp->next;
        ++index;
    }
}

template <class element>
//Removes and returns the last element
element cop3530::PSLL<element>::pop_back() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot pop at back.\n ");

    element temp = tail->data;
    //If there is only one element in the list
    if (head == tail) {
        Node * curr = head;
        curr->next = poolHead;
        poolHead = curr;
        clear();
    }
    else {
        Node * curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        Node * tempNode = tail;
        tempNode->next = poolHead;
        poolHead = tempNode;
        tail = curr;
        tail->next = NULL;
    }
    return temp;
}

template <class element>
//Returns the last element
element cop3530::PSLL<element>::peek_back() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek at back.\n ");
    return tail->data;
}

template <class element>
//Removes and returns the first element and adds the removed node to the pool
element cop3530::PSLL<element>::pop_front() {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop at front.\n ");
    element frontItem = head->data;
    if (head == tail){
        Node * curr = head;
        curr->next = poolHead;
        poolHead = curr;
        clear();
    }
    else {
        Node * temp = head;
        temp->next = poolHead;
        poolHead = temp;
        head = head->next;
    }
    return frontItem;
}

template <class element>
//Returns the first element
element cop3530::PSLL<element>::peek_front() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek at front.\n ");
    return head->data;
}

template <class element>
//Returns if the List is full
bool cop3530::PSLL<element>::is_full() {
    return (length() == pool_size ? true : false);
}

template <class element>
//Returns if the List is empty
bool cop3530::PSLL<element>::is_empty() {
    return (head == NULL && tail == NULL ? true : false);
}

template <class element>
//Returns the length of the current lsit
size_t cop3530::PSLL<element>::length() {
    if (!is_empty()) {
        size_t len = 0;
        Node * temp = head;
        while (temp) {
            ++len;
            temp = temp->next;
        }
        return len;
    }
    else
        return 0;

}

template <class element>
//Clears the list
void cop3530::PSLL<element>::clear() {
    head = NULL;
    tail = NULL;
}
///REMOVE
template <class element>
void cop3530::PSLL<element>::shitPrint() {
    Node * temp = head;
    while (temp) {
        std::cout << temp->data << "   " ;
        temp = temp->next;
    }
    std::cout << std::endl;
}
///REMOVE
template <class element>
void cop3530::PSLL<element>::poolPrint() {
    int howMany = 0;
    Node * temp = new Node();
    temp = poolHead;

    while (temp) {
        std::cout << "EMPTY   "  ;
        temp = temp->next;
        howMany++;
    }
    std::cout << std::endl;
    std::cout << "HOW MANY??  " <<  howMany << std::endl;
}


template <class element>
//Prints all of the elements
std::ostream& cop3530::PSLL<element>::print (std::ostream& out) {
    if (is_empty())
        out << "<empty list>";
    else {
        out << "<";
        Node * temp = head;
        while (temp) {
            if (!temp->next) {
                out << temp->data;
            }
            else {
                out << temp->data << ",";
            }
            temp = temp->next;
        }
        out << ">";
    }
    return out;
}

template <class element>
//Returns the contents of the list
element * cop3530::PSLL<element>::contents() {
    if (is_empty())
        throw std::runtime_error("The list is empty, there are no elements.\n ");
    element * values = new element[length()];
    Node * temp = head;
    int index = 0;
    while (temp) {
        values[index] = temp->data;
        temp = temp->next;
        ++index;
    }
    return values;
}
///FIX
template <class element>
//See if the list contains a certain element with the matching type
bool cop3530::PSLL<element>::contains (element object, const std::type_info& type)  {
    if (is_empty())
        return false;
  //  std::cout << typeid(object).name();
    if (type != typeid (object))
        return false;

    Node * temp = head;
    while (temp) {
        if (temp->data == object)
                return true;
            temp = temp->next;
    }
    return false;
}

template <class element>
//Deallocates free Nodes that are not being used
void cop3530::PSLL<element>::deallocateNodes() {
    if (length() >= 100 && ((pool_size - length()) > (length() / 2))) {
        //Calculating the new size of the pool; added 0.5 because casting truncates the value
        int newSize = int(((length()) / 2) + 0.5);
        int destroyNodes = pool_size - length() - newSize;
        for (int i = 0; i < destroyNodes; ++i)
            poolHead = poolHead->next;
        pool_size = newSize;
    }
}

#endif // PSLL_H
