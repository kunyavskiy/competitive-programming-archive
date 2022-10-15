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

int a[30];
int n;

vector<int> v;
vector<int> u;

void solve(){
    scanf("%d ",&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i]);

    int mx = *max_element(a,a+n);

    int msk = 0;

    for (int i = 0; i < n; i++)
        if (a[i] == mx)
            msk |= (1<<i);


    u.clear();
    u.pb(msk);

    if (msk == (1<<n)-1){
        printf("0\n");
        return ;
    }

    for (int it = 1;;it++){
        v.swap(u);
        u.clear();

        for (int i = 0,sz=v.size(); i < sz; i++)
          for (int j = 0; j < n; j++)
            for (int k = n; k >= j; k--)
              if (__builtin_popcount(v[i] & ((1<<k) - (1<<j))) * 2 >= k - j){               
                u.pb(v[i] | ((1<<k) - (1<<j)));
                if (u.back() == (1<<n)-1){
                    printf("%d\n",it);
                    return ;
                }
                break;
              }

        stable_sort(u.begin(),u.end());
        u.erase(unique(u.begin(),u.end()),u.end());
                
    }
        
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  for (; t-->0; )
    solve();

  return 0;
}

