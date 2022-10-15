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
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double  
#define setval(a,v) memset(a,v,sizeof(a))
using namespace std;

enum evtype {_in=0,_req=1,_out=2};

struct event{
	string name;
	int time;
	evtype type;
	int num;
	event(string _name="",string _time="",evtype _type=_in,int _num=0)
	{
	  name=_name;
	  type=_type;
	  num=_num;
	  if (_time=="")
	  	time=0;
	  else
	  	{
	  		int h,m,s;
	  		sscanf(_time.data(),"%d:%d:%d",&h,&m,&s);
	  		time=(h*60+m)*60+s;
	  	}
	}
};

bool operator<(const event& a,const event& b)
{
	if (a.time!=b.time)
		return a.time<b.time;
	if (a.type!=b.type)
		return a.type<b.type;
	return a.name<b.name;
}

vector<event> evs;
set<string> cur;
multiset<string> now;

string anss[5000];

void print(int num)
{
	char s[1000];
	vector<string> ans(now.begin(),now.end());
	sort(ans.begin(),ans.end());
	ans.erase(unique(ans.begin(),ans.end()),ans.end());
	int sz=ans.size();
	sprintf(s,"%d",sz);
	anss[num]=s;
	for (int i=0;i<sz;i++)
	{
		anss[num]+=((string)" "+ans[i]);
//		assert(ans[i].size()>0);
	}
	anss[num]+='\n';
}

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int n,m;
  cin>>n>>m;
  string t;
  string s;
  for (int i=0;i<n;i++)
  {
  	cin>>t>>s;
  	if (cur.find(s)!=cur.end())
  	{
  		cur.erase(s);
  		evs.pb(event(s,t,_out));
  	}
  	else
  		{
  			cur.insert(s);
  			evs.pb(event(s,t,_in));
  		}
  }
  string t1="";
  for (int i=0;i<m;i++)
  {
  	cin>>t;
//  	assert(t1=="" || t>t1);
  	evs.pb(event("",t,_req,i));
  	t1=t;
  }
  sort(evs.begin(),evs.end());
  for (int i=0;i<evs.size();i++)
  {
   	if (evs[i].type==_req)
  		print(evs[i].num);
  	else if (evs[i].type==_in)
  		now.insert(evs[i].name);
  	else if (evs[i].type==_out)
  	 		now.erase(now.find(evs[i].name));
  	else
  		assert(false); 	
  }
  for (int i=0;i<m;i++)
  	printf("%s",anss[i].data());
  return 0;
}