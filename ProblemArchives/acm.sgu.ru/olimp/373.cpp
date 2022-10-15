#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <string>
#define mp make_pair
#define base 10000
#define outform "%04d"

using namespace std;
int main()
{
	freopen("input.txt","rt",stdin);
	freopen("output.txt","wt",stdout);
	string s;
    getline(cin,s);
	if (s.length()==1)
	{
		switch  (s[0])
		{
		case '0':printf("1\n0");
				 break;
		case '1':printf("1\n1");
				 break;
		case '2':printf("0");
			     break;
		case '3':printf("0");
				 break;
		}
		return 0;
	}
	if (s.length()==2)
	{
		switch (s[0])
		{
		case '0': if (s[1]=='0') printf("1\n00");
				  else printf("0");
				  break;
		case '1':if (s[1]=='1')
					 printf("2\n01\n10");
				 else
				     printf("0");
				  break;
		case '2':if (s[1]=='2')
					 printf("1\n11");
				 else
				     printf("0");
				  break;
		case '3':printf("0");
				  break;
		}
		return 0;
			  
	}
	vector<string> p(2);
	vector<int> q;
	int l=s.length();
	for (int i=0;i<l;i++)
		q.push_back((int)s[i]-(int)'0');
	p[0]='0';
	for (int i=1;i<l;i++)
	{
		int a=q[i-1]-(int)p[0][i-1]+(int)'0'-(i==1?0:(int)p[0][i-2]-int('0'));
		if ((a!=0) && (a!=1))
			break;
        p[0]+=(char)(a+(int)'0') ;
	}
	p[1]='1';
	for (int i=1;i<l;i++)
	{
		int a=q[i-1]-(int)p[1][i-1]+(int)'0'-(i==1?0:(int)p[1][i-2]-int('0'));
		if ((a!=0) && (a!=1))
			break;
        p[1]+=(char)(a+(int)'0'); 
	}
	vector<string> ans;
	if ((p[0].length()==l) && (((int)p[0][l-2]+(int)p[0][l-1]-int('0')-int('0'))==q[l-1]))
		ans.push_back(p[0]);
  
	if ((p[1].length()==l) && (((int)p[1][l-2]+(int)p[1][l-1]-int('0')-int('0'))==q[l-1]))
		ans.push_back(p[1]);
	printf("%d\n",ans.size());
	for (int i=0;i<ans.size();i++)
		printf("%s\n",ans[i].data());
   return 0;
	
}