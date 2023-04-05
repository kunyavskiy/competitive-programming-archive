
import java.io.*;
import java.util.StringTokenizer;

public class L {

    int[] p;
    int[] r;
    int[] w;

    private void solveTest() throws IOException {
        int n = nextInt();
        int m = nextInt();
        char[][] a = new char[n][];
        for (int i = 0; i < n; i++) {
            a[i] = next().toCharArray();
        }
        p = new int[n + m];
        r = new int[n + m];
        w = new int[n + m];
        for (int i = 0; i < n + m; i++) {
            p[i] = i;
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == '+') {
                    int x = get(i);
                    int y = get(n + j);
                    if (x != y) {
                        join(x, y);
                    }
                    x = get(x);
                    w[x]++;
                }
            }
        }
        int res = 0;
        int resx = 0;
        int resy = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (a[i][j] == '.') {
                    int x = get(i);
                    int y = get(n + j);
                    if (x != y) {
                        if (w[x] + w[y] > res) {
                            res = w[x] + w[y];
                            resx = i + 1;
                            resy = j + 1;
                        }
                    } else {
                        if (w[x] > res) {
                            res = w[x];
                            resx = i + 1;
                            resy = j + 1;
                        }
                    }
                }
            }
        }
        out.println(res);
        if (res > 0) {
            out.println(resx + " " + resy);
        }
    }

    private void join(int x, int y) {
        if (r[x] <= r[y]) {
            p[x] = y;
            w[y] += w[x];
            if (r[x] == r[y]) r[y]++;
        } else {
            p[y] = x;
            w[x] += w[y];
        }
    }

    private int get(int i) {
        if (p[i] != i)
            p[i] = get(p[i]);
        return p[i];
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
        new L().run();
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