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

int* v[4];

void operation(string s)
{
	cerr<<s<<endl;
	char a,a1;
	int b;
	char ec;
	if (sscanf(s.data(),"writeln(%c^);",&a)==1)
		{
			printf("%d\n",*v[a-'a']);
			return;		
		}
	if (sscanf(s.data(),"%c^:=%c^%c",&a,&a1,&ec)==3)
		{
			*v[a-'a']=*v[a1-'a'];
			return;
		}
	if (sscanf(s.data(),"%c^:=%d",&a,&b)==2)
		{
			*v[a-'a']=b;
			return;
		}
	if (sscanf(s.data(),"%c:=%c",&a,&a1)==2)
		{
			v[a-'a']=v[a1-'a'];
			return;
		}
	assert(false);	
}


int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n;
  scanf("%d\n",&n);
  v[0]=new int;
  v[1]=new int;
  v[2]=new int;
  v[3]=new int;
  *v[0]=0;
  *v[1]=0;
  *v[2]=0;
  *v[3]=0;
  for (int i=0;i<n;i++)
  	{
  		string s;
  		getline(cin,s);
  		operation(s);
  	}  
  return 0;
}