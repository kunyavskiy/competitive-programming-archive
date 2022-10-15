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

int main()
{                        
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  int a,b,c,d;
  cin>>a>>b>>c>>d;
  if ((a+c==2*b) && (b+d==2*c))
  	{
  		printf("%d\n",2*d-c);
  		return 0;
  	}
  if ((a*c==b*b) && (b*d==c*c))
  {
  	int r=d*d/c;
  	if (r*c==d*d)
  		printf("%d",r);
  	else
  		printf("42\n");
  	return 0;
  }
  printf("42\n");
  return 0;
}