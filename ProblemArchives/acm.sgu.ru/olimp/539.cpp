#include <vector>
#include <fstream>
#include <set>
#include <utility>
#include <algorithm>
#include <string>
#include <stack>
#include <iostream>
#define forc(i,n) for(int i=1;i<=n;i++)
#define read(n) scanf("%d",&n);
#define mp make_pair

using namespace std;

struct ver;
vector<ver> g;
int t[100][8][8][8];
bool used[100];

struct ver
{
   int teg;
   int color;
   vector<int> next;
};

int ctoi(string s)
{
  if (s=="black")
	      return 1;
  if (s=="blue")
	      return 2;
  if (s=="gray")
	      return 3;
  if (s=="green")
	      return 4;
  if (s=="red")
	      return 5;
  if (s=="white")
	      return 6;
  if (s=="yellow")
	      return 7;
  return 0;
}


int convert(int cb,int cu,int ci,int cbn,int cun,int cin,int teg,int color)
{
	int res=0;
	if (cb!=cbn)
		  res++;
	if (cu!=cun)
		  res++;
	if (ci!=cin)
		  res++;
	if ((cu!=0)  && (cun==0))
		res=1<<25;
	if ((cb!=0)  && (cbn==0))
		res=1<<25;
	if ((ci!=0)  && (cin==0))
		res=1<<25;
	if (teg==0)
			res+=cb==color?0:1;
	if (teg==1)
			res+=cu==color?0:1;
	if (teg==2)
			res+=ci==color?0:1;
	return res;


}

int len(int v, int cb,int cu,int ci)
{
	if (t[v][cb][cu][ci]!=-1)
		return t[v][cb][cu][ci];
	used[v]=true;
	if (g[v].next.size()==0)
	{
		int k;
		if (g[v].teg==0)
			k=cb==g[v].color?0:1;
		if (g[v].teg==1)
			k=cu==g[v].color?0:1;
		if (g[v].teg==2)
			k=ci==g[v].color?0:1;
		t[v][cb][cu][ci]=k;
		return k;
	}
   int minres=1<<25;
   int l=g[v].next.size();
   for (int cbn=0;cbn<=7;cbn++)
     for (int cun=0;cun<=7;cun++)
      for (int cin=0;cin<=7;cin++)
	  {
		  int res=convert(cb,cu,ci,cbn,cun,cin,g[v].teg,g[v].color);
		  for (int i=0;i<l;i++)
			  res+=len(g[v].next[i],cbn,cun,cin);
		  minres=min(minres,res);
	  }
  t[v][cb][cu][ci]=minres;
  return minres;
};
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	string s;
	getline(cin,s);
	while (!cin.eof())
	{
		string s1;
		getline(cin,s1);
        s=s+s1;
	};
	stack<int> a;
	//printf("%s",s.data());
	int k=-1;
	for (int i=0;i<s.length();i++)
	{
		string s1;//="";
		for (;(i<s.length()) && (s[i]!='>');i++)
			s1=s1+s[i];
		if (s1[1]=='/')
		{
			a.pop();
			continue;
		};
		ver newver;
		if (!a.empty())
			g[a.top()].next.push_back(++k);
		else k++;
		newver.teg=s1[1]=='b'?0:s1[1]=='u'?1:2;
        string s2;//="";
		for (int j=s1.length()-2;s1[j]!=':';j--)
			s2=s1[j]+s2;
		newver.color=ctoi(s2);
		newver.next.resize(0);
		a.push(k);
		g.push_back(newver);	
	};
	int res=0;
	for (int i1=0;i1<100;i1++)
	  for (int i2=0;i2<=7;i2++)
	    for (int i3=0;i3<=7;i3++)
	      for (int i4=0;i4<=7;i4++)
			  t[i1][i2][i3][i4]=-1;
	for (int i=0;i<g.size();i++)
		res+=used[i]?0:len(i,0,0,0);
	printf("%d",res);
    

	return 0;
}