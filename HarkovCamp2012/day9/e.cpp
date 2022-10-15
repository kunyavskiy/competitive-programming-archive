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

double res=1e18, tres, X[3], Y[3], A[3];

double calc (double ang)
{
  double lb=1e18, ub=-1e18, tmp;
  for (int i=0; i<3; i++)
    tmp=(X[i]*cos(ang)-Y[i]*sin(ang)), lb=min(lb,tmp), ub=max(ub,tmp);
  return ub-lb;
}

double check (double ang)
{
  double tmp=calc(ang)+calc(ang+M_PI/2.0);
  res=min(res,tmp);
  return tmp;
}

int main(){
  int i, it;
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  for (i=0; i<3; i++)
    cin>>X[i]>>Y[i];
  for (i=0; i<3; i++)
    A[i]=sqrt((X[i]-X[(i+1)%3])*(X[i]-X[(i+1)%3])+(Y[i]-Y[(i+1)%3])*(Y[i]-Y[(i+1)%3]));
  for (i=0; i<3; i++)
    res=min(res,A[i]+A[(i+1)%3]);
  for (i=0; i<5000; i++)
  {
    //cerr<<i<<endl;
    double l=M_PI*i/20000.0, r=l+M_PI/20000.0, m1, m2;
    for (it=0; it<30; it++)
    {
      m1=(2.0*l+r)/3.0, m2=(l+2.0*r)/3.0;
      (check(m1)<check(m2))?(r=m2):(l=m1);
    }
  }
  printf("%.8lf\n", (double)res);
  return 0;
}

