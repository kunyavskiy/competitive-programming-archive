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

typedef unsigned int int64;
typedef long double ld;

const int MAXN=21000;



string a[MAXN];
string b[MAXN];
int size[MAXN];
int rorder[MAXN];
pair<string,int> btmp[MAXN];
int64 _hash[MAXN][16];
int64* hash[MAXN];

short int lcp[MAXN];
short int lcs[MAXN];
short int tmp[MAXN];


int comppos;
inline bool comp(const string& a,const string &b){
	return a[comppos] < b[comppos];		
}

int n;

int64 myhash[15];
int64 P[15];


inline void calchash(const string& s,int64* h){
	h[0] = s[0];
	for (int i=1,sz=s.size();i<sz;i++)
		h[i] = h[i-1] + s[i] * P[i];	
}

inline int64 gethash(int64* h,int l,int r){
	return (h[r]-h[l-1])*P[14-r];
}

vector<int> len[15];

int lower_bound(string* a,int l,int r,char c,int i){
	if (a[l][i] >= c)
		return l;
	int mid;
	while (r-l > 1){
		mid = (l+r)>>1;
		if (a[mid][i] < c)
			l=mid;
		else
			r=mid;
	}
	return r;
}

inline int upper_bound(string* a,int l,int r,char c,int i){
	return lower_bound(a,l,r,c+1,i);
}


void solve(string s){
	memset(tmp,0,n*sizeof(short int));
	int l = 0;
	int r = n;
	for (int i=0,sz=s.size();i<sz;i++){
		comppos = i;
		l = lower_bound(a,l,r,s[i],i);
		r = upper_bound(a,l,r,s[i],i);
		tmp[l]++;
		tmp[r]--;
	}
	for (int i=1;i<n;i++)
		tmp[i]+=tmp[i-1];
	for (int i=0;i<n;i++)
		lcp[i]=tmp[i];
	reverse(s.begin(),s.end());
	memset(tmp,0,n*sizeof(short int));
	l = 0;
	r = n;
	for (int i=0,sz=s.size();i<sz;i++){
		comppos = i;
		l = lower_bound(b,l,r,s[i],i);
		r = upper_bound(b,l,r,s[i],i);
		tmp[l]++;
		tmp[r]--;
	}
	for (int i=1;i<n;i++)
		tmp[i]+=tmp[i-1];
	for (int i=0;i<n;i++)
		lcs[rorder[i]]=tmp[i];
	reverse(s.begin(),s.end());
	int pos = 0;
	int cnt = 0;
	calchash(s,myhash);
	int sz= s.size();
	for (int I=0,szl=len[sz-1].size();I<szl;I++){
		int i = len[sz-1][I];
		if (lcp[i] + lcs[i] >= size[i] -1){
			cnt++;
			pos=i;
		}
	}
	for (int I=0,szl=len[sz+1].size();I<szl;I++){
		int i = len[sz+1][I];
		if (lcp[i] + lcs[i] >= sz){
			cnt++;
			pos=i;
		}
	}
	for (int I=0,szl=len[sz].size();I<szl;I++){
		int i = len[sz][I];
		if (lcp[i] + lcs[i] >= sz){
			cnt++;
			pos=i;
		}
		else {
			int lf = lcp[i];
			int rg = sz-lcs[i]-1;
			if ((gethash(myhash,lf,rg-1) == gethash(hash[i],lf+1,rg)) ||
				(gethash(myhash,lf+1,rg) == gethash(hash[i],lf,rg-1))){
					cnt++;
					pos=i;
				}
		}
	}
	printf("%s %d",s.data(),cnt);
	if (cnt == 1)
		printf(" %s\n",string(a[pos].begin(),--a[pos].end()).data());
	else
		printf("\n");
}

char buf[15];

int m;


int main()
{
	freopen("errors.in","r",stdin);
	freopen("errors.out","w",stdout);
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		hash[i] = _hash[i]+1;
	for (int i=0;i<n;i++){
		scanf(" %s ",buf);
		a[i] = buf;
		a[i]+=char(1);
	}
	sort(a,a+n);
	for (int i=0;i<n;i++){
		btmp[i] = mp(string(a[i].rbegin()+1,a[i].rend())+char(1),i);	
	}
	sort(btmp,btmp+n);
	for (int i=0;i<n;i++){
		b[i]=btmp[i].first;
		rorder[i] = btmp[i].second;
	}
	for (int i=0;i<n;i++){
		len[a[i].size()-1].pb(i);
		size[i] = a[i].size();
	}

	
	P[0] = 1;
	for (int i=1;i<15;i++)
		P[i] = P[i-1]*131;
	for (int i=0;i<n;i++)
		calchash(a[i],hash[i]);
	for (int i=0;i<m;i++){
		scanf(" %s ",buf);
		solve(buf);
	}	
	return 0;
}