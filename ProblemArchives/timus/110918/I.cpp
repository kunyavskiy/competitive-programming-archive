#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

struct point{
	int x,y;
	point(){
	}
	point(int x,int y):x(x),y(y){
	}
};



struct comparer{
	int vx,vy;
	comparer(int vx,int vy):vx(vx),vy(vy){		
	}
	bool operator()(int a,int b);
};

point p[11000];
int n;
vector<int> v[21][21];
vector<int> ns;

inline bool comparer::operator()(int a,int b){
	int f1 = p[a].x * vy - p[a].y * vx;
	int f2 = p[b].x * vy - p[b].y * vx;
	if (f1 != f2)
		return f1 < f2;
	f1 = p[a].x * vx + p[a].y * vy;
	f2 = p[b].x * vx + p[b].y * vy;
	return f1 > f2;
}

void solve(int x,int y,int vx,int vy,int id,int& ans,int& best){
	vector<int>& pt = v[vx+10][vy+10];
	comparer comp(vx,vy);
	if (pt.size() == 0){
		pt = ns;
		sort(pt.begin(),pt.end(),comp);
//		cerr << vx<<" "<<vy<<" : "<<pt[0] <<" "<<pt[1] <<" "<<pt[2]<<" "<<pt[3] << endl;
	}
	p[n] = point(x,y);
	p[n+1] = point(x + 20000*vx,y + 20000*vy);
	int cur = upper_bound(pt.begin(),pt.end(),n,comp) - pt.begin();
//	cerr << x <<" "<<y<<" : "<<cur <<" ";
	cur -= lower_bound(pt.begin(),pt.end(),n+1,comp) -pt.begin();
//	cerr << cur << endl;
	if (cur >= ans)
		ans = cur,best = id;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	scanf("%d",&n);
  	ns.resize(n);
  	for (int i = 0; i < n; i++){
  		ns[i] = i;
  		scanf("%d %d",&p[i].x,&p[i].y);
  	}

  	int x,y,vx,vy,q;
  	scanf("%d %d %d %d %d",&q,&x,&y,&vx,&vy);  
  	int ax,bx,ay,by,avx,bvx,avy,bvy;
  	scanf("%d %d %d %d %d %d %d %d",&ax,&bx,&ay,&by,&avx,&bvx,&avy,&bvy);

  	int ans = 0,best = -1;
  	x += 10000;
  	y += 10000;
  	vx += 10;
  	vy += 10;

  	for (int i = 0; i < q; i++){
 		solve(x-10000,y-10000,vx-10,vy-10,i+1,ans,best);
  		x = (ax*x + bx) % 20001;
  		y = (ay*y + by) % 20001;
  		vx = (avx*vx + bvx) % 21;
  		vy = (avy*vy + bvy) % 21;                                     
  	}

	cout << best <<" "<< ans << endl;	
	return 0;
}