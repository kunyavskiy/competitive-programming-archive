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


class ArcadeManao {
vector<string> g;
vector<vector<bool> > used;
int tox,toy;
int n,m;

bool dfs(int x,int y,int up){
	if (!(0 <= x && x < n && 0 <= y && y < m)) return false;
	if (used[x][y] || g[x][y] == '.') return false;
	cerr << x <<" "<<y <<" "<<up << " "<<tox << " "<<toy <<endl;
	if (x == tox && y == toy) return true;
	used[x][y] = 1;
	if (dfs(x,y-1,up)) return true;
	if (dfs(x,y+1,up)) return true;
	for (int i = -up; i <= up; i++)
		if (dfs(x+i,y,up))
			return true;
	cerr << "FAIL" << endl;
	return false;
}


public:
    int shortestLadder(vector <string> _g, int _tox, int _toy) {
    	tox = _tox;
    	toy = _toy;
        --tox,--toy;
        g = _g;
        n = g.size();
        m = g[0].size();
        
        int l = -1;
        int r = n;
        
        
        while (r - l > 1){
        	int mid = (l+r)/2;
        	used = vector<vector<bool> >(n,vector<bool>(m,0));
        	if (dfs(n-1,0,mid))
        		r = mid;
        	else
        		l = mid;
        }
        
        return r;
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
	ArcadeManao *obj;
	int answer;
	obj = new ArcadeManao();
	clock_t startTime = clock();
	answer = obj->shortestLadder(p0, p1, p2);
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
	string t0[] = {"XXXX....","...X.XXX","XXX..X..","......X.","XXXXXXXX"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = 4;
	p3 = 2;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"XXXX","...X","XXXX"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	p2 = 1;
	p3 = 1;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"..X..",".X.X.","X...X",".X.X.","..X..","XXXXX"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	p2 = 3;
	p3 = 4;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"X"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	p2 = 1;
	p3 = 0;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	string t0[] = {"XXXXXXXXXX","...X......","XXX.......","X.....XXXX","..XXXXX..X",".........X",".........X","XXXXXXXXXX"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	p2 = 1;
	p3 = 2;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, true, p3) && all_right;
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
