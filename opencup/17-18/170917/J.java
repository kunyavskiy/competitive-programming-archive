
import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class J {

    private static final long MOD = (long) (1e9 + 7);
    private int M;
    private long res;

    long[][] c;

    private void solve() throws IOException {
        int n = nextInt();
        M = nextInt() * 2;
        sx = new long[M + 1];
        sy = new long[M + 1];

        c = new long[M + 1][M + 1];
        for (int i = 0; i <= M; i++) {
            c[i][0] = c[i][i] = 1;
            for (int j = 1; j < i; j++) {
                c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
                c[i][j] %= MOD;
            }
        }

        init(n);
        for (int i = 0; i < n - 1; i++) {
            int x= nextInt() - 1;
            int y= nextInt() - 1;
            int w = nextInt();
            addEdge(x, y, w);
        }
        dfs(0, -1);
        out.println(res);
    }

    void init(int n) {
        this.n = n;
        this.m = (n - 1) * 2;
        last = 0;
        head = new int[n];
        nx = new int[m];
        dst = new int[m];
        wg = new int[m];
        Arrays.fill(head, -1);
    }


    void addEdge(int x, int y, int w) {
        nx[last] = head[x];
        dst[last] = y;
        wg[last] = w;
        head[x] = last;
        last++;
        nx[last] = head[y];
        dst[last] = x;
        wg[last] = w;
        head[y] = last;
        last++;
    }

    long[] sx;
    long[] sy;

    private int dfs(int x, int p) {
        int j = head[x];
        int s = 1;
        while (j >= 0) {
            int y = dst[j];
            if (y != p) {
                int ss = dfs(y, x);

                sx[0] = 1;
                sy[0] = 1;
                for (int q = 1; q < M; q++) {
                    sx[q] = (sx[q - 1] * ss) % MOD;
                    sy[q] = (sy[q - 1] * (n - ss)) % MOD;
                }
                long t = 0;
                for (int q = 1; q < M; q++) {
                    t += (((Math.min(q, M - q) * sx[q]) % MOD * sy[M - q]) % MOD * c[M][q]);
                    t %= MOD;
                }
                t *= wg[j];
                t %= MOD;
                res += t;
                res %= MOD;

                s += ss;
            }
            j = nx[j];
        }
        return s;
    }

    int n, m;
    int[] head;
    int[] nx;
    int[] dst;
    int[] wg;
    int last;


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
        new J().run();
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