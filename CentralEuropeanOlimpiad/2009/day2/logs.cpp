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

#undef max
inline int max(int a,int b){
	return ((a>b)?a:b);
}



int ans;
int n,m;

char s[1510];
int cnt[1510];
int pos[1510];
int pos1[1510];



int main(){
    freopen("logs.in","r",stdin);
    freopen("logs.out","w",stdout);
	gets(s);
	sscanf(s,"%d %d",&n,&m);
	for (int i=0;i<m;i++)
		pos[i] = i;
	int pt;
	for (int it=0;it<n;it++){
		gets(s);
		pt = -1;
		for (int i=0;i<m;i++){
			cnt[i] = (cnt[i]+1)*(s[i] == '1');			
			if (s[i] == '0')
				pos1[++pt] = i;
		}
		for (int i=0;i<m;i++){
			if (s[pos[i]] == '1')		
				pos1[++pt] = pos[i];	
			pos[i] = pos1[i];
			ans = max(ans,cnt[pos[i]]*(m-i));
		}
	}
	printf("%d\n",ans);
    return 0;
}