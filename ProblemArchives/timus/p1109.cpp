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

const int MAXN = 2110;
const int MAXM = 110000;

struct node{
    int to,c;
    int f;
    node *next,*back;
};

node* g[MAXN];
node* g2[MAXN];
bool used[MAXN];
int n,m,p;

void add(int a,int b,int c = 1){
    node *temp = new node, *temp2 = new node;
    temp->to = b, temp2->to = a;
    temp->c = c, temp2->c = 0;
    temp->f = 0, temp2->f = 0;
    temp->next = g[a], temp2->next = g[b];
    temp->back = temp2, temp2->back = temp;
    g[a] = temp, g[b] = temp2;
}

int d[MAXN];

int dfs(int v,int have){
    if (v == n-1)
        return have;
    ll pushed = 0;
    for (node * &it = g2[v]; it; it = it->next){
        if (!it->c)
            continue;
        if (d[it->to] != d[v] + 1)
            continue;
        int res = dfs(it->to,min(have,it->c));
        if (res){
            it->c -= res, it->f += res;
            it->back->c += res, it->back->f -= res;
            if (v)
                have -= res;
            pushed += res;
        }
        if (!have)
            return pushed;
    }
    return pushed;
}

ll ans = 0;

int bfs(){
    memset(d,63,sizeof(d));
    d[0] = 0;
    queue<int> q;
    q.push(0);
    for (; !q.empty(); ){
        int v = q.front();
        q.pop();
        for (node* it = g[v]; it; it = it->next){
            if (it->c && d[it->to] > d[v] + 1){
                d[it->to] = d[v] + 1;
                q.push(it->to);
            }
        }
    }

    if (d[n-1] > n)
        return false;
    memcpy(g2,g,sizeof(g));
    ans -= dfs(0,2e9);
    return true;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int n,m;
    scanf("%d %d",&n,&m);
    ::n = n+m+2;

    for (int i = 1; i <= n; i++)
        add(0,i);
    for (int i = n+1; i <= n+m; i++)
        add(i, ::n-1);

    int k;
    scanf("%d",&k);
    for (int i = 0; i < k; i++){
        int a,b;
        scanf("%d %d",&a,&b);
        add(a,b+n);
    }

    ans = n+m;

    while (bfs());

    cout << ans << endl;


    return 0;
}