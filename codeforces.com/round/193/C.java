import sun.rmi.server.InactiveGroupException;

import java.io.*;
import java.util.Arrays;
import java.util.Collections;
import java.util.StringTokenizer;
import java.util.TreeSet;


/**
 * Created with IntelliJ IDEA.
 * User: Pavel Kunyavskiy
 * Date: 24/07/13
 * Time: 16:34
 */
public class C {

    class Order implements Comparable<Order>{
        int a,b;
        int id;
        @Override
        public int compareTo(Order o) {
            if (Integer.compare(b, o.b) != 0)
                return Integer.compare(b, o.b);
            if (Integer.compare(a, o.a) != 0)
                return -Integer.compare(a, o.a);
            return Integer.compare(id, o.id);
        }
    }

    class Pair implements Comparable<Pair>{
        int val,pos;
        Pair(int val, int pos){
            this.val = val;
            this.pos = pos;
        }

        @Override
        public int compareTo(Pair o) {
            if (Integer.compare(val, o.val) != 0)
                return -Integer.compare(val, o.val);
            return -Integer.compare(pos, o.pos);
        }
    }


    void solve() throws IOException {
        int n,p,k;
        n = nextInt();
        p = nextInt();
        k = nextInt();
        p -= k;
        Order[] a = new Order[n];
        for (int i = 0; i < n; i++){
            a[i] = new Order();
            a[i].a = nextInt();
            a[i].b = nextInt();
            a[i].id = i+1;
        }
        Arrays.sort(a);

        //for (Order order : a)
        //    System.err.println(order.a+" "+order.b);

        Pair[] b = new Pair[n-p];
        for (int i = p; i < n; i++)
            b[i-p] = new Pair(a[i].a, i);
        Arrays.sort(b);
        int minPos = n;

        for (int i = 0; i < k; i++){
            out.print(a[b[i].pos].id+" ");
            minPos = Math.min(minPos, b[i].pos);
        }
        //System.err.println(minPos);

        Pair[] c = new Pair[minPos];
        for (int i = 0; i < minPos; i++)
            c[i] = new Pair(a[i].b, i);

        Arrays.sort(c);
        for (int i = 0; i < p; i++)
            out.print(a[c[i].pos].id + " ");
        out.println();
    }

    public static void main(String[] args) throws IOException {
        new C().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException {
        try {
            boolean oj = System.getProperty("ONLINE_JUDGE") != null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    String nextToken() throws IOException {
        while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            tokenizer = new StringTokenizer(in.readLine());
        }
        return tokenizer.nextToken();
    }
}
