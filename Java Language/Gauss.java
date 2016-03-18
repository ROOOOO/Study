import java.util.Scanner;


public class Gauss {
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), i, j, k, zero = 0;
        Ratio[][] m = new Ratio[n][n+1];
        Ratio coef;
        Ratio temp[];
        for (i = 0; i < n; i++) {
            for (j = 0; j < n+1; j++) {
                m[i][j] = new Ratio(in.nextInt());
            }
        }
        for (k = 0; k < n; k++) {
            for (j = k; j < n; j++) {
                if (m[j][k].getNum() != 0) {
                    temp = m[k];
                    m[k] = m[j];
                    m[j] = temp;
                    break;
                }
            }
            if(j==n){
                System.out.print("No solution");
                return;
            };
            for (j = k+1; j < n; j++) {
                coef = m[j][k].div(m[k][k]);
                for (i = 0; i <= n; i++) {
                    m[j][i] = m[j][i].ded(coef.mul(m[k][i]));
                }
            }
        }
        for(i = 0; i<n; i++, zero = 0){
            for(j = 0; j<n; j++){
                if(m[i][j].getNum()==0) zero++;
            }
            if(zero==n){
                System.out.print("No solution");
                return;
            }
        }
        
        for(j = n-1; j > 0; j--){
            for(i = j-1; i >= 0; i--){
                if(m[j][j].getNum()==0) continue;
                coef = m[i][j].div(m[j][j]);
                m[i][j] = m[i][j].ded(m[j][j].mul(coef));
                m[i][n] = m[i][n].ded(m[j][n].mul(coef));
            }
        }
        for(i = 0; i<n; i++){
            if(m[i][i].getNum()==0) continue;
            m[i][n] = m[i][n].div(m[i][i]);
        }
        for(i = 0; i<n; i++){
            System.out.println(m[i][n].print());
        }
    }
}
class Ratio {
    private int num;
    private int den;
    int gcd(int a,int b){
        return b == 0 ? a : gcd(b,a % b);
    }
    int lcm(int a, int b){
        return Math.abs(a*b)/gcd(a, b);
    }
    Ratio(int numerator, int denominator){
        this.num = numerator;
        this.den = denominator;
        normalize();
    }
    Ratio(int numerator){
        this.num = numerator;
        this.den = 1;
    }
    void normalize(){
        int ngcd = gcd(this.den, this.num);
        this.den = this.den/ngcd;
        this.num = this.num/ngcd;
        if(den<0){
            this.den = Math.abs(this.den);
            this.num = -this.num;
        }
    }
    public void setDen(int den) {
        this.den = den;
    }
    public void setNum(int num) {
        this.num = num;
    }
    public int getDen() {
        return den;
    }
    public int getNum() {
        return num;
    }
    String print(){
        return num+"/"+den;
    }
    
    Ratio add(Ratio x){
        int newDen = lcm(this.den, x.getDen());
        Ratio ans = new Ratio((newDen/this.den)*this.num + (newDen/x.getDen())*x.getNum(), newDen);
        return ans;
    }
    Ratio ded(Ratio x){
        int newDen = lcm(this.den, x.getDen());
        Ratio ans = new Ratio((newDen/this.den)*this.num - (newDen/x.getDen())*x.getNum(), newDen);
        return ans;
    }
    Ratio mul(Ratio x){
        Ratio ans = new Ratio(this.num*x.getNum(), this.den*x.getDen());
        return ans;
    }
    Ratio div(Ratio x){
        Ratio ans = new Ratio(this.num*x.getDen(), this.den*x.getNum());
        return ans;
    }
}