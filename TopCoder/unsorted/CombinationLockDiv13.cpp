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

const int MAXS = 71;

class CombinationLockDiv1 {

string s, t;

string concat(vector<string> _s){
	string res = "";
	for (int i = 0; i < (int)_s.size(); i++)
		res += _s[i];
	return res;
}


int dp[2][MAXS][MAXS];

public:
    int minimumMoves(vector <string> _s, vector <string> _t) {
        s = concat(_s);
        t = concat(_t);
        	
        memset(dp, 0x3f, sizeof(dp));
        dp[0][0][0] = 0;
        
        for (int i = 0; i < (int)s.size(); i++){
        	int from = s[i] - '0';
        	int to = t[i] - '0';
        	
        	int from2, to2;
        	from2 = (!i ? 0 : s[i-1] - '0');
        	to2 = (!i ? 0 : t[i-1] - '0');
        	
        	for (int up = 0; up < MAXS; up++)
        		for (int down = (from + up - to + 20) % 10; down < MAXS; down+=10){
       				for (int j = 0; j < MAXS; j++)
		        		for (int k = (from2 + j - to2 + 20) % 10; k < MAXS; k+=10)
       						dp[1][up][down] = min(dp[1][up][down], dp[0][j][k] + max(0, up - j) + max(0, down - k));
        		}
        	memcpy(dp[0], dp[1], sizeof(dp[0]));
        	memset(dp[1], 0x3f, sizeof(dp[1]));
        }
        
        int ans = dp[0][0][0];
        for (int i = 0; i < MAXS; i++)
        	for (int j = 0; j < MAXS; j++)
        		ans = min(ans, dp[0][i][j]);
        	
        return ans;   	
    }
};

int main(){
	string s, t;
	getline(cin, s);
	getline(cin, t);
	cout << CombinationLockDiv1().minimumMoves(vector<string>(1, s), vector<string>(1, t)) << endl;
}