#define NDEBUG
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

typedef vector<vector<bool> > graf;


void dfs(int v,const graf& g,bool root,vector<int>& comp,int* used,bool one=false){

	if (used[v]==1 || (used[v]==2 && !root)){
		if (used[v]==2){
			comp.pb(v);
		}
		return;
	}
	comp.pb(v);
	if (used[v]==0)
		used[v]=1;
	for (int i=0;i<g[0].size();i++)
		if (g[v][i]){
			dfs(i,g,false,comp,used);
			if (root && comp.size()>=2 && one)
				break;
		}
	return;
}

graf gen(const graf& g,vector<int> v,int& s,int& t,int* used){
	s=v[0];
	bool sq,tq;
	sq=tq=0;
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	int n=v.size();
	for (int i=0;i<n;i++)
		if (used[v[i]]==2 && v[i]!=s)
			t=v[i];
	graf res;
	res.resize(n);
	for (int i=0;i<n;i++){
		res[i].resize(n);
		if (!sq && v[i]==s){
			s=i;sq=true;
		}
		if (!tq && v[i]==t){
			t=i;tq=true;
		}
		for (int j=0;j<n;j++)
			res[i][j]=g[v[i]][v[j]];
	}
	return res;
}

int tin[50];
int tup[50];
int counter=0;
void sochl(int v,const graf& g,vector<int>& points,int p,bool root,int* used){

	if (used[v])
		return;

	++counter;
	tin[v]=tup[v]=counter;
	int n=g.size();
	used[v]=1;
	int pot=0;
	bool q=false;
	for (int i=0;i<n;i++)
		{
			if (g[v][i]==false)
				continue;
			if (i==p)
					continue;
			if (used[i])
				tup[v]=min(tup[v],tin[i]);
			else{
				sochl(i,g,points,v,false,used);
				tup[v]=min(tup[v],tup[i]);
				if (tup[i]>=tin[v])
					q=true;
				++pot;
				if (root)
					break;
			}

		}
		
	if (!root && q)
		points.pb(v);
}

ostream& operator<<(ostream& os,const graf& g){
	int n=g.size();
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			os<<g[i][j]<<" \n"[j==n-1];
	cerr<<endl<<endl;
	return os;
}

bool cmp(const string& s1,const string& s2){
	int sz1=s1.size();
	int sz2=s2.size();
	if (s1>s2)
		return !cmp(s2,s1);
	for (int i=0;i<sz1 || i<sz2;i++)
		if (s1[i]!=s2[i])
			return s1[i%sz1]<s2[i%sz2];
	return false;

}

string gen(graf& g,int s,int t){
	if (g.size()==2){
		return "~";
	}
	
	
	int used[50];
	
	memset(tin,0,sizeof(tin));
	memset(tup,0,sizeof(tup));
	memset(used,0,sizeof(used));
	vector<int> points;
	counter=0;
	points.clear();
	sochl(s,g,points,-1,true,used);		
	
	
	
	
	if (points.size()!=0){
	
	
		memset(used,0,sizeof(used));
		points.pb(s);
		reverse(points.begin(),points.end());
		points.pb(t);
		for (int i=0;i<points.size();i++)
			used[points[i]]=2;			
		vector<string> parts;
		for (int j=0;j<points.size()-1;j++){
			vector<int> tec;
			dfs(points[j],g,true,tec,used);
			assert(tec.size()>=2);
	//		copy(tec.begin(),tec.end(),ostream_iterator<int>(cerr," "));
			int ns,nt;
			graf part=gen(g,tec,ns,nt,used);
			parts.pb(gen(part,ns,nt));
			used[points[j]]=1;
		}
		string ans;
		ans="S";
		int kol=1;
		int kols=parts.size()-2;
		
	//	if (parts.size()==3)
//			cerr<<parts[0]<<endl<<parts[0]<<endl<<parts[0]<<endl;
		for (int i=0;i<parts.size();i++){
//			if (parts.size()==3){	
	//			cerr<<i<<" "<<ans<<" "<<kol<<" "<<kols<<endl;
	//		}
			if (kols==0){
				ans+=parts[i];
				kol--;
				continue;
			}
			if (kol==0){
				ans+="S";
				kol++;
				kols--;
				--i;
				continue;
			}
			assert(parts[i][0]!='S');
			if (parts[i]<"S"){
				ans+=parts[i];
				kol--;
			}
			else {
				ans+="S";
				kol++;
				kols--;
				--i;
			}
		}
		
		
		return ans;		
	}
	
	vector<string> parts;
	
	memset(used,false,sizeof(used));
	
	used[s]=used[t]=2;
	
	if (g[s][t]==1){
		g[s][t]=false;
		g[t][s]=false;
		parts.pb("~");
	}
	
	
	for (;;){
		vector<int> tmp;
		tmp.clear();
		dfs(s,g,true,tmp,used,true);
		if (tmp.size()<2)
			break;
		graf ng;
		int ns,nt;
		ng=gen(g,tmp,ns,nt,used);
		parts.pb(gen(ng,ns,nt));
	}
	
	sort(parts.begin(),parts.end(),cmp);
	string ans="";
	for (int i=0;i<parts.size()-1;i++)
		ans+="P";
	for (int i=0;i<parts.size();i++)
		ans+=parts[i];
		
	return ans;
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  
  int n,s,t;
 // while (cin>>n>>s>>t){
 	cin>>n>>s>>t;
	  graf g(n);
	  for (int i=0;i<n;i++){
	  	g[i].resize(n);
	  	for (int j=0;j<n;j++){
	  		char c;
	  		scanf(" %c ",&c);
				if (c=='Y')
					g[i][j]=1;
				else
					g[i][j]=0;
	  	}
	  }
  
	  string ans=gen(g,s,t);
	  printf("%s\n",ans.data());
//	  #ifdef ONLINE_JUDGE
//	  	break;
//	  #endif
//	}
  return 0;
}