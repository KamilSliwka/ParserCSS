#include <iostream>
#include "MyString.h"

using namespace std;

struct NodeS {
    MyString name;
    NodeS* next;
    NodeS* previous;
};

struct ListSel {

    NodeS* H = NULL;//Head
    NodeS* T = NULL;//Tail

    void addFirst(MyString name) {
        NodeS* tmp = new NodeS;
        tmp->name = name;
        tmp->previous = NULL;
        tmp->next = NULL;
        H = tmp;
        T = tmp;
    }

    void addBack(MyString name) {
        NodeS* tmp = new NodeS;
        if ((H == NULL) && (T == NULL)) {
            addFirst(name);
        }
        else {
            tmp->name = name;
            tmp->next = NULL;
            tmp->previous = T;
            T->next = tmp;
            T = tmp;
        }
    }

    void addFront(MyString name) {
        NodeS* tmp = new NodeS;
        if ((H == NULL) && (T == NULL)) {
            addFirst(name);
        }
        else {
            tmp->name = name;
            tmp->next = H;
            tmp->previous = NULL;
            H->previous = tmp;
            H = tmp;
        }
    }

    void deleteBack() {
        NodeS* tmp = T;
        NodeS* p = T;
        if (tmp->previous != NULL) {
            tmp = tmp->previous;
            tmp->next = NULL;
            T = tmp;
            delete p;
        }
        else {
            delete p;
            H = NULL;
            T = NULL;
        }
    }

    void deleteFront() {
        NodeS* tmp = H;
        NodeS* p = H;
        if (tmp->next != NULL) {
            tmp = tmp->next;
            tmp->previous = NULL;
            H = tmp;
            delete p;
        }
        else {
            delete p;
            H = NULL;
            T = NULL;
        }
    }

    void deleteAll() {
        if ((H == NULL) && (T == NULL)) {
            return;
        }
        else {
            while (numberOfElements() <= 0) {
                deleteBack();
            }
        }
        H = NULL;
        T = NULL;
    }

    int numberOfElements() {
        int s = 1;
        NodeS* p = H;
        if (p == NULL) {
            return 0;
        }
        else {
            while (p->next != NULL) {
                s++;
                p = p->next;
            }

            return s;
        }
    }
    bool ifNameExist(MyString n) {
        if ((numberOfElements() == 0) || (H == NULL)) {
            return false;
        }
        NodeS* p=NULL;
        p = H;
        while (p != NULL) {
            if (p->name == n) {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    MyString nameInThisIndex(int index) {
        NodeS* p = H;
        int i = 1;
        while (p != NULL) {
            if (index == i) {
                return p->name;
            }
            p = p->next;
            i++;
        }
        return "notExist";
    }
};


