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
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
#endif

using namespace std;

typedef unsigned long long ll;
typedef long double ld;

ll c(ll n,ll k){
    ll ans = 1;
    for (int i = 1; i <= k; i++)
        ans = (ans * (n-i+1)) /i;
    return ans;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n,a,b;
    cin >> n >> a >> b;
    cout << c(n+a,a)*c(n+b,b) << endl;
    return 0;
}