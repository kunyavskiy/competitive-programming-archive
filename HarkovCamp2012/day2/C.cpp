#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <list>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>

#define mp make_pair
#define pb push_back
#define sqr(a) ((a) * (a))
#define zero(a) memset (a, 0, sizeof(a))
#define sz(a) (int)(a.size())

#ifdef LOCAL
	#define LLD "%I64d"
#else 
	#define LLD "%lld"
#endif

//#define DEBUG

using namespace std;

typedef long long ll;
typedef double ld; 
typedef unsigned long long ull;
typedef unsigned int uint;

#define taskname "c"

const int inf = 1000000000;
const ld eps = 1e-9;

const int MAXN = 366;

const ld TMAX = 100;
const ld TMIN = 0.1;
const ld DT = TMIN/TMAX;
const ld TL = 2;
const double DMAXUINT = double(1LL<<32); 

ld T;
ld start = clock();
ld t[366];
int n;

char cur[366];
char best[366];
ld curval,bestval;

uint myrand(){
	static uint seed = 156486u;
	return seed = seed*17239u+23917u;
}

double drand(){
	return double(myrand())/DMAXUINT;
}


bool TLE(){
	ld curt = (clock()-start)/CLOCKS_PER_SEC;
	if (curt > TL)
		return true;
	T = TMAX * pow(DT,curt/TL);
	#ifdef DEBUG
		fprintf(stderr,"Time = %lf of %lf\n",curt,TL);
		fprintf(stderr,"Temperature = %lf\n",T);
		fprintf(stderr,"Current = %lf\n",curval);
		fprintf(stderr,"Best = %lf\n",bestval);
	#endif
	return false;
}


const char* symb = "+-**";

void calc(){
	ld ans = 0;
	ld a = t[1];
	for (int i = 2; i <= n; i++){
		if (cur[i-2] == '*'){
			a = a * t[i];
		}
		else if (cur[i-2] == '+'){
			ans = ans + a;
			a = t[i];
		}
		else {
			assert(cur[i-2] == '-');
			ans = ans + a;
			a = -t[i];
		}
	}
	ans = ans + a;
    curval = abs(ans-n);
    if (bestval > curval+(1e-9)){
    	#ifdef DEBUG
    		fprintf(stderr,"Found %lf\n",curval);
    	#endif
    	memcpy(best,cur,sizeof(char)*(n-1));
    	bestval = curval;
    }
}

void iterate(){
	int id = myrand()%n;
	char nc = symb[myrand()%4];
	if (cur[id] == nc)
		return;
	char prev = cur[id];
	cur[id] = nc;
	ld old = curval;
	calc();
	if (drand() > exp((old - curval)/(max(old,curval))/T)){
		curval = old;
		cur[id] = prev;
	}		
}




int main(){
  freopen(taskname".in","r",stdin);
  freopen(taskname".out","w",stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
  	t[i] = tan(i);

  {
      FILE* f;
  	  char temp[20];
	  sprintf(temp,"answers\\%03d.out",n);
	  f = fopen(temp,"r");
	  fscanf(f,"%s",cur);
	  memcpy(best,cur,sizeof(char)*(n-1));
	  fclose(f);

	  calc();
	  bestval = curval;
  }
  
  for (; !TLE(); ){
  	for (int i = 0; i < 1000; i++)
  		iterate();
  }

  puts(best);
  return 0;
}

