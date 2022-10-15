#include <iostream>
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

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "1941"

typedef long long ll;
typedef long double ld;

map<string,int> x;

string s;

char t[5];

int ncnt[10000];
int cnt[10000];
int ok;


int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif
  	getline(cin,s);
	stringstream str(s);

	int ptr = 0;
	int sz = 0;

	while (str >> t){
		sz++;
		if (x.find(t) == x.end())
		    x[t] = ptr++;
		ncnt[x[t]]++;
	}
	int ans = 0;

	queue<int> q;
	while (scanf(" %s",t) == 1){
		if (x.find(t) == x.end())
			q.push(-1);
		else {
			int tmp = x[t];
			if (cnt[tmp] == ncnt[tmp]) ok--;
			cnt[tmp]++;
			if (cnt[tmp] == ncnt[tmp]) ok++;
			q.push(tmp);
		} 

		if ((int)q.size() > sz){
			int tmp = q.front();
			q.pop();                        
			if (tmp != -1){
				if (cnt[tmp] == ncnt[tmp]) ok--;
				cnt[tmp]--;
				if (cnt[tmp] == ncnt[tmp]) ok++;
			}
		}

		if (ok == ptr)
			ans++;
			
	}

	cout << ans << endl;
    return 0;
}