
import java.io.*;
import java.util.StringTokenizer;

public class I {

    private void solve() throws IOException {
        String s = next();
        boolean[] can = new boolean[4];
        for (int i = 0; i < s.length(); i++) {
            can["NSWE".indexOf(s.charAt(i))] = true;
        }
        String res = "";
        int k = 0;
        for (int i = 0; i < 4; i++) {
            if (can[i]) k |= (1 << (i / 2));
            if (!can[i] && can[i ^ 1]) {
                res += "NSWE".charAt(i);
            }
        }
        if (k == 3) {
            out.println(res);
        } else {
            out.println("X");
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
        new I().run();
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