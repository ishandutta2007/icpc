import java.io.*;
import java.util.*;

public class ColourHolic {
	public int countSequences(int[] A) {
		Arrays.sort(A);
		int a = A[0],b = A[1],c = A[2],d = A[3];
		if (a == 0 && b == 0) {
			if (c == d) return 2;
			if (c+1 == d) return 1;
			return 0;
		}
		{
			int n = a + b + c + d + 5;
			F = new long[n];
			Finv = new long[n];
			Inv = new long[n];
			two = new long[n];
			Inv[1] = 1;
			for (int i = 2; i < n; ++ i) {
				Inv[i] = (MOD-MOD/i) * Inv[MOD%i] % MOD;
			}
			F[0] = Finv[0] = 1;
			for (int i = 1; i < n; ++ i) {
				F[i] = F[i-1] * i % MOD;
				Finv[i] = Finv[i-1] * Inv[i] % MOD;
			}
			two[0] = 1;
			for (int i = 1; i < n; ++ i) {
				two[i] = two[i-1] * 2 % MOD;
			}
		}
		if (a == 0) {
			return (int) calc(b,c,d);
		}
		long answer = 0;
		for (int g = 1; g <= a+b; ++ g) {
			long ways = 0;
			for (int e = 0; e <= g; ++ e) {
				if (e > a || e > b) break;
				int tmp = g-e-a+b;
				if (tmp < 0 || tmp%2 == 1) continue;
				int ob = tmp / 2;
				int oa = a-b+ob;
				if (oa < 0 || oa > a || ob < 0 || ob > b) continue;
				int r = a-e-oa;
				if (r < 0) continue;
				long value = comb(g,e) * comb(g-e,oa) % MOD
					* two[e] % MOD * comb(g-1+r,r) % MOD;
				ways += value;
				ways %= MOD;
			}
			answer += ways * calc(g,c,d) % MOD;
			answer %= MOD;
		}
		return (int) answer;
	}

	long calc(int a,int b,int c) {
		long ret = 0;
		for (int g = c-1; g <= c+1; ++ g) {
			for (int e = 0; e <= Math.min(a,b); ++ e) {
				if (e > g) break;
				int tmp = g-e-a+b;
				if (tmp < 0 || tmp%2 == 1) continue;
				int ob = tmp / 2;
				int oa = a-b+ob;
				if (oa < 0 || oa > a || ob < 0 || ob > b) continue;
				int r = a-e-oa;
				if (r < 0) continue;
				long value = comb(g,e) * comb(g-e,oa) % MOD
					* two[e] % MOD * comb(g-1+r,r) % MOD;
				if (g == c) {
					value = value * 2 % MOD;
				}
				ret += value;
				ret %= MOD;
			}
		}
		return ret;
	}

	long comb(int a,int b) {
		if (a < b) return 0;
		return F[a] * Finv[a-b] % MOD * Finv[b] % MOD;
	}

	long[] F,Finv,Inv,two;
	static final int MOD = (int)1e9+9;


	void debug(Object... o) {
		System.out.println(Arrays.deepToString(o));
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("ColourHolic (1000 Points)");
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

			int[] n = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < n.length; ++i)
				n[i] = Integer.parseInt(Reader.nextLine());
			Reader.nextLine();
			int __answer = Integer.parseInt(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(n, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1420780442;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] n, int __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		ColourHolic instance = new ColourHolic();
		int __result = 0;
		try {
			__result = instance.countSequences(n);
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
		private static final String dataFileName = "ColourHolic.sample";
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
