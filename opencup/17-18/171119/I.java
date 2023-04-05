import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * @author Pavel Mavrin
 */
public class I {

    private static final int MAX = 100000;

    private void solve() throws IOException {
        int n = nextInt();
        int[][] c = new int[n][];
        for (int i = 0; i < n; i++) {
            int x = nextInt();
            c[i] = new int[x];
            for (int j = 0; j < x; j++) {
                c[i][j] = nextInt() - 1;
            }
        }
        int[][] minL = calc(c);
        {
            int i = 0, j = n - 1;
            while (i < j) {
                int[] t = c[i];
                c[i] = c[j];
                c[j] = t;
                i++;
                j--;
            }
        }
        int[][] minR = calc(c);
        {
            int i = 0, j = n - 1;
            while (i < j) {
                int[] t = c[i];
                c[i] = c[j];
                c[j] = t;
                t = minR[i];
                minR[i] = minR[j];
                minR[j] = t;
                i++;
                j--;
            }
        }
        int[] last = new int[MAX];
        Arrays.fill(last, -1);
        int[] p = new int[MAX];
        int res = Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            int x = c[i].length;
            int m = 0;
            for (int j = 0; j < x; j++) {
                if (last[c[i][j]] != i) {
                    p[m++] = Math.min(minL[i][j], minR[i][j]);
                    last[c[i][j]] = i;
                }
            }
            Arrays.sort(p, 0, m);
            if (x > m) {
                res = Math.min(res, x - m + 1);
            }
            for (int j = m - 1; j >= 0; j--) {
                if (p[j] < Integer.MAX_VALUE) {
                    res = Math.min(res, p[j] + (m - j));
                }
            }
        }
        out.println(res);
    }

    private int[][] calc(int[][] c) {
        int n = c.length;
        int[][] res = new int[n][];
        int[] mins = new int[MAX];
        Arrays.fill(mins, Integer.MAX_VALUE);
        int[] last = new int[MAX];
        Arrays.fill(last, -1);
        int[] num = new int[MAX];
        for (int i = 0; i < n; i++) {
            int x = c[i].length;
            res[i] = new int[x];
            for (int j = 0; j < x; j++) {
                int q = c[i][j];
                if (last[q] == i) {
                    num[q]++;
                } else {
                    last[q] = i;
                    num[q] = 1;
                }
            }
            for (int j = 0; j < x; j++) {
                int q = c[i][j];
                res[i][j] = mins[q];
            }
            for (int j = 0; j < x; j++) {
                int q = c[i][j];
                mins[q] = Math.min(mins[q], c[i].length - num[q] + 1);
            }
        }
        return res;
    }

    // ------------------

    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st;
    PrintWriter out = new PrintWriter(System.out);

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    public static void main(String[] args) throws IOException {
        new I().run();
    }

    private void run() throws IOException {
        solve();
        out.close();
    }

}