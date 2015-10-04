import java.io.*;
import java.util.*;

public class LittleElephantAndBoard {
	public int getNumber(int m, int a, int b, int c) {
		{
			if (a+b-c < 0 || (a+b-c)%2 == 1) return 0;
			int x = a+b-c>>1;
			if (x < 0 || b-x < 0 || a-x < 0) return 0;
			c = a-x;
			b = b-x;
			a = x;
			if (a+b+c != m) return 0;
		}
        if (a == 0) {
            if (b == c) return 2;
            if (b+1 == c || b == c+1) return 1;
            return 0;
        }
        {
            int n = m*2 + 5;
            F = new int[n];
            Finv = new int[n];
            Inv = new int[n];
            two = new int[n];
            Inv[1] = 1;
            for (int i = 2; i < n; ++ i) {
                Inv[i] = (int) ((long) (MOD-MOD/i) * Inv[MOD%i] % MOD);
            }
            F[0] = Finv[0] = 1;
            for (int i = 1; i < n; ++ i) {
                F[i] = (int) ((long) F[i-1] * i % MOD);
                Finv[i] = (int) ((long) Finv[i-1] * Inv[i] % MOD);
            }
            two[0] = 1;
            for (int i = 1; i < n; ++ i) {
                two[i] = (two[i-1] + two[i-1]) % MOD;
            }
        }
        long answer = 0;
        for (int g = a-1; g <= a+1; ++ g) {
            for (int e = 0; e <= Math.min(b,c); ++ e) {
				if (e > g) break;
                int tmp;
                tmp = g-e-b+c;
                if (tmp < 0 || tmp%2 == 1) continue;
                int oc = tmp / 2;
                int ob = g-e-oc;
				if (oc < 0 || oc > c || ob < 0 || ob > b) continue;
                int r = b-e-ob;
				if (r < 0) continue;
                long val = comb(g-1+r,r) * two[e] % MOD
					* comb(g,e) % MOD * comb(g-e,ob) % MOD;
				if (g == a) {
					val = val * 2 % MOD;
				}
				answer += val;
				answer %= MOD;
            }
        }
		answer = answer * 2 % MOD;
		return (int)answer;
	}

    long comb(int a,int b) {
        if (a < b) return 0;
        return (long) F[a] * Finv[a-b] % MOD * Finv[b] % MOD;
    }

    int[] F,Finv,Inv,two;
    static final int MOD = (int)1e9+7;
	
	void debug(Object... o) {
		System.out.println(Arrays.deepToString(o));
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("LittleElephantAndBoard (900 Points)");
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

            int M = Integer.parseInt(Reader.nextLine());
            int R = Integer.parseInt(Reader.nextLine());
            int G = Integer.parseInt(Reader.nextLine());
            int B = Integer.parseInt(Reader.nextLine());
            Reader.nextLine();
            int __answer = Integer.parseInt(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(M, R, G, B, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1420784860;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 900 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int M, int R, int G, int B, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		LittleElephantAndBoard instance = new LittleElephantAndBoard();
		int __result = 0;
		try {
			__result = instance.getNumber(M, R, G, B);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (__result == __expected) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + __expected);
			System.err.println("           Received: " + __result);
			return false;
		}
	}

	static class Reader {
        private static final String dataFileName = "LittleElephantAndBoard.sample";
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
