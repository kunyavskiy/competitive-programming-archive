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

#define taskname "B"

using namespace std;

typedef long long int64;
typedef long double ld;

int p[10][26];
int p1[10][26];
int ps,n;

void obr(){
	for (int i=0;i<ps;i++){
		for (int j=0;j<n;j++)
			p1[i][p[i][j]]=j;
	}
	memcpy(p,p1,sizeof(p1));
}

set<string> l,r;

string use(string s,int num){
	string res;
	for (int i=0;i<n;i++)
		res+=s[p[num][i]];
	return res;
}

void go(set<string> &s){
	vector<string> v(s.begin(),s.end());
	s.clear();
	int sz=v.size();
	for (int i=0;i<sz;i++)
		for (int j=0;j<ps;j++)
			s.insert(use(v[i],j));
}

bool check(){
	vector<string> v(l.begin(),l.end());
	int sz=v.size();
	for (int i=0;i<sz;i++)
		if (r.find(v[i])!=r.end())
			return true;
	return false;		
}


int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	int L;
	cin>>n>>ps>>L;
	string s;
	cin>>s;
	l.insert(s);
	cin>>s;
	r.insert(s);
	for (int i=0;i<ps;i++)
	for (int j=0;j<n;j++){
		char c;
		cin>>c;
		p[i][j]=c-'a';
	//	cerr<<p[i][j]<<endl;
	}
	int lt=L/2;
	for (int i=0;i<lt;i++)
		{
			go(l);
			if (check()){
				cout<<i+1<<endl;
				return 0;
			}
		}
	obr();
	//cerr<<"!!!"<<endl;
	for (int i=0;i<L-lt;i++){
		go(r);
		if (check()){
			cout<<lt+i+1<<endl;
			return 0;
		}
	}
	cout<<-1<<endl;
	return 0;
} 