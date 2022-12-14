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


class Gxor {

int id[10][10];
ll outer[1024];

vector<ll> clean(vector<ll> g, ll mask) {
	/*printf("clean({");
	for (ll x : g) {
		printf("%lld ", x);
	}
	printf("},%lld)\n", mask);*/
	for (int i = 0; i < (int)g.size(); i++) {
		if (g[i] & mask) {
			//printf("clean g[%d] = %lld (mask = %lld)\n", i, g[i], mask);
			ll bit = g[i] & mask;
			bit = bit & ~(bit - 1);
			for (int j = 0; j < (int)g.size(); j++)
				if (i != j && (g[j] & bit)) {
				    //printf("xor g[%d] = %lld, new is %lld\n", j, g[j], g[i] ^ g[j]); 
					g[j] ^= g[i];
				}
			swap(g[i], g.back());
			g.pop_back();
			i--;
		}
	}
	return g;
}

ll go(int mask, vector<ll> g) {
	assert(mask & 1);
	ll ans = (1LL << g.size());
	for (int i = mask; i; i = (i - 1) & mask) {
		if (i & 1) continue;
		ll bad = outer[i];
		vector<ll> g2 = clean(g, bad);
		ans -= go(mask ^ i, g2);
	} 
	return ans;
}

public:
    ll countsubs(vector <string> s) {
      int n = 2;
      while (n * (n - 1) / 2 != (int)s[0].length()) n++; 
      {
      	int ptr = 0;
        for (int i = 0; i < n; i++)
       	  for (int j = i+1; j < n; j++)
       	    id[i][j] = id[j][i] = ptr++;	
      }
      
      for (int mask = 0; mask < (1<<n); mask++) { 
      	for (int i = 0; i < n; i++)
       	  for (int j = i+1; j < n; j++)
       	  	if (((mask >> i)&1) != ((mask >> j)&1))
       	  	  outer[mask] |= (1LL << id[i][j]);
      }
      
      vector<ll> g(s.size());
      for (int i = 0; i < (int)s.size(); i++)
      	for (int j = 0; j < (int)s[i].size(); j++)
      	  if (s[i][j] == '1')
      		g[i] |= (1LL << j);	
      
      return go((1<<n)-1, g);
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
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, ll p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	Gxor *obj;
	ll answer;
	obj = new Gxor();
	clock_t startTime = clock();
	answer = obj->countsubs(p0);
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
	
	vector <string> p0;
	ll p1;
	
	// ----- test 0 -----
	disabled = false;
	p0 = {"1","1","0"};
	p1 = 4LL;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 1 -----
	disabled = false;
	p0 = {"011001"};
	p1 = 0LL;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 2 -----
	disabled = false;
	p0 = {"111011"};
	p1 = 1LL;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 3 -----
	disabled = false;
	p0 = {"110","011","101"};
	p1 = 6LL;
	all_right = (disabled || KawigiEdit_RunTest(3, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 4 -----
	disabled = false;
	p0 = {"111110","100000","100101","010101"};
	p1 = 11LL;
	all_right = (disabled || KawigiEdit_RunTest(4, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 5 -----
	disabled = false;
	p0 = {"110010000000111110101001001001101010","101011011000101001111110010000000001","010001101100000010010110000001100010","101100011110001011101000100010001111","111010000010010101010111001000000100","101100001101011101101011011001000010","111111010000000000110000010101100100"};
	p1 = 121LL;
	all_right = (disabled || KawigiEdit_RunTest(5, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	
	// ----- test 6 -----
	disabled = false;
	p0 = {"000000100000100110001000110001001000","010100001000000000000001001010000000","101000100010000100000000010000000010","110001101110110000010000000001000101","000001000000010000000110001010100101","100100010001010000000000000010000010","111001000000111111001001011001010000","100001100000110001011110000001010001","111000000001100100000000000011100000","111010110000011000100000000001101000","001000100000001010001001001000011001","110111001101000100000101000100100100","100111000010100110001100101101000001","000010100000110111000000000100100000","000100001010000000010010000000100100","001100000010010000000100100001100000","001000100100000100001000000100010001","011010000110001000000001010011001100","000100011111100000000010010010110000","000001010101001010011111100000000110","000010000010001010100100010001100000","010001011000000000000100000110000001","010000000100100000000000000000011000","100101001000001100000100001000000001","100010000000000000000001000000010000","1010100000100010010110110"
			"00000000100","000010000000011010111000010111100100","010001101111000100100101110000100000","000110010000000100000000000010000010","111000001000000010010000011100000100","000010101100100100010100000000000000","110010001000100100010000000000000000","011000100000000100110101101100100001","000100000011001110100000001100111010","000110001101100010100000000000010000","000110010010011001010010100110001001","110001100000010000000000100100010110","001110011000110000100110000011001000","000001000100000110011100000100000101","100001000000010000100000101001101100","011010110000011000110011111101011110","010001100010101100000101000000010001","011011000101000001101110100011110110","101000001100010010001100011000000010","001111000011100001110000010010010001","010000001010010000010000101000110000","001101100001000101000100010011001110","001010110110101000010100101101010101","000100010111110010010100101000100101","100010000000010101111010010000110001"};
	p1 = 1086198432923648LL;
	all_right = (disabled || KawigiEdit_RunTest(6, p0, true, p1) ) && all_right;
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
