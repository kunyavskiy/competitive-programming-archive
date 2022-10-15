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


int v[10][110], vptr[10];

int n,m;
int l[110];
int L[10];
int ord[10];
pair<int,int> _L[10];
bool used[110];

#ifdef LOCAL
ld START = clock();
#endif


void out(){
   for (int i = 0; i < m; i++){
      printf("%d\n",vptr[i]);
      for (int j = 0; j < vptr[i]; j++)
        printf("%d%c",v[i][j]," \n"[j == vptr[i]-1]);
   }
   #ifdef LOCAL
      cerr << (int)((clock()-START)*1000/CLOCKS_PER_SEC) << endl;
   #endif

   exit(0);
}


void go(int m,int n){
    if (n == -1 || L[m] == 0){
       if (L[m])
          return;
       if (!m) out();
       go(m-1,upper_bound(l,l+ ::n,L[m-1])-l-1);
       return; 
    }

    if (used[n] || L[m] < l[n]){
        go(m,n-1);
        return;
    }


    L[m] -= l[n];
    v[ord[m]][vptr[ord[m]]++] = l[n];
    used[n] = 1;
    go(m,n-1);
    vptr[ord[m]]--;
    L[m] += l[n];
    used[n] = 0;

    if (l[n] < L[m])
        go(m,n-1);
} 


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    int sum = 0;

    scanf("%d %d",&n,&m);
    for (int i = 0; i < n; i++){
        scanf("%d",&l[i]);
        sum += l[i];
    }
    for (int i = 0; i < m; i++)
        scanf("%d",&L[i]), sum -= L[i];
                                        
    assert(sum == 0);

    for (int i = 0; i < m; i++)
        _L[i] = mp(L[i],i);
                                                                 
    sort(_L,_L+m);
    reverse(_L,_L+m);

    for (int i = 0; i < m; i++)
        L[i] = _L[i].first, ord[i] = _L[i].second;

    sort(l,l+n);   
                             
    go(m-1,upper_bound(l,l+ ::n,L[m-1])-l-1);
    assert(false);                  
    return 0;
}