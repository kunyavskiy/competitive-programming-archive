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

const int MAXN = 210;

struct node{
    int to,c;
    int id;
    int f;
    node *next,*back;
};

node* g[MAXN];
node* g2[MAXN];
bool used[MAXN];
int n,m;

void add(int a,int b,int c,int id){
    node *temp = new node, *temp2 = new node;
    temp->to = b, temp2->to = a;
    temp->c = c, temp2->c = 0;
    temp->id = id, temp2->id = -1;
    temp->f = 0, temp2->f = 0;
    temp->next = g[a], temp2->next = g[b];
    temp->back = temp2, temp2->back = temp;
    g[a] = temp, g[b] = temp2;
}

int ans[MAXN][MAXN];
int d[MAXN];

int dfs(int v,int have,int need){
    if (v == n-1)
        return have;
    ll pushed = 0;
    for (node * &it = g2[v]; it; it = it->next){
        if (it->c < need)
            continue;
        if (d[it->to] != d[v] + 1)
            continue;
        int res = dfs(it->to,min(have,it->c),need);
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

bool bfs(int need){
    memset(d,63,sizeof(d));
    d[0] = 0;
    queue<int> q;
    q.push(0);
    for (; !q.empty(); ){
        int v = q.front();
        q.pop();
        for (node* it = g[v]; it; it = it->next){
            if (it->c >= need && d[it->to] > d[v] + 1){
                d[it->to] = d[v] + 1;
                q.push(it->to);
            }
        }
    }

    if (d[n-1] > n)
        return false;
    memcpy(g2,g,sizeof(g));
    dfs(0,2e9,need);
    return true;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  scanf("%d",&n);

  int n1 = n;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      add(i+1,j+n+1,100,i*n+j);

  for (int i = 0; i < n; i++){
     int x;
     scanf("%d",&x);
     add(0,i+1,x,-1);
  }

  for (int i = 0; i < n; i++){
     int x;
     scanf("%d",&x);
     add(i+n+1,2*n+1,x,-1);
  }

  n = 2*n+2;
                                             
  for (int i = 30; i >= 0; i--){
     while (bfs(1<<i));
  }

  
  for (int i = 0; i < n; i++)
    for (node* it = g[i]; it; it = it->next)
        if (it->id != -1)
            ans[it->id/n1][it->id%n1] = it->f;


  for (node* it = g[0]; it; it = it->next)
     if (it->c){
        printf("NO\n");
        return 0;
     }


  printf("YES\n");
  for (int i = 0; i < n1; i++)
    for (int j = 0; j < n1; j++)
        printf("%d%c",ans[i][j]," \n"[j==n1-1]);


  return 0;
}
