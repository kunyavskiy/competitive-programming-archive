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
	ld a,b,c;
	cin >> a >> b >> c;
	ld l = 0, r = 1e10;

	for (int i = 0; i < 1000; i++){
		ld mid = (l+r)/2;
		if (mid/a +mid/b+mid/c < 1000.0)
			l = mid;
		else
			r = mid;
	}

	ld val = (l+r)/2;

	int res = val;

	if (res+0.5 - val < 1e-9)
		res++;

	cout << res << endl;
	
	
    return 0;
}