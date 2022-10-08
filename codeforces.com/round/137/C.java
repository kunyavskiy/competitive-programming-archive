import java.io.*;
import java.lang.*;
import java.util.*;

public class Main
{

    static final int MAXV = 10000010;
    int p[];
    ArrayList<Integer> primes = new ArrayList();

    void PreCalc(){
        p = new int[MAXV];
        for (int i = 2; i < MAXV; i++){
            if (p[i] == 0){
                primes.add(i);
                p[i] = i;
            }
            for (int j:primes){
                if (i * j >= MAXV || j > p[i])
                    break;
                p[i*j] = j;
            }
                
        }
    }

    void add(int[] cnt, int a,int cf){
        while (a > 1){
            cnt[p[a]]+=cf;
            a /= p[a];
        }
    }

    int dec(int[] cnt,int a,int cf){
        int res = 1;
        while (a > 1){
            if (cnt[p[a]] * cf > 0){
                cnt[p[a]] -= cf;
                res = res * p[a];
            }
            a /= p[a];
        }
        return res;
    }

    void solve() throws IOException{
        PreCalc();
        int[] cnt = new int[MAXV];

        int n = nextInt(), m = nextInt();
        int[] a = new int[n];
        int[] b = new int[m];
        for (int i = 0; i < n; i++){
            add(cnt,a[i] = nextInt(),1);
        }
        for (int i = 0; i < m; i++){
            add(cnt,b[i] = nextInt(),-1);
        }
        System.err.println("!!!");

        out.println(n+" "+m);

        for (int i = 0; i < n; i++){
            out.print(dec(cnt,a[i],1)+" ");
        }
        out.println();
        for (int i = 0; i < m; i++){
            out.print(dec(cnt,b[i],-1)+" ");
        }
        out.println();

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
