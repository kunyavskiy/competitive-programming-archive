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

#define taskname "A"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

pair<int,int> a[2000];

int t[2000];
int t1[2000];
const int inf=1100000000;

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n;
  scanf("%d",&n);
  for (int i=0;i<n;i++)
  {
    scanf("%d %d",&a[i].second,&a[i].first);
    a[i].first+=a[i].second;
  }
  sort(a,a+n);
    for (int j=0;j<=n;j++)
      t[j]=inf;
  t[0]=0;
  t[1]=a[0].second;
  for (int i=1;i<n;i++){
    for (int j=0;j<=n;j++)
      t1[j]=inf;
    for (int j=0;j<=n;j++){
       t1[j]=t[j];
       if (j>0 && t[j-1]<=(a[i].first-a[i].second))
        t1[j]=min(t1[j],t[j-1]+a[i].second);
    }
    memcpy(t,t1,sizeof(t));
  }

 // for (int i=0;i<n;i++)
  //  for (int j=0;j<=n;j++)
   //   cerr<<t[i][j]<<" \n"[j==n];

  int ans=0;
  for (int i=0;i<=n;i++)
    if (t[i]!=inf)
      ans=i;
  cout<<ans<<endl;
  return 0;
}