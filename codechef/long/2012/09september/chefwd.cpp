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

const int N = 4;

const int _b[N][N] = 
{
{1,1,0,0},
{1,0,0,0},
{2,1,1,1},
{0,0,1,0},
};        

                
int a[N][N];
int b[N][N];
int temp[N][N];
int bst[63][N][N];


void multiply(int a[][N],int b[][N],int c[][N]){
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            c[i][j] = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            ll cij = 0;
            for (int k = 0; k < N; k++)
               cij = (cij + a[i][k] *1LL* b[k][j]);
            c[i][j] = cij % MOD;
        }
}

void solve(){
    ll n;
    cin >> n;

    if (n == 1){
        assert(0);
        printf("0\n");
        return;
    }
    if (n == 2){
        printf("5\n");
        return;
    }

    n -= 3;

    memcpy(b,_b,sizeof(b));

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            a[i][j] = (i==j);

    for (int i = 0; (1LL<<i) <= n; i++){
        if (n & (1LL<<i)){
            multiply(a,bst[i],temp);
            memcpy(a,temp,sizeof(a));
        }
    }

    ll d1 = (2LL * a[3][0] + 1LL * a[3][1] + 4LL * a[3][2] + 1LL * a[3][3]) % MOD;
    ll d2 = (2LL * a[2][0] + 1LL * a[2][1] + 4LL * a[2][2] + 1LL * a[2][3]) % MOD;
    ll d3 = (2LL * a[0][0] + 1LL * a[0][1] + 4LL * a[0][2] + 1LL * a[0][3]) % MOD;

    //cerr << d1 << " "<<d2 <<" "<<d3 << endl;

    ll d4 = (d1 + d2 + d3)%MOD;
    ll d5 = (d4 + d2)%MOD;
    ll d6 = (d5 + d4)%MOD;

    cout << (d6 % MOD) << endl;

}





int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int t;
    scanf("%d",&t);

    memcpy(b,_b,sizeof(b));

    for (int i = 0; i < 63; i++){
        memcpy(bst[i],b,sizeof(b));
        multiply(b,b,temp);
        memcpy(b,temp,sizeof(b));
    }

    while (t-->0)
        solve();

  return 0;
}