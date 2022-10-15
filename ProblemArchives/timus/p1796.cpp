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

const int cost[6]={10,50,100,500,1000,5000};
int kol[6];
int one;
vector<int> ans;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    for (int i=0;i<6;i++)
        scanf("%d",&kol[i]);
    scanf("%d",&one);
    int minv,maxv;
    minv=maxv=0;
    bool q=false;
    for (int i=0;i<6;i++){
        maxv+=kol[i]*cost[i];
        if (!q && kol[i]>0){
            minv+=(kol[i]-1)*cost[i];
            q=true;
        }
        else
            minv+=kol[i]*cost[i];
    }
//    cerr<<minv<<" "<<maxv<<endl;
    minv++;
    for (int i=minv;i<=maxv;i++)
        if (i%one==0)
            ans.pb(i/one);
    cout<<ans.size()<<endl;
    for (int i=0;i<ans.size();i++)
        printf("%d ",ans[i]);
    printf("\n");
    return 0;
}