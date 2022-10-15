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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	ld a,r;
	cin >> a >> r;
	a /= 2;
	ld ans = 0;

	if (r <= a){
		ans = r*r*acos(-1.0)/4;
	}
	else if (r <= a*sqrt(2.0)){
		ld b = sqrt(r*r - a*a);
	//	cerr << a<<" "<<b << endl;
		ans = a*b + atan2(abs(b*b-a*a),2*a*b)*r*r/2;
	}
	else {
		ans = a*a;
	}
    

	cout.precision(15);
	cout << fixed << ans * 4 << endl;
  return 0;
}