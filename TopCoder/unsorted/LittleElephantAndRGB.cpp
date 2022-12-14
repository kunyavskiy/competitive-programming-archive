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


const int MAXN = 2510;

class LittleElephantAndRGB {

int bit[MAXN];
int goodafter[MAXN];

void update(int x){
	x = MAXN - x - 1;
	for (;x < MAXN; x = x | (x+1))
		bit[x]++;	
}

int get(int x){
	x = MAXN - x - 1;
	int ans = 0;
	for (;x >= 0; x = (x & (x+1))-1)
		ans += bit[x];
	return ans;
}

string concat(vector<string> _s){
	string s = "";
	for (int i = 0; i < (int)_s.size(); i++)
		s += _s[i];
	return s;
}

public:
    ll getNumber(vector <string> _s, int need) {
        string s = concat(_s);
        int n = s.size();
        
        ll ans = 0;
        goodafter[n] = 0;
        
        for (int b = n-1; b >= 0; b--){
            goodafter[b] = goodafter[b+1];
        	bool good = 0, islast = 1;
        	int curg = 0;
        	int lastg = 0;
        	for (int a = b; a >= 0; a--){
        		if (s[a] != 'G') curg = 0, islast = 0;
        		else {
        			if (islast) lastg++;
        			curg++;
        		}
        		if (curg == need) good = 1;
        		if (good){
        			ans += a*(a+1)/2;
        			ans += (n-b-1)*(n-b)/2;
        			ans -= goodafter[b+1];
        		}
        		else {
        			ans += get(need - lastg);
        		}
        	}
        	
        	good = 0, islast = 1;
        	curg = 0;
        	lastg = 0;
        	
        	for (int d = b; d < n; d++){
        		if (s[d] != 'G') curg = 0, islast = 0;
        		else {
        			if (islast) lastg++;
        			curg++;
        		}
        		if (curg == need) good = 1;
        		if (good)
        			goodafter[b]++;        		
        		else {
        			update(lastg);
        		}
        	}     	
//        	eprintf("%lld\n", ans);
        }
        return ans;
    }
};

class LittleElephantAndRGBStupid {

string concat(vector<string> _s){
	string s = "";
	for (int i = 0; i < (int)_s.size(); i++)
		s += _s[i];
	return s;
}

bool check(string s, int need){
	int curg = 0;
	for (int i = 0; i < (int)s.size(); i++){
		if (s[i] == 'G') curg++;
		else curg = 0;
		if (curg == need) return true;
	}
	return false;
}

public:
    ll getNumber(vector <string> _s, int need) {
        string s = concat(_s);
        int n = s.size();
        ll ans = 0;
                           
        for (int a = 0; a < n; a++)
        	for (int b = a; b < n; b++)
        		for (int c = b+1; c < n; c++)
        			for (int d = c; d < n; d++)
        				if (check(string(s.begin()+a, s.begin()+b+1) + string(s.begin()+c, s.begin()+d+1), need))
        					ans++;
        return ans;        
    }
};



// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <string> p0, int p1, bool hasAnswer, ll p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}" << "," << p1;
	cout << "]" << endl;
	LittleElephantAndRGB *obj;
	ll answer;
	obj = new LittleElephantAndRGB();
	clock_t startTime = clock();
	answer = obj->getNumber(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	p2 = (LittleElephantAndRGBStupid()).getNumber(p0, p1);
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
	all_right = true;
	
	vector <string> p0;
	int p1;
	ll p2;
	
	{
	// ----- test 0 -----
	string t0[] = {"GRG"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = 1ll;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"GG","GG"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3;
	p2 = 9ll;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"GRBGRBBRG"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = 11ll;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"RRBRBBRRR","R","B"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	p2 = 0ll;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	string t0[] = {"GRGGGRBRGG","GGGGGGGG","BRGRBRB"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 4;
	p2 = 12430ll;
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
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
