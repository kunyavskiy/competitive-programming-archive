
import java.io.*;
import java.util.StringTokenizer;

public class C {

    private static final long MOD = (long) (1e9 + 7);

    private void solveTest() throws IOException {
        int n = nextInt();
        int[] x =new int[n];
        for(int i = 0; i < n; i++) {
            x[i] = nextInt();
        }
        n++;
        boolean[][] a = new boolean[n][n];
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                if (gcd(x[i], x[j]) > 1) {
                    a[i][j] = a[j][i] = true;
                }
            }
        }
        a[0][n - 1] = a[n - 1][0] = true;
        long[][] d = new long[n][n];
        long[][] d2 = new long[n][n];
        for (int l = n - 1; l >= 0; l--) {
            for (int r = l + 1; r < n; r++) {
                if (r <= l + 1) {
                    d[l][r] = 1;
                    d2[l][r] = 1;
                } else {
                    for (int m = l + 1; m < r; m++) {
                        if (a[l][m]) {
                            long q = d[l][m];
                            q *= d[m][r];
                            q %= MOD;
                            d[l][r] += q;
                            d[l][r] %= MOD;
                        }
                        if (a[r][m]) {
                            long q = d2[l][m];
                            q *= d[m][r];
                            q %= MOD;
                            d2[l][r] += q;
                            d2[l][r] %= MOD;
                        }
                    }
                    d[l][r] += d2[l][r];
                    d[l][r] %= MOD;
                }
//                System.out.println(l + " " + r + " " + d[l][r]);
            }
        }
        out.println(d[0][n - 1]);
    }

    private int gcd(int a, int b) {
        while (b > 0) {
            int c = a % b;
            a = b;
            b = c;
        }
        return a;
    }

    private void solve() throws IOException {
                solveTest();
    }

    // --------------------------------------

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    String next() throws IOException {
        try {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        } catch (Exception e) {
            throw new IOException();
        }
    }

    int nextInt() throws IOException {
        try {
            return Integer.parseInt(next());
        } catch (Exception e) {
            throw new IOException();
        }
    }

    public static void main(String[] args) throws FileNotFoundException {
        new C().run();
    }

    private void run() throws FileNotFoundException {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
        }
        out.close();
    }

}