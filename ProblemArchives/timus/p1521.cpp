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


const int MAXN = 110000;

int tree[4*MAXN];
int lst;
int n,k;

void build(int n){
    lst = 2;
    while (lst < n)
        lst *= 2;
    for (int i = lst; i < lst+n; i++)
        tree[i] = 1;
    for (int i = lst - 1; i > 0; i--)
        tree[i] = tree[2*i] + tree[2*i+1];
}

void update(int v){
    v += lst;
    tree[v] = 0;
    for (v /= 2; v; v/=2)
        tree[v] = tree[2*v] + tree[2*v+1];
}

int findnext(int v,int k){
    v += lst;
    while (tree[v] < k){
        if (v & 1)
            k -= tree[v];
        v = (v+1)/2;
    }

    while (v < lst){
        if (tree[2*v] >= k)
            v = 2*v;
        else
            k -= tree[2*v], v = 2*v+1;
    }
    return v - lst;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d",&n,&k);
    build(n);
    
    int pos = 0;

    for (int i = 0; i < n; i++){
        pos = findnext(pos,(k-1)%tree[1]+1);
        update(pos);
        printf("%d ",pos+1);
    }

    return 0;
}