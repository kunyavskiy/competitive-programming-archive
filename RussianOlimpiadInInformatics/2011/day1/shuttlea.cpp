#include <iostream>
#include <fstream>
#include <memory.h>
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

const string TASKNAME = "shuttle";
const string INFILE = TASKNAME+".in";
const string OUTFILE = TASKNAME + ".out";

const int MAXN=2000;

int n,m;
char c[MAXN][MAXN];
vector<int> cana,canb;

namespace tlsolve{

bool check(int a,int b,int s){
	for (int i=0;i<n;i++){
		int sdv = ((i/a)*s)%b;
		for (int j=0;j<m;j++)
			if (c[i%a][(j-sdv+b)%b]!=c[i][j])
				return false;
	}
	return true;
}

bool checkb(int a,int b,int s){
	for (int i=0;i<n;i++){
		int sdv = ((i/a)*s)%b;
		for (int j=0;j<b;j++)
			if (c[i%a][(j-sdv+b)%b]!=c[i][j])
				return false;
	}
	return true;
}


bool check1(int a,int b){
	for (int i=0;i<a;i++){
		for (int j=0;j<m;j++)
			if (c[i][j%b]!=c[i][j])
				return false;
	}
	return true;
}


int solve(){
	int besti,bestj,bests;
	besti=-1;
	for (int i=1;2*i<=n;i++)
		for (int j=1;2*j<=m;j++){
			if (besti!=-1 && bestj*besti <= i*j)
				continue;
		    if (!check1(i,j))
				continue;
			for (int s=0;s<j;s++)
				if (check(i,j,s)){
					besti=i;
					bestj=j;
					bests=s;
				}					    
		}
	cout<<besti<<" "<<bestj<<" "<<bests<<endl;
	return 0;
}

}


bool used[MAXN];
int cnt[MAXN];
int p[MAXN];

void period(const string& s){
	int n = s.size();
	p[0] = 0;
	used[0]=0;
	for (int i=1;i<n;i++){
		int j=p[i-1];
		for (;j!=0 && s[j]!=s[i];j=p[j-1]);
		if (s[j]==s[i])
			j++;
		p[i]=j;
		used[i]=0;
	}
	for (int j=p[n-1];j;j=p[j-1])
		used[n-j]=true;	
	used[n]=true;
	for (int i=1;i<=n;i++)
		if (used[i])
			for (int j=1;i*j<=n;j++)
				used[i*j]=true;
	for (int i=0;i<=n;i++)
		cnt[i]+=used[i];
}

char buf[MAXN];

string getv(int id){
	for (int i=0;i<n;i++)
		buf[i]=c[i][id];
	return buf;
}

int main(){
	freopen(INFILE.data(),"r",stdin);
	freopen(OUTFILE.data(),"w",stdout);
	scanf("%d %d\n",&n,&m);
	for (int i=0;i<n;i++)
		gets(c[i]);
	if (n<=20 && m<=20){
		tlsolve::solve();
		return 0;
	}
	for (int i=0;i<n;i++)
		period(c[i]);
	int ansm,ansn;
	for (int i=0;i<=m;i++)
		if (cnt[i] == n){
			ansm=i;
			canb.pb(i);
			break;
		}
	memset(cnt,0,sizeof(cnt));
	for (int i=0;i<m;i++)
		period(getv(i));
	
	for (int i=0;i<=n;i++)
		if (cnt[i] == m){
			ansn=i;
			cana.pb(i);
			break;
		}
	ansn = cana[0];
	ansm = canb[0];
	cout<<ansn<<" "<<ansm<<" "<<0<<endl;	
	return 0;
}
