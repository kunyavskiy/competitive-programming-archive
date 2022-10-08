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

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

int m;
struct Item {
	vector<pair<int, int> > v;
	int len;
	pair<int,int>& operator[](int x){ return v[x];}
	const pair<int,int>& operator[](int x) const{ return v[x];}
	Item(){}
	Item(char* s) {
		len = 1;
		v.resize(m);
		for (int i = 0; i < m; i++) {
			if (s[i] == '^')
				v[i] = mp(i, 1);
			else if (s[i] == '>') {
				int j = i;
				while (j < m && s[j] == '>') j++;
				if (j == m) v[i] = mp(m, 0);
				else if (s[j] == '<') v[i] = mp(-2, -2);
				else if (s[j] == '^') v[i] = mp(j, 1);
				else assert(false);
			} else if (s[i] == '<') {
				int j = i;
				while (j >= 0 && s[j] == '<') j--;
				if (j == -1) v[i] = mp(-1, 0);
				else if (s[j] == '>') v[i] = mp(-2, -2);
				else if (s[j] == '^') v[i] = mp(j, 1);
				else assert(false);
			}
		}
	}
};

Item merge(Item a, Item b) {
	Item res;
	res.v.resize(m);
	res.len = a.len + b.len;
	for (int i = 0; i < m; i++) {
		if (a[i].first == -2)
			res[i] = a[i];
		else if (a[i].first == -1 || a[i].first == m) {
			res[i] = a[i];    
		} else {
			res[i] = b[a[i].first];
			res[i].second += a.len;
		}
	}
	return res;
}

const int MAXN = 100010;
const int MAXSZ = MAXN * 4;

Item tree[MAXSZ];
int down[MAXSZ];
char s[MAXN][12];

int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif

 	int n, q;
    scanf("%d%d%d",&n,&m,&q);
    for (int i = 0; i < n; i++)
    	scanf("%s", s[i]);
    int lst = 2;
    while (lst < n) lst *= 2;
    while (n < lst) {
	    for (int i = 0; i < m; i++)
    		s[n][i] = '^';
    	n++;
    }
    for (int i = 0; i < n; i++) {
    	tree[i + lst] = Item(s[i]);
    	down[i + lst] = i;
    }
    for (int i = lst - 1; i > 0; i--) {
    	tree[i] = merge(tree[2*i+1], tree[2*i]);
    	down[i] = down[2*i+1];
    }                                                       
    /*for (int i = 1; i < 2*lst; i++, eprintf("\n")) {	
    	eprintf("%d:", i);
    	for (int j = 0; j < m; j++)
    		eprintf("(%2d, %2d)", tree[i][j].first, tree[i][j].second);
    }*/
    for (int i = 0; i < q; i++) {
    	char ty;
    	scanf(" %c",&ty);
    	if (ty == 'C') {
    		int x, y; char to;
    		scanf("%d %d %c", &x,&y,&to);
    		x--,y--;
    		s[x][y] = to;
    		tree[x + lst] = Item(s[x]);
    		x += lst;
    		while (x /= 2) {    
		    	tree[x] = merge(tree[2*x+1], tree[2*x]);
    		}
    	} else {
    		int x, y;
    		scanf("%d%d",&x,&y);
    		--x, --y;
    		x += lst;
    		pair<int, int> res;
    		while (true) {
//    			eprintf("%d %d down[x] =%d (%d, %d)\n", x, y, down[x], tree[x][y].first, tree[x][y].second);
   				if (tree[x][y].first == -2) {
   					res = mp(-2, -2);
   					break;
   				}
    			if ((x & (x - 1)) == 0) {
    			    res = tree[x][y];
   			    	res.second = down[x] - res.second;
    			    break;
    			}
    			if ((x & 1) == 1) {
    				x /= 2;
    			} else {
    				if (tree[x][y].first == -1 || tree[x][y].first == m) {
	    			    res = tree[x][y];
    				    if (res.first == 0 || res.first == m)
	    			    	res.second = down[x] - res.second;
    					break;
    				}
    				y = tree[x][y].first;
    			    x--;
    			    x /= 2;
    			}
    		}
    		printf("%d %d\n", res.second + 1, res.first + 1);
    	}
    }
      
    return 0;
}