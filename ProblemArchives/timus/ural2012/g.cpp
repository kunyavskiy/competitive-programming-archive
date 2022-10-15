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

long long A[11000];
long long P, NP, Ma;

long long gcd (long long a, long long b)
{
  return (b)?(gcd(b,a%b)):(a);
}

long long mult (long long a, long long b, long long p)
{
  if (a==0 || b==0)
    return 0ll;
  return (4ll*mult(a/2ll,b/2ll,p)+2ll*((a%2ll)*(b/2ll)+(a/2ll)*(b%2ll))+(a%2ll)*(b%2ll))%p;
}


void gcdex(long long a,long long b,long long& x,long long& y){
	if (b == 0){
		x = 1;
		y = 0;
		return;
	}
	long long x1,y1;
	gcdex(b,a%b,x1,y1);
	x = y1;
	y = x1 - (a/b)*y1;
	return;
}


long long inv (long long a, long long p){
    long long x,y;
    gcdex(a,p,x,y);
    x=((x%p)+p)%p;
    assert(mult(a,x,p) == 1);
    //cerr<<x<<endl;
    return x;
}

long long inter (long long a, long long b)
{
  while (b!=1ll)
    b=gcd(a,b), a/=b;
  return a;
}

int main(){
  int n, i, x;
  long long tmp;
  #ifdef LOCAL
  	freopen("input.txt", "r", stdin);
  	freopen("output.txt", "w", stdout);
  #endif
  scanf("%d", &n);
  for (i=0; i<n; i++)
    scanf("%d", &x), A[i]=x;
  if (n==1)
  {
    printf("1 %d 10\n", (int)(A[0]+1));
    return 0;
  }
  if (A[0]==0 && A[1]!=0)
  {
    puts("1 1 1");
    return 0;
  }
  P=0, Ma=max(A[0],A[1]);
  for (i=2; i<n; P=NP, i++)
  {
    if (A[i]!=0 && A[i-1]==0)
      break;
    if (A[i]==0 && A[i-1]==0)
      continue;
    Ma=max(Ma,A[i]), NP=gcd(P,abs(A[i-1]*A[i-1]-A[i]*A[i-2]));
    //cerr<<i<<"    Ma="<<Ma<<" NP="<<NP<<endl;
    if (NP!=0)
    {
      (A[i]!=0)?(tmp=A[i-1]/gcd(A[i],A[i-1])):(tmp=A[i-1]/gcd(NP,A[i-1]));
      //cerr<<tmp<<endl;
      tmp=gcd(tmp,NP);
      while (tmp!=1ll)
        NP/=tmp, tmp=gcd(NP,tmp);
      //cerr<<NP<<endl;
    }
    if (A[i]==0)
    {
      tmp=gcd(A[i-1],NP), tmp*=tmp;
      assert(tmp%gcd(A[i-2],NP)==0ll);
      tmp/=gcd(A[i-2],NP);
      NP=gcd(NP,tmp);
    }
    if (NP!=0)
    {
    //cerr<<NP<<endl;
    long long b3=gcd(A[i],NP), b2=gcd(A[i-1],NP), b1=gcd(A[i-2],NP);
    //cerr<<b3<<" "<<b2<<" "<<b1<<endl;        
    long long k1=b3/b2, k2=b2/b1;
    assert(b3%b2==0ll && b2%b1==0ll);
    //cerr<<b1<<" "<<b2<<" "<<b3<<"    "<<k1<<" "<<k2<<endl;
    long long t=(k2/k1);
    //long long tk=inter(k1,t);
    //cerr<<"??? "<<tk<<endl;
    //t=k1/tk;
    //cerr<<"!!!! "<<t<<endl;
    tmp=inter(b3,t), tmp=b3/tmp;
    long long tmp2=inter(NP,tmp);
    NP=tmp2*gcd(NP,tmp);
   }
    if (NP<=Ma && NP!=0)
      break;
  }
  //cerr<<"!!!!"<<endl;
  int ans=i;
  if (ans==2)
  {
    if (A[0]==0)
    {
      (A[1]==0)?(printf("2 2 2\n")):(puts("1 1 1"));
      return 0;
    }
    tmp=2ll*((A[1]+A[0])/A[0])+10ll;
    cout<<"2 "<<A[0]*tmp-A[1]<<" "<<tmp<<endl;
    return 0;
  }
  if (P==0)
    P=Ma+1;
  printf("%d ", ans);
  cout<<P<<" ";
  if (A[0]==0 && A[1]==0)
  {
    puts("1");
    return 0;
  }
  cout<<mult(A[1]/gcd(A[1],A[0]),inv(A[0]/gcd(A[1],A[0]),P),P)<<endl;
  PRINT_TIME;
  return 0;
}
