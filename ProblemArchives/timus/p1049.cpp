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

int cnt[11000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	for (int i = 0; i < 10; i++){
		int x;
		cin >> x;
		for (int j = 2; j*j <= x; j++)
			while (x%j == 0)
				cnt[j]++,x/=j;
	    cnt[x]++;
	}
	ll ans = 1;
	for (int i = 2; i <= 10000; i++)
		ans = (ans * (cnt[i]+1))%10;
	cout << ans << endl;	
  return 0;
}