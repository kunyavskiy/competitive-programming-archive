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


int x,y,sx,sy,tx,ty;
int n;

ld solve(int dx,int dy){
    ld TX = dx*x + (abs(dx)%2?(x-tx):tx);
    ld TY = dy*y + (abs(dy)%2?(y-ty):ty);
    return sqrt((sx - TX)*(sx - TX) + (sy - TY) * (sy - TY));
}


bool solve(){                 
    cin >> x >> y >> sx >> sy >> tx >> ty >> n;

    if (sx == 0)
        return 0;

    ld ans = 1e100;

    for (int i = -n; i <= n; i++){
        int j = n - abs(i);
        ans = min(ans, solve(i,j));
        ans = min(ans, solve(i,-j)); 
    }

    cout.precision(15);
    cout << fixed << ans << endl;
    return 1;
}


int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    while (solve());


    return 0;
} 