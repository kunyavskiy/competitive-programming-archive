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
    vector<ll> v;
    int ans = 0;
    v.resize(3);
    cin >> v[0] >> v[1] >> v[2];
    for (;;){
    	ans++;
    	ll best = abs(v[1] - v[0]);
    	for (int i = 0; i < v.size(); i++)
    		for (int j = i+1;j < v.size(); j++)
    			best = min(best,abs(v[i] - v[j]));
    	v.pb(best);
    	if (best == 0)
    		break;
    }
    cout << ans << endl;
  return 0;
}