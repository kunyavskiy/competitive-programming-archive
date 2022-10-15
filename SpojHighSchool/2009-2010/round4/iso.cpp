#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define int64 long long
#define ld long double
#define setval(a,v) memset(a,v,sizeof(a))
#define fileinout
using namespace std;

const int NVAL[12]={10,20,30,40,60,90,100,110,120,130,140,150};
const int MVAL[12]={15,30,40,70,90,130,130,170,130,140,180,260};


map<string,int> num;
string a[150];
int c[150];
vector<int> g[150];
int d[150];
int D[150];
ld pr[150];
bool USED[150];
bool used[150];
int thiscomp[150];
int n;
string ans;
string tans;
string obans;
int obsum;
int kol,tkol;
int sum,tsum;

void vibor(int v,bool write=true)
{
	if (write)
	{
		tans+='\n';
		tans+=a[v];
		tkol++;
		tsum+=c[v];
	}
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
	{
		int to=g[v][i];
		if (!used[to])
		{
			used[to]=true;
			int SZ=g[to].size();
			for (int j=0;j<SZ;j++)
				d[g[to][j]]--;
		} 				
	}
}

void genpr()
{
  for (int i=0;i<n;i++)
			pr[i]=(rand()%10000000+1)*1.0/(rand()%10000000+1); 
}

void genpr1()
{
  for (int i=0;i<n;i++)
			pr[i]=1; 
}


void genpr0()
{
  for (int i=0;i<n;i++)
			pr[i]=0; 
}


void genpri()
{
	ld aaa=0;
  for (int i=0;i<n;i++)
			pr[i]=i;
} 

void genprd()
{
  for (int i=0;i<n;i++)
			pr[i]=c[i]; 
}

bool comp(string a,string b)
{
	return c[num[a]]<c[num[b]];
}

void del()
{	
	stringstream a(tans);
	string tmp;
	memset(d,sizeof(d),0);
	vector<string> ANS;
	tans="";
	for (;a>>tmp;)
	{
		ANS.pb(tmp);
		int v=num[tmp];
		int sz=g[v].size();
		for (int i=0;i<sz;i++)
				d[g[v][i]]++;
	}	
	sort(ANS.begin(),ANS.end(),comp);
	for (int i=ANS.size()-1;i>=0;--i)
	{
		tmp=ANS[i];
		int v=num[tmp];
		bool q=true;
		int sz=g[v].size();
		for (int i=0;i<sz;i++)
		if (d[g[v][i]]==1)
		{
			q=false;
			break;
		}
		if (!q)
			tans+='\n'+tmp;
		else
			{
				tkol--;
				tsum-=c[v];
			}			
	}		  
}


void iterate()
{
		memcpy(used,USED,sizeof(used));
		memcpy(d,D,sizeof(D));
		tsum=0;
		tkol=0;
		tans="";
		int vs[150];
		int nt=0;
		for (int i=0;i<n;i++)
			if (thiscomp[i]==1)
				vs[nt++]=i;
		for (int i=0;i<nt;i++)
	  {
	  	int minnum=-1;
	  	for (int j=0;j<nt;j++)
	  	{
	  		if (d[vs[j]]!=0 && ((minnum==-1) || (d[vs[j]]*c[minnum]*pr[vs[j]]>d[minnum]*c[vs[j]]*pr[minnum])))
	  			minnum=vs[j];
	  	}
	  	if (minnum==-1)
	  		break;        	
	  	vibor(minnum);
	  }
	  if (sum*1.1>tsum)
	  	del();
	  if (sum>tsum)
	  {
		 	sum=tsum;
	  	ans=tans;
	  	kol=tkol;
	  }
}

void dfs(int v)
{
	thiscomp[v]=1;
	int sz=g[v].size();
	for (int i=0;i<sz;i++)
		if (thiscomp[g[v][i]]==0)
			dfs(g[v][i]);
}

bool findnewcomp()
{
	for (int i=0;i<n;i++)
		if (thiscomp[i]==1)
			thiscomp[i]=2;
	static int t=0;
	for (;t<n;t++)
		if (thiscomp[t]==0)
			{
				dfs(t);
				return true;
			}
	return false;
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  cin>>n;
  int por[150];
  for (int i=0;i<n;i++)
  	por[i]=i;
  random_shuffle(por,por+n);
  for (int i=0;i<n;i++)
  {
   	cin>>a[por[i]];
   	num[a[por[i]]]=por[i];
   	cin>>c[por[i]];
  }
  int m;
  cin>>m;    
 setval(g,false);
  for (int i=0;i<m;i++)
  	{
  		string s1,s2;
  		cin>>s1>>s2;
  		g[num[s1]].pb(num[s2]);
  		g[num[s2]].pb(num[s1]);
  		d[num[s1]]++;
  		d[num[s2]]++;
  	} 
  int x;
  cin>>x;
  for(int i=0;i<x;i++)
  {
  	string s;
  	cin>>s;
  	vibor(num[s],false);	
  }       
  obsum=0;
  obans="";
  int obkol=0;
  for (int i=0;i<n;i++)
  	if (!used[i])
  	{
  		if (g[i].size()==1)
				{                          
					int j=g[i][0];
					vibor(j,false);
					obsum+=c[j];
					obans+='\n'+a[j];
					obkol++;
				}						
		} 
	for (;findnewcomp();)
	{
	  memcpy(USED,used,sizeof(used));
		int tl=14000;
		memcpy(D,d,sizeof(d));
		sum=100000000;                   
		genpr1();
		iterate();
		genprd();
		iterate();
		genpr0();
		iterate();
		genpri();
		iterate();
		for (int times=0;times<tl;times++)
		{                                           
			genpr();
			iterate();
		}
		obsum+=sum;
		obans+=ans;
		obkol+=kol;                                         
	}
	printf("%d%s\n%d\n",obkol,obans.data(),obsum);
  return 0;
}