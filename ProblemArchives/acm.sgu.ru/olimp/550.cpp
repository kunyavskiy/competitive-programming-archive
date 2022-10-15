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

int a[255];
int b[255];

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  string s1;
  string s2;
  cin>>s1;
  for (int i=0;i<s1.size();i++)
  	a[s1[i]]++;
  a['2']+=a['5'];
  a['5']=0;
  a['6']+=a['9'];
  a['9']=0;
  cin>>s2;
  for (int i=0;i<s2.size();i++)
  	b[s2[i]]++;
  b['2']+=b['5'];
  b['5']=0;
  b['6']+=b['9'];
  b['9']=0;
  int m=10000000;
  for (int i=0;i<255;i++)
  	if (a[i]!=0)
  		m=min(m,b[i]/a[i]);
  cout<<m<<endl;
  return 0;
}