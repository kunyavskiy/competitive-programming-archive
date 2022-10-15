#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int dx[4] = {1,0,-1,0};
const int dy[4] = {0,-1,0,1};

int d[1010][1010];
vector<int> v[1010][1010];
int n,m;

int main(){
    #ifdef LOCAL
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
       scanf("%d %d",&n,&m);
       for (int i = 0; i < n; i++)
       	  for (int j = 0; j < m; j++){
       	  	int x;
       	  	scanf("%d",&x);
       	  	x *= 2;
       	  	for (int t = 0; t < x; t++){
       	  		int a;
       	  		scanf("%d",&a);
       	  		v[i][j].pb(a);
       	  	}
       	  	v[i][j].pb(1<<30);
       	  }
		memset(d,0x3f,sizeof(d));

		set<pair<int,pair<int,int> > > s;

		d[0][0] = 0;
		s.insert(mp(0,mp(0,0)));

		while (s.size()){
			int x = s.begin()->second.first;
			int y = s.begin()->second.second;
			s.erase(mp(d[x][y],mp(x,y)));
			//cerr << x <<" "<<y<<" "<<d[x][y] << endl;

			int id = upper_bound(v[x][y].begin(),v[x][y].end(),d[x][y]) - v[x][y].begin();
			int rd = d[x][y];

			if (id % 2 == 1)
				rd = v[x][y][id];

			for (int i = 0; i < 4; i++){
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < 0 || ny < 0 || nx >= n || ny >= m)
					continue;
				if (d[nx][ny] <= rd)
					continue;
				s.erase(mp(d[nx][ny],mp(nx,ny)));
				d[nx][ny] = rd;
				s.insert(mp(d[nx][ny],mp(nx,ny)));
			}
		}
		cout << d[n-1][m-1] << endl;
	    return 0;
} 