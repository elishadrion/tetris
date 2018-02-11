#include "LinkedList.hpp"

LinkedList::LinkedList() {
    set_head(nullptr);
}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        Node* next_head = head->next;
        delete head->user;
        delete head;
        set_head(next_head);
    }
}

void LinkedList::set_head(Node* node) {
    head = node;
}

void LinkedList::prepend(User* usr) {
    Node* node = new Node;
    node->user = usr;
    node->next = head;
    set_head(node);
}

unsigned LinkedList::get_length() const {
    return length;
}

Node* LinkedList::get_head() const {
	return head;
}
