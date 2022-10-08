//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;


const int MAXN = 110000;
const int MAXP = 110;

ll down(ll a,ll b){
    return (a - (a % b + b) % b) / b;
}

ll up(ll a,ll b){
    return down(a+b-1,b);
}


struct LinearMin {
    vector<ll> a;
    vector<ll> b;
    vector<ll> till;

    void push(ll na,ll nb) {
        till.pop_back();
        assert(na < a.back());
        while (till.size() > 1){
            if (a.back() * till.back() + b.back() >= na * till.back() + nb){
                a.pop_back();
                b.pop_back();
                till.pop_back();
            }
            else
                break;
        }
        ll temp = up(nb - b.back(),a.back() - na);
//      eprintf("\n"LLD" "LLD" "LLD" "LLD"\n",a.back(),b.back(),na,nb);
//      eprintf(LLD" "LLD"\n",temp,till.back());
        assert(temp > till.back());
        a.pb(na);
        b.pb(nb);
        till.pb(temp);
        till.pb(1LL<<50);
    }

    ll get(int pos){
        int id = upper_bound(till.begin(),till.end(),pos) - till.begin() - 1;
        assert(0 <= id && id < (int)a.size());
        return a[id] * pos + b[id];
    }

    void init(){
        a.pb(0);
        b.pb(0);
        till.pb(-(1LL<<50));
        till.pb((1LL<<50));
    }
};

ll d[MAXN];
int n,m,p;

ll dp[MAXP][MAXN];
int best[MAXP][MAXN];


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
    scanf("%d %d %d",&n,&m,&p);
    for (int i = 1; i < n; i++)
        scanf(LLD,&d[i]);
    for (int i = 1; i < n; i++)
        d[i] += d[i-1];

    vector<ll> t(m);

    for (int i = 0; i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        t[i] = b - d[a-1];
        assert(abs(t[i]) <= (1LL<<50));
    }

    sort(t.begin(),t.end());       
/*  for (int i = 0; i < m; i++)
        t[i] = t.back() - t[i];
    reverse(t.begin(),t.end());*/

    vector<int> sums(m+1);
    for (int i = 0; i < m; i++)
        sums[i+1] = sums[i] + t[i];


    memset(dp,1,sizeof(dp));
    for (int i = 0; i < p; i++)
        dp[i][0] = 0;

    for (int i = 1; i <= p; i++){
        LinearMin Lmin;
        Lmin.init();
        for (int j = 1; j <= m; j++) {
//          eprintf("%d %d\n",i,j);
            ll temp = Lmin.get(t[j-1]) - sums[j] + j * t[j-1];
            dp[i][j] = min(dp[i][j], temp);    
            dp[i][j] = min(dp[i][j], dp[i-1][j]);
//          eprintf("%d%c",dp[i][j]
            Lmin.push(-j, dp[i-1][j] + sums[j]);
            //ll temp = dp[i-1][k] + (j - k) * t[j - 1] - (sums[j] - sums[k]);
        }
    }

    printf(LLD"\n",dp[p][m]);
       
    TIMESTAMP(end);
    return 0;
}