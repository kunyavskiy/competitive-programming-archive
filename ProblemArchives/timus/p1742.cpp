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
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

int next[MAXN];
int n;

vector<int> ts;

bool used[MAXN];


void dfs(int x){
    if (used[x]) return;
    used[x] = true;
    dfs(next[x]);
    ts.pb(x);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&next[i]),--next[i];

    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(i);


    int ans1,ans2;
    ans1 = ans2 = 0;

    memset(used,0,sizeof(used));
    for (int i = 0; i < n; i++)
        if (!used[ts[i]]){
            ans1++;
            dfs(ts[i]);
        }
    
    memset(used,0,sizeof(used));
    for (int i = n-1; i >= 0; i--)
        if (!used[ts[i]]){
            ans2++;
            dfs(ts[i]);
        }

    cout << ans2 <<" "<<ans1 << endl;


    return 0;
}