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
	int n;
	ll dlt = -(1LL<<50LL);
	int pos = -1;

	cin >> n;
	ll last = 0;
	for (int i = 0; i < n; i++){
		ll a;
		cin >> a;
		if (i && (abs(a-last) > dlt)){
			dlt = abs(a - last);
			pos = i;
		}
        last = a;
	}
	cout << pos <<" "<<pos+1<<endl;
  return 0;
}