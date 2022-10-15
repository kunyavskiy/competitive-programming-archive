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

ll n,k;
int q;

const int MAXN = 20000;

ll dels[MAXN];
int cnt[MAXN];
int ptr;

pair<ll,int> _dels[MAXN];

ll gcd(ll a,ll b){
    while (a && b){
        swap(a,b);
        a %= b;
    }
    return a+b;
}
         

ll p[MAXN];
int st[MAXN];
int pptr;

void go(int pos,ll val,int cnt){
    if (pos == pptr){
        assert(n % val == 0);
        _dels[ptr++] = mp(val,cnt);
        assert(ptr <= MAXN);
        return;
    }
    for (int i = 0; i <= st[pos]; i++){
        go(pos+1,val,cnt*(i+1));
        val = val * p[pos];
    }
} 


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf(LLD" %d",&n,&q); 

  ll n1 = n;
  for (int i = 2; i*1LL*i <= n1; i++)
    if (n1 % i == 0){
        p[pptr] = i;
        st[pptr] = 0;
        while (n1 % i == 0){
            st[pptr]++;
            n1 /= i;
        }
        ++pptr;
        assert(pptr <= 70);
    }

  if (n1 > 1)
    p[pptr] = n1,st[pptr++] = 1;

  go(0,1,1);

  sort(_dels,_dels+ptr);
                       

  /*for (int i = 0; i < ptr; i++)
    for (int j = 0; j <= i; j++)
        if (dels[i] % dels[j] == 0)
            cnt[i]++;*/

  for (int i = 0; i < ptr; i++)
    dels[i] = _dels[i].first,cnt[i] = _dels[i].second;

  
  for (int i = 0; i < q; i++){
    int t;ll k;
    scanf("%d "LLD,&t,&k);         
    if (t == 1){
        ll g = gcd(n,k);
        int id = lower_bound(dels,dels+ptr,g) - dels;
        printf("%d\n",cnt[id]);
    }
    else if (t == 2){
        if (n % k != 0)
            printf("0\n");
        else {
            int id = lower_bound(dels,dels+ptr,n / k) - dels;
            printf("%d\n",cnt[id]);
        }
    } else {
        assert(t == 3);
        if (n % k != 0)
            printf("%d\n",ptr);
        else {
            int id = lower_bound(dels,dels+ptr,n / k) - dels;
            printf("%d\n",ptr - cnt[id]);
        }

    }

  }

  return 0;
}