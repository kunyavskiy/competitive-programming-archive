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
typedef unsigned long long ull;
typedef long double ld;

#ifdef LOCAL
    ld START = clock();
    ld START1 = clock();
#endif


const int inf = ((int)2e9+10);

const int M1 = 21;
const int M2 = 19;

int resm=inf, resM, n, m1, m2, k, s;
map<int,int> S;
pair <int, int> B[(1<<M2)+500], C[(1<<M2)+500];
int e, e2, t, bb, cc;
int D[(1<<M1)+500],L[50];

inline int min(int a,int b){
    return (a<b?a:b);
}

inline int max(int a,int b){
    return (a>b?a:b);
}



int main (void){
#ifdef LOCAL
  freopen ("input.txt", "r", stdin);
  freopen ("output.txt", "w", stdout);
#endif
  scanf("%d%d%d", &n, &s, &k);
  int m1 = k/2, m2 = k - m1; 
  if (m2) --m2,++m1;

  for (int i = 0; i < k; i++)
    scanf("%d", &L[i]);
  for (int i=0; i < (1<<m2); i++)
  {
    int mn=0, mx=0, c=0;
    
    for (int j=0; j<m2; j++)
    {
      c += L[j+m1] * (2*(!!(i&(1<<j)))-1);
      mn=min(mn,c), mx=max(mx,c);
      if (mn<-n || mx>n)
        break;
    }
    
    mn=-mn;
    if (mn >= -n && mx <= n && mn+mx<=n)
    {
      B[e]=mp(mn,c), C[e]=mp(n-mx,c); 
      e++;
    }
  }

  
#ifdef LOCAL
  cerr << "INITBS: "<<(clock()-START1)/CLOCKS_PER_SEC << endl;
  START1 = clock();
#endif


  stable_sort(B,B+e);
  stable_sort(C,C+e);


#ifdef LOCAL
  cerr << "INIT1: "<<(clock()-START1)/CLOCKS_PER_SEC << endl;
  START1 = clock();
#endif


  B[e]=mp(inf,0), C[e]=mp(inf,0);
  for (int i=0; i < (1<<m1); i++)
  {
    int c = s;
    for (int j = 0; j < m1; j++)
    {
      if (i&(1<<j))
        c += L[j];
      else
        c -= L[j];
      if (c < 0 || c > n)
        break;
    }
    if (c >= 0 && c <= n)
      D[e2] = c, e2++;
  }

  sort(D, D+e2);


#ifdef LOCAL
  cerr << "INIT: "<<(clock()-START1)/CLOCKS_PER_SEC << endl;
  START1 = clock();
#endif

  pair<int,int> *_B = B, *_C = C;


  for (int i = 0; i < e2; i++){
    t = D[i];
    while (_B->first <= t){
      S[_B->second]++;
      _B++;
    }
    while (_C->first < t){
      int& temp = S[_C->second];
      --temp;
      if (temp <= 0)
        S.erase(_C->second);
      _C++;
    }
    if (S.size()>0)
      resm=min(resm,t + S.begin()->first), resM = max(resM,t+ (--S.end())->first);
  }

  printf("%d %d\n", resm, resM);
#ifdef LOCAL
  cerr << "SOLVE: "<<(clock()-START1)/CLOCKS_PER_SEC << endl;
  cerr << (clock()-START)/CLOCKS_PER_SEC << endl;
#endif
  return 0;
}

