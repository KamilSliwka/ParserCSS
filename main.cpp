#pragma once
#include <iostream>
#include "MyString.h"
#include "ListOfAttribute.cpp"
#include "ListOfSelector.cpp"
#include "MainList.cpp"

using namespace std;


void selectors(MyString *x,char *b,ListofBlock *mainList,bool *s) {
    MyString tmp;
    MyString p;
    *x = (*x).substringAfter('}');
    *x = (*x).removeSpaces(*x);
    *x = (*x).deletesEnter();
    tmp = *x;
    p = *x;
    while (!(tmp == tmp.substringUntil(','))) {
        tmp = p.substringUntil(',');
        tmp = tmp.removeSpaces(tmp);
        (* mainList).addSelector(tmp);
        tmp = p.substringAfter(',');
        p = p.substringAfter(',');
        *b = '{';
    }
    tmp = tmp.removeSpaces(tmp);
    (* mainList).addSelector(tmp);
    *s = true;
}

void atribute(MyString* x, char* b, ListofBlock* mainList,bool* h,MyString* atr) {
    MyString tmp;
    MyString p;
    *h = false;
    *x = (* x).substringAfter(*b);
    *x =  (* x).substringAfter('{');
    tmp = *x;
    p = *x;
    tmp = p.substringUntil(':');
    tmp = tmp.substringAfter('{');
    *atr = tmp.deletesEnter();
    *atr = (* atr).deleteLeadingSpaces();
    *b = ':';
}
void valueFirst(MyString* x, char* b, ListofBlock* mainList, bool* h, MyString* atr) {
    MyString tmp;
    MyString p;
    MyString val;
    *x = (* x).substringAfter(*b);
    tmp = *x;
    p = *x;
    tmp = p.substringUntil(';');
    val = tmp.deletesEnter();
    val = val.deleteLeadingSpaces();
    (* mainList).addAttributeAndValue(*atr, val);
    *b = ';';
    *h = true;
    *x = " ";
}

void valueSecond(MyString* x, char* b, ListofBlock* mainList, bool* h, MyString* atr, bool *s) {
    MyString tmp;
    MyString p;
    MyString val;
    *x = (* x).substringAfter(*b);
    tmp = *x;
    p = *x;
    tmp = p.substringUntil('}');
    val = tmp.deletesEnter();
    val = val.deleteLeadingSpaces();
    *s = false;
    (* mainList).addAttributeAndValue(*atr, val);
    *b = ';';
    *x = " ";
    (*mainList).addSection();
}
void selectorAmount(ListofBlock* mainList, MyString* x) {
    int i;
    *x = (*x).substringUntil(',');
    i = (*x).toInt(*x);
    if ((*mainList).numberOfSection() >= i) {
        cout << i << ",S,? == " << (*mainList).sectionInIndex(i).selector->numberOfElements() << endl;
    }
}
void attributeAmount(ListofBlock* mainList, MyString* x) {
    int i;
    *x = (* x).substringUntil(',');
    i = (* x).toInt(*x);
    if ((*mainList).numberOfSection() >= i) {
        cout << i << ",A,? == " << (*mainList).sectionInIndex(i).attribute->numberOfElements() << endl;
    }
}
void AllSectionsSelectorAmount(ListofBlock* mainList, MyString* x) {
    *x = (* x).substringUntil(',');
    *x = (*x).deleteLeadingSpaces();

    int i = (* mainList).numberOfSelector(*x);
    cout << *x << ",S,? == " << i << endl;
}
void  AllSectionsAttributeAmount(ListofBlock* mainList, MyString* x) {
    *x = (* x).substringUntil(',');
    int i = (* mainList).numberOfAttribute(*x);
    cout << *x << ",A,? == " << i << endl;
}
void selectorOnIndex(ListofBlock* mainList, MyString* x) {
    MyString tmp = *x;
    int i;
    int j;
    *x = (* x).substringUntil(',');
    i = (* x).toInt(*x);
    tmp = tmp.substringAfter(',');
    tmp = tmp.substringAfter(',');
    j = tmp.toInt(tmp);
    if (((*mainList).numberOfSection() >= i) && ((* mainList).sectionInIndex(i).selector->numberOfElements() >= j)) {
        cout << i << ",S," << j << " == " << (* mainList).sectionInIndex(i).selector->nameInThisIndex(j) << endl;
    }
}
void nameOfAttribute(ListofBlock* mainList, MyString* x) {
    MyString tmp = *x;
    int i;
    *x = (* x).substringUntil(',');
    i = (* x).toInt(*x);
    tmp = tmp.substringAfter(',');
    tmp = tmp.substringAfter(',');
    if (((*mainList).numberOfSection() >= i) && ((*mainList).sectionInIndex(i).attribute->ifNameExist(tmp))) {
        cout << i << ",A," << tmp << " == " << (*mainList).sectionInIndex(i).attribute->valueOfName(tmp) << endl;
    }
}
void deleteSectionOnIndex(ListofBlock* mainList, MyString* x) {
    int i;
    *x = (* x).substringUntil(',');
    i = (* x).toInt(*x);
    int s = (* mainList).numberOfSection();
    if (s == 1) {
        (* mainList).deleteAll();
        cout << i << ",D,* == deleted" << endl;
        (* mainList).addBack();
    }
    else if (s >= i) {
        (* mainList).delSection(i);
        cout << i << ",D,* == deleted" << endl;
    }

}

void deleteAttribute(ListofBlock* mainList, MyString* x) {
    MyString tmp = *x;
    int i;
    *x = (* x).substringUntil(',');
    i = (* x).toInt(*x);
    tmp = tmp.substringAfter(',');
    tmp = tmp.substringAfter(',');
    if (((* mainList).numberOfSection() >= i) && ((* mainList).sectionInIndex(i).attribute->ifNameExist(tmp))) {
        (* mainList).delAtributeInSection(i, tmp);
        cout << i << ",D," << tmp << " == " << "deleted" << endl;
    }
}

void valueOfAttribute(ListofBlock* mainList, MyString* x) {
    MyString tmp = *x;
    *x = (* x).substringUntil(',');
    tmp = tmp.substringAfter(',');
    tmp = tmp.substringAfter(',');
    MyString v = (* mainList).valueOfAttributeForSelector1(tmp, *x);
    if (!(v == "brak")) {
        cout << *x << ",E," << tmp << " == " << v << endl;
    }
}

int main()
{    ListofBlock mainList;
    mainList.addFront();
    MyString x="\n";
    char sign;
    char b = '{';
    MyString atr;
    bool h = false;
    bool s = false;
    bool cssparse = true;
    int change = 0;
    int exit=0;
    while (cin.get(sign)) {

        if (cssparse) {
            if (sign == '{') {
                if (x.deletesSpace().deletesEnter().size()> 1) {
                    selectors(&x, &b, &mainList, &s);
                }
            }
            else if ((sign == ':')&&(s==true)) {
                atribute(&x, &b, &mainList, &h, &atr);
            }
            else if (sign == ';') {
                valueFirst(&x, &b, &mainList, &h, &atr);
            }
            else if ((sign == '}') && (h == false)) {
                valueSecond(&x, &b, &mainList, &h, &atr, &s);
            }
            else if ((sign == '}') && (h == true)) {
                x = " ";
                mainList.addSection();
                s = false;
            }
            if (sign == '?') {
                change++;
                if (change == 4) {
                    cssparse=false;
                    x=" ";
                }
            }
            else {
                change = 0;
            }
            if (cssparse) {
                x.append(sign);
            }
        }
        else {
            if (sign != '\n') {
                x.append(sign);
            }
            if (x.substringAfter('0') == "000"){
                break;
            }
            if ((sign == '\n') && (x.size() > 1)) {
                x = x.removeSpaces(x);
                x = x.deletesEnter();
                if (x == "?") {
                    cout << "? == " << mainList.numberOfSection() << endl;
                }
                else if (x == "****") {
                    cssparse = true;
                    x = " ";
                    x.append(sign);
                }
                else if ((x.substringAfter(',') == "S,?") && ((isdigit(x[0])))) {
                    selectorAmount(&mainList,&x);
                }
                else if ((x.substringAfter(',') == "A,?") && ((isdigit(x[0])))) {
                    attributeAmount(&mainList, &x);
                }
                else if ((x.substringAfter(',') == "S,?") && (!(isdigit(x[0])))) {
                    AllSectionsSelectorAmount(&mainList, &x);
                }
                else if ((x.substringAfter(',') == "A,?") && (!(isdigit(x[0])))) {
                    AllSectionsAttributeAmount(&mainList, &x);
                }
                else if (x.substringAfter(',').substringUntil(',') == "S") {
                    selectorOnIndex(&mainList, &x);
                }
                else if (x.substringAfter(',').substringUntil(',') == "A") {
                    nameOfAttribute(&mainList, &x);
                }
                else if (x.substringAfter(',') == "D,*") {
                    deleteSectionOnIndex(&mainList, &x);
                }
                else if (x.substringAfter(',').substringUntil(',') == "D") {
                    deleteAttribute(&mainList, &x);
                }
                else if (x.substringAfter(',').substringUntil(',') == "E") {
                    valueOfAttribute(&mainList, &x);
                }
                x = " ";
            }
        }
    }
    mainList.deleteAll();
    return 0;
}



