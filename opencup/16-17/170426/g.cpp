#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1e6;

char s[N + 1];
int n;

int main() {
	scanf("%s", s);
	n = strlen(s);

	int i = 0, j = 0;
	while (i < n && s[i] == 'L') i++;
	while (j < n && s[n - j - 1] == 'R') j++;
	printf("%d\n", min(i + j + 1, n));
}