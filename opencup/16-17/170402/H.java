
import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;

public class H {

    private void solveTest() throws IOException {
        int n = nextInt();
        int m = nextInt();

        int[][] x = new int[n + 1][2];
        x[0][0] = x[n][0] = 1;
        x[0][1] = nextInt();
        x[n][1] = nextInt();
        for (int i = 1; i < n; i++) {
            x[i][0] = nextInt();
            x[i][1] = nextInt();
        }

        int[] d = new int[n + 1];

        for (int i = 0; i <= n; i++) {
            if (i == n || x[i][0] == 1) {
                int j = i - 1;
                while (j >= 0 && x[j][0] == 2) {
                    j--;
                }
                if (j == i - 1) {
                    if (j < 0) {
                        d[i] = 0;
                    } else {
                        d[i] = d[j] + Math.abs(x[i][1] - x[j][1]);
                    }
                    continue;
                }
                Arrays.sort(x, j + 1, i, new Comparator<int[]>() {
                    @Override
                    public int compare(int[] a, int[] b) {
                        return Integer.compare(a[1], b[1]);
                    }
                });
                d[i] = Integer.MAX_VALUE;
                for (int k = j + 1; k <= i; k++) {
                    int min = Integer.MAX_VALUE;
                    int max = Integer.MIN_VALUE;
                    if (k > j + 1) {
                        min = Math.min(min, m + 1 - x[k - 1][1]);
                        max = Math.max(max, m + 1 - x[j + 1][1]);
                    }
                    if (k < i) {
                        min = Math.min(min, x[k][1]);
                        max = Math.max(max, x[i - 1][1]);
                    }
//                    System.out.println(i + " " + j + "   " + min + " " + max);
                    if (j >= 0) {
                        d[i] = Math.min(d[i], d[j] + Math.abs(x[j][1] - min) + Math.abs(x[i][1] - max) + Math.abs(min - max));
                        d[i] = Math.min(d[i], d[j] + Math.abs(x[j][1] - max) + Math.abs(x[i][1] - min) + Math.abs(min - max));
                    } else {
                        d[i] = Math.min(d[i], Math.abs(x[i][1] - max) + Math.abs(min - max));
                        d[i] = Math.min(d[i], Math.abs(x[i][1] - min) + Math.abs(min - max));
                    }
                }
            }
        }
//        System.out.println(Arrays.toString(d));
        out.println(d[n]);
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
        new H().run();
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