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

const int _b[6][6] = 
{
{1,1,1,0,0,0},
{1,0,0,0,0,0},
{0,1,0,0,0,0},
{0,0,1,1,1,2},
{0,0,0,1,0,0},
{0,0,0,0,1,0}
};        


int a[6][6];
int b[6][6];
int temp[6][6];
int bst[63][6][6];


void multiply(int a[][6],int b[][6],int c[][6]){
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            c[i][j] = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++){
            ll cij = 0;
            for (int k = 0; k < 6; k++)
               cij += a[i][k] *1LL* b[k][j];
            c[i][j] = cij % MOD;
        }
}

void solve(){
    ll n;
    cin >> n;

    memcpy(b,_b,sizeof(b));

    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            a[i][j] = (i==j);

    for (int i = 0; (1LL<<i) <= n; i++){
        if (n & (1LL<<i)){
            multiply(a,bst[i],temp);
            memcpy(a,temp,sizeof(a));
        }
    }                

    cout << ((ll)a[3][0] + (ll)a[4][0] + (ll)a[5][0])%MOD << endl;
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