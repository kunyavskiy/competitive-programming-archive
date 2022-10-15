#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

multiset<int> s;

int a[110000];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int m,n = 0;
  scanf("%d",&m);

  for (scanf("%d",&a[n++]);a[n-1] != -1; scanf("%d",&a[n++]));
  --n;

  for (int i = 0; i < m-1; i++)
  	s.insert(a[i]);

  for (int i = m-1; i < n; i++){
  	s.insert(a[i]);
  	printf("%d\n",*--s.end());
  	s.erase(s.find(a[i-m+1]));
  }


  return 0;
}