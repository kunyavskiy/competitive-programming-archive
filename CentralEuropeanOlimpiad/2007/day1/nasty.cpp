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
#include <sstream>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;


vector<char> ops;

char buf[110000];

void getfunk(){
	gets(buf);
	for (int i=0;buf[i];i++)
		if (buf[i+1] == ' ' || buf[i+1] == 0)
			ops.pb(buf[i]);
}

int res[40];
int n,b;

int _ctoi(char c){
	if ('0' <= c && c<='9')
		return c-'0';
	return c-'A'+10;
}

char _itoc(int i){
	if (i <= 9)
		return i+'0';
	return i+'A'-10;
}

int itoc[500];
int ctoi[500];

int st[110000],ptr;

int mult[40][40];

int calc(int x){
	if (res[x] != -1)
		return res[x];
	ptr = 0;
	int a,b;
	char c;
	for (int i=0,sz = ops.size();i<sz;i++){
		c = ops[i];
		if (c == 'x')
			st[ptr++] = x;
		else if (c == '+'){
			a = st[--ptr];b = st[--ptr];
			st[ptr++] = a+b;
			if (st[ptr-1] >= ::b) st[ptr-1] -= ::b;
		}
		else if (c == '-'){
			a = st[--ptr];b = st[--ptr];
			st[ptr++] = b-a;
			if (st[ptr-1] < 0) st[ptr-1] += ::b;
		}
		else if (c == '*'){
			a = st[--ptr];b = st[--ptr];
			st[ptr++] = mult[a][b];
		}
		else
			st[ptr++] = _ctoi(ops[i]);
	}	
	return res[x] = st[0];
}

int main(){
//	clock_t start = clock();
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	string s;
	getline(cin,s);
	sscanf(s.data(),"%d %d",&b,&n);
	getfunk();
	memset(res,-1,sizeof(res));
	for (int i=0;i<b;i++)
		for (int j=0;j<b;j++)
			mult[i][j] = (i*j)%b;
	for (int i=0;i<b;i++)
		itoc[i] = _itoc(i);
	for (int i='0';i<='9';i++)
		ctoi[i] = _ctoi(i);
	for (int i='A';i<='Z';i++)
		ctoi[i] = _ctoi(i);
		
	for (int i=0;i<n;i++){
		gets(buf);
		printf("%c\n",itoc[calc(ctoi[buf[strlen(buf)-1]])]);		
	}
	
//	cerr << (clock()-start)*1.0/CLOCKS_PER_SEC <<endl;
		
	return 0;
}