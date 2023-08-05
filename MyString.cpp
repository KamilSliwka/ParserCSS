#include "MyString.h"
#include <iostream>

using namespace std;

MyString::MyString() {
    data = nullptr;
    length = 0;
}

MyString::MyString(const char* str) {
    length = 0;
    while (str[length] != '\0') {
        length++;
    }
    data = new char[2*length ];
    for (int i = 0; i < length; i++) {
        data[i] = str[i];
    }
    data[length] = '\0';
}

MyString::MyString(const MyString& other) {
    length = other.length;
    data = new char[2*length];
    for (int i = 0; i < length; i++) {
        data[i] = other.data[i];
    }
    data[length] = '\0';
}

MyString::~MyString() {
    if (length > 0) {
        delete[] data;
    }
}

MyString& MyString::operator=(const MyString& other)  {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[2*length];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
        data[length] = '\0';
    }
    return *this;
}

char& MyString::operator[](int index) {
    return data[index];
}

const char& MyString::operator[](int index) const {
    return data[index];
}

int MyString::size() const {
    return length;
}

bool MyString::equals(MyString a, MyString b) {
    int sa = a.length;
    int sb = b.length;
    int n = 0;
    if (sa > sb) {
        n = sa;
    }
    else {
        n = sb;
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool MyString::operator==(const MyString& other) {
    if (length != other.length) {
        return false;
    }
    else {
        return equals(data, other);
    }
}

MyString MyString::deletesSpace() {
    MyString p = data;
    for (int i = 0; i < size(); i++) {
        if (p[i] ==' ') {
            for (int j = 0; j < size() - i; j++) {
                p[i+j] = p[i+j + 1];

            }
            i--;
            p.length--;
        }
    }
    return p;
}

MyString MyString::deletesEnter() {
    MyString p = data;
    for (int i = 0; i < size(); i++) {
        if (p[i] == '\n'||p[i]=='\t'||p[i]=='\r') {
            for (int j = 0; j < size() - i; j++) {
                p[i + j] = p[i + j + 1];

            }
            i--;
            p.length--;
        }
    }
    return p;
}

MyString MyString::deleteLeadingSpaces() {
    int leadingSpaces = 0;
    while (data[leadingSpaces] == ' ') {
        leadingSpaces++;
    }

    char* new_data = new char[length - leadingSpaces + 1];
    for (int i = 0; i < length - leadingSpaces; i++) {
        new_data[i] = data[i + leadingSpaces];
    }
    new_data[length - leadingSpaces] = '\0';
    return MyString(new_data);
}

    ostream& operator<<(ostream& os, const MyString& str) {
    os << str.data;
    return os;
}

void MyString::append(char c) {
    char* new_data = new char[length + 2];
    for (int i = 0; i < length; i++) {
        new_data[i] = data[i];
    }
    new_data[length] = c;
    new_data[length + 1] = '\0';
    delete[] data;
    data = new_data;
    length++;
}



int MyString::find(char c) {
    MyString p = data;
    for (int i = 0; i < size(); i++) {
        if (p[i] == c) {
            return i;
        }
    }
    return -1;
}


MyString MyString::substring_after(char c) {
    int pos = find(c);
    if (pos == -1) {
        return MyString(data);
    }
    char* new_data = new char[pos + 1];
    for (int i = 0; i < pos; i++) {
        new_data[i] = data[i];
    }
    new_data[pos] = '\0';
    return MyString(new_data);
}

MyString MyString::removeSpaces(const MyString& str) {
    int start = 0, end = str.size() - 1;

    while (start < end && str[start] == ' ') {
        start++;
    }

    while (end >= start && str[end] == ' ') {
        end--;
    }

    char* new_data = new char[end - start + 2];
    for (int i = start; i <= end; i++) {
        new_data[i - start] = str[i];
    }
    new_data[end - start + 1] = '\0';
    MyString result(new_data);
    delete[] new_data;
    return result;
}

int MyString::toInt(const MyString& str) {
    int result = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
        else {
            return 0;
        }
    }
    return result;
}
