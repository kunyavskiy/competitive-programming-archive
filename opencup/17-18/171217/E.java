
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public class E {

    private void solve() throws IOException {
        String pattern = nextLine();
        int l = pattern.length();
        List<String> lines = new ArrayList<>();
        String s;
        while ((s = nextLine()) != null) {
            lines.add(s);
        }
        int n = lines.size();
        int[][] nx = new int[l][256];
        for (int i = 0; i < 256; i++) {
            int j = 0;
            while (j < l && pattern.charAt(j) != i) {
                j++;
            }
            nx[l - 1][i] = j + 1;
        }
        for (int i = l - 1; i >= 0; i--) {
            if (i < l - 1) {
                for (int j = 0; j < 256; j++) {
                    nx[i][j] = nx[i + 1][j] + 1;
                }
            }
            nx[i][pattern.charAt(i)] = 0;
        }
        long t = 0;
        for (String line : lines) {
            int dt = 0;
            for (int i = 0; i < line.length(); i++) {
                char c = line.charAt(i);
                if (c == ' ') continue;
                int p = (int) ((i + t) % l);
                dt = Math.max(dt, nx[p][c]);
            }
            t += dt;
            t++;
//            System.err.println(t);
        }
        out.println(t);
    }

    // --------------------------------------

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    String nextLine() throws IOException {
        return br.readLine();
    }

    public static void main(String[] args) throws FileNotFoundException {
        new E().run();
    }

    private void run() throws FileNotFoundException {
//        br = new BufferedReader(new InputStreamReader(System.in));
        br = new BufferedReader(new FileReader("input.txt"));
        out = new PrintWriter(System.out);
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
        }
        out.close();
    }

}