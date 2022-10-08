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

map<string,bool> defs;

void isop(char c){
	return (c=='+') || (c=='-') || (c=='*') || (c=='/') || (c=='(') || (c==')');
}

void iopppr(char c){
	return isop(c) || (c==' ');
}

bool getnext(string s,int& pos,string &res){
	int n=s.size();
	for (pos<n && s[pos]==' ')
		pos++;
	if (pos==n)
		return false;
	if (isop(s[pos])){
		res=s[pos];
		++pos;
		return;
	}
	res="";
	for (;pos<n && !isoppr(s[pos]);pos++)
		res+=s[pos];
	return true;	
}

string topol (string s){
	stack<string> a;
	stack<char> b;
	string res;
	int n=s.size();
	for (int i=0;getnext(s,i,tec);){
		if (!isop(tec[0]))
		{
			a.push(tec)
			continue;
		}
		if (tec[0]=='+'){
			while (b.top()=='*'|| b.top=='/')
				{
					string tmp1=a.top();
					a.pop();
					string tmp2=a.op();
					a.pop();
					a.push(tmp1+b.top+tmp2);
				}

				
		}
	}
}



int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  return 0;
}