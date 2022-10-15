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

#define taskname "B"

#ifdef LOCAL 
  #define LLD "%I64d"
#else
  #define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

//int64 kol[4];
int64 val1[4][36];
int64 val2[4][4][36][36];
int64 val3[4][4][4][36][36][36];

string pins[100000];
int n,d;

inline int number(char c){
  if (c<='z' && c>='a')
    return c-'a';
  else
    return c-'0'+26;
}

void PreCalc(){     
  for (int i=0;i<n;i++)
    for (int j=0;j<4;j++)
      val1[j][number(pins[i][j])]++;

  for (int i=0;i<n;i++)
    for (int j=0;j<4;j++)
      for (int k=0;k<4;k++)
        val2[j][k][number(pins[i][j])][number(pins[i][k])]++;


  for (int i=0;i<n;i++)
    for (int j=0;j<4;j++)
      for (int k=0;k<4;k++)
        for (int l=0;l<4;l++)
        val3[j][k][l][number(pins[i][j])][number(pins[i][k])][number(pins[i][l])]++;

}

int64 calc3(){
   int64 ans=0;
   for (int i=0;i<36;i++)
      for (int j=0;j<36;j++)
        for (int k=0;k<36;k++)
          for (int i1=0;i1<4;++i1)
            for (int j1=i1+1;j1<4;++j1)
              for (int k1=j1+1;k1<4;++k1)
              {
                int64 tmp=val3[i1][j1][k1][i][j][k];
                ans+=tmp*(tmp-1)/2;
              }  
  return ans;
}

int64 calc2(){
   int64 ans=0;
   for (int i=0;i<36;i++)
      for (int j=0;j<36;j++)
          for (int i1=0;i1<4;++i1)
            for (int j1=i1+1;j1<4;++j1)
              {
                int64 tmp=val2[i1][j1][i][j];
                ans+=tmp*(tmp-1)/2;
              }  
  return ans;
}

int64 calc1(){
   int64 ans=0;
   for (int i=0;i<36;i++)
          for (int i1=0;i1<4;++i1)
              {
                int64 tmp=val1[i1][i];
                ans+=tmp*(tmp-1)/2;
              }  
  return ans;
}
     

int main(){
#ifdef LOCAL
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
#endif
  scanf("%d %d\n",&n,&d);

  for (int i=0;i<n;i++)
    getline(cin,pins[i]);

  PreCalc();

  if (d==1){
    int64 ans=calc3();
    cout<<ans<<endl;
    return 0;
  }

  if (d==2){
    int64 ans=calc2();
    ans-=3*calc3();
    cout<<ans<<endl;
    return 0;
  }

  if (d==3){
    int64 ans=calc1();
    ans-=2*calc2();
    ans+=3*calc3();
    cout<<ans<<endl;
    return 0;
  }

  if (d==4){
    int64 ans=n*1LL*(n-1)/2;
    ans-=calc1();
    ans+=calc2();
    ans-=calc3();
    cout<<ans<<endl;
    return 0;
  }
  
  return 0;
}