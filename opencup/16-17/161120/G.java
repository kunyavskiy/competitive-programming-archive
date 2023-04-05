
import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

public class G {

    private void solve() throws IOException {
        int n = nextInt();
        double[] a = new double[n];
        double[] b = new double[n];
        for (int i = 0; i < n; i++) {
            a[i] = nextInt();
            b[i] = nextInt();
        }
        double l = 0;
        double r = 1e9;
        for (int i = 0; i < n; i++) {
            if (b[i] <= 0) r = Math.min(r, a[i]);
        }
        for (int iter = 0; iter < 100; iter++) {
            double h = (l + r) / 2;
            double min = 1e100;
            double max = -1e100;
            for (int i = 0; i < n; i++) {
                if (b[i] > 0) {
                    max = Math.max(max, (h - a[i]) / b[i]);
                }
                if (b[i] < 0) {
                    min = Math.min(min, (a[i] - h) / (-b[i]));
                }
            }
            if (n * max < min) {
                l = h;
            } else {
                r = h;
            }
        }
        out.println(l);
    }


    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    public static void main(String[] args) throws FileNotFoundException {
        new G().run();
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