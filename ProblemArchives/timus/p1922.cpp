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

pair<int,int> a[1100];
int n;
vector<int> v;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);
    for (int i = 0; i < n; i++)
        scanf("%d",&a[i].first),a[i].second = i+1;

    sort(a,a+n);

    for (int i = 0; i < n; i++)
        if (i+1 >= a[i].first && (i == n-1 || a[i+1].first > i+2)){
           //cerr<<a[i+1].first <<" "<<i+1<<endl;
           v.pb(i+1);
        }

    printf("%d\n",v.size());
    for (int i = 0; i < (int)v.size(); i++){
        printf("%d",v[i]);
        for (int j = 0; j < v[i]; j++)
           printf(" %d",a[j].second);
        printf("\n");
    }

    return 0;
}