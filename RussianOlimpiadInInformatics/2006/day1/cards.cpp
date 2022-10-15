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

int next[1010][10];
string t[1010][2];
string s;

string cnt(int pos,bool c0=true)
{
	if (pos==-1)
		return "";
	if (t[pos][c0]!="")
		return t[pos][c0];
	if (c0)
	{
		t[pos][c0]='0'+cnt(next[pos][0],true);
	}
	for (int i=1;i<10;i++)
	{
		string tmp=char(i+'0')+cnt(next[pos][i]);
		if (t[pos][c0]=="" || t[pos][c0].size()>tmp.size())
			t[pos][c0]=tmp;
		else if (t[pos][c0].size()==tmp.size() && tmp<t[pos][c0])
			t[pos][c0]=tmp;	
	}
	return t[pos][c0];		
}

int main()
{
  freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	cin>>s;
	s='$'+s;
	int n=s.size();
	for (int i=0;i<10;i++)
		next[n-1][i]=-1;
	for (int i=n-2;i>=0;--i){
		for (int j=0;j<10;j++)
			next[i][j]=next[i+1][j];
		next[i][s[i+1]-'0']=i+1;
	}
	cout<<cnt(0,false);
  return 0;
}
