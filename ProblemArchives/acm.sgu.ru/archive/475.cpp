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

#define tm botva456

typedef long long int64;
typedef long double ld;

int t[11][1<<10];
int w[11];
int m[1<<10];
int tm[1<<10];
int g[11];
int s[11];
int n;

const int inf=1<<29;

inline int max(int a,int b){
	return (a>b)?a:b;
}

inline int min(int a,int b){
	return (a<b)?a:b;
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int M;
	scanf("%d %d",&n,&M);
	for (int i=0;i<n;i++)
		scanf("%d %d %d",&w[i],&g[i],&s[i]);
	for (int i=0;i<=n;i++)
		for (int j=0;j<(1<<n);j++)
			t[i][j]=inf;
	t[0][0]=0;
	m[0]=0;
	tm[0]=0;
	for (int i=0;i<n;i++){
		m[1<<i]=w[i];
		tm[1<<i]=g[i];
	}
	for (int i=0;i<(1<<n);i++){
		m[i]=m[i&(i-1)]+m[i&(~(i-1))];
		tm[i]=max(tm[i&(i-1)],tm[i&(~(i-1))]);
	}
	
//	cerr<<m[0]<<" "<<m[1]<<" "<<m[2]<<" "<<m[3]<<endl<<endl;
	
	
	for (int i=0;i<M;i++){
		int cr,yes,no;
		scanf("%d %d %d",&cr,&yes,&no);
		for (int i=0;i<n;i++)
			for (int j=0;j<(1<<n);j++){
				t[i+1][j]=min(t[i+1][j],t[i][j]);
				t[i+1][j^(1<<i)]=min(t[i+1][j^(1<<i)],t[i][j]+s[i]);
			}               

		
	//	cerr<<t[2][0]<<" "<<t[2][1]<<" "<<t[2][2]<<" "<<t[2][3]<<endl;	
			
		for (int j=0;j<(1<<n);j++)
			t[0][j]=t[n][j]+max(((m[j]>cr)?yes:no),tm[(~j)&((1<<n)-1)]);
		t[0][0]=inf;
		for (int i=1;i<=n;i++)
			for (int j=0;j<(1<<n);j++)
				t[i][j]=inf;
	//	cerr<<t[0][0]<<" "<<t[0][1]<<" "<<t[0][2]<<" "<<t[0][3]<<endl<<endl;;
	}
	int ans=inf;
	for (int i=0;i<(1<<n);i++){
		int tmp=t[0][i];
		for (int j=0;j<n;j++)
			tmp+=s[j]*(!!(i&(1<<j)));			
		ans=min(ans,tmp);
	}
	cout<<ans<<endl;
	return 0;
}