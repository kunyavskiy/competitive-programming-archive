#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define timestamp(str) eprintf("[ "str" ] time=%.4lf\n", clock() / double(CLOCKS_PER_SEC))
#else
#define eprintf(...)
#define timestamp(str)
#endif
#define sz(x) (int)((x).size())

typedef long long ll;
typedef double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME ""

const long long linf = 1e18;
const int inf = 1e9;
const double eps = 1e-9;
#define INF inf
#define EPS eps

void solve() {
        ld a, b, c;
        cin>>a>>b>>c;

        ld coef = c/(2.0/sqrt(3.0));
        ld s = sqrt((a+b+c)*(a+b-c)*(a-b+c)*(-a+b+c))/4.0;
        ld h = (2.0*s)/c;

        a/=coef, b/=coef, c/=coef, h/=coef;

        ld x = sqrt(a*a-h*h);

        ld DD = 1.0;
        ld AA = h;
        ld CC = 0;
        ld BB = x-1.0/(sqrt(3.0));

        ld det = AA*DD-BB*CC;
        AA/=det;
        BB/=det;
        CC/=det;
        DD/=det;

        ld A = AA*AA+CC*CC;
        ld B = AA*BB+CC*DD;
        ld C = B;
        ld D = BB*BB+DD*DD;

        //A,B,C,D 1

        //System.err.println(A+" "+B+" "+C+" "+D);

        ld beta = A+D;
        ld alpha = A*D-B*C;



        ld disc =(beta*beta-4.0*alpha);

        //BigDecimal aa = (beta.add(sqrt(disc)).divide(BigDecimal.valueOf(2.0)));
        ld bb = (beta-sqrt(disc))/2.0;

        //aa = BigDecimal.valueOf(1.0).divide(aa,MathContext.DECIMAL128);
        bb = 1.0/bb;

        //aa = sqrt(aa);
        //bb = sqrt(bb);

        coef/=3.0;
        //Locale.setDefault(Locale.US);
        // System.err.printf("%.18f %.18f\n", A, disc);
        printf("%.12lf %.12lf\n", (double)(4.0*coef*sqrt(sqrt(disc)/(beta*beta-disc))), (double)(sqrt(bb)*coef));
//        out.printf("%.18f %.18f\n", (BigDecimal.valueOf(4).multiply(sqrt(sqrt(disc).divide(sqr(beta).subtract(disc),MathContext.DECIMAL128))).multiply(coef)), (sqrt(bb).multiply(coef)));
//  timestamp("end");
//  return 0;
}

int main(){
/*  #ifdef DEBUG
  freopen(TASKNAME ".in", "r", stdin);
  freopen(TASKNAME ".out", "w", stdout);
  #else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif*/

  int t;
//  scanf("%d",&t);
  t = 1;
  for (int i = 0; i < t; i++){
  	solve();
  }

}
