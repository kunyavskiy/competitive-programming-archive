#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

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

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

char buf[100];
bool s[15][15];

bool good(int x,int y){
	if (x < 0 || y < 0 || x >= 15 || y >= 15)
		return false;
	if (!s[x][y])
		return false;
	return true;
}

int cnt = 0,n;

void bfs(int x,int y){

	queue<int> qx,qy;
	qx.push(x);
	qy.push(y);

	while (!qx.empty()){
		int x = qx.front(),y = qy.front();
		qx.pop();qy.pop();

		string s = "";
		cnt++;
		if (good(x+1,y))
			s += "R";
		if (good(x,y+1))
			s += "T";
		if (good(x-1,y))
			s += "L";
		if (good(x,y-1))
			s += "B";

		if (good(x+1,y))
			::s[x+1][y] = 0;
		if (good(x,y+1))
			::s[x][y+1] = 0;
		if (good(x-1,y))
			::s[x-1][y] = 0;
		if (good(x,y-1))
			::s[x][y-1] = 0;

		if (cnt == n)
			s += '.';
		else
			s += ',';
		puts(s.data());

	//	cerr << s << endl;

	    for (int i = 0; i+1 < s.size(); i++)
    		if (s[i] == 'R')
    			qx.push(x+1),qy.push(y);
	    	else if (s[i] == 'T')
    			qx.push(x),qy.push(y+1);
    		else if (s[i] == 'L')
    			qx.push(x-1),qy.push(y);
	    	else if (s[i] == 'B')
    			qx.push(x),qy.push(y-1);
   }
}

void bfsr(int x,int y){
	queue<int> qx,qy;
	qx.push(x),qy.push(y);
	while (!qx.empty()){
		int x = qx.front(),y = qy.front();
		qx.pop();qy.pop();
		::s[x][y] = true;
		char s[50];
		gets(s);
	    for (int i = 0; s[i+1]; i++)
    		if (s[i] == 'R')
    			qx.push(x+1),qy.push(y);
	    	else if (s[i] == 'T')
    			qx.push(x),qy.push(y+1);
    		else if (s[i] == 'L')
    			qx.push(x-1),qy.push(y);
	    	else if (s[i] == 'B')
    			qx.push(x),qy.push(y-1);
   }
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	gets(buf);
	int x,y;
	if (sscanf(buf,"%d %d",&x,&y) == 1){
		n = x;
		for (int i = 0; i < n; i++){
			int x,y;
			scanf("%d %d",&x,&y);
			s[x][y] = true;
		}

		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				if (s[i][j]){
					s[i][j] = 0;
					printf("%d %d\n",i,j);
					bfs(i,j);
					return 0;
				}			
	}

	bfsr(x,y);

	int cnt = 0;
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (s[i][j])
				cnt++;
	printf("%d\n",cnt);
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			if (s[i][j])
  				printf("%d %d\n",i,j);
    return 0;
}