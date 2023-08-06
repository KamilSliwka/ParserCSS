#include <iostream>
#include "ListOfSelector.cpp"
#include "ListOfAttribute.cpp"
#include "MyString.h"
#define SIZE 8

using namespace std;


struct Section {
    ListAtr* attribute;
    ListSel* selector;

    Section() {
        ListAtr* pAtr = new ListAtr;
        ListSel* pSel = new ListSel;
        attribute = pAtr;
        selector = pSel;
    }
    bool operator==(const Section& other) {
        if ((attribute==other.attribute)&&(selector==other.selector)) {
            return true;
        }
        else {
            return false;
        }
    }
};

struct Block {
    Section* array = new Section[SIZE];
    int number = 0;
};

struct Node {
    Block* block ;
    Node* next;
    Node* previous;
};



struct ListofBlock {

    Node* H = NULL;//Head
    Node* T = NULL;//Tail

    void addFirst() {
        Node* tmp = new Node;
        tmp->block = new Block;
        tmp->previous = NULL;
        tmp->next = NULL;
        H = tmp;
        T = tmp;
    }

    void addBack() {
        Node* tmp = new Node;
        if ((H == NULL) && (T == NULL)) {
            addFirst();
        }
        else {
            tmp->block = new Block;
            tmp->next = NULL;
            tmp->previous = T;
            T->next = tmp;
            T = tmp;
        }
    }

    void addFront() {
        Node* tmp = new Node;
        if ((H == NULL) && (T == NULL)) {
            addFirst();
        }
        else {
            tmp->block = new Block;
            tmp->next = H;
            tmp->previous = NULL;
            H->previous = tmp;
            H = tmp;
        }
    }

    void deleteNode(Node* p) {
        int r = p->block->number;
        for (int i = 0; i < r; i++) {
            p->block->array[i].attribute->deleteAll();
            p->block->array[i].selector->deleteAll();
        }
        delete p->block->array;
        delete p->block;

    }

    void deleteBack() {
        Node* tmp = T;
        Node* p = T;
        if (tmp->previous != NULL) {
            tmp = tmp->previous;
            tmp->next = NULL;
            T = tmp;
            deleteNode(p);
            delete p;
        }
        else {
            deleteNode(p);
            delete p;
            H = NULL;
            T = NULL;
        }
    }

    void deleteFront() {
        Node* tmp = H;
        Node* p = H;
        if (tmp->next != NULL) {
            tmp = tmp->next;
            tmp->previous = NULL;
            H = tmp;
            deleteNode(p);
            delete p;
        }
        else {
            deleteNode(p);
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

    void addSection() {
        Node* tmp = T;
        if(tmp->block->number>= SIZE ){
            addBack();
            tmp = tmp->next;
        }
        tmp->block->number++;
    }

    void addSelector(MyString selector) {
        Node* tmp = T;
        int i = tmp->block->number;

        if (i < SIZE) {
            tmp->block->array[i].selector->addBack(selector);
        }
        else {
            addBack();
            tmp = tmp->next;
            tmp->block->array[0].selector->addBack(selector);
        }
    }

    void addAttributeAndValue(MyString atr,MyString val) {
        Node* tmp = T;
        int i = tmp->block->number;
        if (i < SIZE) {
            if (tmp->block->array[i].attribute->ifNameExist(atr)) {
                tmp->block->array[i].attribute->delAttribute(atr);
            }
            tmp->block->array[i].attribute->addBack(atr,val);
        }
        else {
            addBack();
            tmp = tmp->next;
            if (tmp->block->array[i].attribute->ifNameExist(atr)) {
                tmp->block->array[i].attribute->delAttribute(atr);
            }
            tmp->block->array[0].attribute->addBack(atr,val);
        }
    }

    int numberOfSection() {
        Node* tmp = H;
        int index = 0;
        while (tmp!=NULL) {
            index += tmp->block->number;
            tmp = tmp->next;
        }
        return index;
    }

    Block* blockWhereIsSection(int i) {
        Node* tmp = H;
        int index = 0;
        while (tmp != NULL) {
            index += tmp->block->number;
            if (index >= i) {
                break;
            }
            tmp = tmp->next;
        }
        return tmp->block;
    }

    Section sectionInIndex(int i) {
        Node* tmp = H;
        int index = 0;
        int p = 0;
        while (tmp != NULL) {
            index += tmp->block->number;
            if (index >= i) {
                break;
            }
            tmp = tmp->next;
        }
        index = index - tmp->block->number;
        p = i-index;
        return tmp->block->array[p-1];
    }

    void delSection(int i) {
        Section x = sectionInIndex(i);
        Block* z = blockWhereIsSection(i);
        int n = 0;
        for (int j = 0; j < SIZE; j++) {
            if (z->array[j] == x) {
                n = j;
                z->array[j].attribute->deleteAll();
                z->array[j].selector->deleteAll();
                break;
            }
        }
        for (int j = n; j < z->number-1; j++) {
            z->array[j] = z->array[j + 1];
        }
        z->number--;
        if (z->number == 0) {
            Node* p = H;
            while (p!= NULL) {
                if (p->block == z) {
                    if (p == H) {
                        deleteFront();
                        return;
                    }
                    else if (p==T) {
                        deleteBack();
                        return;
                    }
                    else {
                        Node* s = p;
                        s = p->previous;
                        s->next = p->next;
                        s = p->next;
                        s->previous = p->previous;
                        delete p;
                        return;
                    }
                }
                p = p->next;
            }
        }
    }

    void delAtributeInSection(int i,MyString n) {
        Section x = sectionInIndex(i);
        Block* z = blockWhereIsSection(i);
        if (x.attribute->ifNameExist(n)) {
            x.attribute->delAttribute(n);
        }
        if (x.attribute->numberOfElements() == 0) {
            delSection(i);
        }
    }

    Section firstSection() {
        return H->block->array[0];
    }

    Section lastSection() {
        return T->block->array[SIZE-1];
    }

    int numberOfAttribute(MyString n) {
        Node* p = H;
        int cout = 0;
        while (p != NULL) {
            for (int i = 0; i < SIZE; i++) {
                if (p->block->number < i + 1) {
                    break;
                }
                if (p->block->array[i].attribute->ifNameExist(n)) {
                    cout++;
                }

            }
            p = p->next;
        }
        return cout;
    }

    int numberOfSelector(MyString n) {
        Node* p = H;
        int cout = 0;
        while (p != NULL) {
            for (int i = 0; i < SIZE; i++) {
                if (p->block->number < i + 1) {
                    break;
                }
                if (p->block->array[i].selector->ifNameExist(n)) {
                    cout++;
                }
            }
            p = p->next;
        }
        return cout;
    }

    MyString valueOfAttributeForSelector1(MyString n, MyString z) {
        for (int i = numberOfSection(); i > 0; i--) {
            int j=sectionInIndex(i).selector->numberOfElements();
            for(int k=1;k<=j;k++){
                if (z == sectionInIndex(i).selector->nameInThisIndex(k)) {
                    if (sectionInIndex(i).attribute->ifNameExist(n)) {
                        return sectionInIndex(i).attribute->valueOfName(n);
                    }
                }
            }
        }
        return "brak";
    }
};


