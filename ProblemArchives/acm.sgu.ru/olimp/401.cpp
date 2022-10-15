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

#define taskname "E"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int t[110][110][110];
int from[110][110];
int from2[110][110];
int n,m;
int kol[110];
int a[110][110];

const int inf=1<<30;
                        
int calc(int i,int j,int k){
   if (kol[j]<k)
      return t[i][j][k]=inf;
   if (i==-1)
      return 0;
   if (t[i][j][k]!=-1)
      return t[i][j][k];

   //  cerr<<i<<" "<<j<<" "<<k<<endl;


   if (k!=0){
      t[i][j][k]=calc(i-1,j,k-1)+a[j][i];
      return t[i][j][k];
   } 
   t[i][j][k]=inf;
   for (int p=0;p<n;++p)
      if (p!=j)
        for (int l=1;l<=kol[p];++l)
          if (t[i][j][k]>calc(i,p,l)){
            t[i][j][k]=calc(i,p,l);
            from[i][j]=p;
            from2[i][j]=l;
          }
   return t[i][j][k];
}

void gen(int i,int j,int k){
 // cerr<<i<<" "<<j<<" "<<k<<" "<<a[0][i]<<" "<<a[1][i]<<endl;
  if (i==-1)
    return;
  if (k!=0){
    gen(i-1,j,k-1);
    printf("%d ",j+1);
    return;
  }
  gen(i,from[i][j],from2[i][j]);
}



int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d %d",&n,&m);                                       
  for (int i=0;i<m;i++)
    scanf("%d",&kol[i]);                                      
  for (int j=0;j<m;j++)
    for (int i=0;i<n;i++)
      scanf("%d",&a[j][i]);
  memset(t,-1,sizeof(t));
  int ans=inf;
  for (int i=0;i<m;i++)
    for (int j=1;j<=kol[i];j++)
      ans=min(ans,calc(n-1,i,j));
  printf("%d\n",ans);
  for (int i=0;i<m;i++)
    for (int j=1;j<=kol[i];j++)
      if (ans==calc(n-1,i,j)){
        gen(n-1,i,j);
        printf("\n");
        return 0;
      }
  assert(false);
      

  return 0;
} 