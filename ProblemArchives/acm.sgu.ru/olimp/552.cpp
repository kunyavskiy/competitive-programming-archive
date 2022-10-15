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

string str[13];
string str1[13];

void add(string s)
{
	int num=-1;
	if (s[0]<='9' && s[0]>='0')
		num=s[0]-'2';
	if (s[0]=='T')
		num=8;
	if (s[0]=='J')
		num=9;
	if (s[0]=='Q')
		num=10;
	if (s[0]=='K')
		num=11;
	if (s[0]=='A')
		num=12;
	assert(num!=-1);
	str[num]+=s+'\n';
	str1[num]=s+='\n';
}

string ans;
bool isans;

void perebor(int pos,string used,string unused,int last,bool tus)
{
	if (last==5)
	{
		isans=true;
		return;
	}
	if (pos==12)
	{
		if (tus && last==4)
		{
			isans=true;
			return;
		}
		if (used.size()+unused.size()>ans.size())

			ans=used+unused;


		return;
	}
	if (str1[pos]=="")
	{
		perebor(pos+1,used,unused,0,tus);
		return;
	}        
	perebor(pos+1,used+str[pos],unused,last+1,tus);
	perebor(pos+1,used,str1[pos],0,tus);
	return;		
}

void perebor_tus()
{
	perebor(0,"",str1[12],0,false);
	if (str[12]!="")
		perebor(0,str[12],"",1,true);
}


int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n;
  cin>>n;
  for (int i=0;i<n;i++)
  {
  	string s;
  	cin>>s;
  	add(s);
  }
  ans="";
  perebor_tus();
  assert(ans.length()%3==0);
  if (isans==false)
  	{
  		printf("-1");
  		return 0;
  	}
  printf("%d\n%s",ans.length()/3,ans.data());
  return 0;
}