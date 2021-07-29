// bar.h
// This file is used to create bars

#include <iostream>
#include <string>
#include "myrandom.h" // used in autograder, do not remove
using namespace std;

//
// Bar
//
class Bar {
 private:
    // Private member variables for a Bar object
    string categoryPr;
    string namePr;
    int valuePr;
    // int value;
 public:

    // default constructor:
    Bar() {
        categoryPr = "";
        namePr = "";
        valuePr = 0;
    }
    //
    // a second constructor:
    //
    // Parameter passed in constructor Bar object.
    //
    Bar(string name, int value, string category) {
        categoryPr = category;
        namePr = name;
        valuePr = value;
        // this->value = value;
    }

    // destructor:
    virtual ~Bar() {
        // cout << "Object destroyed yo!!!" << endl;
        
    }

    // getName:
	string getName() const {
        
        return namePr; 
	}

    // getValue:
	int getValue() const {
        return valuePr;   
	}

    // getCategory:
	string getCategory() const {
        return categoryPr; 
	}

	// operators
	bool operator<(const Bar &other) const {
	    return this->getValue() < other.getValue();
	}

	bool operator<=(const Bar &other) const {
        return this->getValue() <= other.getValue();
	}

	bool operator>(const Bar &other) const {
        return this->getValue() > other.getValue();
	}

	bool operator>=(const Bar &other) const {
        return this->getValue() >= other.getValue();
	}
};

