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
int64 h[MAXN][2*MAXN+100];
int64 P[2*MAXN+100];

int64 gethash(int num,int l,int r){
	return (h[num][r]-(l?h[num][l-1]:0))*P[2*m-r];
}

bool checkb(int a){
	for (int i=0;i<n;i++){
		int j = 0;
		for (;j+a<=m;j+=a)
			if (gethash(i,0,a-1)!=gethash(i,j,j+a-1))
				return false;
		if (j<m && gethash(i,0,m-j-1) != gethash(i,j,m-1))
			return false;
	}
	return true;
}

bool checkabs(int a,int b,int s){
	for (int i=0;i<n-a;i++)
		if (gethash(i,0,b-1) != gethash(i+a,s,b+s-1))
			return false;
	return true;
}

namespace zeros{
vector<int> cana,canb;
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

int solve(int& ansa,int& ansb){
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
	ansa = cana[0];
	ansb = canb[0];
	//cout<<ansn<<" "<<ansm<<" "<<0<<endl;	
	return 0;
}
}

int main(){
	ld start=clock();
//	freopen(INFILE.data(),"r",stdin);
//	freopen(OUTFILE.data(),"w",stdout);
	scanf("%d %d\n",&n,&m);
	for (int i=0;i<n;i++)
		gets(c[i]);
	P[0]=1;
	for (int i=1;i<=2*m;i++)
		P[i]=P[i-1]*31;
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			if (j==0)
				h[i][j]=c[i][j]-'a'+1;
			else
				h[i][j]=h[i][j-1]+(c[i][j]-'a'+1)*P[j];
	int besta=-1,bestb=-1,bests=0;
	zeros::solve(besta,bestb);
	for (int b=1;2*b<=m;++b){
		if (clock()-start > 1.9*CLOCKS_PER_SEC)
			break;
		if (!checkb(b))
			continue;
		for (int a=1;2*a<=n;++a){
			if (besta != -1 && a*b>=besta*bestb)
				continue;
			for (int s=0;s<b;++s)
				if (checkabs(a,b,s)){
					besta=a;
					bestb=b;
					bests=s;
					break;
				}
		}			
	}	
	cout<<besta<<" "<<bestb<<" "<<bests<<endl;
	return 0;
}
