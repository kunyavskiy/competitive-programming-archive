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

const int MAXN = 110000;

const int inf = (int)1e9;

struct node{
    static node* null;
    node *l,*r,*p;
    int size,par,y;
    bool inv;
    int minv;
    ll mincnt;
    int add;
    int val;
    int sval;

    node(int _sval){
        l = r = p = node::null;
        size = 1;
        par = -1;
        y = (rand()<<16)|rand();
        inv = false;
        minv = 0;
        mincnt = 1;
        val = 0;
        sval = _sval;
        add = 0;
    }
    node(){
        l = r = p = this;
        par = -2;
        size = y = 0;
        inv = 0;
        minv = inf;
        mincnt = 0;
        val = inf;
        sval = 0;
        add = 0;
    }
};

node* node::null = new node();

void add(node* v,int d){
    if (v == node::null)
        return;
    v->add += d;
    v->minv += d;
}

void push(node* v){
    if (v->inv){
        v->inv = false;
        v->l->inv ^= 1;
        v->r->inv ^= 1;
        swap(v->l,v->r);
    }
    add(v->l,v->add);
    add(v->r,v->add);
    v->val += v->add;
    v->add = 0;
}

void update(node* v){
    push(v);
    v->size = v->l->size + v->r->size + 1;
    v->l->p = v;
    v->r->p = v;
    v->minv = min(v->l->minv,v->r->minv);
    v->minv = min(v->minv,v->val);
    v->mincnt = 0;
    if (v->l->minv == v->minv)
        v->mincnt += v->l->mincnt;
    if (v->r->minv == v->minv)
        v->mincnt += v->r->mincnt;
    if (v->val == v->minv)
        v->mincnt += v->sval;
}

node* merge(node* l,node* r){
    if (l == node::null) return r;
    if (r == node::null) return l;
    l->p = r->p = node::null;
    push(l),push(r);
    if (l->y < r->y){
        l->r = merge(l->r,r);
        update(l);
        return l;
    }
    r->l = merge(l,r->l);
    update(r);
    return r;
}

void split(node* v,int k,node* &l,node* &r){
    if (v == node::null){
        assert(!k);
        l = r = node::null;
        return;
    }
    assert(k <= v->size);
    v->p = node::null;
    push(v);
    if (v->l->size >= k){
        r = v;
        split(r->l,k,l,r->l);
        update(r);
        return;
    }
    k -= v->l->size+1;  
    l = v;
    split(l->r,k,l->r,r);
    update(l);
}


void pushall(node* v){
    if (v == node::null)
        return;
    pushall(v->p);
    push(v);
}

int getnum(node* v){
    pushall(v);
    int ans = v->l->size;
    for (; v->p != node::null; v = v->p){   
        if (v->p->r == v)
            ans += v->p->l->size+1;
    }
    return ans;
}

node* getroot(node* v){
    for (;v->p != node::null; v = v->p);
    return v;        
}

node* v2n[MAXN];
int n;

void splitbefore(int v){
    int id = getnum(v2n[v]);
    node *vroot = getroot(v2n[v]);
    node *vL,*vR;
    int pid = vroot->par;
    split(vroot,id+1,vL,vR);
    vL->par = pid;
    vR->par = v;
}

void expose(int v){
    splitbefore(v);
    while (true){
        node* rv = getroot(v2n[v]);
        if (rv->par == -1)
            break;
        splitbefore(rv->par);
        node* nr = getroot(v2n[rv->par]);
        int pid = nr->par;
        nr = merge(nr,rv);
        nr->par = pid;
    }
}

void mkroot(int v){
    expose(v);
    node* temp = getroot(v2n[v]);
    temp->inv ^= 1;
}             

void link(int u,int v){
    mkroot(u);
    mkroot(v);
    getroot(v2n[v])->par = u;
}

vector<int> v[4*MAXN];

void add(int v,int l,int r,int L,int R,int val){
    if (r < L || R < l)
        return;
    if (L <= l && r <= R){
        ::v[v].pb(val);
        return;
    }
    add(2*v,l,(l+r)/2,L,R,val);
    add(2*v+1,(l+r)/2+1,r,L,R,val);
}

int last[MAXN];
bool req[MAXN];
int lst;

int sum0,sumall;


void solve(int v){
    if (v > lst){
        if (req[i])
            printf(LLD"\n",ans - sum0 - sumall);
        return;
    }
    int temp = sumall;
    for (int i = 0; i < (int)::v[v].size(); i++){
        int tmp = ::v[v][i];
        expose(tmp);
        sum0 -= 
    }
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);               
  #endif
    scanf("%d",&n);

    for (int i = 0; i < n; i++)
        v2n[i] = new node(0);

    ll sum = 0;
    ll sum0,sumall;
    sum0 = sumall = 0;

    for (int i = 0; i < n-1; i++){
        int u,v,c;
        scanf("%d %d %d",&u,&v,&c);
        sum += c;
        sum0 += c;
        sumall += c;
        v2n[n+i] = new node(c);
        --u,--v;
        link(u,n+i);
        link(n+i,v);
    }

    
    int cnt = 0;


    int q;
    scanf("%d",&q);

    lst = 2;
    while (lst < q)
        lst *= 2;


    for (int i = 0; i < q; i++){
        scanf(" %c",&c);

        if (c == '+'){
            scanf("%d",&v);
            last[v] = i;
            continue;
        }

        if (c == '-'){
            scanf("%d",&v);
            add(1,0,lst-1,last[v],i,v);
            continue;
        }

        req[i] = true;
    }

    solve(1);

  return 0;
}
