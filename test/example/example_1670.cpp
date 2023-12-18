#include <iostream>


class FrontMiddleBackQueue {
public:
    struct Node {
        int val;
        Node *next, *prev;

        Node(int val) : val(val), next(nullptr), prev(nullptr) {} 
    };

    FrontMiddleBackQueue() : 
        count(0), head(new Node(0)), tail(new Node(0)) {
        head->next = tail;
        tail->prev = head;
        middle = tail;
    }

    ~FrontMiddleBackQueue() {
        Node *curr = head;
        while (curr != nullptr) {
            Node *temp = curr->next;
            delete(curr);
            curr = temp;
        }
    }
    
    void pushFront(int val) {
        Node *curr = new Node(val);
        Node *node1 = head, *node2 = head->next;
        node1->next = curr;
        curr->prev = node1;
        curr->next = node2;
        node2->prev = curr;
        count++;

        if (count % 2 == 1) {
            middle = middle->prev;
        }
    }
    
    void pushMiddle(int val) {
        Node *curr = new Node(val);
        Node *node1 = middle->prev, *node2 = middle;
        node1->next = curr;
        curr->prev = node1;
        curr->next = node2;
        node2->prev = curr;
        count++;

        if (count % 2 == 1) {
            middle = middle->prev;
        }
    }
    
    void pushBack(int val) {
        Node *curr = new Node(val);
        Node *node1 = tail->prev, *node2 = tail;
        node1->next = curr;
        curr->prev = node1;
        curr->next = node2;
        node2->prev = curr;
        count++;

        if (count % 2 == 0) {
            middle = middle->next;
        }
    }
    
    int popFront() {
        if (count == 0) {
            return -1;
        }
        if (count % 2 == 1) {
            middle = middle->next;
        }

        Node *curr = head->next;
        Node *node1 = curr->prev, *node2 = curr->next;
        node1->next = node2;
        node2->prev = node1;
        int result = curr->val;
        delete(curr);
        count--;
        return result;
    }
    
    int popMiddle() {
        if (count == 0) {
            return -1;
        }
        Node *curr = nullptr;
        if (count % 2 == 1) {
            curr = middle;
            middle = middle->next;
        } else {
            curr = middle->prev;
        }
        Node *node1 = curr->prev, *node2 = curr->next;
        node1->next = node2;
        node2->prev = node1;
        int result = curr->val;
        delete(curr);
        count--;
        return result;
    }
    
    int popBack() {
        if (count == 0) {
            return -1;
        }
        if (count % 2 == 0) {
            middle = middle->prev;
        }

        Node *curr = tail->prev;
        Node *node1 = curr->prev, *node2 = curr->next;
        node1->next = node2;
        node2->prev = node1;
        int result = curr->val;
        delete(curr);
        count--;
        return result;
    }
private:
    Node *head, *tail, *middle;
    int count;
};

/**
 * Your FrontMiddleBackQueue object will be instantiated and called as such:
 * FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
 * obj->pushFront(val);
 * obj->pushMiddle(val);
 * obj->pushBack(val);
 * int param_4 = obj->popFront();
 * int param_5 = obj->popMiddle();
 * int param_6 = obj->popBack();
 */

int main() {
    FrontMiddleBackQueue* obj = new FrontMiddleBackQueue();
    obj->pushFront(1);
    obj->pushBack(2);
    obj->pushMiddle(3);
    obj->pushMiddle(4);
    std::cout << obj->popFront() << std::endl;
    std::cout << obj->popMiddle() << std::endl;
    std::cout << obj->popMiddle() << std::endl;
    std::cout << obj->popBack() << std::endl;
    std::cout << obj->popFront() << std::endl;
}