#include <iostream>
#include "barchartanimate.h"
using namespace std;


bool testBarDefaultConstructor() {
	Bar b;
    if (b.getName() != "") {
    	cout << "testBarDefaultConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 0) {
    	cout << "testBarDefaultConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "") {
    	cout << "testBarDefaultConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarDefaultConstructor: all passed!" << endl;
    return true;
}

bool testBarParamConstructor() {
	Bar b("Chicago", 9234324, "US");
    if (b.getName() != "Chicago") {
    	cout << "testBarParamConstructor: getName failed" << endl;
    	return false;
    } else if (b.getValue() != 9234324) {
    	cout << "testBarParamConstructor: getValue failed" << endl;
    	return false;
    } else if (b.getCategory() != "US") {
    	cout << "testBarParamConstructor: getCategory failed" << endl;
    	return false;
    }
    cout << "testBarParamConstructor: all passed!" << endl;
    return true;
}

bool testLessMoreOperator() {
    Bar b1("a", 1, "cat");

    Bar b2("b", 2, "cat");
    
    //(b1 < b2) should return true.  (b2 < b1) should return false.

    //(b1 > b2) should return false.  (b2 > b1) should return true.
    
    if(b2.getValue() < b1.getValue()) {
        cout << "testComparisonOperator: < failed" << endl;
        return false;
    } else if(b1.getValue() > b2.getValue()) {
        cout << "testComparisonOperator: < failed" << endl;
        return false;
    }
    
    cout << "testLessMoreOperator: all passed!" << endl;
    return true;
 
}

bool testBarChartTests() {
    BarChart bc1;
    BarChart bc2(10);
    bc1 = bc2;
    if(bc1.getSize() == bc2.getSize()) {
        return true;
    } else {
    return false;
    }
    BarChart bc(4);
    bc.setFrame("1950");
    cout << bc.getFrame() << endl;
    
    if(bc.getFrame() == "1950") {
        return true;
    } else {
        return false;
    }
    
    bc.clear();
    if(bc.getSize() == 0) {
        return true;
    } else {
        return false;
    }
    
    bc.addBar("Chicago", 1020, "US");
    bc.addBar("NYC", 1300, "US");
    bc.addBar("Paris", 1200, "France");
    bc.addBar("Huyna", 1200, "Ukraine");
    
    bc.dump(cout);
    
    string red("\033[1;36m");
    string blue("\033[1;33m");
    string gold("\033[1;34m");
    map<string, string> colorMap;
    colorMap["US"] = red;
    colorMap["France"] = blue;
    colorMap["Ukraine"] = gold;
    bc.graph(cout, colorMap, 4);
    int n = bc.getSize();
    for (int i = 0; i < n; i++) {
      cout << bc[i].getName() << " ";
      cout << bc[i].getValue() << " ";
      cout << bc[i].getCategory();
      cout << endl;
    }
    
    cout << "Size is: " << n << endl;
    return true;
}

bool testBarChartAnimateTests() {
	
	string filename = "brands.txt";
	ifstream inFile(filename);
	string title;
	getline(inFile, title);
	string xlabel;
	getline(inFile, xlabel);
	string source;
	getline(inFile, source);

	BarChartAnimate bca(title, xlabel, source);
	
	if(bca.getSize() == 0) {
	    return true;
	} else {
	    return false;
	}
 		while (!inFile.eof()) {
		bca.addFrame(inFile);
		cout << "Size is: " << bca.getSize << endl;
	}
	int n = bca.getSize();
	cout << "Final size is: " << n << endl;
	for (int i = 0; i < n; i++) {
  cout << bca[i].getFrame();
  cout << endl;
}
	
	bca.addFrame(inFile);
	bca.animate(cout, 12, -1);
	
    
    return true;
}

int main() {
 	testBarDefaultConstructor();
	testBarParamConstructor();
 	testLessMoreOperator();
 	testBarChartTests();
	testBarChartAnimateTests();
	
    return 0;
}