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


class PalindromeMatrix {

int n,m;
vector<string> g;

int calc(int msk,int val){
//    eprintf("(%d, %d)\n", msk, val);
	int ans = 4;
	for (int i = 0; i <= 15; i++){
		if ((msk & 1) && (!!(i & 1) != !!(i & 4))) continue;
		if ((msk & 2) && (!!(i & 2) != !!(i & 8))) continue;
		if ((msk & 4) && (!!(i & 1) != !!(i & 2))) continue;
		if ((msk & 8) && (!!(i & 4) != !!(i & 8))) continue;
		ans = min(ans, __builtin_popcount(val ^ i));
	}
	return ans;
}

int getBits(int msk,int i){
	int res = 0;
	if (msk & (1<<i)) res |= 4;
	if (msk & (1<<(n - i - 1))) res |= 8;
	return res;
}

int getVals(int i, int j){
	int res = 0;
	if (g[i][j] == '1') res |= 1;
	if (g[i][m-j-1] == '1') res |= 2;
	if (g[n-i-1][j] == '1') res |= 4;
	if (g[n-i-1][m-j-1] == '1') res |= 8;
	return res;
}

int calc(int mask, int msk,int j){
	int sum = 0;
	for (int i = 0; i < n/2; i++)
		sum += calc(getBits(mask, i) | msk, getVals(i, j));
//    eprintf("calc(%d, %d) = %d\n", msk, j, sum);
	return sum;
}

public:
    int minChange(vector <string> _g, int row, int col) {
        g = _g;
    	n = g.size();
    	m = g[0].size();
        vector<int> colmsk;
        for (int i = 0; i < (1<<m); i++)
        	if (__builtin_popcount(i) == col)
        		colmsk.pb(i);
        		
        int ans = n*m;
        
        vector<string> gt(m, string(n, '0'));
        for (int i = 0; i < n; i++)
        	for (int j = 0; j < m; j++)
        		gt[j][i] = g[i][j];
        		
//        calc(3, 1, 1);
//        return -1;
        		
        for (int msk = 0; msk < (1<<n); msk++){
        	if (__builtin_popcount(msk) != row) continue;
        	vector<int> dp, dp2;
			dp = vector<int>(m+1, (int)1e6);
			dp[0] = 0;
			for (int i = 0; i < m/2; i++){
				dp2 = vector<int>(m+1, (int)1e6);
				for (int j = 0; j <= 2*i; j++){
					for (int k = 0; k < 4; k++)
						dp2[j + __builtin_popcount(k)] = min(dp2[j + __builtin_popcount(k)], dp[j] + calc(msk, k, i));
				}
				dp = dp2;
			}
			ans = min(ans, dp[col]);
//			break;
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
bool KawigiEdit_RunTest(int testNum, vector <string> p0, int p1, int p2, bool hasAnswer, int p3) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}" << "," << p1 << "," << p2;
	cout << "]" << endl;
	PalindromeMatrix *obj;
	int answer;
	obj = new PalindromeMatrix();
	clock_t startTime = clock();
	answer = obj->minChange(p0, p1, p2);
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
	all_right = true;
	
	vector <string> p0;
	int p1;
	int p2;
	int p3;
	
	{
	// ----- test 0 -----
	string t0[] = {"0000","1000","1100","1110"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = 2;
	p3 = 1;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"0000","1000","1100","1110"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3;
	p2 = 2;
	p3 = 3;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"01","10"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	p2 = 1;
	p3 = 1;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"1110","0001"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 0;
	p2 = 0;
	p3 = 0;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	string t0[] = {"01010101","01010101","01010101","01010101","01010101","01010101","01010101","01010101"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = 3;
	p3 = 8;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	string t0[] = {"000000000000","011101110111","010001010101","010001010101","011101010101","010101010101","010101010101","011101110111","000000000000","000000000000"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 5;
	p2 = 9;
	p3 = 14;
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 6 -----
	string t0[] = {"11111101001110","11000111111111","00010101111001","10110000111111","10000011010010","10001101101101","00101010000001","10111010100100","11010011110111","11100010110110","00100101010100","01001011001000","01010001111010","10100000010011"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 6;
	p2 = 8;
	p3 = 31;
	all_right = KawigiEdit_RunTest(6, p0, p1, p2, true, p3) && all_right;
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
