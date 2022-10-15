#include <iostream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <fstream>
#include <queue>
#include <memory.h>
#include <stack>
#include <deque>

#define mp make_pair
#define pb push_back

#define taskname "C"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int a[1100000];
int d,n;
const int64 modul=1000000009;
                          
                                                                 
int main(){
#ifdef LOCAL
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
#endif
  scanf("%d %d",&n,&d);
  for (int i=0;i<n;i++)
    scanf("%d",&a[i]);
  sort(a,a+n);
  int l=-1,r;
  int64 ans=1;
  for (r=0;r<n;r++)
  {
    for (;a[l+1]<a[r]-d;l++);
    ans*=r-l;
    ans%=modul;
  }
//  cerr<<ans<<endl;
  printf(LLD,ans);
  return 0;
}