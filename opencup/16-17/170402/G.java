
import java.io.*;
import java.util.StringTokenizer;

public class G {

    private void solveTest() throws IOException {
        int n = nextInt();
        int[] p = readPoint();
        int[] v = readPoint();
        int[][] a = new int[n][];
        for (int i = 0; i < n; i++) {
            a[i] = readPoint();
        }
        for (int i = 0; i < n; i++) {
            System.out.println("dotlabel.top(btex " + (i + 1) + " etex," + getString(a[i]) + ");");
        }
        int x = nextInt();
        System.out.println("draw(" + getString(a[x - 1]));
        for (int i = 0; i < n; i++) {
            x = nextInt();
            System.out.println("--" + getString(a[x - 1]));
        }
        System.out.println(";");
    }

    private String getString(int[] ints) {
        return "(" + ints[0] + "cm, " + ints[1] + "cm)";
    }

    private int[] readPoint() throws IOException {
        return new int[]{nextInt(), nextInt()};
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