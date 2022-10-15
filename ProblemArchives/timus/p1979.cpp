#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <sstream>
//#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME ""

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#ifndef LOCAL
#undef assert
void assert(bool x) {
  if (!x) printf("%d\n", 5 / 0);
}
void assert2(bool x) {
  if (!x) {
    int *tmp = new int[1];
    tmp[int(1e5)] = 100 / 23;
  }
}
#else
#define assert2 assert
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef linux
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

const int inf = 1e9;
const double eps = 1e-9;
const double INF = inf;
const double EPS = eps;

int A[110][110], RA[110][110];
int n;

int main(){     
  int i, j, e=0;
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif
  scanf("%d", &n);
  for (e=1, i=0; i<n; i++)
    for (j=0; j<n; j++)
      A[i][j]=e++;
  for (i=0; i<n; i++, printf("\n"))
    for (j=0; j<n; j++)
      printf("%d ", A[i][j]);
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      RA[i][j]=A[n-1-i][n-1-j];
  for (i=0; i<n; i++, printf("\n"))
  {
    for (j=0; j<n; j++)
      printf("%d ", n*n+A[i][j]);
    for (j=0; j<n; j++)
      printf("%d ", 2*n*n+A[i][j]);
    for (j=0; j<n; j++)
      printf("%d ", 4*n*n+RA[i][n-1-j]);
    for (j=0; j<n; j++)
      printf("%d ", 3*n*n+RA[i][n-1-j]);
  }
  for (i=0; i<n; i++, printf("\n"))
    for (j=0; j<n; j++)
      printf("%d ", 5*n*n+RA[n-i-1][j]);
  TIMESTAMP(end);
  return 0;
}
