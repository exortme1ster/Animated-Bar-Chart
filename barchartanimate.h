// barchartanimate.h
// Here we animate barcharts
#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <unistd.h>
#include "myrandom.h"  // used in autograder, do not remove
#include "barchart.h"

using namespace std;
//
// BarChartAnimate
//
class BarChartAnimate {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, bars, to store a list of
    // BarCharts.  As a result, you must also keep track of the number of
    // elements stored (size) and the capacity of the array (capacity).
    // This IS dynamic array, so it must expand automatically, as needed.
    //
    BarChart* barcharts; // pointer to a C-style array
    int size;
    int capacity;
    map<string, string> colorMap;
    string titlePr;
    string xlabelPr;
    string sourcePr;
    string framePr;

 public:
    // a parameterized constructor:
    // Like the ourvector, the barcharts C-array should be constructed here
    // with a capacity of 4.
    BarChartAnimate(string title, string xlabel, string source) {
    size = 0;
    capacity = 4;
    barcharts = new BarChart[4];
    titlePr = title;
    xlabelPr = xlabel;
    sourcePr = source;
    framePr = "";
    }
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated
    // by BarChartAnimate.
    //
    virtual ~BarChartAnimate() {
    delete[] barcharts;
    barcharts = nullptr;
    size = 0;
    capacity = 4;
    framePr = "";
    titlePr = "";
    xlabelPr = "";
    sourcePr = "";
    }
    //
    // separate function
    // to take words
    //
    string separate(string &word) {
    // Copy three characters of s1 (starting
    // from position 1)
    int pos = word.find(",");
    string sub;
    sub = word.substr(0, pos);
    return sub;
    }
    //
    // Update function to update words after we separated
    //
    void wordUpdate(string &word) {
    int pos = word.find(",");
    word = word.substr(pos + 1);
    }
    // getWords
    // function to getWords and COLORS
    void getWords(int &bcsize_, ifstream &file,
    string &frame_, string &city_, string &line_,
    string &country_, string &popul_, int &population_,
    string &region_, map<string, string> &colorMap,
    int &counter_) {
        getline(file, line_);
        frame_ = separate(line_);
        wordUpdate(line_);
        city_ = separate(line_);
        wordUpdate(line_);
        country_ = separate(line_);
        wordUpdate(line_);
        popul_ = separate(line_);
            if(popul_ != " ") {
            population_ = stoi(popul_);
            }
        wordUpdate(line_);
        region_ = separate(line_);
            if (!colorMap.count(region_)) {
            colorMap[region_] = COLORS.at(counter_%7);
            counter_++;
            }
        wordUpdate(line_);
        }
    // sizeChecker
    // double the size each time it reaches 4
    //
    void sizeChecker() {
         if (size == capacity) {
         int newCapacity = capacity * 2;
         BarChart* newA = new BarChart[newCapacity];
      // copy the elements from A to the new array:
      for (int i = 0; i < size; ++i) {
        newA[i] = barcharts[i];
      }
      // now delete A, and update private data members to point to new array
      // and reflect new capacity:
      delete[] barcharts;
      barcharts = newA;
      capacity = newCapacity;
        }
    }
    // addFrame:
    // adds a new BarChart to the BarChartAnimate object from the file stream.
    // each year has information that we keep in barcharts
    void addFrame(ifstream &file) {
        string line = " ";
        string frame;
        string city;
        string country;
        string popul;
        string region;
        int population;
        string bsize;
        string space;
        int counter = 0;
        getline(file, space, '\n');
        getline(file, bsize, '\n');
        int bcsize = 0;
        if(bsize != "") {
        bcsize = stoi(bsize);
        } else {
            return;
        }
        BarChart bc(bcsize);
        for(int i = 0; i < bcsize; i++) {
        getWords(bcsize, file, frame, city,
        line, country, popul, population,
        region, colorMap, counter);
            if (!file.fail()) {
            bc.setFrame(frame);
            bc.addBar(city, population, region);
            }
        }
        sizeChecker();
        barcharts[size] = bc;
        if (frame != " ")
    	size++;
    }
    // animate:
    // this function plays each frame stored in barcharts.
    // if we didn't recieve color it is 
    // printed using BLACK
	void animate(ostream &output, int top, int endIter) {
		unsigned int microsecond = 50000;
        if(endIter != -1) {
            for(int i = 0; i < endIter; i++) {
                usleep(3 * microsecond);
                output << CLEARCONSOLE;
                output << BLACK << titlePr << endl;
                output << BLACK << sourcePr << endl;
                barcharts[i].graph(output, colorMap, top);
                output << BLACK << xlabelPr << endl;
                output << BLACK << "Frame: "
                << barcharts[i].getFrame() << endl;
            }
        } else {
                for(int i = 0; i < size; i++) {
                 usleep(3 * microsecond);
                 output << CLEARCONSOLE;
                 output << BLACK << titlePr << endl;
                 output<< BLACK << sourcePr << endl;
                 barcharts[i].graph(output, colorMap, top);
                 output << BLACK << xlabelPr << endl;
                 output << BLACK << "Frame: "
                 << barcharts[i].getFrame() << endl;
            } 
        }
	}
    //
    // Public member function.
    // Returns the size of the BarChartAnimate object.
    //
    int getSize() {
        return size;
    }
    //
    // Public member function.
    // Returns BarChart element in BarChartAnimate.
    BarChart& operator[](int i) {
        return barcharts[i];
    }
};
