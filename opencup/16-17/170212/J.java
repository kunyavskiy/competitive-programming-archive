
import java.io.*;
import java.util.StringTokenizer;

public class J {

    private void solveTest() throws IOException {
        int n = nextInt();
        int k = nextInt();
        if (k == 1) {
            out.println(-1);
        } else {
            out.println((n * k + 1) / 2);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < k / 2; j++) {
                    out.println((i + 1) + " " + ((i + j + 1) % n + 1));
                }
                if (k % 2 == 1 && i < (n + 1) / 2) {
                    out.println((i + 1) + " " + ((i + n / 2) % n + 1));
                }
            }
            for (int i = 1; i <= n; i++) {
                out.print(i + " ");
            }
            out.println();
        }
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