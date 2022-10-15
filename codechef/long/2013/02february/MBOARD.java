import java.io.*;
import java.util.Arrays;
import java.util.StringTokenizer;

import static java.lang.System.*;


/**
 * Created with IntelliJ IDEA.
 * User: �
 * Date: 05/02/13
 * Time: 19:47
 * To change this template use File | Settings | File Templates.
 */
public class MBOARD {

    class BitTree{
        int[] bit;
        int n;

        BitTree(int n){
            this.n = n;
            bit = new int[n];
        }

        void update(int a,int dlt){
            if (a == -1) return;
           // System.err.println("update " + a + " " + dlt);
            a = n - a - 1;
            for (;a < n; a = (a|(a+1)))
                bit[a] += dlt;
        }

        int get(int a){
           // System.err.print("get " + a );
            a = n - a - 1;
            int ans = 0;
            for (;a >= 0; a = (a & (a+1))-1)
                ans += bit[a];
          //  System.err.println(" ="+ans);
            return ans;
        }
    }

    int[] lastRow,lastCol;
    int[] valRow,valCol;
    BitTree[] row, col;

    void solve() throws IOException {
        int n = nextInt();
        int q = nextInt();
        lastRow = new int[n];
        valRow = new int[n];

        lastCol = new int[n];
        valCol = new int[n];

        Arrays.fill(lastRow,-1);
        Arrays.fill(lastCol,-1);

        row = new BitTree[2];
        col = new BitTree[2];
        row[0] = new BitTree(q);
        row[1] = new BitTree(q);
        col[0] = new BitTree(q);
        col[1] = new BitTree(q);

        for (int it = 0; it < q; it++){
            String query = nextToken();
            if (query.equals("RowQuery")){
                int id = nextInt()-1;
                if (valRow[id] == 0)
                    out.println(n - col[1].get(lastRow[id]+1));
                else
                    out.println(col[0].get(lastRow[id]+1));
            }
            if (query.equals("ColQuery")){
                int id = nextInt()-1;
                if (valCol[id] == 0)
                    out.println(n - row[1].get(lastCol[id]+1));
                else
                    out.println(row[0].get(lastCol[id]+1));
            }
            if (query.equals("ColSet")){
                int id = nextInt()-1;
                col[valCol[id]].update(lastCol[id],-1);
                valCol[id] = nextInt();
                //System.err.println(valCol[id]);
                lastCol[id] = it;
                col[valCol[id]].update(lastCol[id],1);
            }
            if (query.equals("RowSet")){
                int id = nextInt()-1;
                row[valRow[id]].update(lastRow[id],-1);
                valRow[id] = nextInt();
                lastRow[id] = it;
                row[valRow[id]].update(lastRow[id],1);
            }
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
            boolean oj = getProperty("LOCAL") == null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            out.close();
        } catch (Exception e) {
            e.printStackTrace();
            exit(1);
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