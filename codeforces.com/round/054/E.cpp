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

struct parent{
	int x,y,z,o;
	int lx,ly,lz;
	int parent(int X,int Y,int Z,int O,int Lx,int Ly,int Lz){
		x=X;y=Y;z=Z;o=O;
		lx=Lx;ly=Ly;lz=Lz;		
	}
};

int d[10][10][10][3];
parent p[10][10][10][3]

queue<int> qx,qy,qz,qo;
string X,Y,Z;
string rX,rY,rZ


void bfs(int v){
	memset(d,-1,sizeof(d));
	d[0][0][0][0]=0;
	qx.push(0);qy.push(0);qz.push(0);qo.push(0);
	for (;!qx.empty();){
		int x=qx.front();qx.pop();
		int y=qy.front();qy.pop();
		int z=qz.front();qz.pop();
		int o=qo.front();qo.pop();
		if (x==0 && y==0 && z==0 && o==0){
			rX=rY=rZ="";
			gen(x,y,z,o,rX,rY,rZ);			
			return;
		}
		for (int i=0;i<10;i++)
			for (int j=0;j<10;j++){
				int k=i+j+o;
				int nx=x+(x<X.size() && i==X[x]-'0');
				int ny=y+(y<Y.size() && j==Y[y]-'0');
				int nz=z+(z<Z.size() && k%10==Z[z]-'0');
				int no=k/10;
			}
				
	}
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  return 0;
}