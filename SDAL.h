#ifndef SDAL_H
#define SDAL_H

#include "List.h"
#include <iostream>

namespace cop3530 {

template <typename element>

class SDAL : public List<element>
{
    public:

        SDAL(size_t inputSize = 50);
        SDAL(const SDAL&);
        SDAL& operator=(const SDAL&);
        SDAL(SDAL &&s) noexcept;
        SDAL& operator=(SDAL&&) noexcept;
        virtual ~SDAL();

        void insert(element object, int position) override;
        void push_back (element object) override;
        void push_front (element object) override;
        void replace (element object, int position) override;
        element remove (int position) override;
        element pop_back () override;
        element pop_front () override;
        element & item_at (int position) override;
        element & peek_back () override;
        element & peek_front () override;
        bool is_empty () override;
        bool is_full () override;
        bool is_curr_full ();
        size_t length () override;
        void clear () override;
        bool contains (element object, bool (*equals_function) (const element&, const element&)) override;
        std::ostream& print (std::ostream& out) override;
        element * contents() override;
        void allocate_new();

    private:

        int tail;
        element * list;
        int max_size;
        //Keeps track of the initial size
        int const initial_size;

    public:

    template <typename DataT>
    class SDAL_Iter {
        public:
            //Iterator Compatibility
            using iterator_category = std::forward_iterator_tag;
            using iterator_category_const = const std::forward_iterator_tag;
            using value_type = element;
            using reference = element&;
            using pointer = element*;
            using difference_type = std::ptrdiff_t;

            //Type aliases
            using self_type = SDAL_Iter;
            using self_reference = SDAL_Iter&;

        private:
            pointer here;
        public:
            //Points to here
            explicit SDAL_Iter(pointer start = nullptr) : here (start) {}
            SDAL_Iter (const SDAL_Iter& src) : here (src.here) {}

            reference operator*() const {return *here;}
            reference operator->() const {return here;}
            //Equals sign operator
            self_reference operator=(SDAL_Iter<DataT> const& src) {
                if (this == &src)
                    return *this;
                here = src.here;
                return *this;
            }
            //Pre-increment operator
            self_reference operator++() {
                ++here;
                return *this;
            }
            //Post-increment operator
            self_reference operator++(int) {
                self_type temp(*this);
                ++here;
                return temp;
            }

            bool operator==(SDAL_Iter<DataT> const& rhs) const {return here == rhs.here;}
            bool operator!=(SDAL_Iter<DataT> const& rhs) const {return here != rhs.here;}
    };

    //Iterator Implementation
    using value_type = element;
    using iterator = SDAL_Iter<element>;
    using const_iterator = SDAL_Iter<element const>;
    //Iterator begin and end functions
    iterator begin () {return iterator(list);}
    iterator end () {return iterator(list + tail);}

    const_iterator begin () const {return const_iterator(list);}
    const_iterator end () const {return const_iterator(list + tail);}

};
}

template <typename element>
//Constructor, initializes array
cop3530::SDAL<element>::SDAL(size_t inputSize) : initial_size(inputSize) {

    max_size = inputSize;
    //Setting tail to -1 because it is accessed through index
    tail = 0;
    list = new element [max_size + 1];

}

template <typename element>
//Deep Copy Constructor
cop3530::SDAL<element>::SDAL(const SDAL &orig) : list(nullptr), tail(orig.tail), max_size(orig.max_size), initial_size(orig.initial_size) {
    if (!list)
        return;
    //Make a new array
    list = new element [max_size + 1];
    //Copy the elements over if they exist
    for (int i = 0; i < length(); ++i) {
        element temp = list[i];
        list[i] = new element(temp);
    }
}

template <typename element>
//Deep Copy Assignment Operator
cop3530::SDAL<element>& cop3530::SDAL<element>::operator=(const SDAL &rhs) {
    if (list)
        this->~SDAL();
    using std::swap;
    swap(rhs.list, list);
    swap(rhs.tail, tail);
    swap(rhs.max_size, max_size);
    swap(rhs.initial_size, initial_size);
    rhs.list = nullptr;
    rhs.tail = rhs.max_size = rhs.initial_size = 0;
    return *this;
}

template <typename element>
//Move Constructor
cop3530::SDAL<element>::SDAL(SDAL &&s) noexcept : list(s.list), tail(s.tail), max_size(s.max_size), initial_size(s.initial_size) {
    s.list = nullptr;
    s.max_size = s.tail = s.initial_size = 0;
}

template <typename element>
//Move Assignment Operator
cop3530::SDAL<element>& cop3530::SDAL<element>::operator=(SDAL &&rhs) noexcept {
    if (this != &rhs) {
        delete list;

        using std::swap;
        swap(rhs.list, list);
        swap(rhs.tail, tail);
        swap(rhs.max_size, max_size);
        swap(rhs.initial_size, initial_size);

        rhs.list = nullptr;
        rhs.tail = rhs.max_size = rhs.initial_size = 0;
    }
}

template <typename element>
//Destructor, deallocates array and pointer
cop3530::SDAL<element>::~SDAL() {
    delete [] list;
}

template <typename element>
//Inserts element at a certain position
void cop3530::SDAL<element>::insert(element object, int position) {
    if (is_curr_full())
        allocate_new();
    if (position >= max_size || signed(position)  < 0)
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position >= length()) {
        push_back(object);
        return;
    }
    if (position == 0) {
        push_front(object);
        return;
    }

    for (int i = length(); i > 0; --i) {
        if (i + 1 > position) {
            list[i] = list[i - 1];
        }
    }
    list[position] = object;
    ++tail;
}

template <typename element>
//Inserts element at the back of the list
void cop3530::SDAL<element>::push_back (element object) {
    if (is_curr_full())
        allocate_new();
    list[tail] = object;
    ++tail;
}

template <typename element>
//Inserts element at the front of the list
void cop3530::SDAL<element>::push_front (element object) {
    if (is_curr_full())
        allocate_new();
    if (!is_empty()) {
        for (int i = length(); i >= 0; --i) {
            list[i] = list[i - 1];
        }
    }
    list[0] = object;
    ++tail;
}

template <typename element>
//Replaces an element at the specified index
void cop3530::SDAL<element>::replace (element object, int position) {
    if (position >= max_size  || signed(position)  < 0)
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position > tail)
        throw std::runtime_error("No element at that position to replace.\n ");
    list[position] = object;
}

template <typename element>
//Removes an element at the specified position and moves all the succeeding elements up the list by one
element cop3530::SDAL<element>::remove (int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot remove an element.\n ");
    if (position > max_size  || signed(position)  < 0)
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position >= tail)
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    element to_return;
    if (position == tail - 1) {
        to_return = pop_back();
        return to_return;
    }
    if (position == 0) {
        to_return = pop_front();
        return to_return;
    }

    for (int i = position; i < length(); ++i) {
		if (i == position)
			to_return = list[i];
        list[i] = list[i + 1];
	}
    --tail;
    allocate_new();
    return to_return;
}

template <typename element>
//Removes and returns an element from the back of the list
element cop3530::SDAL<element>::pop_back () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop back.\n ");
    element temp = list[tail - 1];
    --tail;
    allocate_new();
    return temp;
}

template <typename element>
//Removes and returns an element from the front of the list, moving all the succeeding element up the list by one
element cop3530::SDAL<element>::pop_front () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop front.\n ");
    element temp = list[0];
    for (int i = 0; i < length(); ++i)
        list[i] = list[i + 1];
    tail--;
    allocate_new();
    return temp;
}

template <typename element>
//Returns the item at the specified index
element & cop3530::SDAL<element>::item_at (int position) {
    if (position >= length()  || position < 0)
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    if (position > tail)
        throw std::runtime_error("Invalid Index; no element at the specified position.\n ");
    return list[position];
}

template <typename element>
//Returns the element at the back of the list
element & cop3530::SDAL<element>::peek_back () {
    return list[tail - 1];
}

template <typename element>
//Returns the element at the front of the list
element & cop3530::SDAL<element>::peek_front () {
    return list[0];
}

template <typename element>
//Returns whether the list is empty
bool cop3530::SDAL<element>::is_empty () {
    return (!tail);
}

template <typename element>
//Returns whether the list is full
bool cop3530::SDAL<element>::is_full () {
    return false;
}

template <typename element>
//Returns whether the list is full
bool cop3530::SDAL<element>::is_curr_full () {
    return (tail >= max_size);
}

template <typename element>
//Returns the length of the elements in the list
size_t cop3530::SDAL<element>::length () {
    return tail;
}

template <typename element>
//Clears the array of all its values
void cop3530::SDAL<element>::clear () {
    tail = 0;
    delete [] list;
    list = new element [initial_size + 1];
    max_size = initial_size;

}

template <typename element>
//Returns whether the list contains the specified value
bool cop3530::SDAL<element>::contains (element object, bool (*equals_function) (const element&, const element&)) {
    if (is_empty())
        return false;
    for (int i = 0; i < length(); ++i) {
        if (equals_function(object, list[i]))
            return true;
    }
    return false;
}

template <typename element>
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

template <typename element>
//Returns the contents of the list
element * cop3530::SDAL<element>::contents() {
    if (is_empty())
        throw std::runtime_error("The list is empty, there are no elements.\n ");
    element * values = new element[length()];
    for (int i = 0; i < length(); ++i)
        values[i] = list[i];
    return values;
}
template <typename element>
//Allocate a new array is the current one is using too much or too little memory
void cop3530::SDAL<element>::allocate_new() {
    if (is_full()) {
        int new_size = int(max_size  * 1.5 + 0.5);
        element * temp = new element [new_size + 1];
        for (int i = 0; i < max_size; ++i)
            temp[i] = list[i];
        delete [] list;
        list = temp;
        max_size = new_size;

    }
    if (max_size >= 2 * initial_size && ((max_size / 2) > length())) {

        int new_size = int(max_size  * .75 + 0.5);
        element * temp = new element [new_size + 1];
        for (int i = 0; i < new_size; ++i)
            temp[i] = list[i];
        delete [] list;
        list = temp;
        max_size = new_size;
    }
}

#endif // SDAL_H
