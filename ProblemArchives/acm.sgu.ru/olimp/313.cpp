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

struct segment{
	int x1,x2,y1,y2;
	segment(){};
	segment(int x1,int y1,int x2,int y2){
		if (x1>x2)
			swap(x1,x2);
		if (y1>y2)
			swap(y1,y2);
		this->x1=x1;
		this->x2=x2;
		this->y1=y1;
		this->y2=y2;
	}
};

bool operator<(const segment &a,const segment& b){
	if (a.x1!=b.x1)
		return a.x1<b.x1;
	if (a.y1!=b.y1)
		return a.y1<b.y1;
	if (a.x2!=b.x2)
		return a.x2<b.x2;
	if (a.y2!=b.y2)
		return a.y2<b.y2;
	return false;
}

bool operator==(const segment &a,const segment& b){
	if (a.x1!=b.x1)
		return false;
	if (a.y1!=b.y1)
		return false;
	if (a.x2!=b.x2)
		return false;
	if (a.y2!=b.y2)
		return false;
	return true;
}

vector<segment> ans[1000];

const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
int nap[255];

void gen(const string& s,vector<segment>& a){
	int x=0;
	int y=0;
	int sz=s.size();
	for (int i=0;i<sz;i++){
		a.pb(segment(x,y,x+dx[nap[s[i]]],y+dy[nap[s[i]]]));
		x+=dx[nap[s[i]]];
		y+=dy[nap[s[i]]];
	}
	sort(a.begin(),a.end());
	a.erase(unique(a.begin(),a.end()),a.end());
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	nap['L']=3;
	nap['R']=1;
	nap['U']=0;
	nap['D']=2;
	int n;
	string s;
	getline(cin,s);
	sscanf(s.data(),"%d",&n);
	for (int i=0;i<n;i++){
		getline(cin,s);
		gen(s,ans[i]);
//		cerr<<ans[i].size()<<endl;
	}
	sort(ans,ans+n);
	n=unique(ans,ans+n)-ans;
	printf("%d\n",n);
    return 0;
}