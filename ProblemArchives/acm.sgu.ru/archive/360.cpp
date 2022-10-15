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

struct func;

map<char,func> af;

struct func{
	string code;
	char a,b;
	func(string _c="",char _c1='?',char _c2='?')
	{
		code=_c;
		a=_c1;
		b=_c2;
	}
	string operator() (char c='?',char c1='?')
	{
		//cerr<<"call: "<<code<<" with "<<a<<" = "<<c<<" & "<<b<<" = "<<c1<<endl;
		string v="";
		for (int i=0;i<code.size();i++)
		{
			if (code[i]==a)
				v+=c;
			else if (code[i]==b)
				v+=c1;
			else if (code[i]=='L' || code[i]=='R' || code[i]=='C')
				v+=code[i];
			else {
				char n=code[i];	
			//	cerr<<"Found call of "<<n<<endl;
				i++;
				assert(code[i]=='(');
				i++;
				if (code[i]==')')
				{
				//	cerr<<"found no parametrs"<<endl;
					v+=af[n]();
					//cerr<<"end  of "<<n<<endl;
					continue;
				}
				char p1=code[i];
				if (p1==a)
					p1=c;
				else if (p1==b)
					p1=c1;					
				i++;
				if (code[i]==')')
				{
				//	cerr<<"found 1 parametrs: "<<p1<<endl;
					v+=af[n](p1);
				//	cerr<<"end  of "<<n<<endl;
					continue;					
				}
				assert(code[i]==',');
				i++;
				char p2=code[i];
				if (p2==a)					
					p2=c;
				else if (p2==b)
					p2=c1;
				//cerr<<"found 2 parametrs: "<<p1<<" "<<p2<<endl;
				i++;
				assert(code[i]==')');
				v+=af[n](p1,p2);
					//cerr<<"end  of "<<n<<endl;
			}
		}
		return v;
	}	
};

char readfunc(func& res){
	char name,p1,p2;
	p1='?';
	p2='?';
	int g;
	g=scanf(" %c ( %c , %c ) {",&name,&p1,&p2);
	if (g==0 || g==EOF)
		return 0;
	if (g==2 && p1!=')')
		scanf(" ) {");
	if (g==2 && p1==')')
	{
		scanf(" { ");
		p1='?';
	}
	string s;
	char c;
	for (scanf(" %c ",&c);c!='}';scanf(" %c ",&c))
		s+=c;
	res=func(s,p1,p2);
	return name;	
}

char a[50][50];
bool used[50][50];

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  int n,m;
  char c;
  cin>>n>>m;
  for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			cin>>a[i][j];
  func f;
  for (;;)	
  {
  	char c=readfunc(f);
  	if (c==0)
  		break;
  	af[c]=f;  	
  }
	string prog=af['m']();
	int vx=-1;
	int vy=0;
	int x,y;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (a[i][j]=='R')
			{
				x=i;
				y=j;		
			}
	used[x][y]=true;
	int kol=0;
	string s;
	//cerr<<"PROGRM: "<<prog<<endl;	
	for (int i=0;i<prog.size();i++)
	{
		if (prog[i]=='C')
		{
			if (x+vx>=0 && x+vx<n && y+vy>=0 && y+vy<m)
				{
					x=x+vx;
					y=y+vy;
					if (a[x][y]=='*')
					{
						kol++;
						char S[50];
						sprintf(S,"%d %d",x+1,y+1);
						s=s+S+'\n';
						a[x][y]='~';
					}
				//	cerr<<"Go to "<<x<<" "<<y<<endl;
					continue;
				}		
		//	cerr<<"IGNORE"<<endl;
		}
		else if (prog[i]=='L')
		{
			int tmp=vx;
			vx=-vy;
			vy=tmp;
		//	cerr<<"TURN TO "<<vx<<" "<<vy<<endl;;
		}
		else if (prog[i]=='R')
		{
			int tmp=vx;
			vx=vy;
			vy=-tmp;
	//		cerr<<"TURN TO "<<vx<<" "<<vy<<endl;
		}
	}
	printf("%d\n%s",kol,s.data());
  return 0;
}