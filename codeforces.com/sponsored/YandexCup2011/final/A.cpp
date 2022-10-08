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

#define y1 botva

using namespace std;

typedef long long int64;
typedef long double ld;


int x1[30],y1[30];
int x2[30],y2[30];

bool used[10][10];

char pol[35][35];
int res[35][35];
int samp[35][35];
int ans;
int n,m;
int cnt[7];

/*bool check(){
/*	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++)
			if (pol[i][j] == '.')
				fprintf(stderr,".");
			else
				fprintf(stderr,"%d",res[i][j]);
		fprintf(stderr,"\n");
	}
	for (int i=0;i<7;i++)
		for (int j=0;j<7;j++)
			used[i][j] = 0;
	int a,b;
	for (int i=0;i<28;i++){
		a = res[x1[id]][y1[id]];
		b = res[x2[id]][y2[id]];
		if (used[a][b])
			return false;
		used[a][b] = used[b][a] = true;
	}
	return true;		
}*/

int counter;

vector<pair<int,int> > v;

bool use(int x,int y,int val){
	res[x][y] = val;
	int id = pol[x][y] - 'a';
	if (!(0 <= id && id <= 25))
		id = pol[x][y] - 'A'+26;
	int a = res[x1[id]][y1[id]];
	int b = res[x2[id]][y2[id]];
	if (a != -1 && b!= -1){
		if (used[a][b]){
			res[x][y] = -1;
			return false;
		}
		used[a][b] = used[b][a] = true;
	}		
}

void unuse(int x,int y){
	int id = pol[x][y] - 'a';
	if (!(0 <= id && id <= 25))
		id = pol[x][y] - 'A'+26;
	int a = res[x1[id]][y1[id]];
	int b = res[x2[id]][y2[id]];	
	if (a == -1 || b == -1){
		res[x][y] = -1;
		return;
	}
	used[a][b] = used[b][a] = false;
	res[x][y] = -1;
}



int perebor(int x,int y){
	++counter;
	if (counter % 10000 == 0)
		cerr << counter << endl;	
	
	if (y == m){
		perebor(x+1,0);
		return 0;
	}
	if (x == n){
//		if (!check())	return 0;
		ans++;
		if (ans == 1)	memcpy(samp,res,sizeof(res));
		return 1;
	}
	if (pol[x][y] == '.' || res[x][y] != -1)
		return perebor(x,y+1);
	
	
	for (int i=0;i<7;i++){
		if (cnt[i]){
			bool q = true;
			

			v.clear();
			v.pb(mp(x,y));
			v.pb(mp(x+1,y));
			v.pb(mp(x,y+1));
			v.pb(mp(x+1,y+1));
			
			for (int I=0;I<4;I++){
				if (!use(v[I])){
					for (int j=0;j<I;j++)
						unuse(v[j].first,v[j].second,i);
					q = false;
					break;
				}
			}
			if (!q) continue;			
			
			--cnt[i];
			perebor(x,y+1); 
			unuse(x,y);
			unuse(x+1,y);
			unuse(x,y+1);
			unuse(x+1,y+1);
			++cnt[i];			
		}
	}
		
}







int main(){
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf(" %c ",&pol[i][j]);
	memset(x1,-1,sizeof(x1));
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			if (pol[i][j] == '.')
				continue;
			int id = pol[i][j] - 'a';
			if (!(0<=id && id <= 25))
				id = pol[i][j] - 'A' + 26;
			if (x1[id] == -1)
				x1[id] = i,y1[id] = j;
			else
				x2[id] = i,y2[id] = j;
		}
	for (int i=0;i<7;i++)
		cnt[i] = 2;
	memset(res,-1,sizeof(res));	
	perebor(0,0);
	printf("%d\n",ans);
	for (int i=0;i<n;i++){
		for (int j=0;j<m;j++)
			if (samp[i][j] == -1)
				printf(".");
			else
				printf("%d",samp[i][j]);
				printf("\n");
		}
	
	return 0;
}