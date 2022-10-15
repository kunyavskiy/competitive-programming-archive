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

typedef long long ll;
typedef long double ld;


int a[2][2];
int b[2][2];
int temp[2][2];
int res[2][2];

int mod,n;

void mul(int a[][2],int b[][2], int temp[][2]){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            temp[i][j] = 0;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                temp[i][j] = (temp[i][j] + a[i][k] *1LL* b[k][j])%mod;
}

void solve(){
    scanf("%d %d",&n,&mod);
    --n;
    a[0][0] = a[0][1] = a[1][0] = 1;a[1][1] = 2;
    memcpy(b,a,sizeof(b));
    res[0][0] = res[1][1] = 1;
    res[1][0] = res[0][1] = 0;
    

    for (int i = 0; (1<<i) <= n; i++){
        if (n & (1<<i)){
            mul(res,b,temp);
            memcpy(res,temp,sizeof(res));
        }
        mul(b,b,temp);
        memcpy(b,temp,sizeof(b));
    }


    printf(LLD"/"LLD"\n",(res[0][0] + 1LL*res[0][1])%mod, (res[1][0] + 1LL*res[1][1])%mod);  
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);

  for (int i = 0; i < t; i++)
    solve();

  return 0;
}

