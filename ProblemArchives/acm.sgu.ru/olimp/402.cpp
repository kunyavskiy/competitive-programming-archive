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
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

string s;
string t;
int64 cnt[100];

int64 calconly(){
	memset(cnt,0,sizeof(cnt));
	cnt[0]=1;
	for (int i=0;i<s.size();i++)
		for (int j=t.size()-1;j>=0;j--)
			if (s[i]==t[j])
				cnt[j+1]+=cnt[j];
	return cnt[t.size()];
}

int64 calc(){
	memset(cnt,0,sizeof(cnt));
	cnt[0]=1;
	int64 ans=0;
	for (int i=0;i<s.size();i++)
		for (int j=t.size()-1;j>=0;j--)
			if (s[i]==t[j]){
				if (j==t.size()-1)
					ans+=cnt[j]*(1LL<<(s.size()-i-1));
				else
					cnt[j+1]+=cnt[j];
			}
	return ans;
}

int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	getline(cin,s);
	int64 k;
	cin>>k;
	t="";
	for (;;){
		k-=calconly();
		if (k<=0)
			break;
		int sz=t.size();
		t+='A';
		for (;;){
			int64 tmp=calc();
			if (tmp>=k)
				break;
			k-=tmp;
			t[sz]++;
		}		
	}
	cout<<t<<endl;
    return 0;
}