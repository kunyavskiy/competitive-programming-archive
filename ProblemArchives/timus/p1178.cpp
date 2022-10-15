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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


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
	point(int a,int b){
		x = a,y = b;
	}
	point(){
	}
	bool operator<(const point& p) const{
		if (p.y != y)
			return y < p.y;
		return x < p.x;
	}
};

vector<pair<point,int> > v;

vector<pair<int,int> > ans;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;                                           
  	scanf("%d ",&n);
  	for (int i = 0; i < n; i++){
  		int x,y;
  		scanf("%d %d",&x,&y);
  		v.pb(mp(point(x,y),i+1));
  	}

  	sort(v.begin(),v.end());
  	for (int i = 0; i < n; i+=2){
		ans.pb(mp(v[i].second,v[i+1].second));
		if (ans.back().second < ans.back().first)
			swap(ans.back().first,ans.back().second);
	}
	sort(ans.begin(),ans.end());

	for (int i = 0; i < n/2; i++)
		printf("%d %d\n",ans[i].first,ans[i].second);



  return 0;
}