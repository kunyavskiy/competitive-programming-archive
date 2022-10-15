#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <set>
#include <cstdio>
#include <cstdlib>
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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define dbg(a,n) copy(a,a+n,ostream_iterator<int>(cerr," "));cerr<<endl

using namespace std;

typedef long long int64;
typedef long double ld;

const string TASKNAME = "neckless";
const string INFILE = TASKNAME + ".in";
const string OUTFILE = TASKNAME + ".out";

int a[100];
int n;

int main()
{
  freopen(INFILE.data(),"r",stdin);
  freopen(OUTFILE.data(),"w",stdout);
  scanf("%d",&n);
  for (int i=0;i<n;i++){
  	scanf("%d",&a[i]);
  	--a[i];
  }
  for (int i=0;i<n-1;i++){
//  	dbg(a,n);
  	int pos=0;
  	for (;a[pos]!=i;++pos);  	
  	for (;a[(pos+1)%n]!=i+1;++pos){
  //		dbg(a,n);
  		for (int j=i;j>=0;--j)
  			printf("%d %d\n",j+1,a[(pos+1)%n]+1);
  		for (int j=i;j>=0;--j){
  			swap(a[(pos-i+j+n)%n],a[(pos-i+j+1+n)%n]);
  		}
  	}
  }
  printf("0\n");
  return 0;
}