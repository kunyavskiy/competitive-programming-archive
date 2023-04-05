    #include <bits/stdc++.h>

    using namespace std; 

    #define forn(i, n) for (int i = 0; i < (int)(n); i++)

    typedef long double dbl;
    typedef long long ll;

    const dbl EPS = 1e-6;

    int main() {
        int n;
        scanf("%d", &n);
        if (n <= 3) {
            puts("0");
            return 0;
        }
        pair<int, int> p[n];
        forn(i, n) scanf("%d%d", &p[i].first, &p[i].second);
        sort(p, p + n);
        vector<ll> sx(n + 1), sy(n + 1), sxx(n + 1), sxy(n + 1), syy(n + 1);
        forn(i, n) {
            sx[i + 1] = sx[i] + p[i].first;
            sxx[i + 1] = sxx[i] + (ll)p[i].first * p[i].first;
            sxy[i + 1] = sxy[i] + (ll)p[i].first * p[i].second;
            syy[i + 1] = syy[i] + (ll)p[i].second * p[i].second;
            sy[i + 1] = sy[i] + p[i].second;
        }
        dbl res = 1e100;
        auto F = [&]( vector<ll> &s, int l, int r ) {
            return s[r] - s[l];
        };
        auto get_res = [&]( dbl k, dbl b, int l, int r ) {
            return k * k * F(sxx, l, r) + (r - l) * b * b + F(syy, l, r) + 
                2 * (k * b * F(sx, l, r) - b * F(sy, l, r) - k * F(sxy, l, r));
        };
        auto get_res2 = [&]( dbl z, dbl k, dbl b, int l, int r ) {
            return k * k * (F(sxx, l, r) + (r - l) * z * z - 2 * z * F(sx, l, r)) + (r - l) * b * b + F(syy, l, r) + 
                2 * (k * b * (F(sx, l, r) - z * (r - l)) - b * F(sy, l, r) - k * (F(sxy, l, r) - z * F(sy, l, r)));
        };
        auto solve = [&]( dbl &k, dbl &b, int l, int r ) {
            dbl a1 = F(sx, l, r), b1 = r - l, c1 = -F(sy, l, r);
            dbl a2 = F(sxx, l, r), b2 = F(sx, l, r), c2 = -F(sxy, l, r);
            k = -(c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1);
            b = (c1 * a2 - c2 * a1) / (a1 * b2 - a2 * b1);
            dbl sum = 0;
            for (int i = l; i < r; i++) sum += (k * p[i].first + b - p[i].second) * (k * p[i].first + b - p[i].second);
            // printf("l = %d, r = %d ---> k = %Lg b = %Lg : %Lg\n", l, r , k, b, sum);
            return get_res(k, b, l, r);
        };
        // forn(i, n)
        //     printf("%d : %d %d\n", i, p[i].first, p[i].second);
        auto isIn = [&]( int x1, int x2, dbl x ) {
            return x1 - EPS <= x && x <= x2 + EPS;
        };
        auto solve3 = [&]( int i, int z ) {
            dbl A1 = F(sxx, 0, i) - 2 * F(sx, 0, i) * z + (dbl)z * z * i;
            dbl B1 = 0;
            dbl C1 = F(sx, 0, i) - (dbl)z * i;
            dbl D1 = z * F(sy, 0, i) - F(sxy, 0, i);
            dbl A2 = 0;
            dbl B2 = F(sxx, i, n) - 2 * F(sx, i, n) * z + (dbl)z * z * (n - i);
            dbl C2 = F(sx, i, n) - (dbl)z * (n - i);
            dbl D2 = z * F(sy, i, n) - F(sxy, i, n);
            dbl A3 = F(sx, 0, i) - (dbl)z * i;
            dbl B3 = F(sx, i, n) - (dbl)z * (n - i);
            dbl C3 = n;
            dbl D3 = -F(sy, 0, n);
            dbl u;
            u = A3 / A1;
            A3 -= A1 * u, B3 -= B1 * u, C3 -= C1 * u, D3 -= D1 * u;
            u = B3 / B2;
            A3 -= A2 * u, B3 -= B2 * u, C3 -= C2 * u, D3 -= D2 * u;
            dbl b = -D3 / C3;
            dbl k2 = (-D2 - C2 * b) / B2;
            dbl k1 = (-D1 - C1 * b) / A1;
            return get_res2(z, k1, b, 0, i) + get_res2(z, k2, b, i, n);
        };
        for (int i = 2; i <= n - 2; i++) {
            dbl k1, b1, k2, b2;
            dbl r1 = solve(k1, b1, 0, i), r2 = solve(k2, b2, i, n);
            // printf("i = %d : point = %Lg [%d %d]\n", i, (b2 - b1) / (k1 - k2), p[i - 1].first, p[i].first);
            if (fabs(k1 - k2) < EPS || !isIn(p[i - 1].first, p[i].first, (b2 - b1) / (k1 - k2))) {
                res = min(res, solve3(i, p[i - 1].first));
                res = min(res, solve3(i, p[i].first));
            } else {
                // printf("i = %d : case 2 : %Lg + %Lg = %Lg\n", i , r1, r2, r1 + r2);
                res = min(res, r1 + r2);
            }
        }
        printf("%.15Lf\n", res / n);
    }
