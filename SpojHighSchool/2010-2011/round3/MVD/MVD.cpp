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

const ld eps = 1e-6;

struct point{
	int x,y;
	point(){};
	point(int X,int Y){
		x=X;y=Y;
	}
	void load(){	
		scanf("%d %d",&x,&y);
	}
};

point operator-(point a,point b){
	return point(a.x-b.x,a.y-b.y);
}

int64 operator*(point a,point b){
	return a.x*b.x+a.y*b.y;
}

int64 operator^(point a,point b){
	return a.x*b.y-a.y*b.x;
}

void solve(point v1,point v2){
	ld ang=atan2(v1^v2,v1*v2);
	if (abs(ang) < eps)
		printf("F");
	else if (abs(ang - M_PI) < eps || abs(ang + M_PI) < eps)
		printf("B");
	else{
		printf("%c %.15lf","LR"[(v1^v2)<0],double(cos(abs(ang))));
	}
	printf("\n");
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int n;
	cin >> n;
	point p1,p2,p3;
	p2.load();p3.load();	
	for (int i=0;i<n-1;i++){
		p1 = p2;
		p2 = p3;
		p3.load();
		solve(p2-p1,p3-p2);
	}
	return 0;
}