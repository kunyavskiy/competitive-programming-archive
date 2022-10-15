#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class IntoTheMatrix2 {


public:
    int takePills(int turns, int need) {
    	const int magic = 22;
    	vector<ll> can(magic);
    	vector< vector<ll> > c(magic, vector<ll>(magic, 0));
    	c[0][0] = 1;
    	for (int i = 0; i < magic; i++)
    		for (int j = 0; j < magic; j++){	
    			if (i) c[i][j] += c[i-1][j];
    			if (i && j) c[i][j] += c[i-1][j-1];
    		}
    			
    	for (int i = 0; i < (int)can.size(); i++)
    		can[i] = 1;
    		
    	for (int i = 0; i < turns; i++) {
    		for (int j = magic - 1; j >= 0; j--) {
    			ll res = 0;
    			for (int k = 0; k <= j; k++)
    				res += c[j][k] * can[j - k];
    			can[j] = res;
    		}
    	}
    	for (int i = 0; i < magic; i++)
    		if (can[i] >= need)
    			return i;
    	assert(false);    			
    }
};

class IntoTheMatrix {


public:
    int takePills(int turns, int need) {
    	long long res = 1;
    	for (int i = 0; ; i++) {
    		if (res >= need) return i;
    		res *= turns + 1;
    	}
    }
};



int main(){
	while (true) {
		int turns = rand() % 10 + 1;
		int need = rand() % 1000000 + 1;
		printf("%d %d\n", turns, need);
		assert(IntoTheMatrix().takePills(turns, need) == IntoTheMatrix2().takePills(turns, need));
	}
}