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

#define taskname "d"

const int inf = 1000000000;
const ld eps = 1e-9;


pair<int,int> a[1100];
int up[1100];
int cnt;

vector<pair<int,int> > ans;

void solve(int l,int r){
    if (l >= r-1)
    	return;

    int mid = (l+r)/2;

    solve(l,mid);
    solve(mid,r);

    int ptr1 = l;
    int ptr2 = mid;



    for (int i = l; i < mid; i++)
    	ans.pb(mp(a[i].second,up[i]=cnt++));

    for (int i = mid; i < r; i++)
    	ans.pb(mp(up[i]=cnt++,a[i].second));

    for (int i = mid-1; i > l; i--)
    	ans.pb(mp(up[i],up[i-1]));

    for (int i = r-1; i > mid; i--)
    	ans.pb(mp(up[i],up[i-1]));


    while (ptr1 < mid && ptr2 < r){
    	if (a[ptr1].first < a[ptr2].first)
    		ptr1++;
    	else {
    		ans.pb(mp(up[ptr1],up[ptr2]));
    		ptr2++;
    	}	    	
    }

    inplace_merge(a+l,a+mid,a+r);
}

int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  int n;
  scanf("%d",&n);
  for (int i = 0; i < n; i++)
  	scanf("%d",&a[i].first),a[i].second = i;
  cnt = n;  
  solve(0,n);

  printf("%d %d\n",cnt,(int)ans.size());

  for (int i = 0; i < (int)ans.size(); i++)
  	printf("%d %d\n",ans[i].first+1,ans[i].second+1);
  return 0;
}

