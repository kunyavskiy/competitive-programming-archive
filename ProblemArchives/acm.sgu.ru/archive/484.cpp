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

string s[110];
int x,y;
int n,m;

void error(){
	printf("-1\n");
	exit(0);
	
}

void iterate(){
	if (x==n-1 || s[x+1][y]=='.'){
		x++;
		return;
	}
	if (s[x+1][y]=='/'){	
	//	while (s[x+1][y]=='/'){
			if (y==0 || s[x+1][y-1]=='\\')
				error();
			y--;
	//	}
		x++;
		return;
	}
	if (s[x+1][y]=='\\'){	
	//	while (s[x+1][y]=='\\'){
			if (y==m-1 || s[x+1][y+1]=='/')
				error();
			y++;
	//	}	
		x++;
		return;
	}
	assert(false);	
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d\n",&n,&m);
	for (int i=0;i<n;i++)
		getline(cin,s[i]);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (s[i][j]=='P'){	
				x=i;
				y=j;
				s[i][j]='.';
			}
	for (;x!=n;)
		iterate();
	cout<<y+1<<endl;				
    return 0;
}