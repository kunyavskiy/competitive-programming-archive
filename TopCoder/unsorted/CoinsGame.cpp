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


const int dx[4] = {0,1,0,-1};
const int dy[4] = {-1,0,1,0};

const int MOD = 1000000009;

int pow(int a,int b){
	if (!b) return 1;
	if (b&1) return (pow(a,b-1) * 1LL * a) % MOD;
	int temp = pow(a,b/2);
	return (temp * 1LL * temp) % MOD;
}

class CoinsGame {
vector<string> g;

char can[41][41][41][41];
bool used[41][41];
int n,m;

int getcnt(){
	int cnt = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (g[i][j] == '.')
				cnt++;
	return cnt;
}

bool out(int x,int y){
	return !(0 <= x && x < n && 0 <= y && y < m);
}

int dfs(int x,int y,int x2,int y2){
	if (out(x,y) && out(x2,y2))
		return false;
	if (out(x,y) ^ out(x2,y2))
		return true;
	char& res = can[x][y][x2][y2];
	if (res != -1)
		return res;
	res = 0;
	for (int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		int nx2 = x2 + dx[i];
		int ny2 = y2 + dy[i];
		if (!out(nx,ny) && g[nx][ny] != '.')
			nx = x, ny = y;
		if (!out(nx2,ny2) && g[nx2][ny2] != '.')
			nx2 = x2, ny2 = y2;
		if (dfs(nx,ny,nx2,ny2)){
			return res = 1;
		}
	}
	return res = 0;
		
}

public:
    int ways(vector <string> _g) {
        g = _g;
        n = g.size();
        m = g[0].size();
        memset(can,-1,sizeof(can));
        
        for (int i = 0; i < n; i++)
        	for (int j = 0; j < m; j++)
        		if (g[i][j] == '.')
	        		for (int k = 0; k < n; k++)
    	    			for (int t = 0; t < m; t++)
    	    			     if (g[k][t] == '.'){
		        				dfs(i,j,k,t);
		        			}
        				
		memset(used,0,sizeof(used));
		
		int ans = (pow(2,getcnt()) + MOD - 1) % MOD;
		
		
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (!used[i][j] && g[i][j] == '.'){
					int cnt = 0;					
					for (int i2 = 0; i2 < n; i2++)
						for (int j2 = 0; j2 < m; j2++)
							if (!can[i][j][i2][j2] && g[i2][j2] == '.'){
								cnt++;
								used[i2][j2] = true;
							}
					ans = (ans + MOD - pow(2,cnt) + 1) % MOD;
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
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, int p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	CoinsGame *obj;
	int answer;
	obj = new CoinsGame();
	clock_t startTime = clock();
	answer = obj->ways(p0);
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
	all_right = true;
	
	vector <string> p0;
	int p1;
	
	{
	// ----- test 0 -----
	string t0[] = {".."};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"##.#",".###","###.","#.##"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 11;
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"####","#..#","#..#","####"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 0;
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"#.#.#"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 0;
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	string t0[] = {"........","........","........","........","........","........","........","........"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 688856388;
	all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	string t0[] = {"#..#","####","#.##"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3;
	all_right = KawigiEdit_RunTest(5, p0, true, p1) && all_right;
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
