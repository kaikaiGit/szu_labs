import java.util.Scanner;

public class demo5 {
    // 计算电费的函数
    public static double calculateBill(int usage) {
        double bill = 0;
        if (usage <= 50) {
            bill = usage * 0.56;
        } else if (usage <= 220) {
            bill = 50 * 0.56 + (usage - 50) * 0.59;
        } else {
            bill = 50 * 0.56 + 170 * 0.59 + (usage - 220) * 0.66;
        }
        return bill;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请输入10个用电量值（整数）：");
        int t = 10; //循环次数
        while(t-- > 0) {
            int usage = scanner.nextInt(); // 输入用电量
            double bill = calculateBill(usage);
            System.out.println("用电量：" + usage + "，电费：" + bill + "元");
        }
    }
}
