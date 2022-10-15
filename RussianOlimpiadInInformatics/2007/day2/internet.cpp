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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

struct point{
	int64 x,y;
	point(){
		x=y=0;
	}
	point(int64 X,int64 Y)
	{
		x=X;
		y=Y;
	}
};

bool operator<(const point& a,const point& b){
	return a.x<b.x || (a.x==b.x && a.y<b.y);
}

set<point> con;

int main()
{
  freopen("internet.in","r",stdin);
  freopen("internet.out","w",stdout);
  int n;
  int64 k;
  cin>>n>>k;
	for (int i=0;i<n;i++){
		int64 x,y,l;
		char t;
		cin>>x>>y>>t>>l;
		int kx,ky;
		if (t=='N')
			{
				kx=0;
				ky=1;
			}
		if (t=='S'){
			kx=0;
			ky=-1;
		}
		if (t=='W')
			{
				kx=-1;
				ky=0;
			}
		if (t=='E')
		{
			kx=1;
			ky=0;
		}
	//	cerr<<endl<<x<<" "<<y<<" "<<t<<" "<<l<<endl;
		for (int64 i=1;i<=l;i++){
			int64 bx=x+kx*(i-1);
			int64 by=y+ky*(i-1);
			int64 nx=x+kx*i;
			int64 ny=y+ky*i;
		//	cerr<<bx<<" "<<by<<" "<<nx<<" "<<ny<<endl;
			if (bx==nx){
				int64 ty=min(by,ny);
				int64 tx=nx;
				if ((abs(ty+tx))%2==1)
					tx--;
//				cerr<<tx<<" "<<ty<<endl;
				con.insert(point(tx,ty));
				if (con.size()==k)
					{
						cout<<tx<<" "<<ty<<endl;
						return 0;
					}
			}
			if (by==ny){
				int64 tx=min(bx,nx);
				int64 ty=ny;
				if ((abs(ty+tx))%2==1)
					ty--;
	//			cerr<<tx<<" "<<ty<<endl;
				con.insert(point(tx,ty));
				if (con.size()==k)
					{
						cout<<tx<<" "<<ty<<endl;
						return 0;
					}			
			}
		}
  }
  return 0;
}