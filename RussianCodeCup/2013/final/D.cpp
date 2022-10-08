//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

#ifdef LOCAL
static struct __timestamper {
	~__timestamper(){
		TIMESTAMP(end);
	}
} __TIMESTAMPER;
#endif

typedef long long ll;
typedef long double ld;

const int inf = 1e9;

const int MAXN = 1010;

char s[MAXN][MAXN];
int d[2][MAXN][MAXN];
int add[MAXN][MAXN];
int n,m;

queue<int> qx,qy;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

void bfs(int did){
	while (!qx.empty()){
		int x = qx.front();qx.pop();
		int y = qy.front();qy.pop();
		if (s[x][y] == 'W') continue;
		for (int i = 0; i < 4; i++){
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (!(0 <= nx && nx < n)) continue;
			if (!(0 <= ny && ny < m)) continue;
			if (d[did][nx][ny] > d[did][x][y] + 1){
				d[did][nx][ny] = d[did][x][y] + 1;
				qx.push(nx);
				qy.push(ny); 
			}
		}
	}
}



void solve(){
	scanf("%d%d",&n,&m);
	for (int i = 0; i < n; i++)
		scanf("%s",s[i]);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			d[0][i][j] = d[1][i][j] = inf;
	d[0][0][0] = 0;
	qx.push(0); qy.push(0);
	bfs(0);

	d[1][n-1][m-1] = 0;
	qx.push(n-1); qy.push(m-1);
	bfs(1);

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (s[i][j] == 'W'){
				add[i][j] = 2;
        		for (int dir = 0; dir < 4; dir++){
        			int nx = i + dx[dir];
        			int ny = j + dy[dir];
        			if (!(0 <= nx && nx < n)) continue;
        			if (!(0 <= ny && ny < m)) continue;
        			if (s[nx][ny] == 'W') {
        				add[i][j] = 1;
        				continue;
        			}
        		}
			}


	int addv = 0;
	vector< pair<int,int>  > v;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (s[i][j] == 'W'){
				addv += add[i][j];
				v.pb(mp(d[1][i][j] - add[i][j],d[1][i][j]));
			}

	sort(v.begin(), v.end());
	v.pb(mp((int)1e9,(int)1e9));

	int tot = 0;
	ll lnum, ldnum;
	lnum = ldnum = -1;
	for (int i = 0; i+1 < (int)v.size(); i++){
		tot += v[i].second;
		addv -= v[i].second - v[i].first;
		ll cnum = tot + addv;
		ll cdnum = (i+1);
		if (v[i].first * cdnum <= cnum && v[i+1].first * cdnum > cnum){        
			if (lnum == -1 || lnum * cdnum > ldnum * cnum){
				lnum = cnum;
				ldnum = cdnum;
			}
		}
	}         	
//	eprintf("!!"LLD" "LLD"\n",lnum, ldnum);
	assert(v.size() == 1 || lnum != -1);
	{
		ll g = __gcd(lnum, ldnum);
		lnum /= g;
		ldnum /= g;
	}

//	eprintf("!!"LLD" "LLD"\n",lnum, ldnum);

	ll ansnum = d[0][n-1][m-1];
	ll ansdnum = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (s[i][j] == 'W'){
				ll cnum = lnum + d[0][i][j] * ldnum;
				ll cdnum = ldnum;
				if (ansnum * cdnum > ansdnum * cnum){
					ansnum = cnum;
					ansdnum = cdnum;
				}
			}

	assert(__gcd(ansnum, ansdnum) == 1);
	printf(LLD"/"LLD"\n", ansnum, ansdnum);
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int t;
  	scanf("%d",&t);
  	while (t-->0)
  		solve();
      
  return 0;
}