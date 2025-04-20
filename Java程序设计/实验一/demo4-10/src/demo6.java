import java.util.Scanner;

public class demo6 {
    // 逆序打印数字的函数
    public static void reversePrintNum(int number) {
        while (number > 0) {
            // 取出最后一位数字并打印
            System.out.print(number % 10);
            // 移除最后一位数字
            number = number / 10;
        }
        System.out.println(); // 换行
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = 10; // 循环次数为10
        while(t-- > 0) {
            System.out.print("输入第 " + (10-t) + " 个正整数: ");
            int number = scanner.nextInt(); // 输入一个整数
            System.out.print("逆序打印结果: ");
            reversePrintNum(number); // 逆序打印数字
        }
    }
}
