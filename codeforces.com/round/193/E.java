import java.io.*;
import java.util.StringTokenizer;


/**
 * Created with IntelliJ IDEA.
 * User: Pavel Kunyavskiy
 * Date: 24/07/13
 * Time: 18:20
 */
public class E {
    void solve() throws IOException {
        String p = in.readLine();
        String s = in.readLine();
        int k = nextInt();
        String best = "2";

        int cnt = p.length() / k;
        for (int i = 0; i <= p.length() % k; i++){
            int temp = s.length() - i * (cnt+1);
            if (temp < 0) continue;
            if (cnt == 0 && temp != 0) continue;
            if (cnt != 0 && temp % cnt != 0) continue;

            int cnt2 = i + (cnt == 0 ? 0 : temp / cnt);
            //System.err.println("??? cnt2 = "+cnt2);
            if (cnt2 > k) continue;
            //System.err.println("!!! cnt2 = "+cnt2);
            StringBuilder res = new StringBuilder();
            int cntGot = 0;
            for (int j = k-1; j >= 0; j--){
                if ((cntGot < cnt2 - i) ^ (j >= p.length() % k)) {
                    //System.err.println(j+" ignored");
                    res.append("0");
                    continue;
                }
                boolean ok = true;
                int ptr;
                if (cntGot < cnt2 - i){
                    ptr = s.length() / cnt2 * cnt2 - cntGot - 1;
                } else {
                    ptr = (s.length() - 1)/ cnt2 * cnt2 - cntGot + cnt2-1;
                }
                //System.err.printf("CntGot = %d of %d(%d). StartPtr = %d\n", cntGot, cnt2,i, ptr);
                for (int pos = j + (p.length() - j - 1) / k * k; pos >= 0; pos-=k){
                    if (ptr < 0 || s.charAt(ptr) != p.charAt(pos)){
                        //System.err.println(j+" failed by pos = "+pos+" ptr = "+ptr);
                        ok = false;
                        break;
                    }
                    ptr -= cnt2;
                }
                if (ok && ptr < 0) {
                    res.append(1);
                    cntGot++;
                }
                else
                    res.append(0);
            }

            if (cntGot != cnt2)
                continue;

            String cur = res.reverse().toString();


            if (cur.compareTo(best) < 0)
                best = cur;
        }

        if (best.equals("2"))
            best = "0";
        out.println(best);
    }

    public static void main(String[] args) throws IOException {
        new E().run();
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
