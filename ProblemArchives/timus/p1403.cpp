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



#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

struct item{
    int t,v,num;

    bool operator<(const item& b) const{
        return t < b.t;
    }
};

item a[1100];
int n;

int dp[1100][1100];


void print(int i,int j){
    if (j == 0)
        return;
    if (a[i].t >= j && (i?dp[i-1][j-1]:0)+a[i].v == dp[i][j]){
        print(i-1,j-1);
        printf("%d ",a[i].num);
        return;
    }

    print(i-1,j);        
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);

    for (int i = 0; i < n; i++)
        scanf("%d %d",&a[i].t,&a[i].v), a[i].num = i+1;
    sort(a,a+n);

    for (int i = 0; i < n; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (max((i?dp[i-1][j]:0),((i?dp[i-1][j-1]:0)+a[i].v)*(a[i].t >= j)));
        

    int maxv = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= n; j++)
            maxv = max(maxv,dp[i][j]);

    for (int i = 0;i < n; i++)
        for (int j = 0; j <= n; j++)
            if (maxv == dp[i][j]){
                printf("%d\n",j);
                print(i,j);
                return 0;
            }
        

            


    return 0;
}