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

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  for (int i = 0; i < t; i++){
    int n;
    scanf("%d",&n);
    vector<int> x(n),y(n);
    for (int i = 0; i < n; i++){
        scanf("%d %d",&x[i],&y[i]);
    }

    sort(x.begin(),x.end());
    sort(y.begin(),y.end());

    cout << (x[n/2] - x[(n-1)/2] + 1) * 1LL * (y[n/2] - y[(n-1)/2] + 1) << endl;   

  }

  return 0;
}

