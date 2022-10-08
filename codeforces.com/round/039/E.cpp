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

#define norm(x) if (x>=p) x-=p

using namespace std;

typedef long long int64;
typedef long double ld;


int a[1100];
int b[1100];
int c[1100];
int p;

int C[1100][1100];

int t[1100][1];
int kol[1100];
int sign[1100];
int chet[1100];
int nechet[1100];


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n,m;
	scanf("%d %d",&n,&m);
	int k;
	scanf("%d",&k);
	for (int i=0;i<k;i++){
		scanf("%d %d %d",&a[i],&b[i],&c[i]);
		--a[i],--b[i];
	}

	if (n<m){
		for (int i=0;i<k;i++)
			swap(a[i],b[i]);
	}	
		
/*	for (int i=0;i<n;i++){
		bool q=false;
		for (int j=0;j<k;j++)
			q|=a[j]==i;
		if (!q){
			for (int j=0;j<k;j++)
				if (a[j]==n-1)
					a[j]=i;
			break;
		}
	}*/
	
	int p;
	scanf("%d",&p);
	for (int i=0;i<=n;i++)
		for (int j=0;j<=n;j++){
			if (j==0)
				C[i][j]=1;
			else if (i==0)
				C[i][j]=0;
			else
				C[i][j]=C[i-1][j]+C[i-1][j-1];
			norm(C[i][j]);
		}
			
	for (int i=0;i<=n;i++){
		for (int j=0;j<=i;j+=2){
			chet[i]+=C[i][j];
			norm(chet[i]);
		}
		for (int j=1;j<=i;j+=2){
			nechet[i]+=C[i][j];
			norm(nechet[i]);
		}
		if (i%2==1){
			nechet[i]+=chet[i];
			chet[i]=0;
			norm(nechet[i]);
		}
					
	}
	
	for (int i=0;i<m;i++){
		sign[i]=0;
		kol[i]=n;
	}
	for (int i=0;i<k;i++){
		sign[a[i]]^=(c[i]==-1);
		kol[a[i]]--;
	}
		
	t[0][0]=1;
	t[0][1]=0;
	for (int i=0;i<n;i++){
		if (sign[i]==0){
			t[i+1][0]=t[i][0]*nec
		}
	}
	cout<<t[n-1][0]<<endl;		
	return 0;
}