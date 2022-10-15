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


int a[110];

void solve(){
    memset(a,0,sizeof(a));
    int n,m;
    scanf("%d %d",&n,&m);
    for (int i = 0;i < n; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        ::a[b] += a;
    }
    for (int i = 0;i < m; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        ::a[b] -= a;
    }

    int sum = 0;
    for (int i = 0; i <= 100; i++)
        sum += max(0, -a[i]);

    cout << sum << endl;
    return;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  while (t--)
    solve();

  return 0;
}