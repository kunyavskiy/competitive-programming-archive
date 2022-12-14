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

const int inf = 1e9;


class FoxConnection {

vector<int> g[55];

vector<int> sz;
vector<int> cntin;
vector<int> par;
vector<int> have;
vector<int> upcost;
int n;

vector< vector< vector<int> > > dp;

void dfs1(int v, int p){
	par[v] = p;
	sz[v] = 1;
	cntin[v] = have[v];
	upcost[v] = 0;
	for (int i = 0; i < (int)g[v].size(); i++){
		if (g[v][i] != p) {
			dfs1(g[v][i], v);
			sz[v] += sz[g[v][i]];
			cntin[v] += cntin[g[v][i]];
			upcost[v] += upcost[g[v][i]];
		}
	}
	upcost[v] += cntin[v];
}

int calc(int v, int son, int cnt){
	if (son == -1){
		if (cnt == 1 - have[v]) return 0;
		return inf;
	}
	int& res = dp[v][son][cnt + 55];
	if (res != -1) return res;
	if (g[v][son] == par[v]) return res = calc(v, son-1, cnt);
	
	int to = g[v][son];
	res = inf;
	res = min(res, upcost[to] + calc(v, son - 1, cnt + cntin[to]));
	for (int i = -cntin[to] + 1; i <= sz[to] - cntin[to]; i++)
		res = min(res, calc(to, (int)g[to].size() - 1, i) + abs(i) + calc(v, son - 1, cnt - i));
//	eprintf("dp(%d, %d, %d) = %d\n", v, son, cnt, res);	
	return res;	
}

int solve(int root){
    sz = vector<int>(n);
    cntin = vector<int>(n);
    par = vector<int>(n);
    upcost = vector<int>(n);
	dfs1(root, -1);
	if (cntin[root] <= 1) return 0;
	dp = vector< vector< vector<int> > > (n);
	for (int i = 0; i < n; i++)
		dp[i] = vector< vector<int> > (g[i].size(), vector<int>(110, -1));
	return calc(root, g[root].size() - 1, 0);
}

public:
    int minimalDistance(vector <int> a, vector <int> b, string s) {
        n = a.size() + 1;

        for (int i = 0; i < n - 1; i++){
            a[i]--;
            b[i]--;
            g[a[i]].pb(b[i]);
            g[b[i]].pb(a[i]);
        }  
        have = vector<int>(n);
        for (int i = 0; i < n; i++)
        	have[i] = (s[i] == 'Y');
        	
        int ans = inf;
        for (int i = 0; i < n; i++)
        	ans = min(ans, solve(i));
        return ans;
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
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, string p2, bool hasAnswer, int p3) {
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
	cout << "}" << "," << "\"" << p2 << "\"";
	cout << "]" << endl;
	FoxConnection *obj;
	int answer;
	obj = new FoxConnection();
	clock_t startTime = clock();
	answer = obj->minimalDistance(p0, p1, p2);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p3 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p3;
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
	string p2;
	int p3;
	
	{
	// ----- test 0 -----
	disabled = false;
	int t0[] = {1,2,3};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2,3,4};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "YNNY";
	p3 = 2;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	disabled = false;
	int t0[] = {1,1,1,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2,3,4,5};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "NYYYY";
	p3 = 1;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	disabled = false;
	int t0[] = {1,3,4,5,4};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2,2,2,4,6};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "YNYNYY";
	p3 = 2;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	disabled = false;
	int t0[] = {1,2,3,4,5,6,7,8,9};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2,3,4,5,6,7,8,9,10};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "YNNNYNYNNY";
	p3 = 7;
	all_right = (disabled || KawigiEdit_RunTest(3, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	disabled = false;
	int t0[] = {1,2,3,4,3,6,8,7};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2,3,4,5,6,8,9,6};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "YNNYYNYYY";
	p3 = 3;
	all_right = (disabled || KawigiEdit_RunTest(4, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	disabled = false;
	int t0[] = {1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "NY";
	p3 = 0;
	all_right = (disabled || KawigiEdit_RunTest(5, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 6 -----
	disabled = false;
	int t0[] = {1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = "NN";
	p3 = 0;
	all_right = (disabled || KawigiEdit_RunTest(6, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
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
