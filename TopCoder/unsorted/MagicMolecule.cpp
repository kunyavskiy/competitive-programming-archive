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


class MagicMolecule {

vector<string> g;
vector<int> cost;
int res;
int n;

int used[110];

void go(int pos,int cnt,int cur){
	if (pos == n){
		res = min(res,cur);
		return;
	}
	if (cnt < 0) return;
	if (used[pos]){
		go(pos+1,cnt,cur);
		return;
	}
	int tmp = 0;
	for (int i = pos+1; i < n; i++)
		tmp += (g[pos][i] == 'N' && !used[i]);
	if (tmp) go(pos+1,cnt-1,cur + cost[pos]);
	for (int i = pos+1; i < n; i++)
		if (g[pos][i] == 'N'){
			if (used[i] == 0){
				cnt--;
				cur += cost[i];
			}
			used[i]++;
		}
	go(pos+1,cnt,cur);
	for (int i = pos+1; i < n; i++)
		if (g[pos][i] == 'N'){
			used[i]--;
			if (used[i] == 0){
				cnt ++;
				cur -= cost[i];
			}
		}
}

public:
    int maxMagicPower(vector <int> _cost, vector<string> _g) {
    	cost = _cost;
    	g = _g;
    	n = cost.size();
    	int sum = 0;
    	for (int i = 0; i < n; i++)
    		sum += cost[i];
    	res = sum+1;
    	int k = n - (2*n+2)/3;
    	memset(used,0,sizeof(used));
    	go(0,k,0);
        return sum - res;        	
    }
};







// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <string> p1, bool hasAnswer, int p2) {
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
		cout << "\"" << p1[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	MagicMolecule *obj;
	int answer;
	obj = new MagicMolecule();
	clock_t startTime = clock();
	answer = obj->maxMagicPower(p0, p1);
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
	all_right = true;
	
	vector <int> p0;
	vector <string> p1;
	int p2;
	
	{
	// ----- test 0 -----
	int t0[] = {1,2,3};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"NYY","YNN","YNN"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 4;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {1,1,1,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"NNYY","NNYY","YYNN","YYNN"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = -1;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {86,15,100,93,53,50};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"NYYYYN","YNNNNY","YNNYYN","YNYNYN","YNYYNY","NYNNYN"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 332;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {3969,9430,7242,8549,8190,8368,3704,9740,1691};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"NYYYYYYYY","YNYYYYYYY","YYNYYYYYY","YYYNYYYYY","YYYYNYYYY","YYYYYNYYY","YYYYYYNNY","YYYYYYNNY","YYYYYYYYN"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 57179;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
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