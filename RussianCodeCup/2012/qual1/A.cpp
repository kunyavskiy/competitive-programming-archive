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

int a[12];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  while (true){
    for (int i = 0; i < 12; i++)
        scanf("%d",&a[i]);
    if (a[0] == 0)
        break;
    sort(a,a+12);
    if (a[0] == a[3] && a[4] == a[7] && a[8] == a[11])
        puts("yes");
    else
        puts("no");
  }

  return 0;
}