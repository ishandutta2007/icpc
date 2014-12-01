import java.io.*;
import java.util.*;

public class SegmentCutting {
	public long maxValue(int[] X, int[] Y) {
		int n = X.length;
		Point[] points = new Point[n];
		for (int i = 0; i < n; ++ i)
			points[i] = new Point(X[i],Y[i]);
		long answer = 0;
		for (int o = 0; o < n; ++ o) {
			
			Point[] points_o = new Point[n+n-1];
			for (int i = 0; i < n; ++ i) {
				points_o[i] = points[i].substract(points[o]);
			}
			{
				Point t = points_o[o];
				points_o[o] = points_o[0];
				points_o[0] = t;
			}
			Arrays.sort(points_o,1,n);
			for (int i = 1; i < n; ++ i)
				points_o[n+i-1] = points_o[i];
			{
				Calculator ca = new Calculator();
				Calculator cb = new Calculator();
				ca.origin = cb.origin = points[o];
				for (int i = 0; i < n; ++ i)
					ca.modify(points_o[i],1);
				for (int i = 1,j = 1; i < n; ++ i) {
					while (j<i+n-1 && (points_o[i].cross(points_o[j])>0 || i==j)) {
						ca.modify(points_o[j],-1);
						cb.modify(points_o[j],1);
						++ j;
					}
					answer = Math.max(answer,ca.merge(cb));
					ca.modify(points_o[i],1);
					cb.modify(points_o[i],-1);
				}
			}
			{
				Calculator ca = new Calculator();
				Calculator cb = new Calculator();
				ca.origin = cb.origin = points[o];
				for (int i = 0; i < n; ++ i)
					ca.modify(points_o[i],1);
				for (int i = n+n-2,j = n+n-2; i >= n; -- i) {
					while (j>i-n+1 && (points_o[j].cross(points_o[i])>0 || i==j)) {
						ca.modify(points_o[j],-1);
						cb.modify(points_o[j],1);
						-- j;
					}
					answer = Math.max(answer,ca.merge(cb));
					ca.modify(points_o[i],1);
					cb.modify(points_o[i],-1);
				}
			}
		}
		return answer;
	}

	class Calculator {
		Point origin;
		long sum_x2,sum_y2,sum_x,sum_y,count;
		void modify(Point t,int slop) {
			Point o = t.add(origin);
			sum_x2 += o.x*o.x*slop;
			sum_y2 += o.y*o.y*slop;
			sum_x += o.x*slop;
			sum_y += o.y*slop;
			count += slop;
		}
		long merge(Calculator t) {
			long ret = 0;
			ret += this.sum_x2 * t.count;
			ret += this.sum_y2 * t.count;
			ret += this.count * t.sum_x2;
			ret += this.count * t.sum_y2;
			ret -= 2 * this.sum_x * t.sum_x;
			ret -= 2 * this.sum_y * t.sum_y;
			return ret;
		}
	}

	class Point implements Comparable<Point> {
		int x,y;
		Point(int _x,int _y) {
			x = _x;
			y = _y;
		}
		Point add(Point t) {
			return new Point(x+t.x,y+t.y);
		}
		Point substract(Point t) {
			return new Point(x-t.x,y-t.y);
		}
		int cross(Point t) {
			return x*t.y-y*t.x;
		}
		int dot(Point t) {
			return x*t.x+y*t.y;
		}
		Point perp() {
			return new Point(-y,x);
		}
		public int compareTo(Point t) {
			if (this.y*t.y <= 0) {
				if (this.y>0 || t.y>0) return this.y-t.y;
				if (this.y==0 && t.y==0) return this.x-t.x;
			}
			return -this.cross(t);
		}
	}

	// CUT begin
	public static void main(String[] args){
		System.err.println("SegmentCutting (1000 Points)");
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

			int[] x = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < x.length; ++i)
				x[i] = Integer.parseInt(Reader.nextLine());
			int[] y = new int[Integer.parseInt(Reader.nextLine())];
			for (int i = 0; i < y.length; ++i)
				y[i] = Integer.parseInt(Reader.nextLine());
			Reader.nextLine();
			long __answer = Long.parseLong(Reader.nextLine());

			cases++;
			if (caseSet.size() > 0 && !caseSet.contains(cases - 1))
				continue;
			System.err.print(String.format("  Testcase #%d ... ", cases - 1));

			if (doTest(x, y, __answer))
				passed++;
		}
		if (caseSet.size() > 0) cases = caseSet.size();
		System.err.println(String.format("%nPassed : %d/%d cases", passed, cases));

		int T = (int)(System.currentTimeMillis() / 1000) - 1417434248;
		double PT = T / 60.0, TT = 75.0;
		System.err.println(String.format("Time   : %d minutes %d secs%nScore  : %.2f points", T / 60, T % 60, 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT))));
	}

	static boolean doTest(int[] x, int[] y, long __expected) {
		long startTime = System.currentTimeMillis();
		Throwable exception = null;
		SegmentCutting instance = new SegmentCutting();
		long __result = 0;
		try {
			__result = instance.maxValue(x, y);
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
		private static final String dataFileName = "SegmentCutting.sample";
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
