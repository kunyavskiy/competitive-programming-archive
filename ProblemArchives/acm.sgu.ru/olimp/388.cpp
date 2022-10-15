#include <iostream>
#include <iterator>
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

typedef short int sint;


vector<sint> g[15000];
vector<int> c[15000];
vector<sint> back[15000];
int n;
int ans;
char color[15000];

void dfs3(int v,int c){
	if (color[v]!=0)
		return;
	color[v]=c;
	for (int i=0;i<g[v].size();i++)
	dfs3(g[v][i],3-c);
}

void color3(){
	for (int i=0;i<n;i++)
		if (color[i]==0)
		dfs3(i,1);
	for (int i=0;i<n;i++)
		for (int j=0;j<g[i].size();j++)
			if (color[i]==color[g[i][j]]){
				color[i]=3;
				break;
			}
	return;
}
stack<sint> stv;
stack<int> stc;
bool iscik[15000];
bool used[15000];
bool q;


void dfscik(sint v,int p){
	if (used[v]){
		if (!q)	return;
		vector<sint> cik;
		vector<int> ccost;
		//stack<int> tstv=stv,tstc=stc;
		cik.push_back(v);
		ccost.pb(c[v][p]);
		for (;stv.top()!=v;stv.pop()){
			cik.push_back(stv.top());
			ccost.push_back(stc.top());
			stc.pop();
		}
		int mv=1<<30,mpos=-1;
		for (int i=0;i<ccost.size();i++)
			if (ccost[i]<mv){
				mv=ccost[i];
				mpos=i;
			}
		rotate(cik.begin(),cik.begin()+mpos+1,cik.end());
		for (int i=0;i<cik.size();i++){
			iscik[cik[i]]=true;
			color[cik[i]]=i%2+1;
		}
		if (cik.size()%2==1)
			ans+=mv;		
//		copy(cik.begin(),cik.end(),ostream_iterator<int>(cerr," "));
	//	cerr<<" : "<<mv<<endl;
		q=false;
		for (;stv.size()>0;stv.pop());
		for (;stc.size()>0;stc.pop());
		return;
	}
	used[v]=true;
	stv.push(v);
	if (p!=-1)
		stc.push(c[v][p]);
	for (int i=0;i<g[v].size();i++)
		if (i!=p)
			dfscik(g[v][i],back[v][i]);
	if (q){
		stv.pop();
		if (p!=-1) stc.pop();
	}
}


bool root;

void dfs2(sint v,int c){
	if (root)
		c=color[v];
	if (color[v]!=0 && !root)
		return;
	root=false;
	color[v]=c;
	for (int i=0;i<g[v].size();i++)
		dfs2(g[v][i],3-c);	
}

void color2(){
	for (int i=0;i<n;i++)
		if (!used[i]){
			q=true;
			dfscik(i,-1);
		}
	for (int i=0;i<n;i++)
		if (iscik[i]){
			root=true;
			dfs2(i,-1);
		}
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	int k;
	scanf("%d %d",&n,&k);
	for (int i=0;i<n;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		--a;
		back[i].pb(g[a].size());
		back[a].pb(g[i].size());
		g[a].pb(i);
		g[i].pb(a);
		c[i].pb(b);
		c[a].pb(b);
	}
	if (k==1){
		for (int i=0;i<n;i++)
			for (int j=0;j<g[i].size();j++)
				ans+=c[i][j];
		cout<<ans/2<<endl;
		for (int i=0;i<n;i++)
			printf("1 ");
		printf("\n");
		return 0;
	}
	if (k>=3){
		color3();
		cout<<0<<endl;
		for (int i=0;i<n;i++)
		printf("%d ",(int)color[i]);
		printf("\n");
		return 0;
	}
	color2();
	cout<<ans<<endl;
	for (int i=0;i<n;i++)
		printf("%d ",(int)color[i]);
	printf("\n");	
	return 0;
}
