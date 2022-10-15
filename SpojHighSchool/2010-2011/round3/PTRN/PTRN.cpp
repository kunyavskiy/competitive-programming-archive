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

char s[5000][5000];

void print(int x,int y,int sz,bool diag){
	for (int i=0;i<=sz+1;i++)
		for (int j=0;j<=sz+1;j++)
			if (i==0 || i==sz+1 || j==0 || j==sz+1)
				s[x+i][y+j]='*';
			else
				s[x+i][y+j]='.';
	if (diag){
		for (int i=1;i<=sz;i++)
			s[x+i][y+sz-i+1]='/';		
	}
	else {
		for (int i=1;i<=sz;i++)
			s[x+i][y+i]='\\';
	}
	
	
	
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int w,k,sz;
	int t;
	cin>>t;
	for (;t;--t){
		cin>>w>>k>>sz;		
		int x = 0;
		while (w*(sz+1) > 5000);
		while (k*(sz+1) > 5000);
		for (int i=0;i<w*(sz+1)+10;i++)
			for (int j=0;j<k*(sz+1)+10;j++)
				s[i][j]=0;
		for (int i=0;i<w;i++){	
			int y=0;
			for (int j=0;j<k;j++){
				print(x,y,sz,(i+j)%2);
				y+=sz+1;
			}
			x+=sz+1;
		}
		for (int i=0;s[i][0];i++)
			puts(s[i]);
		if (t!=1)
			puts("");
	}
	return 0;
}