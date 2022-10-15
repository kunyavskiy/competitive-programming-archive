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


ll a[10];


void dec(int n){
    while (n)
        a[n%10]--, n/=10;
}

void solve(int n){
    if (n == 0)
        return;
                        
    solve(n/10);

    for (int i = 0; i < 10; i++)
        a[i] *= 10;

    for (int i = 0; i < 10; i++)
        a[i] += ((n/10));

    for (int i = 1; i <= 9; i++)
        a[i]++;
                 
    for (n++;n%10; n++)
        dec(n);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    cin >> n;
    solve(n);

    for (int i = 0; i < 10; i++){
        cout << a[i] << endl;
    }

    return 0;
}