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

bool can(int j){
	if (cnt[j] == a[j].size())
		return false;
	if (j==0)
		return true;
	return a[j-1][cnt[j-1]-1] < a[j][cnt[j]];
}

void add(int j){
	cnt[j]++;
}


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
	cnt[0] = cnt[1] = cnt[2] = 1;
	for (int i=0;i<3;i++)
		if (a[i].size()==0){
			printf("-1\n");
			return;
		}
	m-=3;
	for (;cnt[1] < a[1].size() && a[1][cnt[1]-1] > a[2][0];cnt[1]++)
		m--;
	if (a[1][cnt[1]-1] > a[2][0]){
		printf("-1\n");
		return;
	}
	for (;cnt[0] < a[0].size() && a[0][cnt[0]-1] > a[1][cnt[1]-1];cnt[0]++)
		m--;
	if (a[0][cnt[0]-1] > a[1][cnt[1]-1]){
		printf("-1\n");
		return;
	}
	if (m<0){
		printf("-1\n");
		return;
	}
	for (;m;--m){
		bool q = true;
		for (int j=0;j<3 && q;++j)
			if (cnt[j] < need[j] && can(j)){
				add(j);
				q=false;
			}
		if (!q) continue;			
		if (!can(0) && !can(1)){
			if (can(2))
				add(2);
			else{
				printf("-1\n");
				return;
			}
			continue;
		}		
		if (can(1)){
			add(1);
			continue;
		}		
		if (can(0)){
			add(0);
			continue;
		}
	}
	int ans = abs(cnt[0]-need[0])+abs(cnt[1]-need[1])+abs(cnt[2]-need[2]);
	printf("%d %d %d %d\n",ans,cnt[2],cnt[1],cnt[0]);
}



int main(){
//	freopen(INFILE.data(),"r",stdin);
//	freopen(OUTFILE.data(),"w",stdout);
	int t;
	scanf("%d",&t);
	for (;t;--t)
		solve();
	return 0;
}
