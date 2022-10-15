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
    #undef assert
    #define assert(x) if (!(x)) throw 1
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int P;
int n,m;

struct item{
    int a,b,c,d;
    item(ll a,ll b,ll c,ll d):a(a%P),b(b%P),c(c%P),d(d%P){
    }
    item(){
        a = b = c = d = 0;
    }
};

item merge(item a,item b){
    return item(a.a+b.a,
                a.b + a.a*1LL*b.a + b.b,
                a.c + a.b*1LL*b.a + a.a*1LL*b.b + b.c,
                a.d + a.c*1LL*b.a + a.b*1LL*b.b + a.a*1LL*b.c + b.d
               );
}

item tree[(1<<18)+100];
int lst = 0;


void upd(int v,int val){
    v = v + lst;
    if (val < 0)
        val += (abs(val)/P+1)*P;
    tree[v].a += val;
    tree[v].a %= P;

    for (v>>=1; v; v>>=1)
        tree[v] = merge(tree[2*v],tree[2*v+1]);         
}

item get(int v,int l,int r,int L,int R){
    if (r < L || R < l)
        return item(0,0,0,0);
    if (L <= l && r <= R)
        return tree[v];
    return merge(get(2*v,l,(l+r)/2,L,R),get(2*v+1,(l+r)/2+1,r,L,R));
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    scanf("%d %d %d",&n,&m,&P);
    lst = 2;
    while (lst < n)
        lst *= 2;
    for (int i = 0; i < n; i++){
        int a;
        scanf("%d",&a);
        upd(i,a);
    }

    for (int i = 0; i < m; i++){
        int a,b,c;
        if (scanf(" I %d %d",&a,&b) == 2){
            upd(a-1,b);
        }            
        else {
            scanf(" C %d %d %d",&a,&b,&c);
            item res = get(1,0,lst-1,a-1,b-1);
            printf("1 %d",res.a);
            if (c >= 2) printf(" %d",res.b);
            if (c >= 3) printf(" %d",res.c);
            if (c >= 4) printf(" %d",res.d);
            printf("\n");
        }
    }
    return 0;
}