#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

const int MAXN = 310000;
const int MAXLOG = 20;



int t1[MAXLOG][MAXN];
int t2[MAXLOG][MAXN];
pair<int,int> p[MAXN];
int pref[MAXN];
int suff[MAXN];
int epos[MAXN];
int spos[MAXN];
int lg[MAXN];
int n,s,d;

void build(int t[][MAXN],int* a,int n){	
	for (int i = 0; i < n; i++)
		t[0][i] = a[i];
	for (int i = 1; (1<<i) < n; i++)
		for (int j = 0; j < n; j++)
			t[i][j] = max(t[i-1][j],t[i-1][j+(1<<(i-1))]);
}

int get(int t[][MAXN],int l,int r){
//	r++;
	if (l >= r)
		return -(1<<30);
	int lg = ::lg[r-l] -1;
	int mid = r - (1<<lg);
	return max(t[lg][l],t[lg][mid]);
}

int ans[MAXN];
int upd[MAXN];   


int tree[2*MAXN],lst;
int last[MAXN];


void update(int pos,int dlt){
	pos += lst;
	tree[pos] += dlt;
	for (pos/=2;pos;pos/=2)
		tree[pos] = tree[2*pos]+tree[2*pos+1];
}

int get(int v,int l,int r,int L,int R){
	if (r < L || R < l)
		return 0;
	if (L <= l && r <= R)
		return tree[v];
	int ans = get(2*v,l,(l+r)/2,L,R)+get(2*v+1,(l+r)/2+1,r,L,R);
//	cerr << v <<" "<<l <<" "<<r<<" "<<L<<" "<<R<<" : "<<ans<<endl;
	return ans;
}


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
                                       

	scanf("%d %d %d",&n,&s,&d);        
    lg[1] = 1;
	for (int i =2; i< n; i++)
		lg[i] = lg[i-1] + (!(i&(i-1)));
	for (int i = 0; i < n; i++)
		scanf("%d %d",&p[i].first,&p[i].second);

	sort(p,p+n);

	set<int> s;
	int st = 0;

	for (int i = 0; i < n; i++){
		if (i && p[i].first - p[i-1].first > d){
			s.clear();
			st = i;
		}
		s.insert(p[i].second);
		pref[i] = s.size();
		spos[i] = st;
	}

	s.clear();

	for (int i = n-1; i >= 0; --i){
		if (i != n-1 && p[i+1].first - p[i].first > d){
			s.clear();
			st = i;
		}
		s.insert(p[i].second);
		suff[i] = s.size();
		epos[i] = st;
	}

//	for (int i = 0; i < n; i++)
//		cerr << suff[i] <<" "<<pref[i] <<" "<<epos[i] <<" "<<spos[i] << endl;
                                                                                 
	build(t1,pref,n);
	build(t2,suff,n);                                                                                                                                             
	int q;
	scanf("%d",&q);


	vector<pair<pair<int,int>,int> > reqs;

	for (int i = 0; i < q; i++){
		int l,r;
		scanf("%d %d",&l,&r);
		l = lower_bound(p,p+n,mp(l,-(1<<30))) - p;
		r = upper_bound(p,p+n,mp(r,(1<<30))) - p;
		if (l >= r)
			ans[i] = 0;                                         
		else if (spos[l] == spos[r-1])
			reqs.pb(mp(mp(l,r),i));		
		else 
			ans[i] = max(get(t1,epos[l]+1,r),get(t2,l,spos[r-1]));			
		
	}

	sort(reqs.begin(),reqs.end());
	lst = 2;
	for (;lst < n; lst *= 2);

	for (int i = n-1; i>= 0; --i){
		if (last[p[i].second])
			update(last[p[i].second],-1);
		last[p[i].second] = i;
		update(i,1);

		int lf = lower_bound(reqs.begin(),reqs.end(),mp(mp(i,-(1<<30)),-(1<<30))) - reqs.begin();
		int rg = upper_bound(reqs.begin(),reqs.end(),mp(mp(i,(1<<30)),(1<<30))) - reqs.begin();


		for (int j = lf; j < rg; j++) 
			ans[reqs[j].second] = get(1,0,lst-1,i,reqs[j].first.second-1);						
		
	}

	for (int i = 0; i < q; i++)
		printf("%d\n",ans[i]);	
    return 0;
}