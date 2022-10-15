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


char s[310000];
int n;
vector<int> d;
int can[256],cptr;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);

    for (int i = 1; i < n; i++)
        if (n % i == 0)
            d.pb(i);

    for (int i = 0; i < n; i++){
        s[i] = 'a';     

        ++cptr;
        for (int j = 0; j < (int)d.size(); j++){
            can[(unsigned char)s[(i+d[j])%n]] = cptr;
            can[(unsigned char)s[(i-d[j]+n)%n]] = cptr;
        }

        while (can[(unsigned char)s[i]] == cptr)
            s[i]++;
        assert(s[i] <= 'z');
    }

    puts(s);
    return 0;
}