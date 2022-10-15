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

const int MAXN = 210000;

vector<int> te[MAXN];

int dp[MAXN];
char s[MAXN];
int sum[MAXN];
int N,M;

multiset<int> cur;

void add(int right,int val){
    te[right].pb(val);
    cur.insert(val);
}

int get(int l,int r){
    return sum[r] - sum[l];
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    gets(s);
    sscanf(s,"%d %d",&N,&M);
    gets(s);
    int len = strlen(s);
    for (int i = 0; i <= M+len; i++){
        sum[i+1] = sum[i] + (!isalpha(s[i]) && s[i] != ' ' && s[i]);
    }


    add(1,0);

    int tpos = 0;

    for (int i = 0; i <= len; i++){             
        for (int j = 0; j < (int)te[i].size(); j++)
            cur.erase(cur.find(te[i][j]));

        dp[i] = *cur.begin();

        //cerr << string(s,s+i) <<" "<<dp[i] << endl;

        while (tpos <= i+M && (tpos <= i+N || get(i,tpos) == 0))
            tpos++;

        add(tpos,dp[i]+1);
    }

    cout << dp[len] << endl;      

    return 0;
}