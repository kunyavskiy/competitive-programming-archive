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
#define pb push_back
#define mp make_pair      
using namespace std;
 
typedef long long ll;
typedef long double ld;


class WallGameDiv1 {

int downcost[50];
int dp[55][55][2];

int sum[55];

void initsum(string s){
	int m = s.size();
	for (int i = 0; i < m; i++)
		sum[i+1] = sum[i] + s[i] - '0';
}

int getsum(int l,int r){
	return sum[r] - sum[l];
}


public:
    int play(vector <string> v) {
    	int n = v.size();
    	int m = v[0].size();
    	for (int j = 0; j < m; j++)
    		downcost[j] = v[n-1][j] - '0';
        for (int it = n-2; it >= 0; it--){
        	initsum(v[it]);
        	memset(dp,0x3f,sizeof(dp));
        	dp[0][m][0] = -(1<<30);
        	dp[0][m][1] = -(1<<30);
        	for (int len = m-1; len > 0; len--){
        		for (int lf = 0; lf + len <= m; lf++){
        			int rg = lf + len;
        			dp[lf][rg][0] = 1<<30;
        			if (rg != m) {
        				dp[lf][rg][0] = min(dp[lf][rg][0], max(dp[lf][rg+1][1], downcost[rg]) + getsum(lf+1,rg+1));
        				dp[lf][rg][1] = min(dp[lf][rg][1], max(dp[lf][rg+1][1], downcost[rg]) + getsum(rg,rg+1));
        			}
        			if (lf != 0) {
        				dp[lf][rg][0] = min(dp[lf][rg][0], max(dp[lf-1][rg][0], downcost[lf-1]) + getsum(lf-1,lf));
        				dp[lf][rg][1] = min(dp[lf][rg][1], max(dp[lf-1][rg][0], downcost[lf-1]) + getsum(lf-1,rg-1));
        			}
        		}
        	}
        	for (int i = 0; i < m; i++)
        		downcost[i] = max(dp[i][i+1][0] + getsum(i,i+1), v[0][i] + downcost[i] - '0');
        }
        
        int ans = 1<<30;
        for (int i = 0; i < m; i++)
        	ans = min(ans, downcost[i]);
        return ans;
    }
};







// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.8 (beta) modified by pivanof
#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool KawigiEdit_RunTest(int testNum, vector <string> p0, bool hasAnswer, int p1) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	WallGameDiv1 *obj;
	int answer;
	obj = new WallGameDiv1();
	clock_t startTime = clock();
	answer = obj->play(p0);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p1 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p1;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	vector <string> p0;
	int p1;
	
	{
	// ----- test 0 -----
	string t0[] = {"12","34"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 6;
	all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"99999","99999","99999"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 99;
	all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"11111","90005"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 10;
	all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"4417231387449337370319219832088987579792","3117295688208899006196193430472892512797","0835796222361526836944954410684516919758","1988200069973565052900745230547016216225","8080511471118865780390486996601082102418","4229084185957675819725844582167613108400","9068653877952162764545674979144308771754","8551565425951612499712254182109991511690","7090525592007482152807163656647658543093","9198968742256995592729889137556032960142","2071864379877766468141740053503050313101","1055375249261868472993219156394129253481","2461178270502857106406495509025426298874","8216781259733537757203421037984512664825","4693452554407216935375049784445568498482","2709693439640250842244170297203200674391","5122217695676372684217182241705137947908","6668814191410691246849638388008228444294","4952122070212780440963814752538149378639","9827737761436134120332969866554332504400","3412406588339828249986707470540386748886","7521506848088506994554600408372456405830","1916926179183007872881163173153907665999","66361667914"
			"72761992310264951474925339024","6679667717747231380196787943691121008076","3218993234115685151069259138068533004433","4920152552986426962081492913852060211795","0365186235986445521382132973036266396894","3205351414936828189305188614651974318855","3144278971529524658788277656125598825426","5525287537572356662391582052968411726245","2130137226726919525622574701068062252930","2369996694245544770519574837226971226841","6806769058165410189286521891570936341547","0448109211631660241710734664066810078242","4622919135804954122810530631429501069659","0235247446548732490429856705369583140671","2193399741215975228987754171460722199304","1203037020703833716225328076959743850915","5419885193880826109484912489603262199432"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 7366;
	all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
