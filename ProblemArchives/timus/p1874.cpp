#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

ld l1,l2;

ld f(ld x,ld y){
	return x*y + 1.0/2*sqrt(l1*l1 - x*x)*x + 1.0/2*sqrt(l2*l2-y*y)*y;
}

ld tern2(ld x){
	ld l = 0;
	ld r = l2;

	for (int i = 0; i < 500; i++){
		ld y1 = l + (r-l)/3;
		ld y2 = r - (r-l)/3;
		ld f1 = f(x,y1);
		ld f2 = f(x,y2);
		if (f1 > f2)
			r = y2;
		else
			l = y1;
	}

	return f(x,(l+r)/2);
}


ld tern1(){
	ld l = 0;
	ld r = l1;

	for (int i = 0; i < 500; i++){
		ld x1 = l + (r-l)/3;
		ld x2 = r - (r-l)/3;
		ld f1 = tern2(x1);
		ld f2 = tern2(x2);
		if (f1 > f2)
			r = x2;
		else
			l = x1;
	}

	return tern2((l+r)/2);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  cin >> l1 >> l2;
  cout.precision(15);
//  cerr << fixed<<f(sqrt(2.0),sqrt(2.0)) << endl;
  cout << fixed << tern1() << endl;

  return 0;
}