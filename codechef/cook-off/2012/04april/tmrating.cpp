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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;          

struct item{
    int val1,val2;

    void merge(const item& l,const item& r){
        if (l.val1 >= r.val1){
            val1 = l.val1;
            val2 = max(l.val2,r.val1);
        }
        else {
            val1 = r.val1;
            val2 = max(l.val1,r.val2);
        }
    }

    item(){
        val1 = val2 = -1;
    }
};

item merge(const item& l,const item& r){
    item res;
    res.merge(l,r);
    return res;
}


struct node{
    node *l,*r;
    item val;

    void update(){
        val.merge(l->val,r->val);
    }
};

int x[200000];

node* build(int l,int r){
    if (l == r){
        node* res = new node;
        res->l = res->r = 0;
        res->val.val1 = x[l];
        res->val.val2 = -1;
        return res;
    }
    node* res = new node;
    res->l = build(l,(l+r)/2);
    res->r = build((l+r)/2+1,r);
    res->update();
    return res;
}

int n,m,a,b,c,d;

node* ver[110000];

item get(node* v,int l,int r,int L,int R){
    if (r < L || R < l)
        return item();
    if (L <= l && r <= R)
        return v->val;
    return merge(get(v->l,l,(l+r)/2,L,R),get(v->r,(l+r)/2+1,r,L,R));
}

node* update(node* v,int l,int r,int L,int val){
    if (L < l || r < L)
        return v;
    if (l == L && L == r){
        node* res = new node;
        res->l = res->r = 0;
        res->val.val1 = val;
        res->val.val2 = -1;
        return res;
    }
    node* res = new node;
    res->l = update(v->l,l,(l+r)/2,L,val);
    res->r = update(v->r,(l+r)/2+1,r,L,val);
    res->update();
    return res;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    scanf("%d %d %d %d %d %d",&n,&m,&a,&b,&c,&d);

    for (int i = 0; i < n; i++)
        scanf("%d",&x[i]);

    int lst = 2;
    while (lst < n)
        lst *= 2;

    for (int i = n; i < lst; i++)
        x[i] = 0;

    ver[0] = build(0,lst-1);


    int q;
    scanf("%d",&q);

    int r1 = 0;

    for (int i = 0;  i< q; i++){
        int temp = (a*1LL*r1+d)%(i+1);
        int L,R;
        scanf("%d %d",&L,&R);
        item res = get(ver[temp],0,lst-1,L,R);
        printf("%d %d\n",res.val1,res.val2);      
        r1 = res.val1;
        ver[i+1] = update(ver[i],0,lst-1,(b*1LL*res.val1+d)%n,(c*1LL*res.val2+d)%m);
    }




    return 0;
}

