import java.io.*;
import java.util.*;

public class TheKingsRoadsDiv1 {
	public String getAnswer(int h, int[] A, int[] B) {
        n = (1<<h) - 1;
        H = h;
        for (int i = 0; i < A.length; ++ i) {
            A[i] --;
            B[i] --;
            if (A[i] > B[i]) {
                int tmp = A[i]; A[i] = B[i]; B[i] = tmp;
            }
        }
        for (int i = 0; i < A.length; ++ i) {
            for (int j = i+1; j < A.length; ++ j) {
                if (A[i] > A[j] || A[i] == A[j] && B[i] > B[j]) {
                    int tmp = A[i]; A[i] = A[j]; A[j] = tmp;
                    tmp = B[i]; B[i] = B[j]; B[j] = tmp;
                }
            }
        }
        edges = new List[A.length - 2];
        for (int i = 0; i < edges.length; ++ i) {
            edges[i] = new ArrayList<Integer>();
        }
        int count = 3;
        for (int i = 0; i < A.length; ++ i) {
            if (A[i] == B[i]) {
                count --;
            } else if (i != 0 && A[i] == A[i-1] && B[i] == B[i-1]) {
                count --;
            } else {
                edges[A[i]].add(B[i]);
                edges[B[i]].add(A[i]);
            }
        }
        if (count < 0) {
            return "Incorrect";
        }
        que = new int[n];
        depth = new int[n];
        marked = new boolean[n];
        Arrays.fill(depth,-1);
        for (int i = 0; i < n; ++ i) {
            que[0] = i;
            depth[i] = 1;
            if (dfs(0,1,count)) {
                return "Correct";
            }
            depth[i] = -1;
        }
        return "Incorrect";
	}

    boolean dfs(int qf,int qe,int count) {
        if (count < 0) {
            return false;
        }
        if (qf == qe) {
            return qf == n && count == 0;
        }
        int u = que[qf];
        marked[u] = true;
        ArrayList choice = new ArrayList<Integer>();
        for (int v : edges[u]) {
            if (depth[v] == -1) {
                choice.add(v);
            } else if (!marked[v]) {
                count --;
            }
        }
        if (depth[u] == H) {
            if (dfs(qf+1,qe,count - choice.size())) {
                return true;
            }
        } else {
            for (int i = 0; i < choice.size(); ++ i) {
                for (int j = i+1; j < choice.size(); ++ j) {
                    int a = (int)choice.get(i);
                    int b = (int)choice.get(j);
                    depth[a] = depth[u] + 1;
                    depth[b] = depth[u] + 1;
                    que[qe] = a;
                    que[qe+1] = b;
                    if (dfs(qf+1,qe+2,count - choice.size() + 2)) {
                        return true;
                    }
                    depth[a] = -1;
                    depth[b] = -1;
                }
            }
        }
        marked[u] = false;
        return false;
    }

    List<Integer>[] edges;
    int H;
    int n;
    int[] que;
    int[] depth;
    boolean[] marked;

    void debug(Object... o) {
        System.out.println(Arrays.deepToString(o));
    }

    // CUT begin
    public static void main(String[] args){
        System.err.println("TheKingsRoadsDiv1 (500 Points)");
        System.err.println();
        HashSet<Integer> cases = new HashSet<Integer>();
        for (int i = 0; i < args.length; ++i) cases.add(Integer.parseInt(args[i]));
        runTest(cases);
    }

    static void runTest(HashSet<Integer> caseSet) {
        int cases = 0, passed = 0;
        while (true) {
            String label = Reader.nextLine();
            if (label == null || !label.startsWith("--"))
                break;

            int h = Integer.parseInt(Reader.nextLine());
            int[] a = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < a.length; ++i)
                a[i] = Integer.parseInt(Reader.nextLine());
            int[] b = new int[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < b.length; ++i)
                b[i] = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            String __answer = Reader.nextLine();

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
            System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(h, a, b, __answer))
                passed++;
        }
        if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1424225965;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 500 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
    }

    static boolean doTest(int h, int[] a, int[] b, String __expected) {
        long startTime = System.currentTimeMillis();
        Throwable exception = null;
        TheKingsRoadsDiv1 instance = new TheKingsRoadsDiv1();
        String __result = "";
        try {
            __result = instance.getAnswer(h, a, b);
        }
        catch (Throwable e) { exception = e; }
        double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

        if (exception != null) {
            System.err.println("RUNTIME ERROR!");
            exception.printStackTrace();
            return false;
        }
        else if (__expected.equals(__result)) {
            System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
            return true;
        }
        else {
            System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
            System.err.println("           Expected: " + "\"" + __expected + "\"");
            System.err.println("           Received: " + "\"" + __result + "\"");
            return false;
        }
    }

    static class Reader {
        private static final String dataFileName = "TheKingsRoadsDiv1.sample";
        private static BufferedReader reader;

        public static String nextLine() {
            try {
                if (reader == null) {
                    reader = new BufferedReader(new InputStreamReader(new FileInputStream(dataFileName)));
                }
                return reader.readLine();
            }
            catch (IOException e) {
                System.err.println("FATAL!! IOException");
                e.printStackTrace();
                System.exit(1);
            }
            return "";
        }
    }
    // CUT end
}
