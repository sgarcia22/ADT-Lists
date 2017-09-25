#ifndef SSLL_H
#define SSLL_H

#include <iostream>
#include <typeinfo>

namespace cop3530 {

template <class element>

class SSLL : public ADT<element>
{
    public:

        struct Node {
            element data;
            Node * next;
        };

        SSLL(size_t size);
        ~SSLL();
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
        bool equals (element a, element b);

        private:

            Node * head;
            Node * tail;
            size_t max_size;

        public:


        template <typename DataT>
        class SSLL_Iter {

            public:
                //Iterator Compatibility
                typedef std::forward_iterator_tag iterator_category;
                typedef const std::forward_iterator_tag iterator_category_const;
                using value_type = element;
                using reference = element&;
                using pointer = element*;
                using difference_type = std::ptrdiff_t;

                //Type aliases
                using self_type = SSLL_Iter;
                using self_reference = SSLL_Iter&;
            private:
                Node * here;
            public:
                //Points to here
                explicit SSLL_Iter(Node * start = nullptr) : here (start) {}
                SSLL_Iter (const SSLL_Iter& src) : here (src.here) {}

                reference operator*() const {return here;}
                reference operator->() const {return here->data;}

                self_reference operator = (SSLL_Iter<DataT> const& src) {}
                //Pre-increment operator
                self_reference operator++() {
                    self_type temp(*this);
                    here++;
                    return temp;
                }
                //Post-increment operator
                self_type operator++(int) {
                    self_type temp(*this);
                    ++(*this);
                    return temp;
                }

                bool operator==(SSLL_Iter<DataT> const& rhs) const {return here == rhs.here;}
                bool operator!=(SSLL_Iter<DataT> const& rhs) const {return here != rhs.here;}


        };

        //Iterator Implementation
        using size_t = std::size_t;
        using value_type = element;
        using iterator = SSLL_Iter<element>;
        using const_iterator = SSLL_Iter<element const>;
        //Iterator begin and end functions
        iterator begin () {return iterator(*this);}
        iterator end () {
        ///TODO
        }
        const_iterator begin() const {return iterator(*this);}
        const_iterator end() const {
        ///TODO
        }

};

}

//Constructor, initialize Nodes
template <class element>
cop3530::SSLL<element>::SSLL(size_t size) {
    //Set head and tail equal to null
    head = NULL;
    tail = NULL;
    max_size = size;
}

template <class element>
//Destructor, deallocates and deletes Nodes
cop3530::SSLL<element>::~SSLL() {
    delete head;
    delete tail;
}

template <class element>
//Pushes an element to the front
void cop3530::SSLL<element>::push_front(element object) {
    if (!is_full()) {
        if (is_empty()) {
            head = new Node();
            head->data = object;
            head->next = NULL;
            tail = head;
        }
        else {
            Node * temp = new Node();
            temp->data = object;
            temp->next = head;
            head = temp;
        }

    }
    else
        throw std::runtime_error("The List is full, cannot push to the front.\n ");
}

template <class element>
//Pushes an element to the back
void cop3530::SSLL<element>::push_back(element object) {

    if (!is_full()) {
        Node * curr = new Node();
        curr->data = object;
        curr->next = NULL;
        //If there is no current head pointer
        if (!head) {
            //Since there are no more elements the head and tail pointers equal the same thing
            head = curr;
            tail = curr;
        }
        else {
            //Make the next element in the list equal the current Node
            tail->next = curr;
            tail = tail->next;
        }
    }
    else
        throw std::runtime_error("The List is full, cannot push back.\n ");

}
///CHECK
template <class element>
//Inserts an element at the specified position
void cop3530::SSLL<element>::insert(element object, int position) {
    if (is_full())
        throw std::runtime_error("The list is full, cannot insert.\n ");
    if (is_empty() && position != 0)
        throw std::runtime_error("The list is empty, cannot insert at desired position.\n ");
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

    Node * temp = head;
    int index = 0;
    while (temp) {
        if (index + 1 == position) {
            Node * insertedNode = new Node();
            insertedNode->data = object;
            insertedNode->next = temp->next;
            temp->next = insertedNode;
            break;
        }
        temp = temp->next;
        ++index;
    }
}

template <class element>
//Replaces an element at the specified position
void cop3530::SSLL<element>::replace(element object, int position) {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot replace.\n ");
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    Node * temp = head;
    int index = 0;
    while (temp) {
        if (index == position - 1) {
            temp->data = object;
            break;
        }
        temp = temp->next;
        ++index;
    }
}
///CHECK
template <class element>
//Removes an element at the specified position
void cop3530::SSLL<element>::remove(int position) {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot replace.\n ");
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position == 1) {
        pop_front();
        return;
    }
    if (position == length()) {
        pop_back();
        return;
    }
    Node * temp = head;
    int index = 0;
    while (temp) {
        if (index == position - 2) {
            temp->next = temp->next->next;
            break;
        }
        temp = temp->next;
        ++index;
    }
}

template <class element>
//Returns the item at a specified position
element cop3530::SSLL<element>::item_at(int position) {
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");

    Node * temp = head;
    int index = 0;
    while (temp) {
        if (index == position - 1) {
            return temp->data;
        }
        temp = temp->next;
        ++index;
    }
}

template <class element>
//Removes and returns the last element
element cop3530::SSLL<element>::pop_back() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot pop at back.\n ");

    element temp = tail->data;
    if (head == tail)
        clear();
    else {
        Node * curr = new Node();
        curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        tail = curr;
        tail->next = NULL;
    }
    return temp;
}

template <class element>
//Returns the last element
element cop3530::SSLL<element>::peek_back() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek at back.\n ");
    return tail->data;
}

template <class element>
//Removes and returns the first element
element cop3530::SSLL<element>::pop_front() {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop at front.\n ");
    element frontItem = head->data;
    if (head == tail){
        clear();
        return frontItem;
    }
    head = head->next;

    return frontItem;
}

template <class element>
//Returns the first element
element cop3530::SSLL<element>::peek_front() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek at front.\n ");
    return head->data;
}

template <class element>
//Returns if the List is full
bool cop3530::SSLL<element>::is_full() {
    return (length() == max_size ? true : false);
}

template <class element>
//Returns if the List is empty
bool cop3530::SSLL<element>::is_empty() {
    return (head == NULL && tail == NULL ? true : false);
}

template <class element>
//Returns the length of the current lsit
size_t cop3530::SSLL<element>::length() {
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
void cop3530::SSLL<element>::clear() {
    head = NULL;
    tail = NULL;
}
template <class element>
void cop3530::SSLL<element>::shitPrint() {
    Node * temp = head;
    while (temp) {
        std::cout << temp->data << "   " ;
        temp = temp->next;
    }
    std::cout << std::endl;
}

template <class element>
//Prints all of the elements
std::ostream& cop3530::SSLL<element>::print (std::ostream& out) {
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
element * cop3530::SSLL<element>::contents() {
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

template <class element>
//See if the list contains a certain element through a function pointer to make sure it is the exact element
bool cop3530::SSLL<element>::contains (element object, bool (*equals_function) (element, element))  {
    if (is_empty())
        return false;

    Node * temp = head;
    while (temp) {
        //if (temp->data == object)
        if (equals_function(object, temp->data))
            return true;
        temp = temp->next;
    }

    return false;

} ///DUNNO?~!
template <class element>
//Equals function that compares two elements
bool cop3530::SSLL<element>::equals (element a, element b) {
    return a == b;
}

#endif // SSLL_H
