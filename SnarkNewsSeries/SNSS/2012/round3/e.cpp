#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
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

#define taskname "e"

using namespace std;

typedef long long ll;
typedef long double ld;

ll dp[(1<<15)+10][7];

int x[20];
int y[20];

int n;

int main(){
    #ifdef LOCAL
        freopen(taskname".in","r",stdin);
        freopen(taskname".out","w",stdout);
    #endif

    scanf("%d",&n);

    for (int i = 0; i < n; i++)
        scanf("%d %d",&x[i],&y[i]),--x[i],--y[i];


    for (int i = 0; i < 7; i++)
        dp[0][i] = 1;


    for (int i = 0; i < (1<<n); i++)  
        for (int j = 0; j < 7; j++){ 
            //cerr << i << " "<<j<<" "<<dp[i][j] << endl;
            for (int k = 0; k < n; k++)
                if ((x[k] == j || y[k] == j) && !(i & (1<<k)))
                    dp[i | (1<<k)][x[k] + y[k] - j] += dp[i][j];
        }


    ll ans = 0;

    for (int i = 0; i < 7; i++)
        ans += dp[(1<<n)-1][i];



    for (int i = 0; i < n; i++){
        int cnt = 0;

        for (int j = i; j < n; j++)
            cnt += (x[i] == x[j]) && (y[j] == y[i]);

        assert(ans % cnt == 0);
        ans /= cnt;
    } 

    cout << ans << endl;

    return 0;
} 