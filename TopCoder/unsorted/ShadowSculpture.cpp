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


class ShadowSculpture {

bool have[12][12][12];

bool used[12][12][12];
bool projxy[12][12];
bool projyz[12][12];
bool projzx[12][12];
int n;

void dfs(int x, int y, int z) {
	if (x < 0 || x >= n) return;
	if (y < 0 || y >= n) return;
	if (z < 0 || z >= n) return;
	if (used[x][y][z]) return;
	if (!have[x][y][z]) return;
//	eprintf(" %d %d %d\n", x, y, z);
	used[x][y][z] = true;
	projxy[x][y] = true;
	projyz[y][z] = true;
	projzx[z][x] = true;
	dfs(x-1, y, z);
	dfs(x+1, y, z);
	dfs(x, y-1, z);
	dfs(x, y+1, z);
	dfs(x, y, z-1);
	dfs(x, y, z+1);
}

public:
    string possible(vector <string> xy, vector <string> yz, vector <string> zx) {
     	n = xy.size();
     	bool any = false;
     	for (int x = 0; x < n; x++)
     	for (int y = 0; y < n; y++)
     	for (int z = 0; z < n; z++) {
     		have[x][y][z] = (xy[x][y] == 'Y') && (yz[y][z] == 'Y') && (zx[z][x] == 'Y');
     		any |= have[x][y][z];
     	}
     	if (!any) return "Possible";
     		
     	for (int x = 0; x < n; x++)
     	for (int y = 0; y < n; y++)
     	for (int z = 0; z < n; z++) if (!used[x][y][z] && have[x][y][z]) {
//     	    eprintf("%d %d %d\n", x, y, z);
     		memset(projxy, 0, sizeof(projxy));
     		memset(projyz, 0, sizeof(projyz));
     		memset(projzx, 0, sizeof(projzx));
     		dfs(x, y, z);
     		bool ok = true;
     		for (int i = 0; i < n; i++)
     			for (int j = 0; j < n; j++) {
     				ok &= ((xy[i][j] == 'Y') == projxy[i][j]);
     				ok &= ((yz[i][j] == 'Y') == projyz[i][j]);
     				ok &= ((zx[i][j] == 'Y') == projzx[i][j]);
     			}
     		if (ok) return "Possible";
     	}
     	return "Impossible";     		   
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
bool KawigiEdit_RunTest(int testNum, vector <string> p0, vector <string> p1, vector <string> p2, bool hasAnswer, string p3) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p1[i] << "\"";
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p2[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	ShadowSculpture *obj;
	string answer;
	obj = new ShadowSculpture();
	clock_t startTime = clock();
	answer = obj->possible(p0, p1, p2);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p3 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
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
	
	vector <string> p0;
	vector <string> p1;
	vector <string> p2;
	string p3;
	
	// ----- test 0 -----
	disabled = false;
	p0 = {"YN","NN"};
	p1 = {"YN","NN"};
	p2 = {"YN","NN"};
	p3 = "Possible";
	all_right = (disabled || KawigiEdit_RunTest(0, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = {"YN","NY"};
	p1 = {"YN","NY"};
	p2 = {"YN","NY"};
	p3 = "Impossible";
	all_right = (disabled || KawigiEdit_RunTest(1, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = {"YYY","YNY","YYY"};
	p1 = {"YYY","YNY","YYY"};
	p2 = {"YYY","YNY","YYY"};
	p3 = "Possible";
	all_right = (disabled || KawigiEdit_RunTest(2, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 3 -----
	disabled = false;
	p0 = {"YYY","YNY","YYY"};
	p1 = {"NYY","YNY","YYY"};
	p2 = {"YYY","YNY","YYN"};
	p3 = "Impossible";
	all_right = (disabled || KawigiEdit_RunTest(3, p0, p1, p2, true, p3) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 4 -----
	disabled = false;
	p0 = {"N"};
	p1 = {"N"};
	p2 = {"N"};
	p3 = "Possible";
	all_right = (disabled || KawigiEdit_RunTest(4, p0, p1, p2, true, p3) ) && all_right;
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
