#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class RadioRange {
public:
    double RadiusProbability(vector <int> x, vector <int> y, vector <int> r, int maxR) {
        vector<pair<double, int> > v;
        for (int i = 0; i < (int)x.size(); i++){
        	double d = sqrt(x[i] * 1LL * x[i] + y[i] * 1LL * y[i]);
        	v.pb(mp(max(d - r[i], 0.0), 1));
        	v.pb(mp(min(d + r[i], (double)maxR), -1));
        }
        v.pb(mp((double)maxR, 0));
        double good = 0;
        int bal = 0;
        sort(v.begin(), v.end());
        ld last = 0;
        for (int i = 0; i < (int)v.size(); i++){
        	if (bal == 0) good += v[i].first - last;
        	last = v[i].first;
        	bal += v[i].second;
        }
        return good / maxR;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit-pf 2.3.0
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, vector <int> p2, int p3, bool hasAnswer, double p4) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p2[i];
	}
	cout << "}" << "," << p3;
	cout << "]" << endl;
	RadioRange *obj;
	double answer;
	obj = new RadioRange();
	clock_t startTime = clock();
	answer = obj->RadiusProbability(p0, p1, p2, p3);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p4 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == answer && fabs(p4 - answer) <= 1e-9 * max(1.0, fabs(p4));
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	bool disabled;
	bool tests_disabled;
	all_right = true;
	tests_disabled = false;
	
	vector <int> p0;
	vector <int> p1;
	vector <int> p2;
	int p3;
	double p4;
	
	// ----- test 0 -----
	disabled = false;
	p0 = {0};
	p1 = {0};
	p2 = {5};
	p3 = 10;
	p4 = 0.5;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = {0};
	p1 = {0};
	p2 = {10};
	p3 = 10;
	p4 = 0.0;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = {10};
	p1 = {10};
	p2 = {10};
	p3 = 10;
	p4 = 0.4142135623730951;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 3 -----
	disabled = false;
	p0 = {11,-11,0,0};
	p1 = {0,0,11,-11};
	p2 = {10,10,10,10};
	p3 = 31;
	p4 = 0.3548387096774194;
	all_right = (disabled || KawigiEdit_RunTest(3, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 4 -----
	disabled = false;
	p0 = {100};
	p1 = {100};
	p2 = {1};
	p3 = 10;
	p4 = 1.0;
	all_right = (disabled || KawigiEdit_RunTest(4, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 5 -----
	disabled = false;
	p0 = {1000000000};
	p1 = {1000000000};
	p2 = {1000000000};
	p3 = 1000000000;
	p4 = 0.41421356237309503;
	all_right = (disabled || KawigiEdit_RunTest(5, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 6 -----
	disabled = false;
	p0 = {20,-20,0,0};
	p1 = {0,0,20,-20};
	p2 = {50,50,50,50};
	p3 = 100;
	p4 = 0.3;
	all_right = (disabled || KawigiEdit_RunTest(6, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 7 -----
	disabled = false;
	p0 = {0,-60,-62,-60,63,-97};
	p1 = {-72,67,61,-8,-32,89};
	p2 = {6,7,8,7,5,6};
	p3 = 918;
	p4 = 0.9407071068962471;
	all_right = (disabled || KawigiEdit_RunTest(7, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	if (all_right) {
		if (tests_disabled) {
			cout << "You're a stud (but some test cases were disabled)!" << endl;
		} else {
			cout << "You're a stud (at least on given cases)!" << endl;
		}
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
