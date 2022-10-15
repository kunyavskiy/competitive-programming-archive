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

#define next next_223456
#define perv perv_234567

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

#define taskname "d"

using namespace std;

typedef long long ll;
typedef double ld;

ld dist[55][55];
ld dp[55][55];

int x[55];
int y[55];
int n;

int next[55];
int prev[55];
int used[55];

ld calc(int l,int r){
    //cerr << l <<" "<<r<<"     !"<<endl;
    if (dp[l][r] > -0.5)
        return dp[l][r];

    ld& ans = dp[l][r];

    if (r - l == 2) return ans = 0;
    if (r - l == 1) return -dist[l][r];

    ans = calc(l+1,r) + dist[l+1][r];
    ld dp2[55];

    for (int i = l; i < r; i++)
        dp2[i] = dist[l][i] + calc(l, i);

    for (int j = l+1; j < r; j++){                                
        for (int k = j+1; k < j; k++)
            dp2[j] = min(dp2[j], dp2[k] + dist[j][k] + calc(k,j));
        //cerr <<l <<" "<<r<<" "<<j<<" "<<dp2[j] << endl;
    }

    for (int i = l+1; i < r; i++)
        ans = min(ans, dp2[i] + dist[i][r] + calc(i,r));

    

    //cerr << l <<" "<<r<< " "<<ans << endl;

    return ans; 
}

void solve(){      
    scanf("%d",&n);
    for (int i = 0; i < n; i++){
        scanf("%d %d",&x[i],&y[i]);
        for (int j = 0; j < i; j++)
            dist[i][j] = dist[j][i] =  sqrt((x[i] - x[j]) * 1LL* (x[i] - x[j]) + (y[i] - y[j]) * 1LL* (y[i] - y[j])), dp[i][j] = dp[j][i] = -1.0;
    }


    cout.precision(15);
    cout << fixed << calc(0,n-1) << endl;

}

int main(){
    #ifdef LOCAL
        freopen(taskname".in","r",stdin);
        freopen(taskname".out","w",stdout);
    #endif

    int t;
    scanf("%d",&t);
    while (t-->0){
        solve();
       // cerr << endl << endl;
    }


    return 0;
} 