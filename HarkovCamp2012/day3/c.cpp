#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "c3"

const int inf = 1000000000;
const ll linf = 1LL<<62;
const ld eps = 1e-9;

const ll dx[8] = {1,1,0,-1,-1,-1,0,1};
const ll dy[8] = {0,1,1,1,0,-1,-1,-1};
int can[8];

const int SZ = 100;

ll x,y;
ll ans;

ll d[SZ][SZ];

bool good(int x,int y){
	return 0 <= x && x < SZ && 0 <= y && y < SZ;
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);

  for (int i = 0; i < 8; i++)
  	cin >> can[i];
  cin >> x >> y;


  for (int i = 0; i < SZ; i++)
  	for (int j = 0; j < SZ; j++)
  		d[i][j] = linf;

  d[SZ/2][SZ/2] = 0;

  bool q = true;

  while (q){
  	q = false;

  	for (int i = 0; i < SZ; i++)
  		for (int j = 0; j <SZ; j++)
  			for (int k = 0; k < 8; k++)
  				if (can[k] && good(i+dx[k],j+dy[k])){
  					if (d[i+dx[k]][j+dy[k]] > d[i][j] + 1){
  						q = true;
  						d[i+dx[k]][j+dy[k]] = d[i][j] + 1;
  					}
  				}
  }

  ans = linf;
  bool any = false;

  int x1, x2, y1, y2;

  for (int i = 0; i < SZ; i++)
  	for (int j = 0; j < SZ; j++){
  		ll nx = x + SZ/2 - i;
  		ll ny = y + SZ/2 - j;

  		if (nx == 0 && ny == 0){
  			if (d[i][j] != linf){
  			    if (!any)
  			      ans=d[i][j];
	  			ans = min(ans,d[i][j]);
  				any = true;
  			}
  		}

  		for (x1=-2; x1<=2; x1++)
  		  for (y1=-2; y1<=2; y1++)
  		    for (x2=-2; x2<=2; x2++)
  		      for (y2=-2; y2<=2; y2++)
  		      {
				if (x1*x1+y1*y1==0 || x2*x2+y2*y2==0 || d[x1+SZ/2][y1+SZ/2]==linf || d[x2+SZ/2][y2+SZ/2]==linf)
					continue;
				if (x1==x2 && y1==y2){
					if (nx*y1 == ny*x1 && d[i][j] != linf){
					    if ((x1!=0 && nx%x1!=0) || (y1!=0 && ny%y1!=0))
					    {
					      continue;
					    }
						if (!any || ans > d[i][j] +d[x1+SZ/2][y1+SZ/2]*((abs(nx)+abs(ny))/(abs(x1)+abs(y1))))
							ans = d[i][j] + d[x1+SZ/2][y1+SZ/2]*((abs(nx)+abs(ny))/(abs(x1)+abs(y1)));
						//cerr<<ans<<endl;
						any = true;
					}
					continue;
				}
				if (x1 * y2 - y1 * x2 == 0)
					continue;

				ll det  = x1 * y2 - y1 * x2;
				ll det2 = nx * y2 - ny * x2;
				ll det3 = (x1 * ny - y1 * nx);


				if (abs(det2) % abs(det) == 0 && abs(det3) % abs(det) == 0){
				     assert(nx==(det2/det)*x1+(det3/det)*x2);
				     assert(ny==(det2/det)*y1+(det3/det)*y2);
				     if (d[i][j] != inf  && det2/det >= 0 && det3/det >= 0){
				     	 if (!any || ans > d[i][j] + d[x1+SZ/2][y1+SZ/2]*det2/det + d[x2+SZ/2][y2+SZ/2]*det3/det)
							 ans = d[i][j] + d[x1+SZ/2][y1+SZ/2]*det2/det + d[x2+SZ/2][y2+SZ/2]*det3/det;
						 any = true;
 					}	
				}
			}
  	}

  	if (!any)
  	    printf("-1\n");
  	else
  		cout << ans << endl;
  		


  return 0;
}

