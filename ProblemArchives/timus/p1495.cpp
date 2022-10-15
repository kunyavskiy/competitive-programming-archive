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
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int dp[1000100];
int n;

void relax(int a,int b){
    dp[a] |= (dp[b]<<1);
}

int val[50];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    cin >> n;

    if (n <= 2){
        cout << n << endl;
        return 0;
    }
    
    memset(dp,0,sizeof(dp));
    dp[1] = dp[2] = 2;

    for (int it = 0; it < 35; it++){
        for (int i = 0; i < n; i++){
           relax((10*i+1)%n,i);
           relax((10*i+2)%n,i);
        }
    }

    int need = 0;
    int nlen = 0;

    val[0] = 1;
    for (int i = 1; i < 50; i++)
        val[i] = (val[i-1]*10)%n;


    for (;nlen < 31 && !(dp[0] & (1<<nlen)); nlen++);

    if (nlen > 30){
        printf("Impossible\n");
        return 0;
    }


    while (nlen > 1){
        bool q = false;
        for (int i = 0; i < n && !q; i++)
            if ((need == (i+val[nlen-1])%n) && (dp[i] & (1<<(nlen-1)))){
                printf("1");
                need = i;
                --nlen;
                q = true;
            }
        for (int i = 0; i < n && !q; i++)
            if ((need == (i+2*val[nlen-1])%n) && (dp[i] & (1<<(nlen-1)))){
                printf("2");
                need = i;
                --nlen;
                q = true;
            }
       assert(q);
    }

    assert(need == 1 || need == 2);
    printf("%d\n",need);   

    return 0;
}