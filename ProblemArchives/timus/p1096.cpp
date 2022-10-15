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

int a[1100];
int b[1100];

int d[1100];
int p[1100];
int n;


void print(int v){
    //cerr <<"!!!"<<v<<endl;
    if (v == n-1)
        return;
    print(p[v]);
    printf("%d\n",v+1);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d",&n);

    for (int i = 0; i < n; i++){
        scanf("%d %d",&a[i],&b[i]);
    }
    int need;
    scanf("%d %d %d",&need,&a[n],&b[n]);
    n++;

    queue<int> q;
    memset(d,63,sizeof(d));
    d[n-1] = 0;
    q.push(n-1);

    while (!q.empty()){
        int v = q.front(); q.pop();
        if (a[v] == need || b[v] == need){
            printf("%d\n",d[v]);
            print(v);
            return 0;
        }
        for (int i = 0; i < n; i++)
            if (d[i] > d[v] + 1 && (a[i] == a[v] || a[i] == b[v])){
                d[i] = d[v] + 1;
                p[i] = v;
                q.push(i);
            }
    }

    printf("IMPOSSIBLE\n");

    return 0;
}