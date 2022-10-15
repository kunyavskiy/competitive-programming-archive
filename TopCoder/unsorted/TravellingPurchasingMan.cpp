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
#include <sstream>
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


class TravellingPurchasingMan {

void getthree(string s,int& a,int& b,int& c){
	stringstream str(s);
	str >> a >> b >> c;
}

int dp[1<<16][16];

public:
    int maxStores(int n, vector <string> need, vector <string> r) {
        vector<vector<int> > g(n,vector<int>(n,0));
        for (int i = 0; i < n; i++)	
        	for (int j = 0; j < n; j++)
        		g[i][j] = 0x3fffffff * (i != j);
        		
        for (int i = 0; i < (int)r.size(); i++){
        	int a,b,w;
        	getthree(r[i],a,b,w);
        	g[a][b] = g[b][a] = min(g[a][b],w);
        }
        
        for (int k = 0; k < n; k++)
        	for (int i = 0; i < n; i++)
        		for (int j = 0; j < n; j++)
        			g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        
        int m = need.size();
        
        vector<int> start(m);
        vector<int> end(m);
        vector<int> dur(m);
        
        for (int i = 0; i < m; i++)
        	getthree(need[i],start[i],end[i],dur[i]);
        	
       	for (int i = 0; i < (1<<m); i++)
       		for (int j = 0; j < m; j++)
       			dp[i][j] = 0x3fffffff;
       			
       	for (int i = 0; i < m; i++)
       		if (g[n-1][i] <= end[i])
	       		dp[1<<i][i] = max(g[n-1][i],start[i])+dur[i];
        	
        int ans = 0;	
        	
        for (int i = 0; i < (1<<m); i++)
        	for (int j = 0; j < m; j++){
        		if (dp[i][j] < 0x3fffffff)
        			ans = max(ans, __builtin_popcount(i));
        		for (int k = 0; k < m; k++)
        			if (!(i & (1<<k)) && g[j][k] + dp[i][j] <= end[k])
        				dp[i|(1<<k)][k] = min(dp[i|(1<<k)][k], max(start[k],dp[i][j] + g[j][k]) + dur[k]);
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
bool KawigiEdit_RunTest(int testNum, int p0, vector <string> p1, vector <string> p2, bool hasAnswer, int p3) {
	cout << "Test " << testNum << ": [" << p0 << "," << "{";
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
	TravellingPurchasingMan *obj;
	int answer;
	obj = new TravellingPurchasingMan();
	clock_t startTime = clock();
	answer = obj->maxStores(p0, p1, p2);
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
	
	int p0;
	vector <string> p1;
	vector <string> p2;
	int p3;
	
	{
	// ----- test 0 -----
	p0 = 3;
	string t1[] = {"1 10 10","1 55 31","10 50 100"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	string t2[] = {"1 2 10"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 1;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 3;
	string t1[] = {"1 10 10","1 55 30","10 50 100"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	string t2[] = {"1 2 10"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 2;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 5;
	string t1[] = {"0 1000 17"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	string t2[] = {"2 3 400","4 1 500","4 3 300","1 0 700","0 2 400"};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 0;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
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