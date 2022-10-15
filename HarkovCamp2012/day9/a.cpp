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

#define taskname "a9"

const int inf = 1000000000;
const ll linf = inf*(1LL)*inf;
const ld eps = 1e-9;

struct point{
	ll x,y;

	point(){
	}
	point(ll x,ll y):x(x),y(y){		
	}
};


point operator-(const point& a,const point& b){
	return point(a.x - b.x,a.y-b.y);
}

point operator+(const point& a,const point& b){
	return point(a.x + b.x,a.y + b.y);
}

ll vp(point a,point b){
	return a.x*1LL*b.y -a.y*1LL*b.x;
}


bool operator<(const point& a,const point& b){
	ld ang1 = atan2(a.y,a.x);
	ld ang2 = atan2(b.y,b.x);
	if (a.y < 0 || ang1 < -0.1)
		ang1 += 2*M_PI;
	if (b.y < 0 || ang2 < -0.1)
		ang2 += 2*M_PI;

	if (abs(ang1-ang2) > 0.1)
		return ang1 < ang2;

	return vp(a,b) > 0;    
}

bool cmpxy(const point& a,const point& b){
	if (a.y != b.y)
		return a.y < b.y;
	return a.x < b.x;
}

vector<point> a,b;

vector<point> sum(vector<point> a,vector<point> b){
	rotate(a.begin(),min_element(a.begin(),a.end(),cmpxy),a.end());
	rotate(b.begin(),min_element(b.begin(),b.end(),cmpxy),b.end());

	point start = a[0] + b[0];

	a.pb(a[0]);
	for (int i = 0; i+1 < (int)a.size(); i++)
		a[i] = a[i+1] - a[i];
	a.pop_back();

	for (int i = 0; i+1 < (int)a.size(); i++)
		assert(a[i] < a[i+1]);

	b.pb(b[0]);
	for (int i = 0; i+1 < (int)b.size(); i++)
		b[i] = b[i+1] - b[i];
	b.pop_back();


	for (int i = 0; i+1 < (int)b.size(); i++)
		assert(b[i] < b[i+1]);

	vector<point> c(a.size()+b.size());
	copy(a.begin(),a.end(),c.begin());
	copy(b.begin(),b.end(),c.begin()+a.size());
	sort(c.begin(),c.end());
	vector<point> d(c.size());

	d[0] = start;

	for (int i = 1; i < (int)d.size(); i++)
		d[i] = d[i-1] + c[i-1];
	
	return d;
}

int n;ll dx1,dy1;
int m;ll dx2,dy2;

point nap;

bool compare(pair<ll,ll> a,pair<ll,ll> b){
	assert(a.first >= 0 && a.second >= 0 && b.first >= 0 && b.second >= 0);
	if (abs((b.first * 1.0 / b.second * 1.0) - (a.first * 1.0 / a.second * 1.0)) > 0.5)
	  return (b.first * 1.0 / b.second * 1.0) > (a.first * 1.0 / a.second * 1.0);
	if (a.second == 0)
		return false;
	if (b.second == 0)
		return true;
                                                                                 

	if (a.first / a.second != b.first / b.second)
		return a.first / a.second < b.first / b.second;

	return compare(mp(b.second,b.first%b.second),mp(a.second,a.first%a.second));
}

bool checkin(){
	ll s1,s2;
	s1 = s2 = 0;
	a.pb(a[0]);

	for (int i = 0; i+1 < (int)a.size(); i++){
		ll temp = vp(a[i],a[i+1]);
		s1 += temp;
		s2 += abs(temp);
	}
	return abs(s1) == s2;
}

ll getdist(point p1){
	return vp(p1,nap);
}

int sign(ll a){
	if (a > 0)
		return 1;
	if (a == 0)	
		return 0;
	return -1;
}


bool check(point p1,point p2){
	ll d1 = sign(getdist(p1));
	ll d2 = sign(getdist(p2));
	return d1*d2 <= 0;
}

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

pair<ll,ll> norm(ll ch,ll zn){
	if (zn < 0){
		ch *= -1;
		zn *= -1;
	}
	ll g = gcd(abs(ch),zn);
	ch /= g;
	zn /= g;
	return mp(ch,zn);
}

pair<ll,ll> get(point p1,point p2){
	if (getdist(p1) == 0){
		if (nap.x != 0)
			return norm(p1.x,-nap.x);
		return norm(p1.y,-nap.y);
	}
	if (getdist(p2) == 0){
		if (nap.x != 0)
			return norm(p2.x,-nap.x);
		return norm(p2.y,-nap.y);
	}
	ll a = nap.y;
	ll b = -nap.x;
	//cerr<<b<<endl;
	ll a1 = (p1.y - p2.y);
	ll b1 = (p2.x - p1.x);
	ll c1 = -a1*p1.x-b1*p1.y;

    return norm(c1,a*b1-a1*b);	
}




int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);


  scanf("%d",&n);
  a.resize(n);
  for (int i = 0; i < n; i++)
  	scanf(LLD" "LLD,&a[i].x,&a[i].y);

  scanf(LLD" "LLD,&dx1,&dy1);

  scanf("%d",&m);
  b.resize(m);
  for (int i = 0; i < m; i++)
  	scanf(LLD" "LLD,&b[i].x,&b[i].y);

  scanf(LLD" "LLD,&dx2,&dy2);

  dx1 -= dx2; dy1 -= dy2;

  for (int i = 0; i < m; i++)
  	b[i].x *= -1,b[i].y *= -1;
//  reverse(b.begin(),b.end());

  a = sum(a,b);


  for (int i = 0; i < (int)a.size(); i++)
  	cerr <<"("<<a[i].x<<" "<<a[i].y<<")"<<endl;
  cerr << dx1 <<" "<<dy1<<endl;	

  if (checkin()){
  	assert(false);
  	puts("0/1");
  	return 0;
  }

  if (dx1 == 0 && dy1 == 0){
  	puts("No collision\n");
  	return 0;
  }

  a.pb(a[0]);

  pair<ll,ll> ans = mp(1LL,0LL);

  nap = point(dx1,dy1);
                                

  for (int i = 0; i+1 < (int)a.size(); i++){
  	if (check(a[i],a[i+1])){
  		pair<ll,ll> res = get(a[i],a[i+1]);
  		if (res.first < 0)
  			continue;
  		if (compare(res,ans))
  			ans = res;
  	}
  }
  		


  if (ans.second == 0){
  	puts("No collision\n");
  	return 0;
  }

  assert(gcd(ans.first,ans.second) == 1);
  cout << ans.first << "/"<<ans.second << endl;

  return 0;
}

