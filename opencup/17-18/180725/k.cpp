#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

// n = int(input())
// for i in range(n):
//     h, m, z = input().split()
//     h = int(h)
//     m = h * 60 + int(m)
//     z = float(z[3:])
//     mm = m - 8 * 60 + int(z * 60)
//     mm %= (60 * 24)
//     hh = mm // 60
//     mm = mm % 60
//     print(str(hh // 10) + str(hh % 10) + ":" + str(mm // 10) + str(mm % 10))


int main() {
    int n;
    scanf("%d", &n);
    char str[100];
    while (n--) {
        int h, m;
        scanf("%d%d %s", &h, &m, str);
        m = h * 60 + int(m);
        double z;
        sscanf(str + 3, "%lf", &z);
        // printf("%d %d %lf\n", h, m, z);
        int mm = m - 8 * 60 + int(round(z * 60));
        const int mod = 60 * 24;
        mm = (mm % mod + mod) % mod;
        int hh = mm / 60;
        mm = mm % 60;
        printf("%02d:%02d\n", hh, mm);
    }
}