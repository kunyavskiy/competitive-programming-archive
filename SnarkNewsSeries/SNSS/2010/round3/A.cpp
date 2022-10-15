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

using namespace std;

typedef long long int64;
typedef long double ld;

vector<string> ans;

string gen(int a){
	string res="";
	for (;a;)
		{
			char c='0'+a%10;
			a/=10;
			res=c+res;
		}
	return res;
}

int main(){
//	ans.pb("B");
	ans.pb("S1");
	ans.pb("B");
	int n,sp;
	scanf("%d %d",&n,&sp);
	int id=3;
	for (int i=0;i<sp;i++){
		string s="S";
		s+=gen(id);
		++id;
		ans.pb(s);
	}
	if (sp%2==1)
		ans.pb("B");
	id=1;
	for (int i=0;i<n;i++){
		int kol;
		scanf("%d",&kol);
		for (int j=0;j<kol;j+=2){
			ans.pb(gen(id));
			++id;
			if (j+1==kol)	
				ans.pb("B");
			else
				ans.pb(gen(id));
			++id;
		}
	}
	int str=ans.size()/4;
	if (str*4<ans.size())
		str++;
	for (;ans.size()<str*4;)
		ans.pb("B");
//	for (int i=0;i<ans.size();i++)
//		cerr<<ans[i]<<endl;
	for (int i=0,j=ans.size()-1;i<j;i+=2,j-=2){
		printf("%s/%s,%s/%s ",ans[j].data(),ans[i].data(),ans[i+1].data(),ans[j-1].data());
	}
	printf("\n");	
	return 0;
} 