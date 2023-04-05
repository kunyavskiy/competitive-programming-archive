#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1e6, K = 20, VN = N * K + 1;

int to[VN][2], root, vn = 1;

int main() {
    int n, a, x = 0;
	scanf("%d", &n);
	forn(i, n) {
		scanf("%d", &a);
		x ^= a;
		// printf("add %d : \n", x);
		int v = root;
		for (int i = K - 1; i >= 0; i--) {
			// printf("-%d-> ", (x >> i) & 1);
			int &next = to[v][(x >> i) & 1];
			if (!next)
				next = vn++;
			v = next;
			// printf("%d ", v);
		}
		// puts("");

		int res = 0;
		// printf("x = %d\n" ,x);
		v = 0;
		for (int i = K - 1; i >= 0; i--) {
			int go = 0, bit = (x >> i) & 1;
			if (!bit) {
				//printf("i = %d : v = %d, to[1] = %d\n", i, v, to[v][1]);
				go = (to[v][1] ? 1 : 0);
			} else {
				go = (to[v][0] ? 0 : 1);//rand() % 2; // TODO
			}
			res |= go << i;
			v = to[v][go];
		}		
		printf("%d ", res + (x ^ res));

	}
	puts("");

}