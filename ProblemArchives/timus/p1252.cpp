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

pair<int,int> a[140000];

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i].first),a[i].second = i;

    sort(a,a+n);

    int g = 0;

    for (int i = 0; i < n; i++)
        g = gcd(g, abs(i - a[i].second));

    reverse(a,a+n);

    int g1 = 0;

    for (int i = 0; i < n; i++)
        g1 = gcd(g1, abs(i - a[i].second));

    cout << max((g+n-1)%n,(g1+n-1)%n) << endl;    

    return 0;
}