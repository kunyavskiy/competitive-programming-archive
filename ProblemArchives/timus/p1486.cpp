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
#endif

using namespace std;

typedef unsigned long long ll;
typedef long double ld;

const int P1 = 239017;
const int P2 = 23917;


ll hash[510][510];
char c[510][510];

ll stp1[510],stp2[510];

int n,m;


ll get(int a,int b,int c,int d){
    ll v = hash[c][d];
    if (a) v -= hash[a-1][d];
    if (b) v -= hash[c][b-1];
    if (a && b) v += hash[a-1][b-1];
    v *= stp1[509-d];
    v *= stp2[509-c];
//    cerr << a <<" "<<b<<" "<<c<<" "<<d<<" -> "<<v<<endl;
    return v;     
}

ll v[510*510];
int ptr;


bool check(int k,pair<int,int>& p1,pair<int,int>& p2){
    if (k == 0)
        return true;

    ptr = 0;

    for (int i = 0; i+k <= n; i++)
        for (int j = 0; j+k <= m; j++){
            ll val = get(i,j,i+k-1,j+k-1);
            v[ptr++] = val;
        }
    sort(v,v+ptr);
    bool ok = false;
    ll nv = 0;

    for (int i = 1; i < ptr; i++)
        if (v[i] == v[i-1]){
            ok = true;
            nv = v[i];
        }

    if (!ok)
        return false;


    bool q = false;

    for (int i = 0; i+k <= n; i++)
        for (int j = 0; j+k <= m; j++){
            ll val = get(i,j,i+k-1,j+k-1);
            if (val == nv){
                if (!q){
                    p1 = mp(i,j);
                    q = true;
                }
                else {
                    p2 = mp(i,j);
                    return true;
                }
            }
        }
    assert(false);
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

   stp1[0] = stp2[0] = 1;
   for (int i = 1; i < 510; i++){
       stp1[i] = stp1[i-1]*P1;
       stp2[i] = stp2[i-1]*P2;
   }

   scanf("%d %d",&n,&m);
   for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        scanf(" %c",&c[i][j]);

   for (int i = 0; i < n; i++){
      hash[i][0] = c[i][0];
      for (int j = 1; j < m; j++)
          hash[i][j] = hash[i][j-1] + c[i][j] * stp1[j];
   }

   for (int i = 1; i < n; i++)
     for (int j = 0; j < m; j++)
        hash[i][j] = hash[i-1][j] + hash[i][j] * stp2[i];
    
   int l = 0;
   int r = min(n,m)+1;

   pair<int,int> a,b;

   while (r-l > 1){
      int mid = (l+r)/2;
      if (check(mid,a,b))
        l = mid;
      else
        r = mid;
   }  

   check(l,a,b);

   printf("%d\n",l);
   if (l)
    printf("%d %d\n%d %d\n",a.first+1,a.second+1,b.first+1,b.second+1);
    
   return 0;
}