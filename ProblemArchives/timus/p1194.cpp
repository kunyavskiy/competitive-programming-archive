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

int cnt[50000];




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n,k;
	cin >> n >> k;
	cnt[1] = n;
	int a,b;
	ll ans = 0;
	while (cin >> a >> b){
		ans += cnt[a] * (cnt[a] - 1)/2;
		for (int j = 0; j < b; j++){
			int x,y;
			cin >> x >> y;
			cnt[x] = y;
			ans -= y*(y-1)/2;
		}
	}
	cout << ans << endl;
  return 0;
}