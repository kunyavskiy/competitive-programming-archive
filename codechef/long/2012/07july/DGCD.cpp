// WHAT'S WRONG WITH YOU GUYS??? WTF IS PENTIUM 3??? PLEASE UPGRADE SERVERS! IT'S RIDICULOUS TO TEST SOLUTIONS ON 9-YEAR OLD SYSTEM!"
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

const int MAXN = 51000;
const int MAXLOG = 17;

struct item{
    int mv,gnm,av;

    void add(int x){
        av += x;
        mv += x;
    }

    void merge(const item& a,const item& b){
        if (a.mv < b.mv){
            mv = a.mv;
            gnm = __gcd(a.gnm,__gcd(b.mv - a.mv,b.gnm));
        }
        else {
            mv = b.mv;
            gnm = __gcd(b.gnm,__gcd(a.mv - b.mv,a.gnm));
        }
    }

    item(){
        gnm = av = 0;
        mv = 0;
    }
};

struct SegmTree{
    int* data;
    item* tree;
    int lst,n;

    SegmTree(vector<int>);
    item get(int,int,int,int,int);
    int get(int,int);
    void update(int,int,int,int,int,int);
    void update(int,int,int);
    void push(int);     
};

int size[MAXN];
int _h[MAXN];
int* h = _h+1;
vector<int> g[MAXN];
int p[MAXN];
int val[MAXN];
SegmTree* pos[MAXN];
int up[MAXLOG][MAXN];
int n;

int dfs(int v,int p,int h){
    ::p[v] = p;
    ::h[v] = h;
    size[v] = 1;
    for (int i = 0; i < (int)g[v].size(); i++){
        if (g[v][i] != p)
            size[v] += dfs(g[v][i],v,h+1);
    }
    return size[v];
}

void initlca(){
   for (int i = 0; i < n; i++)
      up[0][i] = p[i];
   up[0][0] = 0; 
   for (int i = 1; i < MAXLOG; i++) 
      for (int j = 0; j < n; j++)
        up[i][j] = up[i-1][up[i-1][j]];
}

int getup(int u,int dh){
    for (int i = 0; (1<<i) <= dh; i++)
        if (dh & (1<<i))
            u = up[i][u];
    return u;
}

int lca(int u,int v){
    if (h[u] > h[v])
        swap(u,v);
    v = getup(v,h[v] - h[u]);
    if (u == v)
        return u;
    for (int i = MAXLOG - 1; i >= 0; i--)
        if (up[i][v] != up[i][u])  
            v = up[i][v], u = up[i][u];
    return p[v];
}

SegmTree* genways(int v,vector<int>& x){
    x.pb(v);
    if (g[v].size() == 1 && (v != 0 || n == 1)){
        return pos[v] = new SegmTree(x);
    }       
    int bid = -1;
    for (int i = 0; i < (int)g[v].size(); i++)
       if (g[v][i] != p[v] && (bid == -1 || size[g[v][i]] > size[g[v][bid]]))
          bid = i;
    for (int i = 0; i < (int)g[v].size(); i++)
        if (g[v][i] != p[v]){
            vector<int> temp;
            genways(g[v][i],((i == bid)?x:temp));
        }       
    return pos[v] = pos[g[v][bid]];
}

int vrequest(int v,int u){
    if (v == u)
        return 0;
    int res = 0;
    while ((u == -1 && u != v) || h[v] > h[u]){
        res = __gcd(res, pos[v]->get(v,u));
        v = p[pos[v]->data[0]];
    }
    return res;
}

int request(int v,int u){
   int l = lca(v,u);
   return __gcd(vrequest(v,l),__gcd(vrequest(u,l),vrequest(l,p[l]))); 
}


void vupdate(int v,int u,int d){
    while (h[v] > h[u]){
        pos[v]->update(v,u,d);
        v = p[pos[v]->data[0]];
    }
}

void update(int v,int u,int d){
   int l = lca(v,u);
   vupdate(v,l,d);
   vupdate(u,l,d);
   vupdate(l,p[l],d);
}

SegmTree::SegmTree(vector<int> v){
   n = v.size();
   lst = 1;
   while (lst < n)
      lst *= 2;
   data = new int[n];
   copy(v.begin(),v.end(),data);
   tree = new item[2*lst];

   for (int i = lst; i < lst+n; i++)
      tree[i].mv = val[data[i-lst]], tree[i].gnm = tree[i].av = 0; 
   for (int i = lst+n; i < 2*lst; i++)                                    
      tree[i].mv = tree[i].gnm = tree[i].av = 0; 
   for (int i = lst-1; i > 0; i--)
      tree[i].merge(tree[2*i],tree[2*i+1]);
}

int hcmp(int a,int b){
    return h[a] < h[b];
}

void SegmTree::push(int v){
    tree[2*v].add(tree[v].av);
    tree[2*v+1].add(tree[v].av);
    tree[v].av = 0;
}

item SegmTree::get(int v,int l,int r,int L,int R){
    if (r < L ||  R < l || R < L)
        return item();
    if (L <= l && r <= R)
        return tree[v];
    push(v);
    item res;
    res.merge(get(2*v,l,(l+r)/2,L,R),
                 get(2*v+1,(l+r)/2+1,r,L,R));
    return res;
}

int SegmTree::get(int u,int v){
    int r = upper_bound(data,data+n,u,hcmp) - data - 1;
    int l = upper_bound(data,data+n,v,hcmp) - data;
    item res = get(1,0,lst-1,l,r);
    return __gcd(res.mv,res.gnm);
}

void SegmTree::update(int u,int v,int d){
    int r = upper_bound(data,data+n,u,hcmp) - data - 1;
    int l = upper_bound(data,data+n,v,hcmp) - data;
    return update(1,0,lst-1,l,r,d);
}

void SegmTree::update(int v,int l,int r,int L,int R,int d){
    if (r < L ||  R < l || R < L)
        return;
    if (L <= l && r <= R)
        return tree[v].add(d);
    
    push(v);
    update(2*v,l,(l+r)/2,L,R,d);
    update(2*v+1,(l+r)/2+1,r,L,R,d);
    tree[v].merge(tree[2*v],tree[2*v+1]);
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    h[-1] = -1;
    memset(p,-1,sizeof(p));
    scanf("%d",&n);
    for (int i = 0; i < n-1; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        g[a].pb(b);
        g[b].pb(a);
    }
    for (int i = 0; i < n; i++){
        scanf("%d",&val[i]);
    }
    dfs(0,-1,0);
    initlca();
    {
      vector<int> temp;
      genways(0,temp);
    }

    int q;
    scanf("%d",&q);
    for (int i = 0; i < q; i++){
        int u,v,d;
        if (scanf(" F %d %d",&u,&v) == 2){
             printf("%d\n",request(u,v));
        }
        else {
            scanf(" C %d %d %d",&u,&v,&d);
            update(u,v,d);
        }
    }

    return 0;
}