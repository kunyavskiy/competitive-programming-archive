#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "e"

const int inf = 1000000000;
const ld eps = 1e-9;

long long D[410][(1<<7)+20];
int A[410], B[410], C[410];
int X[(1<<7)+20], Y[(1<<7)+20];
int T[10];

int main(){
  int n, m, i, j, k;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d%d", &n, &m);
  for (i=0; i<n; i++)
    scanf("%d%d%d", &A[i], &B[i], &C[i]);
  for (i=0; i<m; i++)
    scanf("%d", &T[i]), T[i]--;
  for (i=0; i<(1<<m); i++)
    for (j=0; j<m; j++)
      if (i&(1<<j))
        X[i]=max(X[i],B[T[j]]), Y[i]=max(Y[i],C[T[j]]);
  //for (i=0; i<(1<<m); i++)
  //  cerr<<X[i]<<" "<<Y[i]<<endl;
  D[0][0]=1;
  for (i=0; i<n; i++)
    for (j=0; j<(1<<m); j++)
      if (D[i][j]>0ll)
      {
        //cerr<<i<<" "<<j<<" "<<D[i][j]<<endl;
        for (k=0; k<(1<<m); k++)
          if ((k&j)==0 && X[k]<=A[i] && Y[k]<C[i])
            D[i+1][(k|j)]+=D[i][j];
      }
  cout<<D[n][(1<<m)-1]<<endl; 
  return 0;
}

