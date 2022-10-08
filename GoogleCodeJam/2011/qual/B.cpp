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

const string TASKNAME = "B";
const string TASKMOD = "large";
const string INFILE = TASKNAME+"-"+TASKMOD+".in";
const string OUTFILE = TASKNAME+"-"+TASKMOD+".out";



void PreCalc(){
}

bool opoz[256][256];
char to[256][256];
bool done[256][256];

void print(string s){
	if (s.size()==0){
		printf("[]\n");
		return;
	}
	printf("[%c",s[0]);
	for (int i=1;i<s.size();i++)
		printf(", %c",s[i]);
	printf("]\n");
	
}

void solve(){
	int c;
	char buf[5];
	scanf("%d",&c);
	memset(done,0,sizeof(done));
	memset(opoz,0,sizeof(opoz));
	for (int i=0;i<c;i++){
		scanf(" %s ",buf);
		done[buf[0]][buf[1]]=done[buf[1]][buf[0]]=1;
		to[buf[0]][buf[1]]=to[buf[1]][buf[0]]=buf[2];
	}
	scanf("%d",&c);
	for (int i=0;i<c;i++){
		scanf(" %s ",buf);
		opoz[buf[0]][buf[1]]=opoz[buf[1]][buf[0]]=1;
	}
	string s="";
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		char c;
		scanf(" %c ",&c);
		if (s.size()==0)
			s+=c;
		else {
			int sz = s.size();
			if (done[s[sz-1]][c])
				s[sz-1]=to[s[sz-1]][c];
			else {
				s+=c;
				for (int j=0;j<sz;j++)
					if (opoz[s[j]][c]){
						s="";
						break;
					}
			}
			
		}
	}
	print(s);
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