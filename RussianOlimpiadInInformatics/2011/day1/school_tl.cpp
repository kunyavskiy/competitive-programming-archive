#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <string>
#include <algorithm>
#include <cassert>
#include <ctime>

#define mp make_pair
#define pb push_back

using namespace std;

typedef long long int64;
typedef long double ld;

const string TASKNAME = "school";
const string INFILE = TASKNAME+".in";
const string OUTFILE = TASKNAME + ".out";

vector<int> a[3];
int need[3];
int n,m;
int cnt[3];


void solve(){
	for (int i=0;i<3;i++)
		a[i].clear();
	scanf("%d %d %d %d",&need[2],&need[1],&need[0],&n);
	m = need[0]+need[1]+need[2];
	for (int i=0;i<n;i++){
		int y,t;
		scanf("%d %d",&y,&t);
		a[1996-y].pb(t);		
	}
	sort(a[0].rbegin(),a[0].rend());
	sort(a[1].rbegin(),a[1].rend());
	sort(a[2].rbegin(),a[2].rend());
	int best = -1;
	int besta,bestb,bestc;
	for (int x=1;x<=a[0].size();x++)
		for (int y=1;y<=a[1].size();y++){
			int z = m-x-y;
			if (z<1)
				continue;
			if (z>a[2].size())
				continue;
			if (a[0][x-1] > a[1][y-1])
				continue;
			if (a[1][y-1] > a[2][z-1])
				continue;
			int f = abs(x - need[0])+abs(y-need[1])+abs(z-need[2]);
			if (f < best || best==-1){
				best = f;
				besta = x,bestb=y,bestc=z;
			}                         	
		}
	cout<<best;
	if (best != -1)
		cout<<" "<<bestc<<" "<<bestb<<" "<<besta<<endl;
	else
		cout<<endl;

}



int main(){
	freopen(INFILE.data(),"r",stdin);
	freopen(OUTFILE.data(),"w",stdout);
	int t;
	scanf("%d",&t);
	for (;t;--t)
		solve();
	return 0;
}
