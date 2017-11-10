#ifndef PSLL_H
#define PSLL_H

#include <iostream>
#include <typeinfo>
///DEALLOCATE SHIT
namespace cop3530 {

template <typename element>

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
        bool is_pool_full ();
        bool pool_is_empty();
        size_t length () override;
        size_t pool_length();
        void clear () override;
        void shitPrint(); ///ERASE
        void poolPrint(); ///ERASE
        bool contains (element object, bool (*equals_function) (element, element)) override;
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
        Node * pool_head;
        Node * pool_tail;

        size_t const max_pool_length = 50;
        size_t const total_size;

    public:

        template <typename DataT>
        class PSLL_Iter {
            public:
                //Iterator Compatibility
                using iterator_category = std::forward_iterator_tag;
                using iterator_category_const = const std::forward_iterator_tag;
                using value_type = element;
                using reference = element&;
                using pointer = element*;
                using difference_type = std::ptrdiff_t;

                //Type aliases
                using self_type = PSLL_Iter;
                using self_reference = PSLL_Iter&;

            private:
                Node * here;
            public:
                //Points to here
                explicit PSLL_Iter(Node * start = nullptr) : here (start) {}
                PSLL_Iter (const PSLL_Iter& src) : here (src.here) {}

                reference operator*() const {return here->data;}
                reference operator->() const {return here;}
                //Equals sign operator
                self_reference operator=(PSLL_Iter<DataT> const& src) {
                    if (this == &src)
                        return *this;
                    here = src.here;
                    return *this;
                }
                //Pre-increment operator
                self_reference operator++() {
                    if (here != nullptr) {
                        here = here->next;
                        return *this;
                    }
                }
                //Post-increment operator
                self_reference operator++(int) {
                    if (here != nullptr) {
                        self_type temp(*this);
                        here = here->next;
                        return temp;
                    }
                }

                bool operator==(PSLL_Iter<DataT> const& rhs) const {return here == rhs.here;}
                bool operator!=(PSLL_Iter<DataT> const& rhs) const {return here != rhs.here;}

        };

        //Iterator Implementation
        using size_t = std::size_t;
        using value_type = element;
        using iterator = PSLL_Iter<element>;
        using const_iterator = PSLL_Iter<element const>;
        //Iterator begin and end functions
        iterator begin () {return iterator(head);}
        iterator end () {return iterator(tail->next);}

        const_iterator begin () const {return const_iterator(head);}
        const_iterator end () const {return const_iterator(tail->next);}

};
}

template <typename element>
//Constructor, initialize Nodes
cop3530::PSLL<element>::PSLL(size_t size) : total_size(size) {
    //Set head and tail equal to null
    if (!size)
        throw std::runtime_error("List cannot have a zero size. ");
    head = nullptr, tail = nullptr, pool_head = nullptr, pool_tail = nullptr;

}

template <typename element>
//Deallocate free Nodes
cop3530::PSLL<element>::~PSLL() {
    delete head;
    delete tail;
    delete pool_head;
    delete pool_tail;
}

template <typename element>
//Pushes an element to the front
void cop3530::PSLL<element>::push_front(element object) {
    if (is_full())
        throw std::runtime_error ("The list is full, cannot push front.\n ");
    //If the pool is empty allocate a new node
    if (pool_is_empty()) {
        //If the list is empty, allocate new node and make that the head
        if (is_empty()) {
            head = new Node();
            head->data = object;
            tail = head;
        }
        else {
            Node * temp = new Node();
            temp->data = object;
            temp->next = head;
            head = temp;
        }
    }
    //If there are nodes in the pool
    else {
        if (is_empty()) {
            head = pool_head;
            pool_head = pool_head->next;
            head->data = object;
            tail = head;
        }
        else {
            Node * temp = pool_head;
            temp->data = object;
            temp->next = head;
            head = temp;
            pool_head = pool_head->next;
        }
    }
    deallocateNodes();
}

template <typename element>
//Pushes an element to the back
void cop3530::PSLL<element>::push_back(element object) {
    if (is_full())
        throw std::runtime_error ("The list is full, cannot push back.\n ");
    //If the pool is empty allocate a new node directly to the list
    if (pool_is_empty()) {
        if (is_empty()) {
            head = new Node();
            head->data = object;
            tail = head;
        }
        else {
            tail->next = new Node();
            tail = tail->next;
            tail->data = object;
        }
    }
    //Use a node from the pool and make it part of the list
    else {
        if (is_empty()) {
            head = pool_head;
            head->data = object;
            tail = head;
        }
        else {
            Node * temp = pool_head;
            temp->data = object;
            pool_head = pool_head->next;
            tail->next = temp;
            tail = tail->next;
        }
    }
    deallocateNodes();
}

template <typename element>
//Inserts an element at the specified position
void cop3530::PSLL<element>::insert(element object, int position) {
    if (is_full())
        throw std::runtime_error ("The list is full, cannot insert.\n ");
    if (is_empty() && position != 0)
        throw std::runtime_error("The list is empty, cannot insert at the desired position.\n ");
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
    //Either allocate a new node or use one from the pool if not empty
    Node * temp;
    if (pool_is_empty())
        temp = new Node();
    else {
        temp = pool_head;
        pool_head = pool_head->next;
    }
    temp->data = object;
    Node * curr = head;
    int index = 0;
    while (curr) {
        if (index + 1 == position) {    ///Double check these indices
            temp->next = curr->next;
            curr->next = temp;
            break;
        }
        curr = curr->next;
        ++index;
    }
    deallocateNodes();
}

template <typename element>
//Replaces an element at the specified position
void cop3530::PSLL<element>::replace(element object, int position) {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot replace.\n ");
    if (position > length())
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    Node * curr = head;
    int index = 0;
    while (curr) {
        if (index == position - 1) {
            curr->data = object;
            break;
        }
        curr = curr->next;
        ++index;
    }
}

template <typename element>
//Removes an element at the specified position and adds that removed node to the pool list
void cop3530::PSLL<element>::remove(int position) {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot remove.\n ");
    if (position > length() || !position)
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position == 1) {
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
        if (index == position - 2) {
            Node * temp = new Node();
            temp = curr->next;
            curr->next = curr->next->next;
            if (is_pool_full()) {
                delete temp;
            }
            else {
                temp->next = pool_head;
                pool_head = temp;
            }
            break;
        }
        curr = curr->next;
        ++index;
    }
    deallocateNodes();
}

template <typename element>
//Returns the item at a specified position
element cop3530::PSLL<element>::item_at(int position) {
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

template <typename element>
//Removes and returns the last element
element cop3530::PSLL<element>::pop_back() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot pop at back.\n ");

    element temp = tail->data;
    //If there is only one element in the list
    if (head == tail) {
        Node * curr = head;
        curr->next = pool_head;
        pool_head = curr;
        head = tail = nullptr;
    }
    else {
        Node * curr = head;
        while (curr->next != tail) {
            curr = curr->next;
        }
        //If the pool is full
        if (is_pool_full()) {
            delete tail->next;
            tail->next = nullptr;
        }
        else {
            Node * tempNode = tail;
            tempNode->next = pool_head;
            pool_head = tempNode;
            tail = curr;
            tail->next = NULL;
        }
    }
    deallocateNodes();
    return temp;
}

template <typename element>
//Returns the last element
element cop3530::PSLL<element>::peek_back() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek at back.\n ");
    return tail->data;
}

template <typename element>
//Removes and returns the first element and adds the removed node to the pool
element cop3530::PSLL<element>::pop_front() {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop at front.\n ");
    element frontItem = head->data;

    Node * temp = head;

    if (head->next)
        head = head->next;
    else
        head = nullptr;

    if (is_pool_full())
        delete temp;
    else {
        temp->next = pool_head;
        pool_head = temp;
    }
    deallocateNodes();
    return frontItem;
}

template <typename element>
//Returns the first element
element cop3530::PSLL<element>::peek_front() {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek at front.\n ");
    return head->data;
}

template <typename element>
//Returns if the pool is full
bool cop3530::PSLL<element>::is_full() {
    return (length() == total_size ? true : false);
}

template <typename element>
//Returns if the pool is full
bool cop3530::PSLL<element>::is_pool_full() {
    return (pool_length() == max_pool_length ? true : false);
}

template <typename element>
//Returns if the list is empty
bool cop3530::PSLL<element>::is_empty() {
    return (head == nullptr && tail == nullptr ? true : false);
}

template <typename element>
//Returns if the list is empty
bool cop3530::PSLL<element>::pool_is_empty() {
    return (!pool_length() ? true : false);
}

template <typename element>
//Returns the length of the current list
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

template <typename element>
//returns the length of the pool
size_t cop3530::PSLL<element>::pool_length() {
    if (pool_head == nullptr)
        return 0;
    size_t counter = 0;
    Node * temp = pool_head;
    while (temp) {
        ++counter;
        temp = temp->next;
    }
    return counter;
}

template <typename element>
//Clears the list
void cop3530::PSLL<element>::clear() {
    pool_head = pool_tail = nullptr;
    head = tail = nullptr;
}
///REMOVE
template <typename element>
void cop3530::PSLL<element>::shitPrint() {
    Node * temp = head;
    while (temp) {
        std::cout << temp->data << "   " ;
        temp = temp->next;
    }
    std::cout << std::endl;
}
///REMOVE
template <typename element>
void cop3530::PSLL<element>::poolPrint() {
    Node * temp = pool_head;
    size_t counter = 0;
    while (temp) {
        ++counter;
        std::cout << temp->data << "  ";
        temp = temp->next;
    }
    if (counter == 0) std::cout << "EMPTY\n";
}

template <typename element>
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

template <typename element>
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

template <typename element>
//See if the list contains a certain element with the matching type
bool cop3530::PSLL<element>::contains (element object, bool (*equals_function) (element, element))  {
    if (is_empty())
        return false;
    Node * temp = head;
    while (temp) {
        if (equals_function(object, temp->data))
      //  if (object == temp->data)
            return true;
        temp = temp->next;
    }
    return false;
}

template <typename element> ///TEST WELL, NOT SURE WHEN THIS HAPPENS
//Deallocates free Nodes that are not being used
void cop3530::PSLL<element>::deallocateNodes() {
    if (length() >= 100 && (pool_length() > int((length() / 2) + 0.5))) {
        std::cout << "Going in\n";
        //Calculating the new size of the pool; added 0.5 because casting truncates the value
        size_t new_size = int(((length()) / 2) + 0.5);
        size_t destroy_nodes = pool_length() - new_size;
        Node * temp;
        for (size_t i = 0; i < destroy_nodes; ++i) {
            temp = pool_head;
            pool_head = pool_head->next;
            delete temp;
        }
    }
}

#endif // PSLL_H
