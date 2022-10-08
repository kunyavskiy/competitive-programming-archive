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

const string TASKNAME = "A";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";


void PreCalc(){
}

int n;
int push[2][110];
int pos[2];
vector<int> need[2];

void closer(int& v,int to){
	if (v>to)
		--v;
	else if (v<to)
		++v;
}

void solve(){
	scanf("%d",&n);
	need[0].clear();
	need[1].clear();
	for (int i=0;i<n;i++){
		char c;
		scanf(" %c %d",&c,&push[1][i]);
		push[0][i] = (c=='O');
		push[0][i] = !!push[0][i];
		need[!!push[0][i]].pb(push[1][i]);		
	}
	need[0].pb(1<<29);
	need[1].pb(1<<29);
	pos[0]=pos[1]=1;
	reverse(need[0].begin(),need[0].end());
	reverse(need[1].begin(),need[1].end());
	int time = 0;
	for (int i=0;i<n;i++){		
		int f = push[0][i];
		int s = 1-f;
		for (;;){
			++time;
			closer(pos[s],need[s].back());
			if (pos[f] == push[1][i]){
				need[f].pop_back();
				break;				
			}
			closer(pos[f],need[f].back());		
		}
	}
	printf("%d\n",time);
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
			cerr<<"SOLVED:"<<i<<endl;
		}


  return 0;
}