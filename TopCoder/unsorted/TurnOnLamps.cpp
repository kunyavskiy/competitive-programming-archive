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


class TurnOnLamps {

vector<int> g[55];
vector<int> dp[55][2];
string cur;
string need;

int dfs(int v,int son,int path){
    //cerr << v <<" "<<son<<" "<<path << endl;
	if (son == -1) return 0;
	if (dp[v][path][son] != -1) return dp[v][path][son];
	int& res = dp[v][path][son];
	res = 1<<30;
	int nv = g[v][son];
	if (need[nv] == '0' || cur[nv] == '0') {
		res = min(res, dfs(v,son-1,!path) + dfs(nv, (int)g[nv].size()-1, 1) + !path);
//		cerr << v <<" "<<son <<" "<<path <<" goto "<< nv <<"    "<<(dfs(v,son-1,!path) + dfs(nv, (int)g[nv].size()-1, 1) + !path)<<endl;
	}
	if (need[nv] == '0' || cur[nv] == '1') {
		res = min(res, dfs(v,son-1,path) + dfs(nv, (int)g[nv].size()-1, 0));
//		cerr << v <<" "<<son <<" "<<path <<" not goto "<< nv <<"    "<<(dfs(v,son-1,path) + dfs(nv, (int)g[nv].size()-1, 0))<<endl;
	}
	return res;
}

public:
    int minimize(vector <int> p, string cur, string need) {
    	int n = (int)p.size() + 1;
    	this->cur = "-"+cur;
    	this->need = "-"+need;
        for (int i = 1; i < n; i++)
        	g[p[i-1]].pb(i), dp[p[i-1]][0].pb(-1), dp[p[i-1]][1].pb(-1);
        return dfs(0,(int)g[0].size()-1,0);
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <int> p0, string p1, string p2, bool hasAnswer, int p3) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << "\"" << p1 << "\"" << "," << "\"" << p2 << "\"";
	cout << "]" << endl;
	TurnOnLamps *obj;
	int answer;
	obj = new TurnOnLamps();
	clock_t startTime = clock();
	answer = obj->minimize(p0, p1, p2);
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
	
	vector <int> p0;
	string p1;
	string p2;
	int p3;
	
	{
	// ----- test 0 -----
	int t0[] = {0,0,1,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "0001";
	p2 = "0111";
	p3 = 1;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {0,0,1,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "0000";
	p2 = "0111";
	p3 = 2;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {0,0,1,1,4,4};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "000100";
	p2 = "111111";
	p3 = 2;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {0,0,1,1,4,4};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "100100";
	p2 = "011101";
	p3 = 2;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	int t0[] = {0,0,2,2,3,1,6,3,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "010001110";
	p2 = "000110100";
	p3 = 1;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	int t0[] = {0,0,1,2,4,4,6,1,2,5,2,8,8,3,6,4,14,7,18,14,11,7,1,12,7,5,18,23,0,14,11,10,2,2,6,1,30,11,9,12,5,35,25,11,23,17,14,45,15};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = "0000000000010000000000000010000010100000000000000";
	p2 = "1010111111111011011111000110111111111111111110111";
	p3 = 14;
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, true, p3) && all_right;
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