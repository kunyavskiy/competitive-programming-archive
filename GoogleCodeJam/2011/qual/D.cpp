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
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back   
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

typedef long long int64;
typedef long double ld;

const string TASKNAME = "D";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";




void PreCalc(){
}

int a[1100];
pair<int,int> atmp[1100];
bool used[1100];

void solve(){
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		scanf("%d",&atmp[i].first);
		atmp[i].second = i;
		--atmp[i].first;
		used[i]=false;
	}
	sort(atmp,atmp+n);
	for (int i=0;i<n;i++)
		a[atmp[i].second] = i;
	int ans = 0;
	for (int i=0;i<n;i++){
		if (used[i])
			continue;
		int cnt = 0;
		for (int j=i;!used[j];j=a[j]){
			used[j]=true;
			cnt++;
		}
		if (cnt > 1)
			ans += cnt;			
	}
	cout.precision(10);
	cout<<fixed<<(ld)ans<<endl;
}

int main(){
	freopen(INFILE.data(),"r",stdin);
	freopen(OUTFILE.data(),"w",stdout);
	PreCalc();
	int t;
	cin>>t;
	for (int i=1;i<=t;i++)
		{
			printf("Case #%d: ",i);
			solve();
			if (i>t-20 || i%10==0)
				cerr<<"SOLVED:"<<i<<endl;
		}


  return 0;
}