import java.math.BigInteger;
import java.util.Scanner;

public class FastFib {
    
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        BigInteger[][] m = new BigInteger[2][2];
        BigInteger[][] res = new BigInteger[2][2];
        res[0][0] = BigInteger.ONE;
        res[0][1] = BigInteger.ZERO;
        res[1][0] = BigInteger.ZERO;
        res[1][1] = BigInteger.ONE;
        m[0][0] = BigInteger.ONE;
        m[0][1] = BigInteger.ONE;
        m[1][0] = BigInteger.ONE;
        m[1][1] = BigInteger.ZERO;
        BigInteger a11 = BigInteger.ZERO, a12 = BigInteger.ZERO, a21 = BigInteger.ZERO, a22 = BigInteger.ZERO;
        int n = input.nextInt(), q, i, count = 1, j;
        n--;
        for(i = n; n>0; n>>=1, count++){
            q = n&1;
            if(q==1) {
                res = mulM(res, powM(m, count));
            }
        }
        a11 = (res[0][0]);
        System.out.println(a11);
    }
    public static BigInteger[][] powM(BigInteger[][] a, int n){
        BigInteger a11 = BigInteger.ZERO, a12 = BigInteger.ZERO, a21 = BigInteger.ZERO, a22 = BigInteger.ZERO;
        BigInteger[][] temp = new BigInteger[2][2];
        temp[0][0] = a[0][0];
        temp[0][1] = a[0][1];
        temp[1][0] = a[1][0];
        temp[1][1] = a[1][1];
        for(int i = 0; i<n-1; i++) {
            a11 = (temp[0][0].multiply(temp[0][0])).add(temp[0][1].multiply(temp[1][0]));
            a12 = (temp[0][0].multiply(temp[0][1])).add(temp[0][1].multiply(temp[1][1]));
            a21 = (temp[1][0].multiply(temp[0][0])).add(temp[1][1].multiply(temp[1][0]));
            a22 = (temp[1][0].multiply(temp[0][1])).add(temp[1][1].multiply(temp[1][1]));
            temp[0][0] = a11;
            temp[0][1] = a12;
            temp[1][0] = a21;
            temp[1][1] = a22;
        }
        return temp;
    }
    public static BigInteger[][] mulM(BigInteger[][] a, BigInteger b[][]){
        BigInteger a11 = BigInteger.ZERO, a12 = BigInteger.ZERO, a21 = BigInteger.ZERO, a22 = BigInteger.ZERO;
        BigInteger[][] temp = new BigInteger[2][2];
        a11 = (a[0][0].multiply(b[0][0])).add(a[0][1].multiply(b[1][0]));
        a12 = (a[0][0].multiply(b[0][1])).add(a[0][1].multiply(b[1][1]));
        a21 = (a[1][0].multiply(b[0][0])).add(a[1][1].multiply(b[1][0]));
        a22 = (a[1][0].multiply(b[0][1])).add(a[1][1].multiply(b[1][1]));
        temp[0][0] = a11;
        temp[0][1] = a12;
        temp[1][0] = a21;
        temp[1][1] = a22;
        return temp;
    }
}

