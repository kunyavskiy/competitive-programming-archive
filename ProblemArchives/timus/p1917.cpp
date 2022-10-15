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

int cnt[1000100];


int n,p;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&n,&p);

    for (int i = 0; i < n; i++){
        int t;
        scanf("%d",&t);
        cnt[t]++;
    }

    int a,b;
    a = b = 0;

    int ccnt = 0;

    for (int i = 0; i <= 1000000; i++){
        if (i*(ccnt+cnt[i]) > p){
            a += ccnt;
            b += !!ccnt;
            ccnt = 0;              
        }
        if (i*cnt[i] > p)
           break;
        ccnt += cnt[i];
    }

    a += ccnt;
    b += !!ccnt;

    cout << a <<" "<<b << endl;

    return 0;
}