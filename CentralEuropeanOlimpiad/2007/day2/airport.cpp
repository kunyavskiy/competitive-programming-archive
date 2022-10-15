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

bool cur[1100];
pair<int,int> ops1[6000];
pair<int,int> ops2[6000];
int n,m;
bool used[5100][5100];

char curop[11000];

void dfs(int i,int j){
	if (used[i][j])
		return;
	used[i][j] = true;
	if (i == n && j == m)
		return;
	//fprintf(stderr,"i = %d, j = %d, cur = %d%d ops1 = (%d,%d), ops2 = (%d,%d)\n",i,j,cur[0],cur[1],ops1[i].first,ops1[i].second,ops2[i].first,ops2[i].second);
	bool q = false;	
	if (i != n && cur[ops1[i].first] != ops1[i].second){
		q = true;
		cur[ops1[i].first] ^= 1;
		curop[i+j] = '1';
		dfs(i+1,j);
		cur[ops1[i].first] ^= 1;		
	}
	if (j != m && cur[ops2[j].first] != ops2[j].second){
		q = true;
		cur[ops2[j].first] ^= 1;
		curop[i+j] = '2';
		dfs(i,j+1);
		cur[ops2[j].first] ^= 1;		
	}
	if (!q){
		curop[i+j] = 0;
		puts(curop);
		exit(0);
	}
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d",&n);
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		if (scanf(" RES %d",&ops1[i].first) == 1)
			ops1[i].second = 1;
		else{
			assert( scanf(" L %d",&ops1[i].first) == 1);
			ops1[i].second = 0;
		}	
		--ops1[i].first;		
	}
	scanf("%d",&m);
	for (int i=0;i<m;i++){
		if (scanf(" RES %d",&ops2[i].first) == 1)
			ops2[i].second = 1;
		else{
			assert( scanf(" L %d",&ops2[i].first) == 1);
			ops2[i].second = 0;
		}			
		--ops2[i].first;
	}
	dfs(0,0);
	puts("The performances will always finish.\n" );
	return 0;
}