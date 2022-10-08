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

const string TASKNAME = "C";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

void solve(){
	int n;
	scanf("%d",&n);
	int64 sum,minv,x=0;
	sum = 0;
	minv = 1LL<<60LL;
	for (int i=0;i<n;i++){
		int tmp;
		scanf("%d",&tmp);
		minv = min(minv,tmp*1LL);
		sum+=tmp;
		x^=tmp;
	}
	if (x != 0)
		printf("NO\n");
	else
		cout<<sum-minv<<endl;
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