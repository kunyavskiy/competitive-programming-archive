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


class TreesAnalysis {

vector< vector<int> > g1, g2;

void convert(const vector<int>& a, vector<vector<int>> &b){
	int n = a.size() + 1;
	b.resize(n);
	for (int i = 0; i < (int)a.size(); i++)
		b[i].pb(a[i]), b[a[i]].pb(i);
}

vector<int> tin1;
vector<int> tout1;
vector<int> size1;
int timer;

int  dfs1(int v, int p){
    printf("%d %d\n", v, p);
	tin1[v] = timer++;
	size1[v] = 1;
	for (int x : g1[v])
		if (x != p)
			size1[v] += dfs1(x, v);
	tout1[v] = timer;
    return size1[v];
}

vector<bool> good;
int cntg, cntt;
int cnt1;

int solve(int sz1, int sz2, int is){
    int res = is;
    res = max(res, sz1 - is);
    res = max(res, sz2 - is);
    res = max(res, (int)g1.size() - sz2 - sz1 + is);
    return res * res;
}

int dfs2(int v, int p){
    printf("%d %d\n", v, p);
	int cur = -cntg, curs = -cntt;
	cntt++;
	if (good[v]) cntg++;
	int res = 0;
	for (int x : g2[v])
		if (x != p)
			res += dfs2(x, v);
	cur += cntg, curs += cntt;
	return res + solve(cnt1, curs, cur);
}

public:
    ll treeSimilarity(vector <int> t1, vector <int> t2) {
         convert(t1, g1);
         convert(t2, g2);
         timer = 0;
         int n = g1.size();
         tin1 = vector<int>(n);
         tout1 = vector<int>(n);
         size1 = vector<int>(n);
         dfs1(0, -1);
         ll tot = 0;
         
         good = vector<bool>(n);
         
         for (int i = 1; i < n; i++){
         	for (int j = 0; j < n; j++)
         		good[j] = tin1[i] <= tin1[j] && tout1[j] <= tout1[i];
         	cntg = cntt = 0;
         	cnt1 = size1[i];
         	tot += dfs2(0, -1);
         	printf("\n\n");
         }
         return tot;
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
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, bool hasAnswer, ll p2) {
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
	TreesAnalysis *obj;
	ll answer;
	obj = new TreesAnalysis();
	clock_t startTime = clock();
	answer = obj->treeSimilarity(p0, p1);
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
		res = answer == p2;
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
	ll p2;
	
	// ----- test 0 -----
	disabled = false;
	p0 = {1};
	p1 = {1};
	p2 = 1LL;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = {2,4,1,0};
	p1 = {1,4,4,4};
	p2 = 111LL;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = {1,2,3,4};
	p1 = {1,2,3,4};
	p2 = 128LL;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 3 -----
	disabled = false;
	p0 = {2,3,4,4,5,8,5,6,10,8};
	p1 = {9,0,1,0,3,0,5,0,7,10};
	p2 = 6306LL;
	all_right = (disabled || KawigiEdit_RunTest(3, p0, p1, true, p2) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 4 -----
	disabled = false;
	p0 = {222,261,167,133,174,150,165,311,208,268,111,222,154,277,282,201,46,124,194,331,4,216,111,275,72,322,137,216,241,48,72,101,232,165,151,263,139,16,122,140,84,135,314,106,309,126,102,151,208,27,242,93,83,314,136,77,82,215,16,232,286,156,294,38,67,204,206,137,174,282,188,143,84,279,236,136,158,10,65,332,122,44,329,62,174,67,102,216,245,296,287,307,93,197,169,268,266,294,157,277,95,68,214,135,211,127,82,108,212,161,243,212,207,119,119,158,97,290,21,217,230,85,171,13,138,294,304,204,318,115,70,210,195,223,37,164,149,3,164,328,316,108,330,48,38,324,222,193,50,41,184,93,148,41,151,139,106,301,264,80,249,110,244,109,212,223,279,330,67,27,301,165,236,194,3,157,1,217,311,87,105,4,286,37,6,31,111,66,230,227,244,322,196,65,69,305,112,133,231,68,153,206,309,248,329,58,69,69,328,0,29,233,243,305,167,80,65,194,190,179,142,196,324,206,134,50,272,261,10,147,329,322,14,142,169,21,296,284,241,55,304,150,166,230,167,304,87,156,156,97,274,324,196,101,82,106,260,242,233,207,305,10,166,53,18,154,233,217,296,263,168,138,30,115,135,188,98,309,292,204,150,210,332,330,166,96,70,24,229,215,201,285,40,287,142,68,133,208,268,161,310,41,203,73,275,184,163,227,89,110,328,108,112,125,164,127,179,267,221,49,139,1,84,136,38,6,70,246,243,3,188,297};
	p1 = {174,262,195,288,157,278,36,133,230,273,222,138,97,23,189,141,296,55,45,301,81,199,188,289,187,164,113,58,138,300,289,282,329,91,130,178,92,143,48,81,311,133,151,286,171,196,199,80,83,121,65,151,277,136,49,111,58,36,259,14,31,9,136,181,122,324,249,114,9,37,259,242,165,174,34,36,298,92,301,237,178,82,65,295,110,311,274,235,68,56,259,180,195,52,110,68,140,71,52,296,290,115,213,82,209,209,74,178,302,131,99,205,296,309,288,180,329,71,143,58,152,273,196,7,169,88,231,331,213,181,80,249,170,246,16,127,75,276,332,174,21,180,163,78,242,312,295,199,89,142,85,195,115,119,95,94,279,290,3,33,93,284,20,47,47,78,331,271,113,179,249,331,92,324,9,71,232,46,28,289,80,28,80,134,20,280,277,48,205,107,52,320,4,191,160,182,189,227,295,115,54,195,78,292,189,273,301,69,305,36,222,167,326,106,48,45,74,61,181,311,292,270,201,34,314,218,214,92,269,18,37,151,142,209,11,227,327,198,28,272,152,22,47,143,332,253,273,35,78,130,295,223,181,329,18,238,300,186,274,99,300,322,41,185,311,288,198,2,37,83,238,133,122,178,107,106,66,238,69,90,38,109,246,278,288,250,321,269,130,28,115,122,33,185,275,99,130,99,152,268,133,249,180,30,210,201,324,29,290,143,3,269,68,106,230,1,269,29,120,259,324,328,23,243,9,61,14,118,199,146,237,14};
	p2 = 11478648052LL;
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