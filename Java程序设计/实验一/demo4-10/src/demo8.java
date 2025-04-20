public class demo8 {
    public static void main(String[] args) {
        // 定义变量存储分子和分母，以及总和
        double sum = 0.0; // 用于存储总和
        int numerator = 1; // 初始分子
        int denominator = 1; // 初始分母
        for(int i=1; i<=30; i++) {
            sum += (double)numerator / denominator; // 累加
            // 分子加1,分母乘3
            numerator += 1;
            denominator *= 3;
        }
        // 输出前30项的总和
        System.out.println("前30项的和为: " + sum);
    }
}
