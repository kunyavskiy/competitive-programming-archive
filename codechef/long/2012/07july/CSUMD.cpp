// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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

const int MOD = 1000000007;

int a[2][2];
int b[2][2];
int temp[2][2];

void mul(int a[][2], int b[][2],int c[][2]){
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++){
            c[i][j] = 0;
            for (int k = 0; k < 2; k++)
                c[i][j] = (c[i][j] + a[i][k] * 1LL * b[k][j])%MOD;
        }
}

void solve(){
    int n;
    scanf("%d",&n);
    if (n == 1){
        printf("1\n");
        return;
    }
    if (n == 2){
        printf("3\n");
        return;
    }
    n -= 2;
    a[0][0] = a[1][1] = 1;
    a[0][1] = a[1][0] = 0;
    b[0][1] = b[0][0] = 2;
    b[1][0] = 1, b[1][1] = 0;


    for (int i = 0; i < 30; i++){
        if (n & (1<<i)){
            mul(a,b,temp);
            memcpy(a,temp,sizeof(a));
        }
        mul(b,b,temp);
        memcpy(b,temp,sizeof(b));
    }
    //cerr << a[0][0] <<" "<<a[0][1] <<endl <<a[1][0] <<" "<<a[1][1] <<endl;
    printf("%d\n",(int)((3LL*a[0][0] + a[0][1])%MOD));
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  int t;
  scanf("%d",&t);
  while (t-->0)
    solve();

  return 0;
}