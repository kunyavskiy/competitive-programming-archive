//#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( _WIN32 || __WIN32__ )
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

bool READONLY;

#define STARTREAD() if (READONLY) {ll ff; fgetpos(stdin, &ff); printf("%I64d\n", ff);}

#define ENDREAD() if (READONLY){ return;}


#define TASKNAME "A"
#define TASKMOD "dbg"

typedef long long ll;
typedef long double ld;

void PreCalc(){
}

void solve(){
    STARTREAD();
	int n, x;
	scanf("%d %d",&n,&x);
	vector<int> v(n);
	for (int i = 0; i < n; i++){
		scanf("%d",&v[i]);
	}
	ENDREAD();
	sort(v.begin(), v.end());
	int res = 0;
	while (!v.empty()){
		res++;
		int tmp = v.back(); v.pop_back();
		int id = upper_bound(v.begin(), v.end(), x - tmp) - v.begin() - 1;
		if (id != -1) v.erase(v.begin() + id);
	}
	printf("%d\n", res);
}


int main(int argc, char** argv){
  eprintf("%s\n", argv[1]);
  int ONETEST = -1;
  if (argc >= 2) {
  	if (!strcmp(argv[1], "READONLY")) READONLY = true;
	if (!strcmp(argv[1], "ONETEST")) ONETEST = atoi(argv[2]);
	eprintf("%d\n", READONLY);
  }
  freopen(TASKNAME"-"TASKMOD".in","r",stdin);
  if (READONLY) {
	  freopen(TASKNAME"-"TASKMOD".poses","w",stdout);
  } else if (ONETEST != -1) {
     FILE* poses = fopen(TASKNAME"-"TASKMOD".poses", "r");
     for (int i = 1; i <= ONETEST; i++) {
     	ll temp;
     	assert(fscanf(poses, "%I64d", &temp) == 1);
     	if (i == ONETEST) {
     		fsetpos(stdin, &temp);
     	}
     }
     fclose(poses);
     static char buf[200];
     sprintf(buf, TASKNAME"-"TASKMOD".out.%03d", ONETEST);
	 freopen(buf,"w",stdout);
  } else {
	  freopen(TASKNAME"-"TASKMOD".out","w",stdout);
  }
	
  PreCalc();
  TIMESTAMP(PreCalc);	

  int testNum;
  if (ONETEST == -1){
	  char buf[1000];
	  gets(buf);
	  sscanf(buf,"%d",&testNum);
  }

  int startTest = 1;
  int endTest = testNum;

  if (ONETEST != -1){
  	startTest = endTest = ONETEST;
  }

  for (int testId = startTest; testId <= endTest; testId++){
  	if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
	  	TIMESTAMPf("Test %d",testId);
	if (!READONLY) printf("Case #%d: ",testId);
  	solve();                        
  }
      
  TIMESTAMP(end);
  return 0;
}