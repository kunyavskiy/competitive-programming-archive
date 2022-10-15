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

int t[60][6000];
int h[60];
int n,kol;
bool used[60];

void gen(int a,int b){
	if (a==0){
		return;
	}
	used[a]=true;
	for (int last=0;last<a;last++)
		for (int j=0;j<=b;j++){
			int np=j+abs(h[a]-h[last])+2*(a!=n-1);
			if (np==b && t[last][j]+h[a]==t[a][b]){
				gen(last,j);
				return;
			}
		}
	assert(false);
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int P,sum=0;
  	scanf("%d",&n);
  	P=2*n;
  	for (int i=1;i<=n;i++)
  		scanf("%d",&h[i]);
  	h[0]=h[n+1]=0;
  	n+=2;
  	for (int i=1;i<n;i++){
  		P+=abs(h[i]-h[i-1]);
  		sum+=h[i];
  	}
  	for (int j=0;j<n;j++)
	  	for (int i=0;i<=P;i++)
  			t[j][i]=(1<<30);
  	t[0][0]=0;
  	for (int i=1;i<n;i++){
  		for (int last=0;last<i;last++)
  			for (int j=0;j<=P;j++){
  				int np=j+abs(h[i]-h[last])+2*(i!=n-1);
  				t[i][np]=min(t[i][np],t[last][j]+h[i]);
  			}  		
  	}
	int best=P;
	for (int i=0;i<=P;i++)
		if (i*2>=P)
			if (t[n-1][i]<=t[n-1][best])
				best=i;	
	printf("%d\n",sum-t[n-1][best]);
	kol=0;
	gen(n-1,best);
//	cerr<<best<<" "<<P<<endl;
	for (int i=1;i<n-1;i++)
		kol+=!used[i];
	cout<<kol<<endl;
	for (int i=1;i<n;i++)
		if (!used[i])
			printf("%d ",i);	
    return 0;
}