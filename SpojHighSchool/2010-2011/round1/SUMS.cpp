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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int n;
int a[40];
int ptr;
bool q;

void print(){
	q=true;
	for (int i=0;i<ptr;i++)
		printf("%d ",a[i]);
	printf("\n");
}


void perebor(int sum,int chet,int nechet){
	if (sum==n){
		if (chet==nechet)
			print();
		return;
	}
	int last=(ptr==0)?1:(a[ptr-1]);
	for (int i=last;sum+i<=n;i++){
		a[ptr++]=i;
		perebor(sum+i,chet+((i&1)==0),nechet+((i&1)==1));
		--ptr;
	}

}


int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int t;
	cin>>t;
	for (int i=0;i<t;i++){
		cin>>n;
		q=false;
		perebor(0,0,0);
		if (!q) printf("Impossible\n");		
	}
  return 0;
}