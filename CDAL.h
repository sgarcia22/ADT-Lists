#ifndef CDAL_H
#define CDAL_H
#include "ADT.h"

#include <iostream>

namespace cop3530 {

template <typename element>

class CDAL : public ADT<element>
{
    public:
        CDAL();
        CDAL(const CDAL&);
        CDAL& operator=(const CDAL&);
        CDAL(CDAL &&s) noexcept;
        CDAL& operator=(CDAL&&) noexcept;
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
        bool is_curr_arr_full ();
        size_t length () override;
        void clear () override;
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

    public:

template <typename DataT>
        class CDAL_Iter {

            public:
                //Iterator Compatibility
                using iterator_category = std::forward_iterator_tag;
                using iterator_category_const = const std::forward_iterator_tag;
                using value_type = DataT;
                using reference = DataT&;
                using pointer = DataT*;
                using difference_type = std::ptrdiff_t;

                //Type aliases
                using self_type = CDAL_Iter;
                using self_reference = CDAL_Iter&;

            private:
                Node * here;
                pointer here_list;
                int temp_iter_tail;
            public:
                //Points to here
                explicit CDAL_Iter(Node * start = nullptr, pointer start_pointer = nullptr) : here (start), here_list (start_pointer), temp_iter_tail (0) {}
                CDAL_Iter (const CDAL_Iter& src) : here (src.here) {}

                reference operator*() const {return *(here_list);}
                reference operator->() const {return here_list;}
                //Equals sign operator
                self_reference operator=(CDAL_Iter<DataT> const& src) {
                    if (this == &src)
                        return *this;
                    here = src.here;
                    return *this;
                }
                //Pre-increment operator
                self_reference operator++() {
                    if (here_list != nullptr && here != nullptr) {
                        here_list++;
                        temp_iter_tail++;
                        if (!(temp_iter_tail % 50)) {
                            here = here->next;
                            here_list = here->list;
                        }
                        return *this;
                    }
                }
                //Post-increment operator
                self_type operator++(int) {
                    if (here_list != nullptr && here != nullptr) {
                        self_reference temp(*this);
                        here_list++;
                        temp_iter_tail++;
                        if (!(temp_iter_tail % 50)) {
                            here = here->next;
                            here_list = here->list;
                        }
                        return temp;
                    }
                }

                bool operator==(CDAL_Iter<DataT> const& rhs) const {return here_list == rhs.here_list;}
                bool operator!=(CDAL_Iter<DataT> const& rhs) const {return here_list != rhs.here_list;}

        };

        //Iterator Implementation
        using size_t = std::size_t;
        using value_type = element;
        using iterator = CDAL_Iter<element>;
        using const_iterator = CDAL_Iter<element const>;
        //Iterator begin and end functions
        iterator begin () {return iterator(data, data->list);}
        iterator end () {
            Node * temp = data;
            while (temp->next)
                temp = temp->next;

            element * temp_iter_tail = temp->list;
            int temp_counter = tail % 50;
            while (temp_counter > 0) {
                temp_iter_tail++;
                temp_counter--;
            }

            return iterator(temp, temp_iter_tail);
        }

        const_iterator begin() const {return const_iterator(data, data->list);}
        const_iterator end() const {
            Node * temp = data;
            while (temp->next)
                temp = temp->next;

            element * temp_iter_tail = temp->list;
            int temp_counter = tail % 50;
            while (temp_counter > 0) {
                temp_iter_tail++;
                temp_counter--;
            }

            return const_iterator(temp, temp_iter_tail);
        }
};
}

template <typename element>
//Constructor, initializes one node and its array with 50 slots
cop3530::CDAL<element>::CDAL() {
    data = new Node();
    data->list = new element[array_size];
    tail = 0;
    data->next = NULL;
}

template <typename element>
//Copy Constructor
cop3530::CDAL<element>::CDAL(const CDAL &orig) : data(orig.data), tail(orig.tail), array_size(orig.array_size), unused_arrays(orig.unused_arrays) {    }

template <typename element>
//Copy Assignment Operator
cop3530::CDAL<element>& cop3530::CDAL<element>::operator=(const CDAL &rhs) {
    data = rhs.data;
    tail = rhs.tail;
    array_size = rhs.array_size;
    unused_arrays = rhs.unused_arrays;
    return *this;
}

template <typename element>
//Move Constructor
cop3530::CDAL<element>::CDAL(CDAL &&s) noexcept : data(s.data), tail(s.tail), array_size(s.array_size), unused_arrays(s.unused_arrays) {
    s.data = nullptr;
    s.tail = s.array_size = s.unused_arrays = 0;
}

template <typename element>
//Move Assignment Operator
cop3530::CDAL<element>& cop3530::CDAL<element>::operator=(CDAL &&rhs) noexcept {
    if (this != &rhs) {
        delete data;

        data = rhs.data;
        tail = rhs.tail;
        array_size = rhs.array_size;
        unused_arrays = rhs.unused_arrays;

        rhs.data = nullptr;
        rhs.tail = rhs.array_size = rhs.unused_arrays = 0;
    }
}

template <typename element>
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

template <typename element>
//Inserts element at a certain position
void cop3530::CDAL<element>::insert(element object, int position) {
  //If the list is full allocate a new Node with an array that fits 50 items
    if (position >= length()  || position < 0)
         throw std::runtime_error ("Invalid Index; no element at the specified position.\n ");

    //This will be the new array with the added elements
    element * values = new element[length() + 1];
    //Get old array
    element * curr = contents();
    //Copy values from current into new array and insert the new value
    for (int i = 0; i < length() + 1; ++i) {
        if (i < position)
            values[i] = curr[i];
        else if (i == position)
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

template <typename element>
//Inserts element at the back of the list
void cop3530::CDAL<element>::push_back (element object) {

    size_t temp_tail = tail % 50;

    Node * temp = data;
    while (temp) {
        if (!(temp->next)) {
            temp->list[temp_tail] = object;
        }
        temp = temp->next;
    }

    //If the list is full allocate a new Node with an array that fits 50 items
    if (is_curr_arr_full())
        allocate_new();

    ++temp_tail;
   //Move temp_tail pointer to correct new index
    if (temp_tail == 50 && unused_arrays > 0)
        --unused_arrays;
    ++tail;

}

template <typename element>
//Inserts element at the front of the list
void cop3530::CDAL<element>::push_front (element object) {

    size_t temp_tail = tail % 50;

    Node * curr = data;
    //Will keep track of the last index in the previous array
    element temp;
    //Will keep track of the last index in the current array
    element last_temp;

    while (curr) {

        if (!(curr->next)) {

             for (int i = temp_tail; i >= 0; --i) {
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

     //If the list is full allocate a new Node with an array that fits 50 items
    if (is_curr_arr_full()) {
        allocate_new();
    }

    ++temp_tail;
     if (temp_tail == 50 &&unused_arrays > 0)
        --unused_arrays;
    ++tail;
}

template <typename element>
//Replaces an element at the specified index
void cop3530::CDAL<element>::replace (element object, int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot replace.\n ");
    if (position >= length()  || position < 0)
         throw std::runtime_error ("Invalid Index; no element at the specified position.\n ");
    Node * temp = data;
    while (temp) {
        //If the desired element is in another node, go to the next node and decrease the position index
        //to match the appropriate node array index
        if (position > 50) {
            temp = temp->next;
            position -=50;
        }
        else {
            temp->list[position] = object;
            break;
        }
    }
}

template <typename element>
//Removes an element at the specified position and moves all the succeeding elements up the list by one
void cop3530::CDAL<element>::remove (int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot replace.\n ");
    if (position >= length()  || position < 0)
         throw std::runtime_error ("Invalid Index; no element at the specified position.\n ");

    if (position == length() - 1) {
        pop_back();
        return;
    }
    if (position == 0) {
        pop_front();
        return;
    }

    size_t temp_tail = tail % 50;
    //Increase the number of unused arrays
    if (!temp_tail)
        ++unused_arrays;
    size_t temp_unused = unused_arrays;
    //This will be the new array with the added elements
    element * values = new element[length() - 1];
    //Get old array

    element * curr = contents();
    //Copy values from current into new array and insert the new value
    for (int i = 0; i < length() - 1; ++i) {
        if (i < position)
            values[i] = curr[i];
        else if (i >= position)
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

template <typename element>
//Removes and returns an element from the back of the list
element cop3530::CDAL<element>::pop_back () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop at the back.\n ");

    element * curr = contents();
    element last;
    size_t temp_length = length();

    clear();

    for (int i = 0; i < temp_length - 1; ++i) {
        if (i - 1 == temp_length - 1) {
            last = curr[i];
            break;
        }
        push_back(curr[i]);
    }

    delete curr;

    //Deallocate unused arrays if condition holds
    deallocate_old();
    return last;

}

template <typename element>
//Removes and returns an element from the front of the list, moving all the succeeding element up the list by one
element cop3530::CDAL<element>::pop_front () {

    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop at the front.\n ");

    element * curr = contents();

    element front = curr[0];

    size_t temp_length = length();

    clear();

    for (int i = 1; i < temp_length; ++i)
        push_back(curr[i]);


    delete curr;

    //Deallocate unused arrays if condition holds
    deallocate_old();
    return front;
}

template <typename element>
//Returns the item at the specified index
element cop3530::CDAL<element>::item_at (int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, there are no elements.\n ");
    if (position < 0 || position >= length())
        throw std::runtime_error ("Invalid Index; no element at the specified position.\n ");
    int current_index = 0;
    Node * temp = data;
    while (temp) {
        if (position >= array_size) {
            temp = temp->next;
            position -= 50;
        }
        else {
            return temp->list[position];
        }
    }
}

template <typename element>
//Returns the element at the back of the list
element cop3530::CDAL<element>::peek_back () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot peek back.\n ");
    element last_element;
    element * curr = contents();
    for (int i = 0; i < length(); ++i)
        if (i == length() - 1)
            last_element = curr[i];
    delete curr;
    return last_element;
}

template <typename element>
//Returns the element at the front of the list
element cop3530::CDAL<element>::peek_front () {
    if (is_empty())
        throw std::runtime_error("The list is empty, cannot peek front.\n ");
    return data->list[0];
}

template <typename element>
//Returns whether the list is empty
bool cop3530::CDAL<element>::is_empty () {
    return (tail == 0 && !(data->next));
}

template <typename element>
//Returns whether the current array is full
bool cop3530::CDAL<element>::is_curr_arr_full () {
    return ((tail % 50) + 1 == array_size);
}

template <typename element>
//Returns whether the list is full, always returns false because the list allocates new nodes
bool cop3530::CDAL<element>::is_full () {
    return false;
}

template <typename element>
//Returns the length of the elements in the list
size_t cop3530::CDAL<element>::length () {
    return tail;
}

template <typename element>
//Clears the array of all its values
void cop3530::CDAL<element>::clear () {
    //Delete each array in each Node and it's respective Node
    delete [] data;
    data = NULL;
    //Make a new list with data pointing to it
    data = new Node();
    data->list = new element[array_size];
    tail = 0;
    data->next = NULL;
    unused_arrays = 0;
}

template <typename element>
//Returns whether the list contains the specified value
bool cop3530::CDAL<element>::contains (element object, bool (*equals_function) (element, element)) {
    if (is_empty())
        return false;

    element * curr = contents();
    for (int i = 0; i < length(); ++i)
        if (equals_function(object, curr[i]))
            return true;
    return false;
}

template <typename element>
//Returns whether two elements are equal
bool cop3530::CDAL<element>::equals(element a, element b) {
    return (a == b ? true : false);
}

template <typename element>
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

template <typename element>
//Returns the contents of the list
element * cop3530::CDAL<element>::contents() {
    if (is_empty())
        throw std::runtime_error("The list is empty, there are no elements.\n ");
    size_t temp_tail = tail % 50;
    element * values = new element[length()];
    int current_index = 0;
    Node * curr = data;
    while (curr) {
        if (!(curr->next)) {
            for (int i = 0; i < temp_tail; ++i, ++current_index) {
                if (i == temp_tail)
                    break;
                values[current_index] = curr->list[i];
            }
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

template <typename element>
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

template <typename element>
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
