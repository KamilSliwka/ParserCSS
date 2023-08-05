#include <iostream>
#include "MyString.cpp"

using namespace std;

struct NodeA {
    MyString name;
    MyString value;
    NodeA* next;
    NodeA* previous;
};

struct ListAtr {

    NodeA* H = NULL;//Head
    NodeA* T = NULL;//Tail

    void addFirst(MyString name,MyString value) {
        NodeA* tmp = new NodeA;
        tmp->name = name;
        tmp->value = value;
        tmp->previous = NULL;
        tmp->next = NULL;
        H = tmp;
        T = tmp;
    }

    void addBack(MyString name, MyString value) {
        NodeA* tmp = new NodeA;
        if ((H == NULL) && (T == NULL)) {
            addFirst(name,value);
        }
        else {
            tmp->name = name;
            tmp->value = value;
            tmp->next = NULL;
            tmp->previous = T;
            T->next = tmp;
            T = tmp;
        }
    }

    void addFront(MyString name, MyString value) {
        NodeA* tmp = new NodeA;
        if ((H == NULL) && (T == NULL)) {
            addFirst(name,value);
        }
        else {
            tmp->name = name;
            tmp->value = value;
            tmp->next = H;
            tmp->previous = NULL;
            H->previous = tmp;
            H = tmp;
        }
    }

    void deleteBack() {
        NodeA* tmp = T;
        NodeA* p = T;
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
        NodeA* tmp = H;
        NodeA* p = H;
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
            while ((H == NULL) && (T == NULL)) {
                deleteBack();
            }
        }
        H = NULL;
        T = NULL;
    }

    int numberOfElements() {
        int s = 1;
        NodeA* p = H;
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
        NodeA* p = NULL;
        p = H;
        while (p != NULL) {
            if (p->name == n) {
                return true;
            }
            p = p->next;
        }
        return false;
    }

    MyString valueOfName(MyString n) {
        NodeA* p = H;
        while (p != NULL) {
            if (p->name == n) {
                return p->value;
            }
            p = p->next;
        }
        return"error";
    }

    void delAttribute(MyString n) {
        if (H->name == n) {
            deleteFront();
            return;
        }
        NodeA* p = H;
        while (p->next != NULL) {
            if (p->name == n) {
                NodeA* s = p;
                s = p->previous;
                s->next = p->next;
                s = p->next;
                s->previous = p->previous;
                delete p;
                return;
            }
            p = p->next;
        }
    }

    MyString nameInThisIndex(int index) {
        NodeA* p = H;
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

