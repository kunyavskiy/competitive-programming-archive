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


class SurveillanceSystem {
vector<int> ids[50];

int count(string s){
	int ans = 0;
	for (int j = 0; j < (int)s.size(); j++)
		ans += (s[j] == 'X');
    return ans;
}
public:
    string getContainerInfo(string s, vector <int> v, int L) {
    	int n = s.size();
        for (int i = 0; i+L <= n; i++){
        	ids[count(string(s.begin()+i,s.begin()+i+L))].pb(i);
        }
        string result(n,'-');
        sort(v.begin(),v.end());
        for (int i = 0; i < (int)v.size(); i++)
        	for (int j = 0; j < (int)ids[v[i]].size(); j++)
        		for (int k = 0; k < L; k++)
        			result[ids[v[i]][j]+k] = '?';
        for (int i = 0; i < (int)v.size(); ){
//            printf("%d",i);
        	int j = i;
        	for (;j < (int)v.size() && v[j] == v[i]; j++);
        	int cnt = (int)ids[v[i]].size() - (j - i) + 1;
//        	printf(" %d\n",cnt);
        	for (int k = 0; k + cnt <= (int)ids[v[i]].size(); k++)
        		for (int q = ids[v[i]][k+cnt-1]; q < ids[v[i]][k]+L; q++)
        			result[q] = '+';
        	i = j; 
        }
        return result;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, string p0, vector <int> p1, int p2, bool hasAnswer, string p3) {
	cout << "Test " << testNum << ": [" << "\"" << p0 << "\"" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p1[i];
	}
	cout << "}" << "," << p2;
	cout << "]" << endl;
	SurveillanceSystem *obj;
	string answer;
	obj = new SurveillanceSystem();
	clock_t startTime = clock();
	answer = obj->getContainerInfo(p0, p1, p2);
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
	all_right = true;
	
	string p0;
	vector <int> p1;
	int p2;
	string p3;
	
	{
	// ----- test 0 -----
	p0 = "-X--XX";
	int t1[] = {1,2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 3;
	p3 = "?" "?++++";
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = "-XXXXX-";
	int t1[] = {2};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 3;
	p3 = "?" "?" "?-?" "?" "?";
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = "------X-XX-";
	int t1[] = {3,0,2,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 5;
	p3 = "++++++++++?";
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = "-XXXXX---X--";
	int t1[] = {2,1,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 3;
	p3 = "?" "?" "?-?" "?++++?" "?";
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = "-XX--X-XX-X-X--X---XX-X---XXXX-----X";
	int t1[] = {3,3,3,3,3,3,3,3,3,3,3,3,3};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 7;
	p3 = "?" "?" "?++++?++++++++++++++++++++?" "?" "?" "?" "?" "?--";
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
