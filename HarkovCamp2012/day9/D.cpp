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

#define taskname "d"

const int inf = 1000000000;
const ld eps = 1e-9;

long double X[3], Y[3], s, A[3], F[3], C[2];

int main(){
  int i;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  for (i=0; i<3; i++)
    cin>>X[i]>>Y[i];
  s=((X[0]-X[2])*(Y[1]-Y[2])-(Y[0]-Y[2])*(X[1]-X[2]))/2.0, s=fabs(s);
  for (i=0; i<3; i++)
    A[i]=sqrt((X[i]-X[(i+1)%3])*(X[i]-X[(i+1)%3])+(Y[i]-Y[(i+1)%3])*(Y[i]-Y[(i+1)%3]));
  sort(A,A+3);
  if (A[0]*A[0]+A[1]*A[1]>=A[2]*A[2])
  {
    printf("%.8lf\n", (double)(A[0]*A[1]*A[2]/(4.0*s)));
    return 0;
  }
  for (i=0; i<2; i++)
    C[i]=A[i]/(2.0*cos(asin(2.0*s/(A[2]*A[i]))));
  printf("%.8lf\n", (double)(max(C[0],C[1])));
  return 0;
}

