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


typedef bitset<400> Line;

class PerfectSquare {
public:
    int ways(vector <int> x) {
        int n = 1;
        while (n * n < (int)x.size()) n++;
        vector< Line > v(2*n);
        vector<int> b(2*n, 1);
        map<int, vector<int> > primes;
        for (int i = 0; i < n; i++)
        	for (int j = 0; j < n; j++){
        		v[i][i*n+j] = 1;
        		v[j+n][i*n+j] = 1;
        	}
        for (int i = 0; i < (int)x.size(); i++){
        	for (int j = 2; j * j <= x[i]; j++){
        		if (x[i] % j == 0) {
        			int cnt = 0;
        			while (x[i] % j == 0) 
        		         x[i] /= j, cnt++;
        		    if (cnt % 2 == 1)
        		    	primes[j].pb(i);
        		}
        	}
        	if (x[i] != 1)
        		primes[x[i]].pb(i);
        }
        
        for (const auto& u : primes) {
        	b.pb(0);
        	v.pb(Line());
        	for (const auto& a  : u.second)
        		v.back()[a] = 1;
        }
        
        int cnt = 0;
        for (int i = 0; i < n*n; i++){
        	for (int j = cnt; j < (int)v.size(); j++)
        		if (v[j][i]) {
        			swap(v[j], v[cnt]);
        			swap(b[j], b[cnt]);
        			break;
        		}
        	if (!v[cnt][i]) continue;
        	for (int j = 0; j < (int)v.size(); j++)
        		if (j != cnt && v[j][i]) {
        			v[j] ^= v[cnt];
        			b[j] ^= b[cnt];
        		}        		
        	cnt++;
        }
        
        for (int i = cnt; i < (int)v.size(); i++)
        	if (b[i]) return 0;
        	
        int deg = n * n - cnt;
        int res = 1;
        for (int i = 0; i < deg; i++) 
        	res = (res * 2) % 1000000007;
        return res;
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
bool KawigiEdit_RunTest(int testNum, vector <int> p0, bool hasAnswer, int p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}";
	cout << "]" << endl;
	PerfectSquare *obj;
	int answer;
	obj = new PerfectSquare();
	clock_t startTime = clock();
	answer = obj->ways(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p1 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p1;
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
	int p1;
	
	// ----- test 0 -----
	disabled = false;
	p0 = {1,1,1,2};
	p1 = 1;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = {620,620,620,620};
	p1 = 2;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = {1,2,3,4,5,6,7,8,9};
	p1 = 1;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 3 -----
	disabled = false;
	p0 = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
	p1 = 0;
	all_right = (disabled || KawigiEdit_RunTest(3, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 4 -----
	disabled = false;
	p0 = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	p1 = 4;
	all_right = (disabled || KawigiEdit_RunTest(4, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 5 -----
	disabled = false;
	p0 = {9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690};
	p1 = 993282280;
	all_right = (disabled || KawigiEdit_RunTest(5, p0, true, p1) ) && all_right;
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
