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

int cnt[11000];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n,m;
  	scanf("%d %d",&n,&m);

  	for (int i = 0; i < m; i++){
  		int a;
  		scanf("%d",&a);
  		cnt[a-1]++;
  	}

  	for (int i = 0; i < n; i++)
  		printf("%d.%02d%%\n",(cnt[i]*100)/m,((cnt[i]*10000)/m + (((cnt[i]*10000)%m) * 2 >= m))%100);
  		

  return 0;
}