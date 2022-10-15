#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstdio>
#include <cstdlib>
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

const string TASKNAME = "memory";
const string INFILE = TASKNAME + ".in";
const string OUTFILE = TASKNAME + ".out";\

typedef unsigned int uint;

struct segment{
	uint l,r;
	segment(){
	};
	segment(int L,int R){
		l=L,r=R;
	}
	bool operator<(const segment& rp) const{
		if (r-l != rp.r - rp.l)
			return r - l < rp.r - rp.l;
		return l < rp.l;
	}
};

map<uint,uint> l;
map<uint,uint> r;
set<segment> s;

segment ans[110000];

segment getmem(int size){
	set<segment>::iterator iter = s.lower_bound(segment(0,size-1));
	if (iter == s.end()){
		printf("-1\n");
		return segment(0,0);
	}
	segment seg=*iter;
	segment ans(seg.l,seg.l+size-1);
	s.erase(iter);
	l.erase(seg.l);
	r.erase(seg.r);
	seg.l += size;
	if (seg.l <= seg.r){
		s.insert(seg);
		l[seg.l] = seg.r;
		r[seg.r] = seg.l;
	}
	printf("%d\n",ans.l);
	return ans;
}

void cleanmem(segment seg){
	if (seg.r == 0)
		return;
	if (l.find(seg.r + 1) != l.end()){
		int tmp = l[seg.r+1];
		l.erase(seg.r+1);
		s.erase(segment(seg.r+1,tmp));
		seg.r = tmp;
	}
	if (r.find(seg.l - 1) != r.end()){
		int tmp = r[seg.l - 1];
		r.erase(seg.l - 1);
		s.erase(segment(tmp,seg.l-1));
		seg.l = tmp;
	}
	s.insert(seg);
	l[seg.l] = seg.r;
	r[seg.r] = seg.l;
}


int main()
{
//	ld TIME = clock();
    freopen(INFILE.data(),"r",stdin);
    freopen(OUTFILE.data(),"w",stdout);
	int n;
	scanf("%d",&n);
	s.insert(segment(1,n));
	l[1] = n;
	r[n] = 1;
	int q;
	scanf("%d",&q);
	for (int i=1;i<=q;i++){
		int r;
		scanf("%d",&r);
		if (r > 0)
			ans[i]=getmem(r);
		else
			cleanmem(ans[-r]);
	}  
//	cerr << (clock()-TIME)/CLOCKS_PER_SEC << endl;
    return 0;
}