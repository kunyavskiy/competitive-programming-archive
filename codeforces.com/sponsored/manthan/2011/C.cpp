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

#undef min
int min(int a,int b){
	return (a<b)?a:b;
}

int t[4100][4100][2];
int ti,td,tr,ts;
char s1[4100],s2[4100];
int n,m;

int calc(int n,int m,int k){
	if (n<0 && m<0)
		return 0;
	if (n<0)
		return ti*(m+1);
	if (m<0)
		return td*(n+1);
	int& ans=t[n][m][k];
	if (ans != -1)
		return ans;
	ans=1<<29;
	if (k == 0){
		if (s1[n]==s2[m])
			ans=min(ans,calc(n-1,m-1,0));	
		ans=min(ans,calc(n-1,m,0)+td);
		ans=min(ans,calc(n,m-1,0)+ti);
		ans=min(ans,calc(n-1,m-1,0)+tr);
		if (n>=1)
			ans=min(ans,calc(n,m-1,1)+ts+tr*(s1[n-1]!=s2[m]));			
	}
	else {
		if (s1[n] == s2[m])
			ans=min(ans,calc(n-2,m-1,0));
		ans=min(ans,calc(n,m-1,1)+ti);
		ans=min(ans,calc(n-2,m-1,0)+tr);		
	}
//	cerr<<n<<" "<<m<<" "<<k<<" : "<<ans<<endl;
	return ans;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	gets(s1);
	sscanf(s1,"%d %d %d %d",&ti,&td,&tr,&ts);
	gets(s1);
	gets(s2);
	tr=min(tr,td+ti);
	n=strlen(s1);
	m=strlen(s2);
	memset(t,-1,sizeof(t));
	cout<<calc(n-1,m-1,0)<<endl;
    return 0;
}