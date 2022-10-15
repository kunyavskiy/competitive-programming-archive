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

#define TASKNAME "HOB2"

typedef long long ll;
typedef long double ld;


const int MAXN = 4000000;

int start[MAXN];
int inconv[MAXN];
int len[MAXN];
int ans[MAXN];
int id[MAXN];

void solve(){
	int r,n;
	scanf("%d %d",&r,&n);
	memset(id,-1,sizeof(int)*r);

	int ptr = 0;

	for (int i = 0; i < n; i++){
		scanf("%d %d",&start[i],&inconv[i]);
//		cerr << start[i] <<" "<<inconv[i] << " "<<i <<" "<<r << endl;
		if (inconv[i] == r){
			assert(id[ptr] != -1);
			ans[i] = ptr;
			len[i] = 1;
		} else {
			ans[i] = (ptr - inconv[i] + r) % r;
			len[i] = 31415926;
			assert(inconv[i] == 0 || id[ans[i]] != -1);
			len[id[ptr]] = start[i] - start[id[ptr]];
			id[ptr] = i;
			++ptr;
			if (ptr == r) ptr = 0;
		}
	}

	for (int i = 0; i < n; i++)
		printf("%d %d\n",ans[i],len[i]);
	#ifdef LOCAL
		printf("\n");
	#endif
	return;
}

int main(){
  #ifdef LOCAL
    freopen(TASKNAME".in","r",stdin);
    freopen(TASKNAME".out","w",stdout);
  #endif

  int t;
  scanf("%d",&t);
  while (t-->0){
//  	cerr <<"!!"<<endl;
  	solve();
  } 

      
  return 0;
}