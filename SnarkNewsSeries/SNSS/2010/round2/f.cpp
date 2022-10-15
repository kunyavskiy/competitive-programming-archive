#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "F"

using namespace std;

typedef long long int64;
typedef long double ld;

pair<int,int> evs[10000];
int ptr;
ld ans=0;
int p[10000];
bool used[10000];
int pl[10000];
int sum;
ld len[10000];

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	int n,m,kol,K;
	scanf("%d %d %d %d",&n,&m,&kol,&K);
	--K;
	for (int i=0;i<n-1;i++)
		cin>>len[i];
	for (int i=0;i<m;i++)
		cin>>p[i];
	for (int i=0;i<kol;i++)
		{
			int l,r;
			scanf("%d %d",&l,&r);
			--l;--r;
			evs[ptr++]=mp(l,i);
			evs[ptr++]=mp(r,i);
		}	
	memset(pl,-1,sizeof(pl));
	sort(evs,evs+ptr);
	int pt=0;
	ans=0;
	for (int i=0;i<n-1;i++)
	   	{
			int tmp=pt;
			for (;pt<ptr && evs[pt].first==i;++pt)
		       if (pl[evs[pt].second]!=-1)
					{
					//	cerr<<"OUT "<<evs[pt].second<<endl;
						sum-=p[pl[evs[pt].second]];
						used[pl[evs[pt].second]]=false;
						pl[evs[pt].second]=-2;
					}
			for (int j=tmp;j<pt;j++)
				if (pl[evs[j].second]==-1){
					int bst=-1;
					for (int k=0;k<m;k++)
						if (!used[k] && (bst==-1 || p[bst]<p[k]))
							bst=k;
					if (bst==-1) continue;
					//cerr<<"IN "<<evs[j].second<<endl;
					sum+=p[bst];
					used[bst]=true;
					pl[evs[j].second]=bst;					
				}
			if (pl[K]>-1)
				ans+=p[pl[K]]*1.0/sum * len[i];
			//cerr<<pl[K]<<" "<<ans<<" "<<sum<<endl;
		}                             
	cout.precision(10);
	cout<<fixed<<ans<<endl;
	return 0;
}                                