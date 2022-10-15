#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "quest"

using namespace std;

typedef long long int64;
typedef long double ld;

map<string,int> day;

char s[10000];

void getfirst(){
	gets(s);
	for (int i=0;s[i];i++){
		if (s[i]==' '){
			for (int j=i;s[j];j++)
				s[j]=s[j+1];
			--i;
		}
	}
	int tmp=strlen(s);
	s[tmp]=',';
	s[tmp+1]=0;
	string t="";
	for (int i=0;s[i];i++){
		if (s[i]==':'){
			int tmp=0;
			sscanf(s+i+1,"%d",&tmp);
			day[t]=tmp;
			i++;
			for (;s[i]>='0' && s[i]<='9';i++);
			t="";
			continue;
		}
		t+=s[i];
	}
}

int solve(){
	gets(s);
	for (int i=0;s[i];i++){
		if (s[i]==' '){
			for (int j=i;s[j];j++)
				s[j]=s[j+1];
			--i;
		}
	}
	int tmp=strlen(s);
	s[tmp]='|';
	s[tmp+1]=0;
	int ans=1<<30;
	int cur=0;	
	string t="";
	for (int i=0;s[i];i++){
		if (s[i]=='|'){
			cur=max(day[t],cur);
			ans=min(ans,cur);
			t="";
			cur=0;
			continue;
		}
		if (s[i]=='&'){
			cur=max(cur,day[t]);
			t="";
			continue;
		}
		t+=s[i];
	}
	return ans;
}



int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	getfirst();
	cout<<solve()<<endl;
	return 0;
} 