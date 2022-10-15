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


char s[110000];

void solve(){
    gets(s);
    int n = strlen(s);
    ll ans  = n * 1LL *(n+1)/2;

    for (int i = 0; i < n; ){
        if (s[i] == '4') {
            i++;
            continue;
        }
        int j = i;
        while (s[j] == '7')
            j++;

        ans -= (j-i)*1LL*(j-i+1)/2;
        i = j;
    }

    cout << ans << endl;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  gets(s);
  sscanf(s,"%d",&t);

  while (t-->0)
    solve();

  return 0;
}