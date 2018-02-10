#ifndef LIST_HPP
#define LIST_HPP
#include "User.hpp"
class Node {
    public:
        Node* next;
        User* user;
}

class LinkedList {
    private:
        unsigned length;
        Node* head;

    public:
        LinkedList();
        ~LinkedList();
        void prepend(User*);
        void set_head(Node*);
        unsigned get_length() const;

};


#endif