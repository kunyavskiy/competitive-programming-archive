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
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

struct razb{
	int sum,p,last;
};

razb r[500000];
int cnt;
int a[15];
int n;
int maxr;
int req[500];

vector<int> rs[41];

void gen(int num){

	for (int i=r[num].last;i<n;i++){
		if (r[num].sum+a[i]>maxr) continue;
		r[cnt].sum=r[num].sum+a[i];
		r[cnt].p=num;
		r[cnt++].last=i;
//		cerr<<r[cnt-1].sum<<endl;
		gen(cnt-1);		
	}
}

int d[500000];
int p[500000];

const int inf=1<<29;

int solve(int r1,int r2){
	int sz1=rs[r1].size();
	int sz2=rs[r2].size();
	if (sz2==0){
		printf("-1\n");
		exit(0);
	}
	if (r1!=r2){
		for (int i=0;i<sz1;i++){
			int v=rs[r1][i];
			p[v]=min(d[v],p[v]);
//			cerr<<v<<endl;
			for (;r[v].p!=-1;v=r[v].p){
				p[r[v].p]=min(p[r[v].p],p[v]+1);
//				cerr<<r[v].p<<endl;
			}
			d[rs[r1][i]]=inf;			
		}	
	//	cerr<<"!!!"<<endl;
	//	cerr<<endl<<endl;
		for (int i=0;i<sz2;i++){
			int v=rs[r2][i];
			int v0=v;
			for (int cnt=0;v!=-1;v=r[v].p,cnt++){
				d[v0]=min(d[v0],p[v]+cnt);
	//			cerr<<v<<" "<<r[v].p<<endl;
			}	
		}
	//	cerr<<"!!!"<<endl;
		for (int i=0;i<sz1;i++){
			int v=rs[r1][i];
			for (;v!=-1;v=r[v].p){
				p[v]=inf;
				//cerr<<v<<endl;
			}
		}
		//cerr<<endl<<endl;
	}
	int ans=inf;
	for (int i=0;i<sz2;i++)
		ans=min(ans,d[rs[r2][i]]);
	return ans;		
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	r[0].sum=0;
	r[0].p=-1;
	r[0].last=0;
	cnt=1;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	sort(a,a+n);
	reverse(a,a+n);
	int m;
	scanf("%d",&m);
	maxr=0;
	for (int i=0;i<m;i++){
		scanf("%d",&req[i]);
		maxr=max(maxr,req[i]);
	}
//	cerr<<maxr<<endl;
	gen(0);
	cerr<<"!!!"<<endl;
//	cerr<<cnt<<endl;
	for (int i=0;i<cnt;i++)
		rs[r[i].sum].pb(i);
	for (int i=0;i<cnt;i++)
		d[i]=p[i]=inf;
	d[0]=0;
	int ans=0;
	for (int i=0;i<m;i++){
		ans=solve(((i==0)?(0):(req[i-1])),req[i]);
/*		for (int j=0;j<cnt;j++){
			assert(p[j]==inf && (r[j].sum==req[i] || d[j]==inf));
		}*/
	//	cerr<<i<<" "<<ans<<endl;
	}
	cout<<ans<<endl;
    return 0;
}