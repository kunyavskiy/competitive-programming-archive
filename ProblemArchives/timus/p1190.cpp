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


int bval[5100];
int val[5100];

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        string s;
        cin >> s;
        int x;
        cin >> x;
        if (x) cin >> val[i] ;else val[i] = -1;
    }

    memcpy(bval,val,sizeof(bval));
    
    val[n-1] = max(val[n-1],1);

    int sum = 0;

    for (int i = n-2; i >= 0; i--)
        if (val[i] != -1 && val[i] < val[i+1]){
            printf("NO\n");
            return 0;
        } 
        else 
           val[i] = max(val[i],val[i+1]);

    for (int i = 0; i < n; i++)
        sum += val[i];


    if (sum > 10000){
        printf("NO\n");
        return 0;
    }

    sum = 0;
    memcpy(val,bval,sizeof(bval));

    if (val[0] == -1)
        val[0] = 10000;
     for (int i = 1; i < n; i++)
        if (val[i] == -1)
            val[i] = val[i-1];

    for (int i = 0; i < n; i++)
        sum += val[i];


    if (sum < 10000){
        printf("NO\n");
        return 0;
    }

    printf("YES\n");


    return 0;
}