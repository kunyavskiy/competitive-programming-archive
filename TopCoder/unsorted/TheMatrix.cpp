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


class TheMatrix {
public:
    int MaxArea(vector <string> g) {
        int ans = 0;
        for (int i = 0; i < (int)g.size(); i++)	
        	for (int j = i + 1; j <= (int)g.size(); j++){
        		int cnt = 0;
        		for (int k = 0; k < (int)g[i].size(); k++){
        			bool ok = true;
        			for (int q = i + 1; q < j; q++)
        				if (g[q][k] == g[q-1][k]) {ok = false; break;}
        			if (!ok) cnt = -1;
        			cnt++;
        			if (k && g[i][k] == g[i][k-1]) cnt = min(cnt, 1);
        			ans = max(ans, (j - i) * cnt);
        		}
        	}
        return ans;
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
	TheMatrix *obj;
	int answer;
	obj = new TheMatrix();
	clock_t startTime = clock();
	answer = obj->MaxArea(p0);
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
	int p1;
	
	{
	// ----- test 0 -----
	disabled = false;
	string t0[] = {"1","0"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	all_right = (disabled || KawigiEdit_RunTest(0, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	disabled = false;
	string t0[] = {"0000"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	all_right = (disabled || KawigiEdit_RunTest(1, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	disabled = false;
	string t0[] = {"01"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	all_right = (disabled || KawigiEdit_RunTest(2, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	disabled = false;
	string t0[] = {"001","000","100"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	all_right = (disabled || KawigiEdit_RunTest(3, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	disabled = false;
	string t0[] = {"0"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 1;
	all_right = (disabled || KawigiEdit_RunTest(4, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	disabled = false;
	string t0[] = {"101","010"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 6;
	all_right = (disabled || KawigiEdit_RunTest(5, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 6 -----
	disabled = false;
	string t0[] = {"101","011","101","010"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 8;
	all_right = (disabled || KawigiEdit_RunTest(6, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
	{
	// ----- test 7 -----
	disabled = false;
	string t0[] = {"11001110011000110001111001001110110011010110001011","10100100010111111011111001011110101111010011100001","11101111001110100110010101101100011100101000010001","01000010001010101100010011111000100100110111111000","10110100000101100000111000100001011101111101010010","00111010000011100001110110010011010110010011100100","01100001111101001101001101100001111000111001101010","11010000000011011010100010000000111011001001100101","10100000000100010100100011010100110110110001000001","01101010101100001100000110100110100000010100100010","11010000001110111111011010011110001101100011100010","11101111000000011010011100100001100011111111110111","11000001101100100011000110111010011001010100000001","00100001111001010000101101100010000001100100001000","01001110110111101011010000111111101011000110010111","01001010000111111001100000100010101100100101010100","11111101001101110011011011011000111001101100011011","10000100110111000001110110010000000000111100101101","0101001110110110111000001100011001111100111101"
			"1100","01101010011111010000011001111101011010011100001101","11011000011000110010101111100000101011011111101100","11100001001000110010100011001010101101001010001100","11011011001100111101001100111100000101011101101011","11110111100100101011100101111101000111001111110111","00011001100110111100111100001100101001111100001111","10001111100101110111001111100000000011110000100111","10101010110110100110010001001010000111100110100011","01100110100000001110101001101011001010001101110101","10110101110100110110101001100111110000101111100110","01011000001001101110100001101001110011001001110001","00100101010001100110110101001010010100001011000011","00011101100100001010100000000011000010100110011100","11001001011000000101111111000000110010001101101110","10101010110110010000010011001100110101110100111011","01101001010111010001101000100011101001110101000110","00110101101110110001110101110010100100110000101101","11010101000111010011110011000001101111010011110011","1001000001000111001101110100111011001000"
			"1100011100","00111101110001001100101001110100110010100110110000","00010011011000101000100001101110111100100000010100","01101110001101000001001000001011101010011101011110","00000100110011001011101011110011011101100001110111","00110011110000011001011100001110101010100110010110","00111001010011011111010100000100100000101101110001","10101101101110111110000011111011001011100011110001","00101110010101111000001010110100001110111011100011","01111110010100111010110001111000111101110100111011"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 12;
	all_right = (disabled || KawigiEdit_RunTest(7, p0, true, p1) ) && all_right;
	tests_disabled = tests_disabled || disabled;
	// ------------------
	}
	
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
