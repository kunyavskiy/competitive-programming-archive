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

enum res {_1,_0,_x,_pr};

res operator&(res a,res b){
	if (a==_pr || b==_pr)
		return _pr;
	if (a==_x)
		return b;
  if (b==_x)
  	return a;
  if (a==b) 
  	return a;
  return _pr;
}

vector<pair<int,int> > g[2][10000];
int n,m;
int len[100];
res st[2][10000];
pair<int,int> f[100];
bool used[2][10000];

void clear(){
	for (int i=0;i<n;i++)
		g[0][i].clear();
	for (int i=0;i<m;i++)
		g[1][i].clear();
	memset(len,0,sizeof(len));
	memset(used,0,sizeof(used));
}

void read(){
	int k;
	scanf("%d",&k);
	for (int i=0;i<k;i++)
		scanf("%d",&len[i]);
	scanf("%d\n",&n);
	for (int i=0;i<26;i++)
		f[i]=mp(-1,-1);
	string s;
	if (n)
		getline(cin,s);
	int ptr=0;
	for (int i=0;i<n;i++)
		{
			//cerr<<s[i]<<" "<<ptr<<endl;
			if (s[i]=='0')
				st[0][ptr]=_0;
			if (s[i]=='1')
				st[0][ptr]=_1;
		//	g[0][ptr].pb(mp(1,ptr));
			if (s[i]<='z' && s[i]>='a'){
				for (int j=0;j<len[s[i]-'a'];j++)
					st[0][ptr+j]=_x;
			
				if (f[s[i]-'a']==mp(-1,-1))
					f[s[i]-'a']=mp(0,ptr);
				else {
					for (int j=0;j<len[s[i]-'a'];j++){
						g[0][ptr+j].pb(mp(f[s[i]-'a'].first,f[s[i]-'a'].second+j));
						g[f[s[i]-'a'].first][f[s[i]-'a'].second+j].pb(mp(0,ptr+j));		
					}
				}
				ptr+=len[s[i]-'a'];				
			}
			else 
				ptr++; 
		}	
	
  n=ptr;
	
	scanf("%d\n",&m);	
	if (m)
		getline(cin,s);
	ptr=0;
	for (int i=0;i<m;i++)
		{
			if (s[i]=='0')
				st[1][ptr]=_0;
			if (s[i]=='1')
				st[1][ptr]=_1;
			//g[1][ptr].pb(mp(0,ptr));
			if (s[i]<='z' && s[i]>='a'){
				for (int j=0;j<len[s[i]-'a'];j++)
					st[1][ptr+j]=_x;			
			
				if (f[s[i]-'a']==mp(-1,-1))
					f[s[i]-'a']=mp(1,ptr);
				else {
					for (int j=0;j<len[s[i]-'a'];j++){
						g[1][ptr+j].pb(mp(f[s[i]-'a'].first,f[s[i]-'a'].second+j));
						g[f[s[i]-'a'].first][f[s[i]-'a'].second+j].pb(mp(1,ptr+j));		
					}
				}
				ptr+=len[s[i]-'a'];				
			}
			else 
				ptr++; 
		}	

	m=ptr;
	
	for (int i=0;i<n;i++){
		g[0][i].pb(mp(1,i));
		g[1][i].pb(mp(0,i));
	}
}



res dfs(int a,int b){
	if (used[a][b])
		return st[a][b];
	//cerr<<a<<" "<<b<<endl;
	res tmp=st[a][b];
  used[a][b]=true;
	for (int i=0;i<g[a][b].size();i++)
		tmp=tmp&dfs(g[a][b][i].first,g[a][b][i].second);
	return tmp;
}

void print(int st){
	vector<int> a;
	a.pb(1);
	int c=0;
	for (int i=0;i<st;i++){
		if (a.back()!=0)
			a.pb(0);
		for (int j=0;j<a.size();j++){
			a[j]*=2;
			a[j]+=c;
			c=a[j]/1000000;
			a[j]%=1000000;
		} 
	}
	while (a.back()==0)
		a.pop_back();
	printf("%d",a.back());
	for (int i=(int)a.size()-2;i>=0;i--)
		printf("%06d",a[i]);
	printf("\n");
}

void solve(){
	clear();
	read();
//	cerr<<"!!!!"<<n<<" "<<m<<endl;
	if (n!=m){
		cout<<0<<endl;
		return;
	}
	int st=0;
	for (int i=0;i<2;i++)
		for (int j=0;j<n;j++)
			if (!used[i][j]){
				res tmp=dfs(i,j);
			//	cerr<<"!!!!"<<i<<" "<<j<<" "<<tmp<<" "<<endl;
				if (tmp==_pr){
					cout<<0<<endl;
					return;
				}
				if (tmp==_x)
					st++;
			}
//	cerr<<st<<endl;
	print(st);
}

int main(){                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
	int x;
	cin>>x;
	for (int i=0;i<x;i++)
		solve();
  return 0;
}