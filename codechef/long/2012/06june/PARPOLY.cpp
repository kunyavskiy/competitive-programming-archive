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


const int MOD = 1000000007; 
typedef vector<int> poly;

int todeg;

int eval(const vector<int>& v,int a){
   int val = 0;
   for (int i = (int)v.size()-1; i >= 0; i--){
      val = (val * 1LL * a + v[i]) % MOD;
   }
   return val;
}

poly operator*(const poly& a,const poly& b){
    poly c(todeg+1);
    for (int i = 0; i <=todeg; i++)
        for (int j = 0; i+j <=todeg; j++)
           c[i+j] = (c[i+j] + (a[i]*1LL*b[j]))%MOD; 
    return c;
}

poly operator^(poly a,int st){
    poly res(todeg+1);
    res[0] = 1;
    for (int i = 0; (1<<i) <= st; i++){
        if (st & (1<<i)){
            res = res * a;
        }                 
        a = a*a;
    }
    return res;
}

void solve(){
    int m,n,x;
    scanf("%d %d %d",&m,&n,&x);
    todeg = n;
    poly p(todeg+1);
    poly g;
    int d;
    scanf("%d",&d);
    g.resize(d+1);
    for (int i = 0; i <= d; i++)
        scanf("%d",&g[i]);

    for (int i = 0; i <= n; i++)
        p[i] = eval(g,(i*1LL*x)%MOD);



    p = p ^ m;
    printf("%d\n",p.back());
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);
  while (t-->0)
    solve();


  return 0;
}