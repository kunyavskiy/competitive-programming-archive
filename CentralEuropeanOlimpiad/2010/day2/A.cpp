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

#define lf(x) (((x)<<1)+1)
#define rg(x) (((x)+1)<<1)
#define par(x) (((x)-1)>>1)

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int treel[1<<20];
int treer[1<<20];
int treel2[1<<20];
int treer2[1<<20];
int n,vmax,v;
int lst,sz;

int calc(int val,int v){
  if (val>=treer2[v])
    return treer[v];
  if (val<=treel2[v])
    return treel[v];
  return val-treel2[v]+treel[v];
}

inline int binary(int v){
  int l,r;
  l=0;
  r=vmax+1;
  for (;r-l>1;){
    int m=(l+r)/2;
    if (calc(calc(m,lf(v)),rg(v))<=treel[v])
      l=m;
    else
      r=m;
  }
  //assert(calc(calc(l,lf(v)),rg(v))==treel[v]);
  //if (l!=vmax)
    //assert(calc(calc(l+1,lf(v)),rg(v))>treel[v]);
  return l;
}

void update(int v){
  if (lf(v)>=sz)
    return;
  treel[v]=calc(calc(0,lf(v)),rg(v));
  treer[v]=calc(calc(vmax,lf(v)),rg(v));
  //assert(treel[v]<=treer[v]);
  treel2[v]=binary(v);
  treer2[v]=treel2[v]+treer[v]-treel[v];
}

void setval(int v,int a){

 // cerr<<"SET "<< v<< " TO "<<a<<endl;

  v=v+lst-1;

  if (a==1){
    treel[v]=1;
    treer[v]=vmax;
    treel2[v]=0;
    treer2[v]=vmax-1;
  }
  else if (a==-1){
    treel[v]=0;
    treer[v]=vmax-1;
    treel2[v]=1;
    treer2[v]=vmax;
  }
 // else
    //assert(false);
  for (v=par(v);v;v=par(v))
    update(v);
  update(v);
}

int delt[110000];
pair<int,int> dts[110000];
int dt[110000];

void inittree(){
  lst=2;
  for (;lst<=n+10;lst*=2);
  sz=lst*2-1;
  for (int i=lst-1;i<sz;i++)
    {
      treel[i]=treel2[i]=0;
      treer[i]=treer2[i]=vmax;
    }
  for (int i=lst-2;i>=0;i--)
    update(i);
}

int main(){
#ifdef LOCAL
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
#endif
  scanf("%d %d %d",&n,&vmax,&v);
  for (int i=0;i<n;i++){
    char c;
    scanf(" %c %d",&c,&dt[i]);
  //  cerr<<c;
    if (c=='+')
      delt[i]=1;
    else
      delt[i]=-1;
  }
  //cerr<<endl;
  for (int i=n-1;i>0;i--)
    dt[i]=dt[i]-dt[i-1];
  dt[0]=2000000100;
  for (int i=0;i<n-1;i++)
    dts[i]=mp(dt[i+1],i+1);
  sort(dts,dts+n-1);

  int ans=dts[0].first-1,val=v;

  inittree();

  for (int i=0;i<n-1;){
    int j=i;
    for (;j<n-1 && dts[i].first==dts[j].first;j++)
      setval(dts[j].second,delt[dts[j].second]);
 //   cerr<<dts[j].first-1<<" "<<treel[0]<<" "<<treer[0]<<endl;
    if (treel[0]<=v && v<=treer[0]){
      if (j==n-1){
        printf("infinity\n");
        return 0;
      }
      ans=dts[j].first-1;
      val=treel2[0]+(v-treel[0]);
      if (v==treer[0])
         val=vmax;          
      //assert(calc(val,0)==v);
    }             
    i=j;
  }

 // cerr<<treel[0]<<" "<<treer[0]<<endl;
  //cerr<<treel[1]<<" "<<treer[1]<<endl;

  if (treel[0]<=v && v<=treer[0]){
        printf("infinity\n");
        return 0;
  }
  printf("%d %d\n",ans,val);
  return 0;
}