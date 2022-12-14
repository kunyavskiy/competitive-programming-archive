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


class BearCharges {

double dist[10][10];
int n;

double dp[10][1024];

double solve(int start, int mask) {
	double& ans = dp[start][mask];
	if (ans > -0.5) return ans;
	if (mask == 0) return ans = 0;
	
	ans = 1e11;
	for (int i = 0; i < n; i++) {
		if (mask & (1<< i)) {
			int nmask = mask ^ (1<<i);
			for (int j = nmask; ; j = (j - 1) & nmask) {
				double first = solve(i, j);
				double second = solve(start, nmask ^ j);
				ans = min(ans, max(first, second) + dist[start][i]);
				if (!j) break;
			}			
		}
	}
	//eprintf("%d %x %f\n", start, mask, ans);
	return ans;
}

public:
    double minTime(vector <int> x, vector <int> y) {
        n = (int)x.size();
        for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			     dist[i][j] = sqrt((x[i] - x[j]) * 1LL * (x[i] - x[j]) + (y[i] - y[j]) * 1LL * (y[i] - y[j]));
			     
		for (int i = 0; i < n; i++)
			for (int j = 0; j < (1<<n); j++)
				dp[i][j] = -1;
				
		return solve(0, (1<<n)-2);
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
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, bool hasAnswer, double p2) {
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
	cout << "}";
	cout << "]" << endl;
	BearCharges *obj;
	double answer;
	obj = new BearCharges();
	clock_t startTime = clock();
	answer = obj->minTime(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == answer && fabs(p2 - answer) <= 1e-9 * max(1.0, fabs(p2));
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
	double p2;
	
	// ----- test 0 -----
	disabled = false;
	p0 = {10,11,12};
	p1 = {0,0,1};
	p2 = 2.414213562373095;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = {0,1,-2};
	p1 = {0,0,0};
	p2 = 3.0;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = {0,0,0,-1,1};
	p1 = {1,0,-1,0,0};
	p2 = 3.0;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 3 -----
	disabled = false;
	p0 = {-2,0,0,1,0};
	p1 = {0,1,-1,0,0};
	p2 = 4.23606797749979;
	all_right = (disabled || KawigiEdit_RunTest(3, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 4 -----
	disabled = false;
	p0 = {-500000000,-300000000,-100000000,200000000,300000000,400000000,600000000,900000000,950000000,1000000000};
	p1 = {0,0,0,0,0,0,0,0,0,0};
	p2 = 1.5E9;
	all_right = (disabled || KawigiEdit_RunTest(4, p0, p1, true, p2) ) && all_right;
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
