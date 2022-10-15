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

const string TASKNAME = "shuttle";
const string INFILE = TASKNAME+".in";
const string OUTFILE = TASKNAME + ".out";

const int MAXN=2000;

char c[MAXN][MAXN];
int n,m;

bool check(int a,int b,int s){
	for (int i=0;i<n;i++){
		int sdv = ((i/a)*s)%b;
		for (int j=0;j<m;j++)
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


int main(){
	freopen(INFILE.data(),"r",stdin);
	freopen(OUTFILE.data(),"w",stdout);
	scanf("%d %d\n",&n,&m);
	for (int i=0;i<n;i++)
		gets(c[i]);
	int besti,bestj,bests;
	besti=-1;
	for (int i=1;2*i<=n;i++)
		for (int j=1;2*j<=m;j++){
			if (besti!=-1 && bestj*besti <= i*j)
				continue;
		    if (!check1(i,j))
				continue;
			for (int s=0;s<j-((j-1)*(n>=20 || m>=20));s++)
				if (check(i,j,s)){
					besti=i;
					bestj=j;
					bests=s;
				}					    
		}
	cout<<besti<<" "<<bestj<<" "<<bests<<endl;
	return 0;
}
