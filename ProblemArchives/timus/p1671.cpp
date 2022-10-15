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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 110000;

int a[MAXN];
int b[MAXN];
bool used[MAXN];
int num[MAXN];
int ans[MAXN];

int p[MAXN];

int get(int a){
    if (p[a] == a)
        return a;
    return p[a] = get(p[a]);
}

bool join(int a,int b){
    if (get(a) == get(b))
        return false;
    p[get(a)] = get(b);
    return true;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    int n,m;
    scanf("%d %d",&n,&m);
    for (int i = 0; i < m; i++){
        scanf("%d %d",&a[i],&b[i]);
        --a[i],--b[i];
    }

    int q;
    scanf("%d",&q);
    for (int i = 0; i < q; i++){
        scanf("%d",&num[i]);
        --num[i];
        used[num[i]] = true;
    }

    for (int i = 0; i < n; i++)
        p[i] = i;

    int res = n;

    for (int i = 0; i < m; i++){
        if (!used[i])
            res -= join(a[i],b[i]);
    }

    for (int i = q-1; i >= 0; i--){
        ans[i] = res;
        res -= join(a[num[i]],b[num[i]]);
    }

    for (int i = 0; i < q; i++)
        printf("%d ",ans[i]);


    return 0;
}