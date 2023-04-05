
import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class E {

    private void solveTest() throws IOException {
        int n = nextInt();
        long[] a = new long[n];
        long[] b = new long[n];
        long[] c = new long[2 * n + 1];
        for (int i = 0; i < n; i++) {
            a[i] = nextInt();
        }
        for (int i = 0; i < n; i++) {
            b[i] = nextInt();
        }
        for (int i = 0; i < 2 * n + 1; i++) {
            c[i] = nextInt();
        }
        b[0] = Math.min(b[0], c[0]);
        a[n - 1] = Math.min(a[n - 1], c[2 * n]);
        long d = b[0];
        long res = Long.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            res = Math.min(res, d + c[2 * i + 1] + a[i]);
            if (i < n - 1) {
                d = Math.min(d + c[2 * i + 1] + c[2 * i + 2], b[i + 1]);
            }
        }
        d = b[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            res = Math.min(res, d + c[2 * i + 2] + a[i]);
            if (i > 0) {
                d = Math.min(d + c[2 * i + 1] + c[2 * i + 2], b[i]);
            }
        }
        out.println(res);
    }

    private void solve() throws IOException {
        while (true) {
            try {
                solveTest();
            } catch (IOException e) {
                return;
            }
        }
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
        new E().run();
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