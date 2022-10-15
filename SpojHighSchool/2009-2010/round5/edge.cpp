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
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define fileinout
using namespace std;

const int maxn=16000; // это надо увеличить если что

// куча кода который тебе не нужен

struct myvec{
	int sz;
	int* val;
	int szmem;
	inline myvec(){sz=szmem=0;val=NULL;};
	inline myvec(int SZ){
		sz=SZ;
		val=new int[sz];
		for (int i=0;i<sz;i++)
			val[i]=0;
		szmem=sz;
	}
	inline void push_back(int x){
		if (sz+1>szmem){
			int* tmp;
			tmp=new int[max(min(2*szmem,maxn),1)];
			memcpy(tmp,val,szmem*sizeof(int));
			delete[] val;
			szmem=max(min(szmem*2,maxn),1);
			val=tmp;
		}
		val[sz++]=x;
	}
	inline 	int size() const{
		return sz;
	}
	inline 	~myvec(){
		delete[] val;
		val=NULL;
	}
	inline 	void clear(){
		sz=szmem=0;
		delete[] val;
		val=NULL;
	}
	inline 	int* begin() const{
		return val;
	}
	inline 	int* end() const{
		return val+sz;
	}
	inline 	int& operator[](int ind){
		return val[ind];
	}
};


myvec  g[maxn];  
int per[maxn];   
int used[maxn];  
int z[maxn];
bool bef[maxn];
int kol[maxn];
int n;
int m;

bool dcomp(int a,int b){
	return g[a].size()>g[b].size();
}

inline void init(bool read=false){

	if (read){
		for (int i=0;i<n;i++)
			g[i].clear();
		scanf("%d",&n);
	}
	for (int i=0;i<n;i++)
		used[i]=kol[i]=z[i]=0;
	if (read){
		m=0;
		for (;;m++){
			int a,b;
			scanf("%d %d",&a,&b);
			if (a==0 && b==0)
				break;
			g[a].pb(b);
			g[b].pb(a);
			z[a]++;
			z[b]++;
		}
		for (int i=0;i<n;i++)
			per[i]=i;
	}
	else{
		for (int i=0;i<n;i++)
			z[i]=g[i].size();	
	}
	return;
}

inline int randomize(){
	for (int i=0;i<n;i++)
		random_shuffle(g[i].begin(),g[i].end());
	return rand()%n;
}

const int inf=1<<25;

int bal;
int maxbal;
int ansbal;
char string_buf[50];
string tans;
string ans;

inline void addagent(int v){
	string_buf[0]=0;
	sprintf(string_buf,"a %d\n",v);
	tans+=string_buf;
	bal++;
	maxbal=max(maxbal,bal);
	kol[v]++;
	return;
}

inline void remagent(int v){
	string_buf[0]=0;
	sprintf(string_buf,"r %d\n",v);
	tans+=string_buf;
	bal--;
	kol[v]--;
	return;
}

inline void moveagent(int v,int v2){
	string_buf[0]=0;
	sprintf(string_buf,"m %d %d\n",v,v2);
	tans+=string_buf;
	kol[v]--;
	kol[v2]++;
	return;
}

inline void endgraf(){
	tans=(((tans+'d')+'\n')+'\n');
	return;
}


namespace dfs_solution{

void solve(int v,int par){
	if (used[v]!=0)
		return;
	int sz=g[v].size();
	used[v]=1;
	if (par==-1)
		addagent(v);
	else{
		for (int i=0;i<sz;i++)
			if (z[g[v][i]]==1 && used[g[v][i]]==1)
			{
				moveagent(g[v][i],v); 
				z[v]--;
				z[g[v][i]]--;
			}
		if (kol[v]==0){
			z[par]--;
			z[v]--;
			addagent(par);
			moveagent(par,v);
		}
		else if (z[par]!=0)
			{
				if (kol[v]==1 && z[v]!=1)
					addagent(v);
				moveagent(v,par);
				remagent(par);
				z[par]--;
				z[v]--;
			}
		while(kol[v]>1)
			remagent(v);			
	}
	if (z[v]==0){
		if (kol[v])
			remagent(v);
		used[v]=2;
		return;	
	}
	int kolu1=0;
	int kolu0=0;
	for (int i=0;i<sz;i++)
		if (used[g[v][i]]==1 && g[v][i]!=par && z[g[v][i]]!=0)
			kolu1++;
		else if (used[g[v][i]]==0)
			kolu0++;
	if (kolu0==0 && kolu1==0){
		remagent(v);
		used[v]=2;
		return;
	}
	if (kolu0==0 && kolu1==1){
		for (int i=0;i<sz;i++)
			if (used[g[v][i]]==1 && g[v][i]!=par && z[g[v][i]]!=0){
				z[v]--;
				z[g[v][i]]--;
				moveagent(v,g[v][i]);
				remagent(g[v][i]);
				used[v]=2;
				return;
			}
	}	
	if (kolu1!=0){
		addagent(v);
		for (int i=0;i<sz;i++)
			if (used[g[v][i]]==1 && g[v][i]!=par && z[g[v][i]]!=0){
				z[v]--;
				z[g[v][i]]--;
				moveagent(v,g[v][i]);
				moveagent(g[v][i],v);
			}
		remagent(v);
	}
	for (int i=0;i<sz;i++)
		if (used[g[v][i]]==0)
			solve(g[v][i],v);
	used[v]=2;
	if (kol[v]!=0)
		remagent(v);
	return;
}

}


namespace bfs_solution{

int its;

bool zusedcmp(int a,int b){
	if (used[a]==1)
		return false;
	if (used[b]==1)
		return true;
	return z[a]<z[b];		
}

void solve(){
	init();
	int mind=0;
	for (int i=0;i<n;i++)
		if (g[i].size()<g[mind].size())
			mind=i;
	set<pair<int,int> > s;
	s.insert(mp(z[mind],mind));
	for (;!s.empty();){
		int fr;
		fr=s.begin()->second;
		s.erase(s.begin());
		used[fr]=1;
		int sz=g[fr].size();
		sort(g[fr].begin(),g[fr].end(),zusedcmp);
		for (int i=0;i<sz;i++){
			if (used[g[fr][i]])
				break;
			int to=g[fr][i];
			if (i==sz-1 || used[g[fr][i+1]]==1){
				while (kol[fr]==0)
					addagent(fr);
				moveagent(fr,to);
				if (kol[to]==2)
					remagent(to);
				s.erase(mp(z[to],to));
				z[to]--;
				z[fr]--;
				s.insert(mp(z[to],to));
				while(kol[fr]!=0)
					remagent(fr);
				break;
			}
			if (z[to]==1){
				if (g[to].size()!=1)
					{
						moveagent(to,fr);
						if (kol[fr]!=1 || z[fr]==1)
							remagent(fr);
						s.erase(mp(1,to));
						z[fr]--;
						continue;
					}
				while ((z[fr]!=1 && kol[fr]==1) || (kol[fr]==0))
					addagent(fr);
				moveagent(fr,to);
				remagent(to);
				s.erase(mp(1,to));
				z[fr]--;
				continue;
			}
			s.erase(mp(z[to],to));
			z[to]--;
			while ((z[fr]!=1 && kol[fr]==1) || (kol[fr]==0))
				addagent(fr);
			z[fr]--;
			moveagent(fr,to);
			if (kol[to]==2)
				remagent(to);
			s.insert(mp(z[to],to));
		}
		while (kol[fr]!=0)
			remagent(fr);
	}
	endgraf();
	ansbal=maxbal;
	ans=tans;
}

};

namespace before_solution{

int d[maxn];

void solve(){
	init();
	memset(bef,false,sizeof(bef));
	set<pair<int,int> > tmp;
	set<pair<int,int> > zs;
	queue<int> q;
	tmp.clear();
	for (int i=0;i<n;i++)
		tmp.insert(mp(0,i));
	memset(d,0,sizeof(d));	
	tans="";
	bal=0;
	maxbal=0;		
	for (int i=0;i<n;i++){
		int v;
		if (!q.empty()){
			v=q.front();
			q.pop();
			tmp.erase(mp(d[v],v));
		}
		else if (zs.size()){
			v=zs.begin()->second;
			zs.erase(zs.begin());
			int sz=g[v].size();
			for (int j=0;j<sz;j++)
				if (!bef[g[v][j]])
						q.push(g[v][j]);
			i--;
			continue;
		}
		else
		{
			v=(--tmp.end())->second;
			tmp.erase(--tmp.end());
		}
		int sz=g[v].size();
		bef[v]=true;
		for (int i=0;i<sz;i++)
			{
				int to=g[v][i];
				if (bef[to]==false)
				{
					tmp.erase(mp(d[to],to));
					d[to]++;
					tmp.insert(mp(d[to],to));
					continue;
				}
				if (z[to]==1)
					{
						if (kol[to]==0)
							addagent(to);
						moveagent(to,v);
						z[to]--;
						zs.erase(mp(1,to));
						z[v]--;
						if (kol[v]==2)
							remagent(v);
					}
			}		
		for (int i=0;i<sz;i++)
			{	
				int to=g[v][i];
				if (bef[to]==false)
					continue;
				if (z[to]==0)
					continue;
				for (;(z[v]!=1 && kol[v]==1) || kol[v]==0;)
					addagent(v);
				moveagent(v,to);
				if (kol[to]!=1)
					remagent(to);
				zs.erase(mp(z[to],to));
				z[to]--;
				zs.insert(mp(z[to],to));
				z[v]--;
			}
		while (kol[v]>1)
			remagent(v);
		if (z[v]==0 && kol[v]!=0)
			remagent(v);
		else 
			zs.insert(mp(z[v],v));
	}
	endgraf();
	if (maxbal<ansbal){
		ansbal=maxbal;
		ans=tans;
	} 
}

}

// дальше нужен


void solve(){
	init(true);
	ansbal=inf;
	tans="";
	bfs_solution::solve();	
	int tlit=20; //если тл  то уменьшаь вот это. а если сильно много времени отсанется то можно это и увеличить.
	for (int i=0;i<n && tlit;i++)
		if (g[i].size()==1)
		{
			init();
			tans="";
			bal=0;
			maxbal=0;
			int a=i;
			dfs_solution::solve(a,-1);
			endgraf();
			if (maxbal<ansbal){
				ansbal=maxbal;
				ans=tans;
			}			
			tlit--;
			break;
		}
	int maxd=0;
	for (int i=0;i<n;i++)
		if (g[i].size()>g[maxd].size())
			maxd=i;	
	init();
	tans="";
	bal=0;
	maxbal=0;
	int a=maxd;
	dfs_solution::solve(a,-1);
	endgraf();
	if (maxbal<ansbal){
		ansbal=maxbal;
		ans=tans;
	}			
	tlit--;
	for (int i=0;i<tlit;i++){
		init();
		tans="";
		bal=0;
		maxbal=0;
		int a;
		a=rand()%n;
		dfs_solution::solve(a,-1);
		endgraf();
		if (maxbal<ansbal){
			ansbal=maxbal;
			ans=tans;
		}                   
	}
	for (int i=0;i<5;i++) // или вот эту циферку 5. и это тоже можно иногда увеличить.
	{
		randomize();
		before_solution::solve();
	}
	printf("%s",ans.data());
}




long long time() // от этого можно срандиться или ставить отсечение по времени если у тебя получится и не косяк.
{
	asm("rdtsc");  
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  srand(time()); // вот этот сранд с ним можно сдать много-мнго раз. а еще его можно поподгонять.
  int i;
  n=0;
  scanf("%d",&i);
  for (;i;--i)
  	solve();
  return 0;
}

// и коменты стоит убрать если не косяк

