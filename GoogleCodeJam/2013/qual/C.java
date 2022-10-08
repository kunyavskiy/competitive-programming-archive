import java.io.*;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.StringTokenizer;



public class C {

    final static String TaskName = "C";
    final static String TaskMode = "large-2";
    final static int maxN = 55;

    ArrayList<BigInteger> answer;

    int[] sum;
    int[] cur;

    boolean setValue(int pos,int len,int val){
         cur[pos] = val;
         for (int i = 0; i < len; i++)
              sum[pos+i] += (i == pos?1:2) * cur[i] * cur[pos];
         for (int aSum : sum)
            if (aSum >= 10)
                return false;
         return true;
    }

    void unsetValue(int pos,int len){
        for (int i = 0; i < len; i++)
            sum[pos+i] -= (i == pos?1:2)*cur[i] * cur[pos];
        cur[pos] = 0;
    }

    void dfs(int pos,int len){
        if (pos > len - pos - 1){
            StringBuilder s = new StringBuilder();
            for (int i = 0; i < len; i++)
                s.append(cur[i]);
            System.err.print("len = " + len+"   ");
            BigInteger temp = new BigInteger(s.toString());
            System.err.println(temp+" "+temp.multiply(temp));

            answer.add(temp.multiply(temp));
            return;
        }
        for (int i = (pos==0?1:0); i <= 3; i++){
            boolean q = true;
            q &= setValue(pos, len, i);
            if (pos != len - pos - 1) q &= setValue(len - pos - 1, len, i);
            if (q) dfs(pos+1,len);
            unsetValue(pos, len);
            if (pos != len - pos - 1) unsetValue(len - pos - 1, len);
        }
    }

    void PreCalc() {
        answer = new ArrayList<BigInteger>();
        for (int i = 1; i <= maxN; i++){
            sum = new int[2*i];
            cur = new int[i];
            dfs(0,i);
        }


    }

    void solveOne() throws IOException {
        BigInteger a = new BigInteger(nextToken());
        BigInteger b = new BigInteger(nextToken());
        int ans = 0;
        for (BigInteger value : answer){
            if (a.compareTo(value) <= 0 && value.compareTo(b) <= 0)
                ans++;
        }
        out.println(ans);
    }

    void solve() throws IOException {
        long start = System.currentTimeMillis();
        PreCalc();
        int testNum = nextInt();
        for (int testId = 1; testId <= testNum; testId++){
            out.printf("Case #%d: ", testId);
            solveOne();
            if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
                System.err.printf("Test %d\n", testId);
        }
        System.err.println(System.currentTimeMillis() - start);
        System.err.println("Count = "+answer.size());
    }


    public static void main(String[] args) throws IOException {
        new C().run();
    }

    BufferedReader in;
    StringTokenizer tokenizer;
    PrintWriter out;

    public void run() throws IOException {
        try {
            Reader reader = new FileReader(TaskName+"-"+TaskMode+".in");
            Writer writer = new FileWriter(TaskName+"-"+TaskMode+".out");
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
