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

#define taskname "acm"

using namespace std;

typedef long long int64;
typedef long double ld;

char comand[1000];
string s;

bool solve(){
	gets(comand);
	s=comand;
	if (s==";STOP;")
		return false;
	s="Rating "+s;
	for (int i=0;i<s.size();i++)
		if (s[i]==';'){
			s=string(s.begin(),s.begin()+i)+string(": ")+string(s.begin()+i+1,s.end());
			break;
		}
	for (int i=0;i<s.size();i++)
		if (s[i]==';')
			s[i]='\n';
		
	s+="\n----------";
	for (int it=0;it<3;it++){
		for (int i=0;i<s.size();i++)
			if (s[i]=='/'){
				s=string(s.begin(),s.begin()+i)+string(", ")+string(s.begin()+i+1,s.end());
				break;
			}
	}
	puts(s.data());	
	return true;
}


int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	for (;solve(););
	return 0;
} 