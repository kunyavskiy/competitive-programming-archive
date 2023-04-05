
import java.io.*;
import java.util.StringTokenizer;

public class P12 {

    private void solve() throws IOException {
        int n = nextInt();
        for (int i = 0; i < n; i++) {
            String z = next();
            String x = next();
            String y = next();
            int[] a = calc(x, z);
            int[] b = calc(y, z);
            if (a[0] >= 0 && b[0] >= 0 && (b[1] >= a[0] + x.length() ||  a[1] >= b[0] + y.length())) {
                out.println("YES");
            } else {
                out.println("NO");
            }
        }
    }

    int[] calc(String x, String y) {
        String q = x + "%" + y;
        int[] p = new int[q.length() + 1];
        p[0] = -1;
        int[] res = new int[2];
        res[0] = res[1] = -1;
        for (int i = 1; i < p.length; i++) {
            int k = p[i - 1];
            while (k >= 0 && q.charAt(k) != q.charAt(i - 1)) k = p[k];
            p[i] = k + 1;
            if (p[i] == x.length()) {
                res[1] = i - x.length();
                if (res[0] == -1) res[0] = i - x.length();
            }
        }
        return res;
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
        new P12().run();
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