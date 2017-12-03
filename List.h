#ifndef LIST_H
#define LIST_H
#include <iostream>

namespace cop3530 {

template <typename element>

class List
{
    public:
        virtual void insert(element object, int position) = 0;
        virtual void push_back (element object) = 0;
        virtual void push_front (element object) = 0;
        virtual void replace (element object, int position) = 0;
        virtual element remove (int position) = 0;
        virtual element pop_back () = 0;
        virtual element pop_front () = 0;
        virtual element & item_at (int position) = 0;
        virtual element & peek_back () = 0;
        virtual element & peek_front () = 0;
        virtual bool is_empty () = 0;
        virtual bool is_full () = 0;
        virtual size_t length () = 0;
        virtual void clear () = 0;
        virtual bool contains (element object, bool (*equals_function) (const element&, const element&)) = 0;
        virtual std::ostream& print (std::ostream& out) = 0;
        virtual element * contents () = 0;
};
}
#endif // LIST_H
