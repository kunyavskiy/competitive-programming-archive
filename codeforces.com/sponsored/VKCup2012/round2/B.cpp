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

pair<pair<int,int>,int> a[110000];
int n,k,h;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d %d",&n,&k,&h);

    for (int i = 0; i < n; i++)
        scanf("%d",&a[i].first.first);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i].first.second),a[i].second = i;

    sort(a,a+n);

    ld l = 0;
    ld r = 1e20;

    for (int i = 0; i < 300; i++){
        ld m = (l+r)/2;
        int cnt = 1;

        for (int j = 0; j < n && cnt <= k; j++){
            if (cnt <= m * a[j].first.second + (1e-5))
                cnt++;
        }

        if (cnt >= k+1)
            r = m;
        else
            l = m;

    }

    ld m = r;
    int cnt = 1;

//    cerr << m << endl;

    for (int j = 0; j < n && cnt <= k; j++){
        if (cnt <= m * a[j].first.second + (1e-5))
            cnt++,printf("%d ",a[j].second+1);
    }

    

  return 0;
}

