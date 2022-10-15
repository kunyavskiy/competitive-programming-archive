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


struct point{
	int x,y;
	ld p;
	point(int x,int y):x(x),y(y){};
	point(int x,int y, ld p):x(x),y(y),p(p){};
	point(){}
};

int operator*(const point& a,const point& b){
	return a.x * b.y - a.y * b.x;
}

point operator-(const point& a, const point& b){
	return point(a.x - b.x, a.y - b.y);
}

bool check(const point& a, const point& b, const point& c, const point& d){
	ll s1 = abs((c - a) * (b - a));
	ll s2 = 0;
	s2 += abs((a - d) * (b - d));
	s2 += abs((b - d) * (c - d));
	s2 += abs((c - d) * (a - d));
	return s2 == s1;
}

bool operator<(const point& a, const point& b){
	if (a.y != b.y)
		return a.y < b.y;
	return a.x < b.x;
}




class Constellation {

int sgn(int x){
	return (x > 0) - (x < 0);
}

public:
    double expectation(vector <int> x, vector <int> y, vector <int> _p) {
        int n = x.size();
        vector<point> v(n);
        for (int i = 0; i < n; i++){
        	v[i] = point(x[i], y[i], _p[i]/1000.0);
        }
        
        sort(v.begin(), v.end());
        
        ld prevprob = 1.0;
        ld ans = 0.0;
        
        for (int i = 0; i < n; i++){
        	for (int j = i+1; j < n; j++)
        		for (int k = i+1; k < n; k++){
        			if (j == k) continue;
        			if ((v[j] - v[i]) * (v[k] - v[i]) <= 0) continue;
        			ld prob = prevprob * v[i].p * v[j].p * v[k].p;
        			if (prob <= 1e-20) continue;
        			for (int a = i+1; a < n && prob > 1e-20; a++){
        				if (a == j || a == k) continue;
        				if (check(v[i], v[j], v[a], v[k]) || check(v[i], v[k], v[a], v[j])){
        					prob *= 1.0 - v[a].p;
        					continue;
        				}
        				if (sgn((v[a] - v[i]) * (v[j] - v[i])) * sgn((v[k] - v[i]) * (v[a] - v[i])) == 1 && !check(v[i], v[j], v[k], v[a])){
        					prob *= 1.0 - v[a].p;
        					continue;
        				}
        			}
        					//eprintf("%d is bad for (%d, %d, %d)", a, i,j,k);
        				
        			ans += prob * ((v[j] - v[i]) * (v[k] - v[i])) / 2.0;
        			//eprintf("%lf %lf\n", (double)prob, (double)(((v[j] - v[i]) * (v[k] - v[i])) / 2.0));
        		}
        	prevprob *= 1.0 - v[i].p;
        }
        return (double)ans;
        			
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, vector <int> p2, bool hasAnswer, double p3) {
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
		cout << p1[i];
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p2.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p2[i];
	}
	cout << "}";
	cout << "]" << endl;
	Constellation *obj;
	double answer;
	obj = new Constellation();
	clock_t startTime = clock();
	answer = obj->expectation(p0, p1, p2);
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
		res = answer == answer && fabs(p3 - answer) <= 1e-9 * max(1.0, fabs(p3));
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
	vector <int> p1;
	vector <int> p2;
	double p3;
	
	{
	// ----- test 0 -----
	int t0[] = {0,0,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,1,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {500,500,500};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 0.0625;
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {0,1,0,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0,1,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1000,1000,400,800};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 0.6000000000000001;
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {-1,-1,-1,0,0,0,1,1,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-1,0,1,-1,0,1,-1,0,1};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {500,500,500,500,500,500,500,500,500};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 1.9375;
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {0,0,1,2,2};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,1,2,1,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1000,500,200,500,1000};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 1.3;
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	int t0[] = {1,5,5,8,2,6,9};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {3,6,4,2,5,7,9};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {100,400,200,1000,400,900,600};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 12.888936;
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, true, p3) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	int t0[] = {-100,100,-100,100,-42,57,-34,76,35,-75,-54,10,43};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {-100,-100,100,100,52,-57,-84,63,-43,50,63,10,-44};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1000,1000,1000,1000,342,747,897,325,678,34,53,6,253};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 40000.0;
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
