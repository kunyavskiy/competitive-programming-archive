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
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char a[4][4];
char b[4][4];
char t[4][4];

void print(){
	for (int i = 0; i < 4; i++)
		for (int j = 0; j <4; j++)
			if (a[i][j] == 'X')
				printf("%c",b[i][j]);
}

void rotate(){
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			t[j][3-i] = a[i][j];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			a[i][j] = t[i][j];
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

  for (int i = 0; i < 4; i++)
  	for (int j = 0; j < 4; j++)
  		scanf(" %c ",&a[i][j]);
  for (int i = 0; i < 4; i++)
  	for (int j = 0; j < 4; j++)
  		scanf(" %c ",&b[i][j]);

  print();  rotate();
  print();  rotate();
  print();  rotate();
  print();  rotate();

  return 0;
}