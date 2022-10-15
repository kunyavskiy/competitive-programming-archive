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


struct node{
   int sum;
   node *l,*r;
   int lf,rg;

   void makesons(){
      l = new node();
      r = new node();
      int m = (lf+rg)/2;
      l->lf = lf;l->rg = m;
      r->lf = m;r->rg = rg;
      l->l = l->r = r->l = r->r = 0;
      l->sum = m - lf;
      r->sum = rg - m;
   }
};


node* root;

void setzero(node* v,int x){
    if (x < v->lf || x >= v->rg)
        return;
    if (v->rg - v->lf == 1){
        v->sum = 0;
        return;
    }
    if (!v->l) v->makesons();
    setzero(v->l,x);
    setzero(v->r,x);
    v->sum--;
}

int get(int x){
    node* v = root;

    while (v->rg - v->lf > 1){
        if (!v->l) return v->lf + x;
        if (x < v->l->sum)
            v = v->l;
        else
            x -= v->l->sum, v = v->r;
    }                                
    return v->lf;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int m;
    scanf("%*d %d",&m);

    root = new node();
    root->l = root->r = 0;
    root->lf = 0;
    root->rg = 1000000100;
    root->sum = root->rg - root->lf;

    for (int i = 0; i < m; i++){
       char c; int x;
       scanf(" %c %d",&c,&x);
       x = get(x);
       
       if (c == 'L')
          printf("%d\n",x);
       else {
          setzero(root,x);
       }            
    }

    return 0;
}