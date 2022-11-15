// testing the implementation of class Collection
// Mikhail Nesterenko
// 4/11/2022

#include <iostream>
#include "collection.hpp"

using std::cout; using std::endl;


void testfunc(Collection); // function to test pass-by-value for collection

int main() {

    Collection c1;

    // testing regular member functions
    c1.addNumber(1.);
    c1.addNumber(2.);
    c1.addNumber(3.);
    c1.addNumber(3.); // trying to add duplicate, should not add it

    cout << "c1 size is after number addition is: " << c1.size() << endl;
    cout << "Collection value: " << c1.value() << endl;

    if (c1.check(1.) != -1) // check() returns -1 if number not present
        cout << "1 is present in the array" << endl;

    if (c1.check(5.) != -1)
        cout << "5 is present in the array" << endl;

    cout << "c1 before removal of 2.0: "; c1.output();
    c1.removeNumber(2.);
    cout << "c1 after removal of 2.0: "; c1.output();

    // uncomment this when you debugged the first part
    
    testfunc(c1); // testing copy constructor

    cout << "c1 after testfunc call: ";
    c1.output(); // if destructor is implemented correctly
                 // this should print properly after testfunc completes

    Collection c2, c3;

    c3=c2=c1; // testing stackability of the overloaded assignment
    cout << "c3 after stackable assingment: ";
    c3.output();

    c3=c3; // testing protection against self-assingment
    cout << "c3 after self-assignment: ";
    c3.output();
    
}



// tests pass-by-value for object of class Collection
void testfunc(Collection c){ // copy constructor is invoked on "c"
    cout << "parameter c: ";
    c.output();
} // destructor is invoked when "c" goes out of scope

//member function definitions
int Collection::check(double number) {
    int arrayindex = 0;
    for (int i = 0; i < size_; i++) {
        if (col_[i] == number) {
            arrayindex = i;
            break;
        }

        else
            arrayindex = -1;
    }

    return arrayindex;
}
void Collection::addNumber(double number) {
    if (check(number) == -1) {
        double* tmp = new double[size_ + 1];
        size_++;
        for (int i = 0; i < size_ - 1; ++i) {
            tmp[i] = col_[i];
        }
        tmp[size_ - 1] = number;
        delete[] col_;
        col_ = tmp;
    }

}
void Collection::removeNumber(double number) {
    bool found = 0;
    if (check(number) != -1) {
        double* tmp = new double[size_ - 1];
        size_--;

        for (int i = 0; i < size_; ++i) {
            if (col_[i] == number) {
                found = 1;

            }
            else {
                if (!found)
                    tmp[i] = col_[i];
                else
                    tmp[i - 1] = col_[i];
            }
        }
        tmp[size_ - 1] = col_[size_];
        delete[] col_;
        col_ = tmp;
    }

}
void Collection::output() const {
    for (int i = 0; i < size_; ++i) {
        cout << col_[i] << " ";
    }
    cout << endl;
}
double Collection::value() const{
    double total = 0;

    for (int i = 0; i < size_; ++i) {
        total = total + (col_[i]);

    }

    return total;
}

//constructors
Collection::Collection() {
    
    size_ = 0;
    col_ = new double[0];

   
}

Collection::Collection(const Collection& c) {
  size_ = c.size_;
  for (int i = 0; i < size_; ++i) {
      col_[i] = c.col_[i];
  }
}

Collection& Collection::operator=(const Collection& c) {
    
    size_ = c.size_;
    for (int i = 0; i < size_; ++i) {
        col_[i] = c.col_[i];
    }
    delete[] c.col_;
    return *this;
}

//destructor
Collection::~Collection() {
    delete[] col_;
}
