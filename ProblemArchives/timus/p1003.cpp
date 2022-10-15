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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif


#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

struct req{
	int l, r, res,id;
};

bool cmp1(const req& a,const req& b){
	return a.l < b.l;
}

bool cmp2(const req& a,const req& b){
	return a.id < b.id;
}


req reqs[5100];
int n;

bool read(){
	scanf("%d",&n);
	if (n == -1)
		return 0;
	scanf("%d",&n);
	char buf[10];
	for (int i = 0; i < n; i++){
		int a,b;
		scanf("%d %d %s",&a,&b,buf);
		if (buf[0] == 'e')
			reqs[i].res = 0;
		else
			reqs[i].res = 1;
		reqs[i].l = a;
		reqs[i].r = b;
		reqs[i].id = i;
	}
	reqs[n].l = reqs[n].r = 1<<30;
	return true;
}

int p[11000];
map<int,int> num;

int get(int i){
	if (num.find(i) == num.end()){
		int temp = num.size();
		p[temp] = temp;
		return num[i] = temp;
	}
	return num[i];
}

int root(int a){
	if (a == p[a])
		return a;
	return p[a] = root(p[a]);
}

void join(int a,int b){
	a = root(a);
	b = root(b);
	if (a != b)
		p[a] = b;
}


void solve(){

	num.clear();

	for (int i = 0; i < n; i++){
		reqs[i].l = get(reqs[i].l-1);
		reqs[i].r = get(reqs[i].r);
	}

	int cnt = num.size();

	for (int i = 0; i < 2*cnt; i++)
		p[i] = i;

	for (int i = 0; i < n; i++){
		join(reqs[i].l*2,reqs[i].r*2 + reqs[i].res);
		join(reqs[i].l*2+1,reqs[i].r*2 + !reqs[i].res);


		bool ok = true;

		for (int j = 0; j < cnt; j++)
			if (root(2*j) == root(2*j+1))
				ok = false;

		if (!ok){
			printf("%d\n",i);	
			return;
		}
	}
	printf("%d\n",n);	
	return ;
}



int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	while (read())
		solve();
  return 0;
}