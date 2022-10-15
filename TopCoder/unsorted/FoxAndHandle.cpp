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


class FoxAndHandle {

bool check(string s,string t){
	int cnt[26];
	memset(cnt,0,sizeof(cnt));
	for (int i = 0; i < (int)s.size(); i++)
		cnt[s[i]-'a']++;
	int ptr = 0;
	for (int j = 0; j < (int)t.size(); j++){
		cnt[t[j]-'a'] -= 2;
		if (cnt[t[j]-'a'] < 0)
			return false;
		while (ptr < (int)s.size() && s[ptr] != t[j])
			++ptr;
		if (ptr == (int)s.size())
			return false;
		++ptr;
	}
	
	int can = 0;
	
	for (int i = ptr; i < (int)s.size(); i++)
		if (cnt[s[i]-'a'] > 0)
			can++, cnt[s[i]-'a'] -= 2;
			
	return (t.size()+can)*2 >= s.size();

}

public:
    string lexSmallestName(string s) {
        string t = "";
        for (int i = 0; i*2 < (int)s.size(); i++){
        	t += "a";
        	for (int j = 0; j < 26; j++){
        		if (check(s,t))
        			break;
        		t[i]++;
        	}
        }
        return t;
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, string p0, bool hasAnswer, string p1) {
	cout << "Test " << testNum << ": [" << "\"" << p0 << "\"";
	cout << "]" << endl;
	FoxAndHandle *obj;
	string answer;
	obj = new FoxAndHandle();
	clock_t startTime = clock();
	answer = obj->lexSmallestName(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p1 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
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
	
	string p0;
	string p1;
	
	{
	// ----- test 0 -----
	p0 = "foxfox";
	p1 = "fox";
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = "ccieliel";
	p1 = "ceil";
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = "abaabbab";
	p1 = "aabb";
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = "bbbbaaaa";
	p1 = "bbaa";
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = "fedcbafedcba";
	p1 = "afedcb";
	all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	p0 = "nodevillivedon";
	p1 = "deilvon";
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
