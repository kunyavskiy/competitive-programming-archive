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

typedef long long ll;
typedef long double ld;

const int MAXN = 51000;

char s[MAXN];
bool used[MAXN];

void compress(){
	int ptr = 0;
	for (int i = 0; s[i]; i++)
		if (!used[i]) {
			s[ptr++] = s[i];
		}
	for (int i = 0; i < ptr; i++)
		used[i] = false;
	s[ptr] = 0;
}

vector<int> best;
int bestlen;

void update(int from,int len){
	eprintf("FOUND : %s\n",string(s+from,s+from+2*len).data());
	if (len < bestlen || bestlen == -1){
		bestlen = len;
		best.clear();
	}
	if (len == bestlen)
		best.pb(from);
}

vector<int> zfunc(const string& s){
	int n = s.size();
	vector<int> z(n);
	int l, r;
	l = r = 0;
	z[0] = s.size();
	for (int i = 1; i < n; ++i) {
		if (i <= r)
			z[i] = min (r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] -1 > r) {
			l = i;
			r = i+z[i]-1;
		}
	}
	for (int i = 0; i < n; i++)
		assert(string(s.begin(),s.begin()+z[i]) == string(s.begin()+i,s.begin()+i+z[i]));
	return z;
}

string reversed(const string& s){
	string temp = s;
	reverse(temp.begin(),temp.end());
	return temp;
}

int getif(vector<int>& v,int id){
	if ((int)v.size() <= id) return 0;
	return v[id];
}

void updateval(int l,int mid,int r){
	eprintf("%s\n",string(s+l,s+mid).data());
	eprintf("%s\n",string(s+mid,s+r).data());
	int llen = mid - l;
	int rlen = r - mid;
	vector<int> zlr = zfunc(string(s+l,s+mid) + '$' + string(s+mid,s+r));
	vector<int> zrl = zfunc(string(s+mid,s+r) + '$' + string(s+l,s+mid));
	vector<int> zlrev = zfunc(reversed(string(s+l,s+mid)));
	vector<int> zrrev = zfunc(reversed(string(s+mid,s+r)));
	for (int i = 0; i < mid; i++)
		if (i + getif(zrl,rlen + 1 + i) >= mid)
			update(i,mid-i);

	for (int i = 1; i <= mid - l; i++){
		eprintf("!!! %d\n",bestlen);
		if (bestlen != -1 && i > bestlen) continue;
		int klft = getif(zlrev,i - 1);
		int krt = getif(zrl,rlen + i);
		eprintf("%d %d %d\n",i,klft,krt);
		for (int j = i - klft; j <= krt; j++)
			update((mid - i)-(i-j),i);
	}
	for (int i = 1; i <= mid - l; i++){
		if (bestlen == -1 || i > bestlen) continue;
		int klft = getif(zrrev,i - 1);
		int krt = getif(zlr,llen + i);
		for (int j = i - klft; j <= krt; j++)
			update((mid + i)-(i-j),i);
	}
}


void solve(int l,int r){
	if (r - l <= 1) return;
	int mid = (l+r)/2;
	solve(l,mid);
	solve(mid,r);
	updateval(l,mid,r);
}



int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	gets(s);

  	bestlen = -1;
  	updateval(1,3,7);
  	exit(0);

  	while (true){
  		bestlen = -1;
  		best.clear();
  		solve(0,strlen(s));
  		if (bestlen == -1)
  			break;
  		sort(best.begin(),best.end());	
  		for (int i = 0; i < (int)best.size(); i++){
  			if (!used[best[i]])
  				for (int j = 0; j < bestlen; j++)
  					used[best[i] + j] = true;
  		}
		compress();
  	}

  	puts(s);
      
    TIMESTAMP(end);
    return 0;
}