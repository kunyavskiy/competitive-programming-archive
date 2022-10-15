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
                 

const int small[8] = { 0 ,4 ,8, 14, 20 , 24 , 28 , 34 };
const int big[5] = {0, 4, 16, 20, 24};

bool check(int n){
	if (n <= 37){
		for (int i = 0; i < 8; i++)
			if (small[i] == n)
				return true;
	    return false;
	}

	int temp = (n - 38)% 34;

	for (int i = 0; i < 5; i++)
		if (temp == big[i])
			return true;
	return false;

}


int main(){

  int n;
  cin >> n;
  cout << (check(n)?"Black\n":"White\n") << endl;

/*  for (int i = 0; i < 1000; i++)
  	if (check(i))
  		cout << i << endl;*/
  return 0;
}

