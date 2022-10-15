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

typedef long long int64;
typedef long double ld;

int a[300][300];
int nz[300][300];
int n,m;                
vector<pair<int,int> > ans;

const int dx[4]={0,-1,0,1};
const int dy[4]={-1,0,1,0};

bool good(int x,int y){
    return x>=0 && y>=0 && x<n && y<m;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif    
    scanf("%d %d",&n,&m);
    for (int i=0;i<n;i++)
       for (int j=0;j<m;j++)
        scanf("%d",&a[i][j]);
    int cnt=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++){
            nz[i][j]=4;
            if (a[i][j]) cnt++;
            for (int nap=0;nap<4;++nap)
                if (!good(i+dx[nap],j+dy[nap]) || a[i+dx[nap]][j+dy[nap]]==0)
                    nz[i][j]--;
        }
    int ptr=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<m;j++)
            if (nz[i][j]+1==a[i][j])
                ans.pb(mp(i,j));
    for (;ptr!=ans.size();++ptr){
        int x=ans[ptr].first;
        int y=ans[ptr].second;
        if (nz[x][y]+1<a[x][y]){
            printf("No solution\n");
            return 0;
        }
        nz[x][y]=-1000;
        for (int i=0;i<4;i++)
            if (good(x+dx[i],y+dy[i])){
                nz[x+dx[i]][y+dy[i]]-=1;
                if (nz[x+dx[i]][y+dy[i]]+1==a[x+dx[i]][y+dy[i]])
                    ans.pb(mp(x+dx[i],y+dy[i]));
            }                                               
    }
    if (ans.size()!=cnt){
       printf("No solution\n");
       return 0;
    }
   // printf("%d\n",(int)ans.size());
    for (int i=0;i<ans.size();i++)
        printf("%d %d\n",ans[i].first+1,ans[i].second+1);
    return 0;
}