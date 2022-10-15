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
                  
int a[1100][1100];
int64 na[1100][1100];
int por[1100];
int64 cur[1100];
int n,k;

bool cmp(int a,int b){
    for (int i=k-1;i>=0;i--)
        if (na[a][i]!=na[b][i])
            return na[a][i]>na[b][i];
    return false;
}

void add(int num){
    for (int i=0;i<k;i++)
        cur[i]+=na[num][i];
    for (int i=0;i<k-1;i++){
        cur[i+1]+=(cur[i]>>3);
        cur[i]&=7;
    }
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&n,&k);
    for (int i=0;i<n;i++)
        for (int j=0;j<k;j++)
            scanf("%d",&a[i][j]);
    for (int i=0;i<n;i++){
        for (int j=0;j<k-1;j++){
            na[i][j]+=a[i][j];
            na[i][j+1]+=(na[i][j]>>3);
            na[i][j]&=7;
        }                          
        na[i][k-1]+=a[i][k-1];
    }

    for (int i=0;i<n;i++)
        por[i]=i;
    sort(por,por+n,cmp);

    int ans=-1;
    for (int i=0;i<n;i++){
        add(por[i]);
        if (cur[k-1]>=8){
            ans=i+1;
            break;
        }
    }   
    if (ans==-1){
        printf("NO SOLUTION\n");
        return 0;
    }                        

    for (int i=ans;i<n;i++)
        memset(a[por[i]],0,sizeof(a[por[i]]));

    cur[k-1]-=8;
    for (int j=k-1;j>=0;j--){
        for (int i=0;i<ans && cur[j];i++){
            int tmp=min(a[por[i]][j]*1LL,cur[j]);
            cur[j]-=tmp;
            a[por[i]][j]-=tmp;
        }
        if (j) cur[j-1]+=cur[j]*8;            
    }                             
    int kol=0;
    for (int i=0;i<n;i++)
        for (int j=0;j<k;j++)
            if (a[i][j])
                kol++;
    printf("%d\n",kol);
    for (int i=0;i<n;i++)
        for (int j=0;j<k;j++)
            if (a[i][j])
                printf("%d %d %d\n",i+1,j,a[i][j]);   
    return 0;
}