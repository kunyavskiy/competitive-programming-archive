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

set<int64> can;
string s;
int n;

void per(int pos,int64 tec){
	if (pos==n)
	{
		can.insert(tec);
		return;
	}
	per(pos+1,tec);
	per(pos+1,tec*10+s[pos]-'0');
}

int main()
{
  freopen("cards.in","r",stdin);
	freopen("cards.out","w",stdout);
	cin>>s;
	n=s.size();
	assert(n<=18);
	per(0,0);	
	for (int64 i=1;;i++)
		if (can.find(i)==can.end())
		{
			cout<<i<<endl;
			return 0;
		}
  return 0;
}
