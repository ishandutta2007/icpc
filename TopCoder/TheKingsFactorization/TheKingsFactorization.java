import java.io.*;
import java.util.*;

public class TheKingsFactorization {
	public long[] getVector(long N, long[] primes) {
		long[] ret = new long[primes.length*2];
		long left = N;
		int tot = 0;
		for (long x : primes) {
			left /= x;
			ret[tot++] = x;
		}
		for (int i = 0; i < primes.length-1; ++ i) {
			if (i == primes.length-2 && left <= primes[i+1]) {
				break;
			}
			for (long j = primes[i]; j <= primes[i+1]; ++ j) {
				if (left % j == 0) {
					ret[tot++] = j;
					left /= j;
					break;
				}
			}
		}
		if (left != 1)
			ret[tot++] = left;
		long[] t = ret;
		ret = new long[tot];
		for (int i = 0; i < tot; ++ i)
			ret[i] = t[i];
		Arrays.sort(ret);
		return ret;
	}
	
	void debug(Object... o) {
		System.out.println(Arrays.deepToString(o));
	}

// CUT begin
	public static void main(String[] args){
		System.err.println("TheKingsFactorization (250 Points)");
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

            long N = Long.parseLong(Reader.nextLine());
            long[] primes = new long[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < primes.length; ++i)
                primes[i] = Long.parseLong(Reader.nextLine());
            Reader.nextLine();
            long[] __answer = new long[Integer.parseInt(Reader.nextLine())];
            for (int i = 0; i < __answer.length; ++i)
                __answer[i] = Long.parseLong(Reader.nextLine());

            cases++;
            if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
                continue;
    		System.err.print(String.format("  Testcase #%d ... ", cases - 1));

            if (doTest(N, primes, __answer))
                passed++;
	    }
	    if (caseSet.size() > 0) cases = caseSet.size();
        System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

        int T = (int)(System.currentTimeMillis() / 1000) - 1419699603;
        double PT = T / 60.0, TT = 75.0;
        System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(long N, long[] primes, long[] __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		TheKingsFactorization instance = new TheKingsFactorization();
		long[] __result = new long[0];
		try {
			__result = instance.getVector(N, primes);
		}
		catch (Throwable e) { exception = e; }
		double elapsed = (System.currentTimeMillis() - startTime) / 1000.0;

		if (exception != null) {
			System.err.println("RUNTIME ERROR!");
			exception.printStackTrace();
			return false;
		}
		else if (equals(__result, __expected)) {
			System.err.println("PASSED! " + String.format("(%.2f seconds)", elapsed));
			return true;
		}
		else {
			System.err.println("FAILED! " + String.format("(%.2f seconds)", elapsed));
			System.err.println("           Expected: " + toString(__expected));
			System.err.println("           Received: " + toString(__result));
			return false;
		}
	}

	static boolean equals(long[] a, long[] b) {
		if (a.length != b.length) return false;
		for (int i = 0; i < a.length; ++i) if (a[i] != b[i]) return false;
		return true;
	}

	static String toString(long[] arr) {
		StringBuffer sb = new StringBuffer();
		sb.append("[ ");
		for (int i = 0; i < arr.length; ++i) {
			if (i > 0) sb.append(", ");
			sb.append(arr[i]);
		}
		return sb.toString() + " ]";
	}

	static class Reader {
        private static final String dataFileName = "TheKingsFactorization.sample";
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
