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
#define pb push_back
#define mp make_pair      
using namespace std;
 
typedef long long ll;
typedef long double ld;


class TheBrickTowerEasyDivOne {
public:
    int find(int rc, int rh, int bc, int bh) {
        /*set<ll> s;
        for (int i = 0; i <= rc; i++){
        	if (bc >= i - 1 && i) s.insert(rh * 1LL * i + bh * 1LL * (i-1));
        	if (bc >= i && i) s.insert(rh * 1LL * i + bh * 1LL * i);
        	if (bc >= i + 1) s.insert(rh * 1LL * i + bh * 1LL * (i+1));
        }   
        return s.size();*/
        if (rh == bh){
        	return min(rc, bc + 1) + min(rc + 1, bc);
        }
        int ans = 1;
        for (int i = 1; i <= rc; i++){
        	ans += bc >= i-1;
        	ans += bc >= i;
        	ans += bc >= i+1;
        }
        return ans;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, int p0, int p1, int p2, int p3, bool hasAnswer, int p4) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1 << "," << p2 << "," << p3;
	cout << "]" << endl;
	TheBrickTowerEasyDivOne *obj;
	int answer;
	obj = new TheBrickTowerEasyDivOne();
	clock_t startTime = clock();
	answer = obj->find(p0, p1, p2, p3);
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
	all_right = true;
	
	int p0;
	int p1;
	int p2;
	int p3;
	int p4;
	
	{
	// ----- test 0 -----
	p0 = 1;
	p1 = 2;
	p2 = 3;
	p3 = 4;
	p4 = 4;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 4;
	p1 = 4;
	p2 = 4;
	p3 = 7;
	p4 = 12;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 7;
	p1 = 7;
	p2 = 4;
	p3 = 4;
	p4 = 13;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 47;
	p1 = 47;
	p2 = 47;
	p3 = 47;
	p4 = 94;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, true, p4) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING




//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
