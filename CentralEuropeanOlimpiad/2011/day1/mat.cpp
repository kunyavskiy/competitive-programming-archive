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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXN = 1100000;


int a[MAXN];
pair<int,int> b[MAXN];
pair<int,int> c[MAXN];
int n,m;


bool cmpsec(const pair<int,int>& a,const pair<int,int>& b){
	return a.second < b.second;
}

bool check(int l){
	sort(b+l,b+l+n);
	volatile bool ans = true;
	for (int i=0;i<n;i++)
		if (b[l+i].second - l != a[i])
			ans = false;
	sort(b+l,b+l+n,cmpsec);
	return ans;
}

vector<int> ans;

int fen[MAXN];

inline void update(int x){
	for (;x<m;x=(x|(x+1)))
		fen[x]++;
//	for (int i=0;i<10;i++)
//		cerr << fen[i] << " \n"[i==9];
}

inline int get(int x){
	int ans = 0;
	for (;x!=-1;x=(x&(x+1))-1)
		ans += fen[x];
	return ans;
}

inline int get(int l,int r){
	return get(r) - get(l-1);
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++){
		scanf("%d",&a[i]);
		--a[i];
		//a[i] = i;
	}
	for (int i=0;i<m;i++){
		scanf("%d",&b[i].first);
//		b[i].first = i;
		b[i].second = i;
		c[i] = b[i];
	}
//	random_shuffle(a,a+n);
//	random_shuffle(b,b+m);
	for (int i=0;i<m;i++){
		b[i].second = i;
		c[i] = b[i];
	}
	sort(c,c+m);
	for (int i=0;i<m;i++){		
		int x = c[i].second;
		update(x);
		if (x - a[0] < 0)
			continue;
		if (x + n - a[0] > m)
			continue;
//		cerr <<"!!!"<<x<<" "<<get(x-a[0],x+n-a[0]-1)<<endl;
		if (get(x-a[0],x+n-a[0]-1) != 1)
			continue;
//		cerr << x -a[0] << endl;
		if (check(x-a[0]))
			ans.pb(x-a[0]+1);		
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",int(ans.size()));
	for (int i=0,sz=ans.size();i<sz;i++)
		printf("%d ",ans[i]);				
	printf("\n");
	return 0;
}