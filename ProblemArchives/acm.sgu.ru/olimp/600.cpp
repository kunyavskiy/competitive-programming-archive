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

#define x0 botva458
#define y0 botva455

using namespace std;

struct cmpsec{
	bool operator()(const pair<int,int>& a,const pair<int,int>& b){
		if (a.second != b.second)
			return a.second < b.second;
		return a.first < b.first;
	}
};

set<pair<int,int> >  s1;
set<pair<int,int>,cmpsec> s2;

int x0,y0;

bool in(int lx,int rx,int ly,int ry){
	return (lx < x0 && x0 < rx) && (ly < y0 && y0 < ry);
}

void erase(const pair<int,int>& a){
	s1.erase(a);
	s2.erase(a);
}

bool iterate(){
	if (s1.empty() || s2.empty())
		return false;
	int lx = s1.begin()->first;
	int rx = (--s1.end())->first;
	int ly = s2.begin()->second;
	int ry= (--s2.end())->second;
	if (!in(lx,rx,ly,ry))
		return false;
	for (;!s1.empty() && s1.begin()->first == lx;)
		erase(*s1.begin());
	for (;!s1.empty() && (--s1.end())->first == rx;)
		erase(*--s1.end());
	for (;!s2.empty() && s2.begin()->second == ly;)
		erase(*s2.begin());
	for (;!s2.empty() && (--s2.end())->second == ry;)
		erase(*--s2.end());
	return true;
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	int n;
	scanf("%d %d %d",&n,&x0,&y0);
	for (int i=0;i<n;i++){
		int a,b;
		scanf("%d %d",&a,&b);
		s1.insert(mp(a,b));
		s2.insert(mp(a,b));
	}	
	int cnt=0;
	for (;iterate();cnt++);
	cout<<cnt<<endl;
    return 0;
}