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


inline int get(){
  char c;
  scanf(" %c",&c);
  if ('a' <= c && c <= 'z')
    return c-'a';
  return c-'A' + 26;
}

void solve(){
    int n,m;
    scanf("%d",&n);
    ll mask = 0;

    for (int i = 0; i < n; i++){
        int a = get(),b = get();
        mask ^= (1LL<<a);
        mask ^= (1LL<<b);
    }

    scanf("%d",&m);


    vector<ll> b(m,0);


    for (int i = 0; i < m; i++){
        int a = get(),c = get();
        ll& temp = b[i];
        temp ^= (1LL<<a);
        temp ^= (1LL<<c);
    }

    for (int i = 63; i > 0; i--){
        int id = -1;
        for (int j = 0; j < m; j++)
            if (b[j] & (1LL<<i)){
                if (id == -1)
                    id = j;
                else
                    b[j] ^= b[id];
            }
        if (mask & (1LL<<i)){
            if (id == -1){
                printf("NO\n");
                return;
            }
            else 
                mask ^= b[id];
        }

        if (id != -1)
            b[id] = 0;
    }

    printf("YES\n");
    return;
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