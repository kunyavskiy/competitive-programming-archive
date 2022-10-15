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

const int MOD = 1000000009;

class DrivingPlans {

vector<vector<int>> g;
vector<vector<int>> w;
vector<int> d;
vector<int> cnt;

vector<int> dijkstra(int st){
	vector<int> d(g.size(), 1<<30);
	vector<int> used(g.size(), 0);
	d[st] = 0;
	for (int i = 0; i < (int)g.size(); i++){
		int best = -1;
		for (int j = 0; j < (int)g.size(); j++)
			if (!used[j] && (best == -1 || d[best] > d[j])) best = j;
		used[best] = 1;
		for (int j = 0; j < (int)g[best].size(); j++)
			d[g[best][j]] = min(d[g[best][j]], d[best] + w[best][j]);
	}
	return d;
}

int go(int v){
	if (cnt[v] != -2) return cnt[v];
//	eprintf("%d\n", v);
	int& res = cnt[v];
	res = 0;
	for (int i = 0; i < (int)g[v].size(); i++){
		if (w[v][i] == 0) return res = -1;
//		eprintf("%d --> %d\n", v, g[v][i]);
		if (d[v] != d[g[v][i]] + w[v][i]) continue;
		int temp = go(g[v][i]);
//		eprintf("%d !--> %d = %d\n", v, g[v][i], temp);
		if (temp == -1) return res = -1;
		res = (res + temp) % MOD;
	}
	if (v == (int)g.size()-1) res++;
	return res;
}

public:
    int count(int n, vector <int> a, vector <int> b, vector <int> c) {
        g.resize(n), w.resize(n);
        for (int i = 0; i < (int)a.size(); i++){
        	--a[i], --b[i];
        	g[a[i]].pb(b[i]); w[a[i]].pb(c[i]);
        	g[b[i]].pb(a[i]); w[b[i]].pb(c[i]);
        }
        
        d = dijkstra(n-1);
        cnt = vector<int>(n, -2);
//        eprintf("%d %d %d %d\n", d[0], d[1], d[2], d[3]);
        return go(0);
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
bool KawigiEdit_RunTest(int testNum, int p0, vector <int> p1, vector <int> p2, vector <int> p3, bool hasAnswer, int p4) {
	cout << "Test " << testNum << ": [" << p0 << "," << "{";
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
	cout << "}" << "," << "{";
	for (int i = 0; int(p3.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p3[i];
	}
	cout << "}";
	cout << "]" << endl;
	DrivingPlans *obj;
	int answer;
	obj = new DrivingPlans();
	clock_t startTime = clock();
	answer = obj->count(p0, p1, p2, p3);
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
		res = answer == p4;
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
	
	int p0;
	vector <int> p1;
	vector <int> p2;
	vector <int> p3;
	int p4;
	
	// ----- test 0 -----
	disabled = false;
	p0 = 4;
	p1 = {1,1,2,3};
	p2 = {2,3,4,4};
	p3 = {1,1,1,1};
	p4 = 2;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = 4;
	p1 = {1,1,2,3};
	p2 = {2,3,4,4};
	p3 = {1,1,1,0};
	p4 = -1;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = 7;
	p1 = {1,1,2,3,4,4,5,6};
	p2 = {2,3,4,4,5,6,7,7};
	p3 = {1,1,2,2,3,3,4,4};
	p4 = 4;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) ) && all_right;
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