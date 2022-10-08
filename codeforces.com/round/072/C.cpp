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



char s[51][51];
int d[51][51];
int p[51][51];
bool g[51][51];
int n,m;

string ans="-1";


int qx[2600],ql,qr,qy[2600];

inline void init(){
	ql = 0;
	qr = 0;
}

inline void push(int x,int y){
	qx[qr]=x;
	qy[qr]=y;
	qr++;
}

inline void pop(int& x,int& y){
	x = qx[ql];
	y = qy[ql];
	ql++;	
}

inline bool empty(){
	return ql == qr;
}

const int inf = 1<<28;

inline bool good(int x,int y){
	return x>=0 && y>=0 && x<n && y<m && g[x][y];
}

const int dx[4] = {1,0,-1,0};
const int dy[4] = {0,1,0,-1};


int px,py,nap;
void gen(int ex,int ey,string& s){
	if (::s[ex][ey] == 'T')
		return;
	nap = -1;
	for (int i=0;i<4;i++){
		px = ex - dx[i];
		py = ey - dy[i];
		if (good(px,py) && d[px][py]+1 == d[ex][ey])
			if (nap == -1  || (::s[px][py] < ::s[ex-dx[nap]][ey-dy[nap]]))
				nap = i;		
	}
	gen(ex-dx[nap],ey-dy[nap],s);
	if (::s[ex][ey] != 'S')
		s+=::s[ex][ey];
	
}


int sx,sy,ex,ey;
void solve(){
	init();
	push(sx,sy);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++){
			d[i][j] = inf;
		}
	d[sx][sy] = 0;
	push(sx,sy);
	int x,y;
	int tox,toy;
	for (;!empty();){
		pop(x,y);
		for (int i=0;i<4;i++){
			tox = x+dx[i],toy=y+dy[i];
			if (good(tox,toy) && d[tox][toy] == inf){
				d[tox][toy] = d[x][y]+1;
				p[tox][toy] = i;
				push(tox,toy);
				if (tox == ex && toy == ey){
					ql = qr;
					break;
				}
			}
		}
	}
	if (d[ex][ey] == inf){
		cerr<<"NONE"<<endl;
		return;
	}
	if (ans.size() > d[ex][ey]-1 || ans == "-1"){
		ans = "";
		gen(ex,ey,ans);
		reverse(ans.begin(),ans.end());
		cerr<<ans<<endl;	
		return;
	}
	if (ans.size() == d[ex][ey]-1){
		string tmp = "";
		gen(ex,ey,tmp);		
		reverse(tmp.begin(),tmp.end());
		cerr<<tmp<<endl;
		if (ans > tmp)
			ans = tmp;
		return ;
	}
	cerr<<"NONE"<<endl;
}


void mkg(char a,char b,char c,char d){
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (s[i][j] == a || s[i][j] == b || s[i][j] == c || s[i][j] == d || s[i][j] == 'S' || s[i][j] =='T')
				g[i][j] = true;
			else
				g[i][j] = false;
}

int k;

char can[4];


void perebor(int pos){	
	if (pos == k){
		mkg(can[0],can[1],can[2],can[3]);
		cerr<<can[0]<<" "<<can[1]<<" "<<can[2]<<" "<<can[3]<<" : ";
		solve();
		return;
	}
	can[pos] = (pos?can[pos-1]+1:'a');
	for (;can[pos]<='z';++can[pos])
		perebor(pos+1);
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	scanf("%d %d %d ",&n,&m,&k);
  	can[0] = can[1] = can[2] = can[3] = '?';
  	for (int i=0;i<n;i++)
  		for (int j=0;j<m;j++){
  			scanf(" %c ",&s[i][j]);
  			if (s[i][j] == 'T')
  				sx=i,sy=j;
  			else if (s[i][j] =='S')
  				ex=i,ey=j;  				
  		}
  	perebor(0);
  	cout<<ans<<endl;
	return 0;
}