
import java.io.*;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class P9 {

    private int solveTest() throws IOException {

        return 0;
    }

    private void solve() throws IOException {
        int n = nextInt();
        int k = nextInt();
        PriorityQueue<Karmon> pq = new PriorityQueue<>();
        int s = 0;
        for (int i = 0; i < n; i++) {
            int x = nextInt();
            pq.add(new Karmon(x));
            s += x;
            if (pq.size() > k) {
                Karmon kk = pq.remove();
                s -= kk.bp;
            }
            if (pq.size() == k) {
                out.print(s + " ");
            }
        }
        out.println();
    }

    class Karmon implements Comparable<Karmon> {
        int bp;

        public Karmon(int bp) {
            this.bp = bp;
        }

        @Override
        public int compareTo(Karmon karmon) {
            return Integer.compare(bp, karmon.bp);
        }
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
        new P9().run();
    }

    private void run() throws FileNotFoundException {
        br = new BufferedReader(new FileReader("input.txt"));
        out = new PrintWriter("output.txt");
        try {
            solve();
        } catch (IOException e) {
            e.printStackTrace();
        }
        out.close();
    }

}