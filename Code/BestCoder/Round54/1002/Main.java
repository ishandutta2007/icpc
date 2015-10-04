import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
    public static void main(String[] args) {
        new Main().run();
    }

    void run() {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        int cas = in.nextInt();
        for (int ca = 0; ca < cas; ++ ca) {
            int n = in.nextInt();
            BigInteger A[] = new BigInteger[n];
            for (int i = 0; i < n; ++ i) {
                A[i] = in.nextBigInteger();
            }
            if (judge(A)) {
                out.println("Yes");
            } else {
                out.println("No");
            }
            out.flush();
        }
        in.close();
        out.close();
    }

    boolean judge(BigInteger A[]) {
        int count_zero = 0;
        for (int i = 0; i < A.length; ++ i) {
            if (A[i].equals(BigInteger.ZERO)) {
                count_zero ++;
            }
        }
        if (count_zero > 0) {
            if (count_zero == A.length)
                return true;
            return false;
        }
        for (int i = 1; i + 1 < A.length; ++ i) {
            if (!A[i].multiply(A[i]).equals(A[i - 1].multiply(A[i + 1])))
                return false;
        }
        return true;
    }
}
