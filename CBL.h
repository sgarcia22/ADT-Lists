#ifndef CBL_H
#define CBL_H
#include "ADT.h"
#include <stdlib.h>
namespace cop3530 {

template <typename element>

class CBL : public ADT<element>
{
    public:
        CBL();
        CBL(const CBL&);
        CBL& operator=(const CBL&);
        CBL(CBL &&s) noexcept;
        CBL& operator=(CBL&&) noexcept;
        virtual ~CBL();

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

        element * list;
        size_t head;
        size_t tail;
        size_t const initial_size;
        size_t max_size;

    public:

    template <typename DataT>
    class CBL_Iter {
        public:
            //Iterator Compatibility
            using iterator_category = std::forward_iterator_tag;
            using iterator_category_const = const std::forward_iterator_tag;
            using value_type = element;
            using reference = element&;
            using pointer = element*;
            using difference_type = std::ptrdiff_t;

            //Type aliases
            using self_type = CBL_Iter;
            using self_reference = CBL_Iter&;

        private:
            pointer here;

        public:
            //Points to here
            explicit CBL_Iter(pointer start = nullptr) : here (start) {}
            CBL_Iter (const CBL_Iter& src) : here (src.here) {}

            reference operator*() const {return *here;}
            reference operator->() const {return here;}
            //Equals sign operator
            self_reference operator=(CBL_Iter<DataT> const& src) {
                if (this == &src)
                    return *this;
                here = src.here;
                return *this;
            }
            //Pre-increment operator
            self_reference operator++() {
                if (here == max_size - 1)
                    here = 0;
                else
                    ++here;
                return *this;
            }
            //Post-increment operator
            self_reference operator++(int) {
                self_type temp(*this);
                if (here == max_size - 1)
                    here = 0;
                else
                    ++here;
                return temp;
            }

            bool operator==(CBL_Iter<DataT> const& rhs) const {return here == rhs.here;}
            bool operator!=(CBL_Iter<DataT> const& rhs) const {return here != rhs.here;}

    };

    //Iterator Implementation
    using size_t = std::size_t;
    using value_type = element;
    using iterator = CBL_Iter<element>;
    using const_iterator = CBL_Iter<element const>;
    //Iterator begin and end functions
    iterator begin () {return iterator(list + head);}
    iterator end () {return iterator(list + tail);}

    const_iterator begin () const {return const_iterator(list + head);}
    const_iterator end () const {return const_iterator(list + tail);}
};
}

template <typename element>
//Constructor, initializes values
cop3530::CBL<element>::CBL(size_t input_size) : initial_size(input_size) {
    max_size = input_size;
    head = tail = 0;
    list = new element [max_size + 1];
}

template <typename element>
//Copy Constructor
cop3530::CBL<element>::CBL(const CBL &orig) : list(orig.list), head(orig.head), tail(orig.tail), max_size(orig.max_size), initial_size(orig.initial_size) {    }

template <typename element>
//Copy Assignment Operator
cop3530::CBL<element>& cop3530::CBL<element>::operator=(const CBL &rhs) {
    list = rhs.list;
    head = rhs.head;
    tail = rhs.tail;
    max_size = rhs.max_size;
    initial_size = rhs.initial_size;
    return *this;
}

template <typename element>
//Move Constructor
cop3530::CBL<element>::CBL(CBL &&s) noexcept : list(s.list), head(s.head), tail(s.tail), max_size(s.max_size), initial_size(s.initial_size) {
    s.list = nullptr;
    s.max_size = s.tail = s.head = s.initial_size = 0;
}

template <typename element>
//Move Assignment Operator
cop3530::CBL<element>& cop3530::CBL<element>::operator=(CBL &&rhs) noexcept {
    if (this != &rhs) {
        delete list;

        list = rhs.list;
        head = rhs.head;
        tail = rhs.tail;
        max_size = rhs.max_size;
        initial_size = rhs.initial_size;

        rhs.list = nullptr;
        rhs.max_size = rhs.initial_size = rhs.head = rhs.tail = 0;
    }
}

template <typename element>
//Destructor, deallocates array and pointer
cop3530::CBL<element>::~CBL() {
    delete [] list;
}
template <typename element>
//Inserts element at the back of the list
void cop3530::CBL<element>::push_back (element object) {
    if (is_full())
        allocate_new();
    if (tail == max_size - 1)
        tail = 0;
    list[tail] = object;
    ++tail;
}
template <typename element>
//Inserts element at the front of the list
void cop3530::CBL<element>::push_front (element object) {
    if (is_full())
        allocate_new();
    if (head == 0)
        head = max_size - 1;
    else
        --head;
    list[head] = object;
}
template <typename element>
//Inserts element at a certain position
void cop3530::CBL<element>::insert(element object, int position) {
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

    size_t temp_tail = tail;
    for (int i = length(); i > 0; --i, --temp_tail) {
        if (temp_tail == -1)
            temp_tail = max_size - 1;
        if (temp_tail + 1 >= position) {
            list[temp_tail] = list[temp_tail - 1];
        }
    }
    list[position - 1] = object;
    if (tail == max_size)
        tail = 0;
    else
        ++tail;
}
template <typename element>
//Replaces an element at the specified index
void cop3530::CBL<element>::replace (element object, int position) {
    if (position > max_size)
        throw std::runtime_error("Not a valid position.\n ");
    if (position - 1 > std::abs(tail - head))
        throw std::runtime_error("No element at that position to replace.\n ");
    list[position - 1] = object;
}
template <typename element>
//Removes an element at the specified position and moves all the succeeding elements up the list by one
void cop3530::CBL<element>::remove (int position) {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot remove an element.\n ");
    if (position > max_size)
        throw std::runtime_error("Not a valid position.\n ");
    if (position - 1 > tail)
        throw std::runtime_error("No element at that position to remove.\n ");
    for (int i = position - 1; i < length(); ++i) {
        if (i == max_size - 1)
            i = 0;
        list[i] = list[i + 1];
    }
    --tail;
    allocate_new();
}
template <typename element>
//Removes and returns an element from the back of the list
element cop3530::CBL<element>::pop_back () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop back.\n ");
    element temp = list[tail - 1];
    if (!tail)
        tail = max_size - 1;
    else
        --tail;
    allocate_new();
    return temp;
}
template <typename element>
//Removes and returns an element from the front of the list, moving all the succeeding element up the list by one
element cop3530::CBL<element>::pop_front () {
    if (is_empty())
        throw std::runtime_error ("The list is empty, cannot pop front.\n ");
    element temp = list[head];
    if (head == max_size - 1)
        head = 0;
    else
        ++head;
    allocate_new();
    return temp;
}
template <typename element>
//Returns the item at the specified index
element cop3530::CBL<element>::item_at (int position) {
    if (position > max_size)
        throw std::runtime_error("Not a valid position.\n ");
    if (position - 1 > tail)
        throw std::runtime_error("No element at that position.\n ");
    return list[position - 1];
}
template <typename element>
//Returns the element at the back of the list
element cop3530::CBL<element>::peek_back () {
    size_t temp_tail = tail;
    if (!temp_tail)
        temp_tail = max_size - 1;
    else
        --temp_tail;
    return list[temp_tail];
}
template <typename element>
//Returns the element at the front of the list
element cop3530::CBL<element>::peek_front () {
    return list[head];
}
template <typename element>
//Returns whether the list is empty
bool cop3530::CBL<element>::is_empty () {
    return (head == tail);
}
template <typename element>
//Returns whether the list is full
bool cop3530::CBL<element>::is_full () {
    return (length() == max_size);
}
template <typename element>
//Returns the length of the elements in the list
size_t cop3530::CBL<element>::length () {
    return std::abs(tail - head);
}
template <typename element>
//Clears the array of all its values
void cop3530::CBL<element>::clear () {
    tail = head = 0;
    delete [] list;
    list = new element [initial_size + 1];
    max_size = initial_size;

}
///ERASE
template <typename element>
void cop3530::CBL<element>::shitPrint() {
    int j = head;
    for (int i = 0; i < length(); ++i, ++j) {
        if (j == max_size - 1)
            j = 0;
        std::cout << list[j] << "  ";
    }
    std::cout << "\nTAIL: " << tail << std::endl;
    std::cout << "SIZE: " << max_size << std::endl;
}
template <typename element>
//Returns whether the list contains the specified value
bool cop3530::CBL<element>::contains (element object, bool (*equals_function) (element, element)) {
    if (is_empty())
        return false;
    size_t temp_index = head;
    for (int i = 0; i < length(); ++i) {
        if (equals_function(object, list[temp_index]))
            return true;
        if (temp_index == max_size - 1)
            temp_index = 0;
        else
            ++temp_index;
    }
    return false;
}
template <typename element>
//Prints out the contents of the list to the ostream
std::ostream& cop3530::CBL<element>::print (std::ostream& out) {
    if (is_empty())
        out << "<empty list>";
    else {
        out << "<";
        size_t temp_head = head;
        for (int i = 0; i < length(); ++i, ++temp_head) {
            if (head == max_size - 1)
                head = 0;
            if (i == length() - 1)
                out << list[head];
            else
                out << list[head] << ",";
        }
        out << ">";
    }
    return out;
}
template <typename element>
//Returns the contents of the list
element * cop3530::CBL<element>::contents() {
    if (is_empty())
        throw std::runtime_error("The list is empty, there are no elements.\n ");
    element * values = new element[length()];
    size_t temp_head = head;
    for (int i = 0; i < length(); ++i, ++temp_head)
        if (temp_head == max_size - 1)
            head  = 0;
        values[i] = list[temp_head];
    return values;
}
template <typename element> ///TEST
//Allocate a new array is the current one is using too much or too little memory
void cop3530::CBL<element>::allocate_new() {

    if (is_full()) {
        int new_size = int(max_size  * 1.5 + 0.5);
        element * temp = new element [new_size + 1];
        size_t temp_head = head;
        for (int i = 0; i < max_size; ++i, ++temp_head) {
            if (temp_head == max_size - 1)
                temp_head = 0;
            temp[i] = list[temp_head];
        }
        delete [] list;
        list = temp;
       // std::cout << "\nMAX SIZE: " << new_size << std::endl;
        max_size = new_size;
    }

    if (max_size >= 2 * initial_size && ((max_size / 2) > length())) {
        int new_size = int(max_size  * .75 + 0.5);
        element * temp = new element [new_size + 1];
        size_t temp_head = head;
        for (int i = 0; i < new_size; ++i, ++temp_head) {
            if (temp_head == max_size - 1)
                temp_head = 0;
            temp[i] = list[temp_head];
        }
        delete [] list;
        list = temp;
        max_size = new_size;
    }
}
#endif // CBL_H
