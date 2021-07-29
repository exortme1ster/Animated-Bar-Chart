// barchart.h
// In this file we create a barchart

#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <map>
#include "myrandom.h" // used in autograder, do not remove
#include "bar.h"

using namespace std;

// Constants used for bar chart animation.  We will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RED("\033[1;36m");
const string PURPLE("\033[1;32m");
const string BLUE("\033[1;33m");
const string CYAN("\033[1;31m");
const string GREEN("\033[1;35m");
const string GOLD("\033[1;34m");
const string BLACK("\033[1;37m");
const string RESET("\033[0m");
const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

//
// BarChart
//
class BarChart {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // Bars.  As a result, you must also keep track of the number of elements
    // stored (size) and the capacity of the array (capacity).  This is not a
    // dynamic array, so it does not expand.
    //
    Bar* bars;  // pointer to a C-style array
    int capacity;
    int size;
    string framePr;

 public:
    // default constructor:
    BarChart() {
        bars = nullptr;
        capacity = 0;
        size = 0;
        framePr = "";
    }
    // parameterized constructor:
    // Parameter passed in determines memory allocated for bars.
    BarChart(int n) {
        bars = new Bar[n];
        capacity = n;
        size = 0;
        framePr = "";
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an BarChart that contains
    // a copy of an existing BarChart.  Example: this occurs when passing
    // BarChart as a parameter by value.
    //
    BarChart(const BarChart& other) {
    this->bars = new Bar[other.capacity];
    this->size = other.size;
    this->capacity = other.capacity;
    this->framePr = other.framePr;
    
        for (int i = 0; i < other.size; ++i) {
              this->bars[i] = other.bars[i];
            }
    }
    //
    // copy operator=
    //
    // Called when you assign one BarChart into another, i.e. this = other;
    //
    BarChart& operator=(const BarChart& other) {
    //
    // special case: are we assigning to ourself?
    //
    if (this == &other)
      return *this;
    // 
    // unlike a copy constructor, *this* vector exists and so we first
    // have to free the memory associated with this vector:
    //
    delete[] bars;  // since we new'd an array, we delete[] an array
    //
    // allocate this array with same capacity as the other:
    //
    this->bars = new Bar[other.capacity];
    this->size = other.size;
    this->capacity = other.capacity;
    this->framePr = other.framePr;
    //
    // now make a copy the elements from the other vector into this one:
    //
    for (int i = 0; i < other.size; ++i) {
      this->bars[i] = other.bars[i];
    }

    //
    // done, this vector is now a copy of the other vector:
    //
    return *this;  // we have to return a vector based on how = works:
    }
    // clear
    // frees memory and resets all private member variables to default values.
    void clear() {
        delete[] bars;
        bars = nullptr;
        size = 0;
        capacity = 0;
        framePr = "";
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the
    // BarChart.
    //
    virtual ~BarChart() {
        delete[] bars;
        bars = nullptr;
        size = 0;
        capacity = 0;
        framePr = "";
    }
    // setFrame
    // set the frame of the BarChart object.
    void setFrame(string frame) {
    	framePr = frame;
    }
    
    // getFrame()
    // Returns the frame of the BarChart oboject.
    string getFrame() {
        return framePr;
    }

    // addBar
    // adds a Bar to the BarChart.
    // we add until size reach capacity
    bool addBar(string name, int value, string category) {
      if(capacity != size) {
      bars[size] = Bar(name, value, category);
      size++;
      } else {
          return false;
      }
        return true;
    }
    // getSize()
    // Returns the size (number of bars) of the BarChart object.
    int getSize() {
        return size;
    }
    
    // operator[]
    // Returns Bar element in BarChart.
    // This gives public access to Bars stored in the Barchart.
    // If i is out of bounds, throw an out_of_range error message:
    // "BarChart: i out of bounds"
    Bar& operator[](int i) {
        return bars[i];
    }
    
    // dump
    // Used for printing the BarChart object.
    // mostly used for debug purpose
    void dump(ostream &output) {

        sort(bars, bars + capacity, greater<Bar>());
        output << "frame: " << getFrame() << endl;
            for (int i = 0; i < size; i++) {
         output << bars[i].getName() << " ";
         output << bars[i].getValue() << " ";
         output << bars[i].getCategory();
         output << endl;
    }
}
    // outpurFirst
    // function to output first(top) bar
    //
    void outputFirst(ostream &output,
    map<string, string> &colorMap, int top,
    int lengthMax, string barstring,
    string category) {
        for (int i = 0; i < lengthMax; i++) {
            barstring += BOX;
        }
          if (colorMap.count(category)) {
             output << colorMap[category] <<
             barstring << " " << bars[0].getName()
             << " " << bars[0].getValue() << endl;
            } else {
             output << colorMap["DEFAULT"] <<
             barstring << " " << bars[0].getName()
             << " " << bars[0].getValue() << endl;
            }
    }
    // outputOther
    // function to output other
    // bars (excluding top bar)
    void outputOther(ostream &output,
    map<string, string> &colorMap, int top,
    int lengthMax, string barstring,
    string category, int &counter, 
    double percentage, int &j) {
            for(int z = 0; z < percentage; z++) {
                barstring += BOX;
                counter++;
            }
            if(colorMap.count(category)) {
            output << colorMap[category] <<
            barstring << " " << bars[j].getName()
            << " " << bars[j].getValue() << endl;
            } else {
            output << colorMap["DEFAULT"] <<
            barstring << " " << bars[j].getName()
            << " " << bars[j].getValue() << endl;
            }
    }
    // graph
    // Used for printing out the bar.
    // top is used to output ezact amount of bars
    void graph(ostream &output, map<string, string> &colorMap, int top) {
    	int lenMax = 60;  // this is number of BOXs that should be printed
                          // for the top bar (max value)
        string color = "\033[1;37m";
        colorMap["DEFAULT"] = color;

        sort(bars, bars + capacity, greater<Bar>());
        string barstr = "";
        string category = bars[0].getCategory();
        outputFirst(output, colorMap, top,
        lenMax, barstr, category);
        double percentage = 0.0;
        double value = 0.0;
        string barstr1 = "";
        int counter = 0;
        for (int j = 1; j < top; j++) {
            string category1 = bars[j].getCategory();
            percentage = double(bars[j].getValue())
            / double(bars[0].getValue());
            value = percentage * lenMax;
            int perc = int(value);
            outputOther(output, // output other bars
            colorMap, top,
            lenMax, barstr1,
            category1, counter, 
            perc, j);
            barstr1 = "";
            counter = 0;
        }
    }
};
