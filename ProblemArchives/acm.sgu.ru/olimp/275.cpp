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

int n,m;
int a[10][10];
int b[10][10];
int k;

typedef vector<int> mask3;

mask3 use(const mask3 &m,int x,int y){
	mask3 m1,m2;
	for (int i=0;i<m.size();i++){
		m1.pb(m[i]&a[x][y]);
		m1.pb(m[i]&~a[x][y]);
	}
	for (int i=0;i<m1.size();i++)
		if (m1[i]&(m1[i]-1))
			m2.pb(m1[i]);		
	return m2;
}

map<mask3,int> ans;

int calc(const mask3 &m){
	if (ans.find(m)!=ans.end())
		return ans[m];
	if (m.size()==0)
		return 0;
	int cans=1<<30;
	for (int i=0;i<n;i++)
		for (int j=0;j< ::m;j++){
			mask3 m1=use(m,i,j);
			if (m1!=m)
				cans=min(calc(m1)+1,cans);						
		}
	ans[m]=cans;
	return cans;
}

ostream& operator<<(ostream& os,mask3 a){
	os<<"(";
	copy (a.begin(),a.end(),ostream_iterator<int>(os," "));
	os<<")";
	return os;
}

void gen(const mask3& m){
	if (m.size()==0)
		return;
	int cans=ans[m];
	for (int i=0;i<n;i++)
		for (int j=0;j< ::m;j++){
			mask3 m1=use(m,i,j);
		//	cerr<<i<<" "<<j<<" "<<m<<" : "<<m1<<endl;
			if (ans[m1]+1==cans){
				b[i][j]=true;
				gen(m1);
				return;
			}
		}
	assert(false);
}



int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int k;
  cin>>n>>m>>k;
  for (int i=0;i<k;i++){
  	for (int j=0;j<n;j++)
  		for (int k=0;k<m;k++)
  		{
  			char c;
  			scanf(" %c ",&c);
  			if (c=='1')
	  			a[j][k]|=(1<<i);
  		}
  }
  vector<int> e;
  e.pb(1<<k);
  e[0]--;
  cout<<calc(e)<<endl;
  gen(e);
  for (int i=0;i<n;i++){
  	for (int j=0;j<m;j++)
  		cout<<b[i][j];
  	cout<<endl;
  }
  return 0;
}