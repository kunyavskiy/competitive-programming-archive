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


const int MAXN = 100;
const ld eps = 1e-9;

ld a[MAXN][MAXN];
ld b[MAXN];
bool buity[MAXN];
int n,m,s;
vector<int> g[MAXN];
ld ans[MAXN];
vector<int> reqs;



void build2(int v){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2*n; j++)
            a[i][j] = 0;
        if (i == v){
            a[i][i] = 1;
            a[i][i+n] = -1;
            b[i] = 0;
            continue;
        }
        if (i == n-1){
            a[i][i] = 1;
            b[i] = 0;
            continue;
        }
        a[i][i] = 1;
        for (int j = 0; j < (int)g[i].size(); j++)
            a[i][g[i][j]] -= 1.0/g[i].size();
        b[i] = 0;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < 2*n; j++)
            a[i+n][j] = 0;
        if (buity[i] && i != v){
            a[i+n][i] = 1;
            a[i+n][i+n] = -1;
            b[i+n] = 0;
            continue;
        }
        if (i == n-1){
            a[i+n][i+n] = 1;
            b[i+n] = 1;
            continue;
        }
        a[i+n][i+n] = 1;
        for (int j = 0; j < (int)g[i].size(); j++)
            a[i+n][g[i][j]+n] -= 1.0/g[i].size();
        b[i+n] = 0;
    }
}


void solve(){

   /* {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++)
                fprintf(stderr,"%5.2lf ",(double)a[i][j]);
            fprintf(stderr," = %.2lf\n",(double)b[i]);
        }
        cerr << endl << endl;
    }*/

    
    for (int i = 0; i < n; i++){

        int id = i;
        for (int j = i+1; j < n; j++)
            if (fabsl(a[j][i]) > fabsl(a[id][i]))
               id = j;

        for (int j = 0; j < n; j++)
           swap(a[id][j],a[i][j]);
        swap(b[id],b[i]);
        assert (fabsl(a[i][i]) > eps)


        for (int j = 0; j < n; j++){
            if (i == j)
                continue;
            ld coef = a[j][i]/a[i][i];

            for (int k = 0; k < n; k++)
                a[j][k] -= coef*a[i][k];
            b[j] -= b[i] * coef;
        }                
    }

    ld sum = 0;

    for (int i = 0; i < n; i++){
        b[i] /= a[i][i];
        //assert(b[i] > -eps && b[i] < 1+eps);
        sum += b[i];
    }
}

bool used[MAXN];

bool dfs(int v){
    if (v == n-1)
        return true;
    if (used[v])
        return false;
    used[v] = true;
    for (int i = 0; i < g[v].size(); i++)
        if (dfs(g[v][i]))
            return true;
    return false;
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d %d %d",&n,&m,&s);
  for (int i = 0; i < s; i++){
    int a;
    scanf("%d",&a);
    buity[a-1] = true;    
    reqs.pb(a-1);
  }

  for (int i = 0; i < m; i++){
    int a,b;
    scanf("%d %d",&a,&b);
    g[a-1].pb(b-1);
  }

  for (int i = 0; i < n; i++){
    memset(used,0,sizeof(used));
    assert(dfs(i));
  }

  assert(2 <= n && n <= 30);
  assert(s < n);
  assert(!buity[n-1]);


  for (int i = 0; i < s; i++){

    build2(reqs[i]);
    n *= 2;
    solve();
    n /= 2;    

    ans[i] = b[0];
  }   



  for (int i = 0; i < s; i++)
    printf("%.18lf\n",double(ans[i]));
  return 0;
}