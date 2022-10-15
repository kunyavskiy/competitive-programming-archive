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

#define forn(i,n) for(int i=0;i<(n);i++)
#define ford(i,n) for(int i=(n)-1;i>=0;i--)

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long long ll;
typedef long double ld;

const ld eps=1e-9;

bool cmp(ld a,ld b){
    return a<b-b*eps;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int64 a,b;
  int64 r1,r2,r3,r4;
  int64 d,h;
  cin>>a>>b>>d>>r1>>r2>>r3>>r4>>h;
  a*=h;
  b*=h;
  r1*=h;
  r2*=h;
  r3*=h;
  r4*=h;
  int64 R1,R2;
  if (h<=d){
    R1=r2;
    R2=r4;
  }
  else{
    R1=r1+((r2-r1)*d)/h;
    R2=r3+((r4-r3)*d)/h;
  }

//  cerr<<R1<<" "<<R2<<endl;

  int64 dx=a-R1-R2;
  int64 dy=b-R1-R2;
  if (dx<0 || dy<0 || R1*2>min(a,b) || R2*2>min(a,b)){
      printf("NO\n");
      return 0; 
  }          
//  cerr<<dx<<" "<<dy<<endl;
  int64 D=dx*dx+dy*dy;
  if (D<(r2+r4)*(r2+r4))
    printf("NO\n");
  else
    printf("YES\n");
  return 0;
}