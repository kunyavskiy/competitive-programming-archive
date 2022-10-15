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
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

const int dx[4]={0,-1,0,1};
const int dy[4]={1,0,-1,0};
const int p[4][6]={{4,1,0,3,5,2},{3,0,2,5,4,1},{2,1,5,3,0,4},{1,5,2,0,4,3}};
const char names[6]={'U','F','R','B','L','D'};


int g[24][4];


vector<int> mul(vector<int> a,int b){
	vector<int> res(6);
	for (int i=0;i<6;i++)
		res[i]=a[p[b][i]];
	return res;
}

map<vector<int>,int> perms;
vector<vector<int> > v;
vector<int> e;

void gen(){
	set<vector<int> > s;
	
	for (int i=0;i<6;i++)
		e.pb(i);
		
	assert(mul(vector<int>(p[0],p[0]+6),2)==e);
	assert(mul(vector<int>(p[1],p[1]+6),3)==e);
	assert(mul(vector<int>(p[2],p[2]+6),0)==e);
	assert(mul(vector<int>(p[3],p[3]+6),1)==e);
		
	s.insert(e);
	for (;;){
		v=vector<vector<int> >(s.begin(),s.end());
		int size=s.size();
		for (int i=0;i<v.size();i++)
			for (int j=0;j<4;j++)
				s.insert(mul(v[i],j));
		if (s.size()==size)
			break;
	}
	v=vector<vector<int> > (s.begin(),s.end());
	for (int i=0;i<v.size();i++)
		perms[v[i]]=i;
	for (int i=0;i<v.size();i++)
		for (int j=0;j<4;j++)
			g[i][j]=perms[mul(v[i],j)];
			
	for (int i=0;i<v.size();i++)
		for (int j=0;j<4;j++)
			assert(g[g[i][j]][(j+2)%4]==i);
			
}


int d[10][10][30];
int fromx[10][10][30];
int fromy[10][10][30];
int fromp[10][10][30];
bool used[10][10][30];

int val[6];

bool good(int i,int j){
	return i>=0 && i<8 && j>=0 && j<8;
}


void deikstra(int x,int y,int p){

	for (int i=0;i<10;i++)
		for (int j=0;j<10;j++)
			for (int k=0;k<30;k++){
				d[i][j][k]=(1<<30);
				used[i][j][k]=false;
			}

	d[x][y][p]=val[v[p][5]];
	fromx[x][y][p]=-1;
	

	for (;;){
		bool q=false;
		for (int i=0;i<8;i++)
			for (int j=0;j<8;j++)
				for (int k=0;k<24;k++)
					for (int num=0;num<4;num++){
						int nx=i+dx[num];
						int ny=j+dy[num];
						int np=g[k][num];
						if (good(nx,ny) && d[nx][ny][np]>d[i][j][k]+val[v[np][5]]){
							d[nx][ny][np]=d[i][j][k]+val[v[np][5]];
							fromx[nx][ny][np]=i;
							fromy[nx][ny][np]=j;
							fromp[nx][ny][np]=k;
							q=true;
						}
					}
		if (!q)
			break;
	}

}

void print(int x,int y,int p,int mysum){

	static int sum=0;
	sum+=val[v[p][5]];
	
	if (fromx[x][y][p]==-1)
		{
			assert(sum==mysum);
			assert(v[p]==e);
			printf(" %c%c",(char)y+'a',(char)x+'1');
			return;
		}
	print(fromx[x][y][p],fromy[x][y][p],fromp[x][y][p],mysum);
	printf(" %c%c",(char)y+'a',(char)x+'1');	
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    freopen("1016.err","w",stderr);
  #endif
  
  gen();
  int fx,fy,ex,ey;
  char c,tmp;
  scanf(" %c %c ",&c,&tmp);
  fy=c-'a';
  fx=tmp-'1';
  scanf(" %c %c ",&c,&tmp);
  ey=c-'a';
  ex=tmp-'1';
  cin>>val[1]>>val[3];
  cin>>val[0]>>val[2];
  cin>>val[5]>>val[4]; 


  deikstra(fx,fy,perms[e]);
  
  int ans=d[ex][ey][0];
  for (int i=0;i<24;i++)
  	ans=min(ans,d[ex][ey][i]);
 	
  cout<<ans;
  for (int i=0;i<24;i++)
  	if (d[ex][ey][i]==ans){
		  print(ex,ey,i,d[ex][ey][i]);
		  break;
		 }
  printf("\n");		
  return 0;
}