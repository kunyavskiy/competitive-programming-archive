import java.io.*;
import java.lang.*;
import java.util.*;

public class Main
{

    void solve() throws IOException{
        int n = nextInt(), m = nextInt(),q = nextInt();
        int[][] a = new int[n][m];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                a[i][j] = nextInt();

        int[] p1 = new int[n], p2 = new int[m];
        int[] rp1 = new int[n], rp2 = new int[m];

        for (int i = 0; i < n; i++)
            p1[i] = rp1[i] = i;
        for (int i = 0; i < m; i++)
            p2[i] = rp2[i] = i;

        for (int i = 0; i < q; i++){
            char c = nextToken().charAt(0);
            int x = nextInt()-1, y = nextInt()-1;
            if (c == 'c'){
                int t = p2[x];
                p2[x] = p2[y];
                p2[y] = t;
                rp2[p2[x]] = x;
                rp2[p2[y]] = y;
            }
            else if (c == 'r'){
                int t = p1[x];
                p1[x] = p1[y];
                p1[y] = t;
                rp1[p1[x]] = x;
                rp1[p1[y]] = y;
            }
            else {
                out.println(a[p1[x]][p2[y]]);
            }
        }

    }

    public static void main(String[] args) throws IOException{
        new Main().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException
    {
        try {                                                   
            boolean oj = System.getProperty("ONLINE_JUDGE") != null;
            Reader reader = oj ? new InputStreamReader(System.in) : new FileReader("input.txt");
            Writer writer = oj ? new OutputStreamWriter(System.out) : new FileWriter("output.txt");
            in = new BufferedReader(reader);
            tokenizer = null;
            out = new PrintWriter(writer);
            solve();
            in.close();
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
