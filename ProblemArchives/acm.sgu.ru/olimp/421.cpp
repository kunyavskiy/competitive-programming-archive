#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int inf =1<<25;
vector<int> t(1000);//,from(1000);
string text;
vector<string> slov(100),from(1000);


char makesmall(char c)
{
	return ((c<='z') && (c>='a'))?c:(char)((int)c-(int)'A'+(int)'a');
}

char makebig(char c)
{
	return !((c<='z') && (c>='a'))?c:(char)((int)c+(int)'A'-(int)'a');
}
int rast(char a,char b)
{
	a=makesmall(a);
	b=makesmall(b);
	return a<b?min(b-a,26-b+a):min(a-b,26-a+b);
}

int len(int sim)
{
	if (sim<-1)
	{
		return inf;
	}
	if (sim==-1)
	{
		return 0;
	}
	if (t[sim]!=inf)
	{
		return t[sim];
	}
	t[sim]=inf;
	int l=slov.size()-1;
	for (int i=0;i<=l;i++)
	  {
		  int l1=slov[i].length()-1;
		  int res=len(sim-l1-1);
		  if (res!=inf)
		  {		    
		    for (int j=0;j<=l1;j++)
			    res+=rast(slov[i][j],text[sim-l1+j]);
		    if (t[sim]>res)
				from[sim]=(sim-l1-1)==-1?slov[i]:from[sim-l1-1]+slov[i];
		    t[sim]=min(t[sim],res);
		  }
	  }
	return t[sim];
}



void print()
{
	int l=text.length();
	for(int i=0;i<l;i++)
		printf("%c",((text[i]<='z') && (text[i]>='a'))?makesmall(from[l-1][i]):makebig(from[l-1][i]));
}
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
    int n;
	scanf("%d\n",&n);
	slov.resize(n);
	for (int i=0;i<n;i++)
	{
		getline(cin,slov[i]);
		for (int j=0;j<slov[i].length();j++)
			if (slov[i][j]==' ')
				slov[i].erase(j--,1);
	}
	getline(cin,text);
		for (int j=0;j<text.length();j++)
			if (text[j]==' ')
				text.erase(j--,1);
//	t.resize(text.length());
//	from.resize(text.length());
	for (int i=0;i<text.length();i++)
	  t[i]=inf;
	int k=len(text.length()-1);
	if (k==inf)
		printf("-1");
	else
	  print();

}