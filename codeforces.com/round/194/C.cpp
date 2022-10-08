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

#define TASKNAME "C"

typedef long long ll;
typedef long double ld;

char s[10000];
int m;

set<string> used;

int len[11000];

void print(const string& s){
	assert(s.size() == 8);
	if (used.find(s) != used.end())
		return;
	m--;
	used.insert(s);
	puts(s.data());
	if (m == 0)
		exit(0);
	#ifdef LOCAL
		if (m % 10000 == 0)
			TIMESTAMPf("%d",m);
	#endif
}

vector<int> cur;

bool havezero(int x,int cnt){
	for (int i = 0; i < cnt; i++){
		if (x % 10 == 0) return true;
		x /= 10;
	}
	return false;
}

void printv(int tot){
	do {
		int ptr = 0;
		for (int i = 0; i < (int)cur.size(); i++){
			sprintf(s+ptr,"%d",cur[i]);
			ptr += len[cur[i]];
		}
		assert(tot == ptr);
		if (ptr == 8){
			print(s);
			continue;
		}
		for (int i = 0; ; i++){
			if (!havezero(i, 8 - ptr)) continue;
			sprintf(s+ptr,"%0*d", 8 - ptr, i);

			if (strlen(s) > 8) break;
			print(s);
		}
	} while (next_permutation(cur.begin(), cur.end()));
}

int n0;

void gen(int n,int tot){      
	if (n == 0){
		printv(tot);
		return;
	}
	int last = (cur.empty()? 0 : cur.back());
	for (int i = last; i <= n && tot + len[i] <= 8; i++){
		cur.pb(i);
		gen(n-i, tot+len[i]);
		cur.pop_back();
	}
	char temp[10];
	vector<int> tcur = cur;
	if (tot <= 3){
		int ptr = 0;
		do {
			sprintf(s+ptr,"%d",cur[i]);
			ptr += len[cur[i]];    

		} while (next_permutation(cur.begin(), cur.end()));

    }
}


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	int n;
    scanf("%d %d",&n,&m);  
    n0 = n;
    for (int i = 0; i < 10; i++)
    	len[i] = 1;
    for (int i = 10; i <= 10000; i++)
    	len[i] = len[i/10] + 1;
    gen(n,0);
    assert(false);              
    TIMESTAMP(end);
    return 0;
}