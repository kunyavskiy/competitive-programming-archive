// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
              

#define tlassert(x) if (!(x)) { printf("BOTVA!");while (true);}

const int MOD = 1000000007;

template<typename T>
void ADD(T& a,T b){
    a += b;
    if (a >= MOD) a -= MOD;
    if (a < 0) a += MOD;
}

int sign(int a){
    return (a > 0) - (a < 0);    
}

namespace Line{
    int bad[20];
    int x;
    int n;
    int a,b;

    const int MAXN = 11000;

    vector<int> g[MAXN];
    vector<int> gt[MAXN];
    vector<int> g2[MAXN];

    vector<int> ts;
    bool used[MAXN];
    int color[MAXN];

    void clear(){
        for (int i = 0; i < MAXN; i++)
            g[i].clear(), gt[i].clear(),g2[i].clear();
    }

    void addedge(int a,int b){
        if (binary_search(bad,bad+n,a))
            return;
        if (binary_search(bad,bad+n,b))
            return;
        a += MAXN/2;
        b += MAXN/2;
        if (a < 0 || a >= MAXN)
            return;
        if (b < 0 || b >= MAXN)
            return;

        g[a].pb(b);
        gt[b].pb(a);
    }

    int ans[MAXN];

    void dfs1(int v){
        if (used[v]) return;
        used[v] = true;
        for (int i = 0; i < (int)g[v].size(); i++)
            dfs1(g[v][i]);
        ts.pb(v);
    }


    void dfs2(int v,int c){
        if (color[v] != -1) return;
        color[v] = c;
        for (int i = 0; i < (int)gt[v].size(); i++)
            dfs2(gt[v][i],c);
    }


    int dfs3(int v,int to){
        if (ans[v] != -3)
            return ans[v];
        if (to == v){
            for (int i = 0; i < (int)g2[v].size(); i++)
                if (g2[v][i] == v)
                    return Line::ans[v] = -1;
            return Line::ans[v] = 1;
        }
        int& ans = Line::ans[v];
        ans = 0;

        for (int i = 0; i < (int)g2[v].size(); i++){
            if (g2[v][i] == v) continue;
            int tmp = dfs3(g2[v][i],to);
            if (tmp == -1) return ans = -1;
            ADD(ans,tmp);
        }

        if (ans){
            for (int i = 0; i < (int)g2[v].size(); i++)
                if (g2[v][i] == v)
                    return ans = -1;
        }
        return ans;
    }


    int solve(){                        
        int gc = __gcd(abs(a),abs(b));
        sort(bad,bad+n);
        clear();

        for (int i = -MAXN/2; i < MAXN/2; i++){
            if (abs(i) > 1000 && sign(a) != sign(b) && sign(a) && sign(b)){
                addedge(i,i);
                addedge(i,i+gc);
                addedge(i,i-gc);
            }
            addedge(i,i+a);
            addedge(i,i+b);
        }

        for (int i = 0; i < MAXN; i++){
            sort(g[i].begin(),g[i].end());
            g[i].erase(unique(g[i].begin(),g[i].end()),g[i].end()); 
        }

        memset(used,0,sizeof(used));
        ts.clear();


        for (int i = 0; i < MAXN; i++)
            dfs1(i);
        memset(color,-1,sizeof(color));
        reverse(ts.begin(),ts.end());


        int cid = 0;

        for (int j = 0; j < MAXN; j++)
            if (color[ts[j]] == -1)
                dfs2(ts[j], cid++);

        for (int i = 0; i < MAXN; i++)
            for (int j = 0; j < (int)g[i].size(); j++){
                g2[color[i]].pb(color[g[i][j]]);
            }

        for (int i = 0; i < MAXN; i++)
            ans[i] = -3;

        int t = dfs3(color[MAXN/2], color[x + MAXN/2]);
        if (t == -2)
            return 0;
        return t;
    }
}


pair<int,int> bad[20];
int n;
int x,y;
int ax,ay,bx,by;

int dp[(1<<16)+100];


const int MAXFAC = 1000100;

int f[MAXFAC];
int invf[MAXFAC];

int pow(int a,int b){
    if (!b) return 1;
    if (b&1) return (pow(a,b-1) * 1LL * a)%MOD;
    int res = pow(a,b/2);
    return (res * 1LL * res) % MOD;
}


int Cnk(int x,int y){
    if (x < 0 || y < 0 || x < y)
        return 0;
    int ans = (((f[x] * 1LL * invf[x-y]) % MOD) * 1LL * invf[y]) % MOD;
    return ans;
}


void expand(int ax,int ay,int bx,int by,int& x,int& y){
    int det1 = ax * by - ay * bx;
    int det2 = x * by - y * bx;
    int det3 = ax * y - ay * x;

    //tlassert(ax * det2 + bx * det3 == x * det1);
    //tlassert(ay * det2 + by * det3 == y * det1);
    //tlassert(det1);

    if (det2 % det1 || det3 % det1){
        x = y = -1;
        return;
    }
    x = det2 / det1;
    y = det3 / det1;    
}
        

void solve(){
    scanf("%d %d %d",&x,&y,&n);
    scanf("%d %d %d %d",&ax,&ay,&bx,&by);
    for (int i = 0; i < n; i++)
        scanf("%d %d",&bad[i].first,&bad[i].second);

    if (ax == 0 && bx == 0){
        swap(ax,ay);
        swap(bx,by);
        swap(x,y);
        for (int i = 0; i < n; i++)
            swap(bad[i].first,bad[i].second);
    }

    if (ax == 0 && bx == 0){
        printf("%d\n",(x || y)?0:-1);
        return;
    }

    if (ax * by == ay * bx){
        Line::a = ax;
        Line::b = bx;
        if (ax * y != ay * x || bx * y != by * x){
            printf("0\n");
            return;
        }

        Line::x = x;
        Line::n = 0;
        for (int i = 0; i < n; i++)
            if (ax * bad[i].second == ay * bad[i].first && bx * bad[i].second == by * bad[i].first){
                Line::bad[Line::n++] = bad[i].first;
            }

        printf("%d\n",Line::solve());
        return;
    }

    for (int i = 0; i < n; i++){
        expand(ax,ay,bx,by,bad[i].first,bad[i].second);

        if (bad[i].first < 0 || bad[i].second < 0)
            swap(bad[i],bad[n-1]), i--,n--;
    }

    expand(ax,ay,bx,by,x,y);
                                                         
    bad[n++] = mp(x,y);

    sort(bad,bad+n);

    n = unique(bad,bad+n) - bad;

    if (x < 0 || y < 0){
        printf("0\n");
        return;
    }

    while (bad[n-1] != mp(x,y))
        --n;

    for (int i = 1; i < (1<<n); i++){               
        int last = 31 - __builtin_clz(i);
        int other = i ^ (1<<last);

        if (other == 0){
            dp[i] = Cnk(bad[last].first+bad[last].second,bad[last].second);
            continue;
        }
        int last2 = 31 - __builtin_clz(other);

        dp[i] = (dp[other] * 1LL *  Cnk(bad[last].first+bad[last].second - bad[last2].first - bad[last2].second,bad[last].second - bad[last2].second)) % MOD;
    }


    for (int i = (1<<n)-1; i >= 0; i--)
        for (int j = (i+1)|i; j < (1<<n); j = (j+1)|i)
            ADD(dp[i], -dp[j]);


    printf("%d\n",(int)((dp[1<<(n-1)]%MOD+MOD)%MOD));
    return;
}

int START = clock();


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXFAC; i++){
    f[i] = (f[i-1] * 1LL * i) % MOD;
    invf[i] = pow(f[i], MOD-2);
  }
      

  int t;
  scanf("%d",&t);
  while (t-->0){
    cerr << t << endl;
    solve();
  }

  return 0;
}