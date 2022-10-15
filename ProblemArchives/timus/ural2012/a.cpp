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

int S[550][550], A[550][550], D[550][550], Prev[550][550], res=-1, resid, n, k, R[550];

inline int get (int x, int y)
{
  return S[x][n]-S[x][y];
}

int main(){
  int i, j, l, tmp;
  #ifdef LOCAL
  	freopen(".in", "r", stdin);
  	freopen(".out", "w", stdout);
  #endif
  scanf("%d%d", &n, &k);
  for (i=0; i<n-1; i++)
    for (j=0; i+j+1<n; j++)
      scanf("%d", &A[i][i+j+1]);
  for (i=0; i<n; i++)
    for (j=0; j<n; j++)
      S[i+1][j+1]=A[i][j]+S[i+1][j]+S[i][j+1]-S[i][j];// cerr<<i<<" "<<j<<" "<<S[i+1][j+1]<<" "<<A[i][j]<<endl;
  memset(D,-1,sizeof(D)), D[0][0]=0;
  for (i=1; i<n; i++)
    for (j=1; j<=min(k,i); j++)
      for (l=0; l<i; l++)
      {   
        //cerr<<i<<" ???? "<<j<<" "<<l<<" "<<D[l][j-1]<<endl;
        if (D[l][j-1]!=-1)
        {
          tmp=S[i][n]-S[l][n]-S[i][i]+S[l][i];
          //cerr<<l<<" "<<i<<" "<<j<<"        "<<tmp<<" !!!  "<<S[l+1][n]<<" "<<S[l+1][i]<<endl;
          if (D[l][j-1]+tmp>D[i][j])
            D[i][j]=D[l][j-1]+tmp, Prev[i][j]=l;
        }
      }
  for (i=n-1; i>0; i--)
    if (res<D[i][k])
      resid=i, res=D[i][k];
  assert(res!=-1);
  printf("%d\n", res);
  for (i=k; i>0; i--)  
    R[i]=resid, resid=Prev[resid][i];
  for (i=1; i<=k; i++)
    printf("%d ", R[i]);
  printf("\n");
  PRINT_TIME;
  return 0;
}
