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

const ld eps = 1e-5;


class CandyOnDisk {

ll x[100],y[100],r[100];
ld L[100],R[100];
int n;

ld dist(ll x1,ll y1,ll x2,ll y2){
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


void update(const ll& x, const ll& y,const ll& ,const ld& L,const ld& R, ll& x2, ll& y2, ll& r2, ld& L2,ld& R2){
	if (L > R) return;
	ld d = dist(x,y,x2,y2);
	ld d1 = abs(d - L);
	L2 = min(L2,d1);
	R2 = max(R2,d1);
	d1 = abs(d + L);
	L2 = min(L2,d1);
	R2 = max(R2,d1);
	ld d2 = abs(d - R);
	L2 = min(L2,d2);
	R2 = max(R2,d2);
	d2 = abs(d + R);
	L2 = min(L2,d2);
	R2 = max(R2,d2);
	
	if (L - eps <= d && d <= R + eps)
		L2 = min(L2,(ld)0);	
	
	R2 = min(R2,(ld)r2);
}

public:
    string ableToAchieve(vector <int> _x, vector <int> _y, vector <int> _r, int sx, int sy, int tx, int ty) {
       n = _x.size();
       for (int i = 0; i < n; i++) {
       	    x[i] = _x[i], y[i] = _y[i], r[i] = _r[i];
		    ld d = dist(x[i],y[i],sx,sy);
		    if (d <= r[i])
		    	L[i] = R[i] = d;
		    else
		    	L[i] = 1e30, R[i] = -2;
       }
       
       if (sx == tx && sy == ty)
       	return "YES";
       
	   //for (int i = 0; i < n; i++)
	   //	   fprintf(stderr,"%lf ",(double)dist(x[i],y[i],tx,ty));
	   //fprintf(stderr,"\n");
       
       while (true){
       	   bool any = false;
       	   
       	   
       	   for (int i = 0; i < n; i++)
       	   	  fprintf(stderr,"[%lf,%lf] ",(double)L[i],(double)R[i]);
       	   fprintf(stderr,"\n");
       	   
       	   for (int i = 0; i < n; i++){
       	   		ld d = dist(x[i],y[i],tx,ty);
       	   		if (L[i]-eps <= d && d <= R[i]+eps)
       	   			return "YES";
       	   		for (int j = 0; j < n; j++)
       	   			if (i != j){
       	   				ld tmpL = L[j];
       	   				ld tmpR = R[j];
       	   				update(x[i],y[i],r[i],L[i],R[i], x[j],y[j],r[j],L[j],R[j]);
       	   				any |= (abs(L[j] - tmpL) > eps || abs(R[j] - tmpR) > eps);
       	   			}
       	   }
       	   
       	   if (!any)
         	   	return "NO";
       }
       return "FAIL";
    }
};


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <int> p0, vector <int> p1, vector <int> p2, int p3, int p4, int p5, int p6, bool hasAnswer, string p7) {
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
	cout << "}" << "," << p3 << "," << p4 << "," << p5 << "," << p6;
	cout << "]" << endl;
	CandyOnDisk *obj;
	string answer;
	obj = new CandyOnDisk();
	clock_t startTime = clock();
	answer = obj->ableToAchieve(p0, p1, p2, p3, p4, p5, p6);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << "\"" << p7 << "\"" << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << "\"" << answer << "\"" << endl;
	if (hasAnswer) {
		res = answer == p7;
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
	int p3;
	int p4;
	int p5;
	int p6;
	string p7;
	
	{
	// ----- test 0 -----
	int t0[] = {0,4};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {3,3};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = -1;
	p4 = -2;
	p5 = 6;
	p6 = 1;
	p7 = "YES";
	all_right = KawigiEdit_RunTest(0, p0, p1, p2, p3, p4, p5, p6, true, p7) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {0,3};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {5,3};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = -4;
	p4 = 0;
	p5 = -2;
	p6 = 0;
	p7 = "YES";
	all_right = KawigiEdit_RunTest(1, p0, p1, p2, p3, p4, p5, p6, true, p7) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 0;
	p4 = 0;
	p5 = 571;
	p6 = 571;
	p7 = "NO";
	all_right = KawigiEdit_RunTest(2, p0, p1, p2, p3, p4, p5, p6, true, p7) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {0};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 571;
	p4 = 571;
	p5 = 571;
	p6 = 571;
	p7 = "YES";
	all_right = KawigiEdit_RunTest(3, p0, p1, p2, p3, p4, p5, p6, true, p7) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	int t0[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 2;
	p4 = 2;
	p5 = 19;
	p6 = 19;
	p7 = "YES";
	all_right = KawigiEdit_RunTest(4, p0, p1, p2, p3, p4, p5, p6, true, p7) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	int t0[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 2;
	p4 = 2;
	p5 = 19;
	p6 = 19;
	p7 = "NO";
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, p3, p4, p5, p6, true, p7) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}

	{
	// ----- test 5 -----
	int t0[] = {0,1};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	int t1[] = {0,0};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	int t2[] = {1000000000, 1000000000};
			p2.assign(t2, t2 + sizeof(t2) / sizeof(t2[0]));
	p3 = 0;
	p4 = 0;
	p5 = 1000000000;
	p6 = 0;
	p7 = "NO";
	all_right = KawigiEdit_RunTest(5, p0, p1, p2, p3, p4, p5, p6, true, p7) && all_right;
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
