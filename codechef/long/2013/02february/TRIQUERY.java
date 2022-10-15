import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

/**
 * Created with IntelliJ IDEA.
 * User: �
 * Date: 06/02/13
 * Time: 12:58
 * To change this template use File | Settings | File Templates.
 */
public class TRIQUERY {
    class BitTree{
        int[] bit;
        int n;

        BitTree(int n){
            this.n = n;
            bit = new int[n];
        }

        void update(int a,int dlt){
            for (;a < n; a = (a|(a+1)))
                bit[a] += dlt;
        }

        int get(int a){
            int ans = 0;
            for (;a >= 0; a = (a & (a+1))-1)
                ans += bit[a];
            return ans;
        }
    }

    class Event implements Comparable<Event>{
        int x,ly,ry;
        int type,id;

        Event(int x,int ly,int ry,int type,int id){
            this.x = x;
            this.ly = ly;
            this.ry = ry;
            this.type = type;
            this.id = id;
        }

        @Override
        public int compareTo(Event o) {
            if (x != o.x) return (x < o.x) ? -1 : ((x == o.x) ? 0 : 1);
            return (type < o.type) ? -1 : ((type == o.type) ? 0 : 1);
        }
    }

    void solve() throws IOException {
        int n = nextInt();
        int q = nextInt();
        int[] ans = new int[q];

        int[] x = new int[n], y = new int[n];
        int[] xq = new int[q], yq = new int[q],dq = new int[q];

        Event[] evs = new Event[q+n];
        for (int i = 0; i < n; i++){
            evs[i] = new Event(x[i] = nextInt(), y[i] = nextInt(),0,0,0);
        }
        for (int i = 0; i < q; i++){
            xq[i] = nextInt();
            yq[i] = nextInt();
            dq[i] = nextInt();
            evs[i+n] = new Event(xq[i],yq[i],yq[i]+dq[i],-1,i);
        }
        Arrays.sort(evs);
        BitTree bit = new BitTree(600000);
        for (Event ev : evs) {
            if (ev.type == 0)
                bit.update(ev.ly,1);
            else
                ans[ev.id] = - (bit.get(ev.ry) - bit.get(ev.ly - 1));
        }

        for (int i = 0; i < n; i++){
            evs[i] = new Event(x[i] + y[i], y[i],0,0,0);
        }
        for (int i = 0; i < q; i++){
            evs[i+n] = new Event(xq[i] + yq[i] + dq[i],yq[i],yq[i]+dq[i],1,i);
        }

        Arrays.sort(evs);
        bit = new BitTree(600000);
        for (Event ev : evs) {
            if (ev.type == 0)
                bit.update(ev.ly,1);
            else
                ans[ev.id] += (bit.get(ev.ry) - bit.get(ev.ly - 1));
        }

        for (int i : ans){
            out.println(i);
        }
    }

    public static void main(String[] args) throws IOException {
        new WORDPLAY().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException {
        try {
            boolean oj = System.getProperty("LOCAL") == null;
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