#ifndef LOCAL
   #pragma comment(linker, "/STACK:67108864")
#endif

#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <functional>
#include <iterator>
#include <time.h>
#include <assert.h>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <utility>

#define MPI 3.141592653589793238462643
#define eps 1e-8
#define inf ((int)1e9)
#define pb push_back
#define mp make_pair
#define zero(a) memset(a,0,sizeof(a))
#define sqr(x) ((x)*(x))

#if defined(__WIN32__) && defined(__GNUC__)
   #define LLD "%I64d"
#else
   #define LLD "%lld"
#endif

#ifndef __GNUC__
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
typedef double ld;

#ifdef LOCAL
    ld START = clock();
    #define TIME (clock()-START)/CLOCKS_PER_SEC
    #define PRINT_TIME cerr << "Time: "<< TIME <<"s"<< endl;
#else
  #define PRINT_TIME (void)0
#endif


struct node{
    ll dp[2];
    node* next[26];
    int cnt;
    node(void*){
        for (int i = 0; i < 26; i++)
            next[i] = this;
        dp[0] = dp[1] = 0;
        cnt = 0;    
    }
    node();
};

node* null = new node(NULL);

node::node(){
    for (int i = 0; i < 26; i++)
        next[i] = null;
    dp[0] = dp[1] = -1;
    cnt = 0;
} 


char s[110000];

node* root = new node();

void add(){
      node* t = root;
      for (int i = 0; s[i]; i++){
      t->cnt++;                 
        if (t->next[(int)(s[i]-'a')] == null)
            t->next[(int)(s[i]-'a')] = new node();
        t = t->next[(int)(s[i]-'a')];     
      }
      t->cnt++;
}

void dfs(node* v){
    if (v == null)
        return;

    ll sum = 0;
    int cnt = 0;
  for (int i = 0; i < 26; i++){
        dfs(v->next[i]);
        sum += v->next[i]->dp[1];
        cnt += v->next[i]->cnt;
    }

    v->dp[0] = v->dp[1] = 1LL<<60;

    for (int i = 0; i < 26; i++) {
          v->dp[0] = min(v->dp[0], (sum - v->next[i]->dp[1] + v->next[i]->dp[0] + cnt - v->next[i]->cnt));
          v->dp[1] = min(v->dp[1], (sum - v->next[i]->dp[1] + v->next[i]->dp[0] + cnt));
    }

    //cerr << v <<" "<<v->dp[0] << " "<<v->dp[1] << endl;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
  #endif

  gets(s);
  int n;
  sscanf(s,"%d",&n);

  for (int i = 0; i < n; i++){
     gets(s);
     add();
  }

  dfs(root);

  cout << root->dp[1] << endl;

  PRINT_TIME;
  return 0;
}
