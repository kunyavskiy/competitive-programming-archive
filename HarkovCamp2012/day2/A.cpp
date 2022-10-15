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

#define taskname "a"

const int inf = 1000000000;
const ld eps = 1e-9;

int cf1, cf2;
int n;

void outp (double r, double a)
{
  if (n==0)
    return;
  n--;
  printf("%.8lf %.8lf\n", r*cos(a), r*sin(a));
}

void gen (double r, int cnt, double sd, int num)
{
  for (int i=0; i<num; i++)
    outp(r,(2.0*i*M_PI/cnt)+sd);
}

int main(int argc,char** argv){
  assert(argc >= 3);
  sscanf(argv[1],"%d",&cf1);
  sscanf(argv[2],"%d",&cf2);
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  scanf("%d", &n);
  if (cf2==0)
  {
    cerr<<"?????????????????????????????????????????    "<<cf1<<endl;
    int m=n;
    while (m%(cf1+1)!=0)
      m++;
    m/=(cf1+1);
    gen(1.0,m*cf1,0,m*cf1);
    double R=sqrt(1.0/((double)(cf1*cf1*cf1)))-0.1;
    gen(R,m,M_PI/(m*cf1),n-m*cf1);
    return 0;
  }
  cerr<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
  int m=n;
  while (m%7!=0)
    m++;
  m/=7;
  gen(1.0,m*4,0,m*4);
  double R;
                                  
  R=sqrt(1/8.0);
  gen(R,m*2,M_PI/(6.0*m),2*m);


  R=sqrt(1.0/64.0);
  gen(R,m,M_PI/(m*3.0),m);
  /*int m=n;
  while (m%(rt+1)!=0)
    m++;
  m/=(rt+1);
  gen(1.0,m*rt,0,m*rt);
  gen(R,m,M_PI/(m*rt),n-m*rt);*/
  /*if (n&1)
  {
    n++;
    gen(1.0,n/2,0,-1);
    gen(R,n/2,2.0*M_PI/n,0);
    return 0;
  }
  gen(1.0,n/2,0,-1);
  gen(R,n/2,2.0*M_PI/n,-1);*/
  return 0;
}

