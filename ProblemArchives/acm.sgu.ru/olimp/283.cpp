#include <iostream>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <memory.h>

#define pb push_back
#define mp make_pair

using namespace std;

typedef long long int64;
typedef long double ld;

int t[11][11][11][11][11];

void swap(){
    for (int i=0;i<10;i++)
        memcpy(t[i],t[i+1],sizeof(t[i]));
    memset(t[10],1,sizeof(t[10]));
}

int a[11],b[11];


int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n,m;
  scanf("%d %d",&m,&n);
  for (int i=1;i<=n;i++)
    scanf("%d %d",&a[i],&b[i]);
  int tmp=0;
  memset(t,1,sizeof(t));
  t[0][0][0][0][0]=0;
  for (;tmp!=m;tmp++){
    //cerr<<tmp<<endl;
    for (int i1=n;i1>=0;i1--)
        for (int i2=n;i2>=0;i2--)
            for (int i3=n;i3>=0;i3--)
                for (int i4=n;i4>=0;i4--){
                    for (int j=0;j<=n;j++)
                        if ((j==0 || a[j]>=0) && (b[j]<1 || i1!=j) && (b[j]<2 || i2!=j) && (b[j]<3 || i3!=j) && (b[j]<4 || i4!=j)){
                           t[a[j]][j][i1][i2][i3]=min(t[0][i1][i2][i3][i4]+1,t[a[j]][j][i1][i2][i3]);
//                           cerr<<i1<<" "<<i2<<" "<<i3<<" "<<i4<<" "<<j<<endl;
                        }
//                    cerr<<"!!!"<<t[0][i1][i2][i3][i4]<<endl;
                }
    swap();
  //  cerr<<"!!!!!!!"<<endl;
  }
  //cerr<<"!!!!"<<endl;
  int ans=1<<30;
  for (int j=0;j<=10;j++)
      for (int i1=0;i1<=n;i1++)
         for (int i2=0;i2<=n;i2++)
            for (int i3=0;i3<=n;i3++)
               for (int i4=0;i4<=n;i4++)
                    ans=min(ans,t[j][i1][i2][i3][i4]);
  cout<<ans<<endl;                                                                                 
  return 0;
}
            