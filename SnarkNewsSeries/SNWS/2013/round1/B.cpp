#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

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

        int t;
        cin >> t;

        for (int i = 0; i < t; i++){
        	ll n,w,h;
        	cin >> n >> w >> h;
        	ll ans = 1<<30;

        	for (int j = 1; j <= n; j++)
        		if (n % j == 0)
        			ans = min(ans,2*(j*w + (n/j)*h));
       		cout << ans << endl; 
        }


    return 0;
} 