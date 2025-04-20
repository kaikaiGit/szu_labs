/*
编写Java应用程序，根据用户输入的5个日期（每行一个日期），计算相邻两个日期之间间隔的时数，共4个结果（时数）。
注：用户输入的时间格式为“××××年××月××日××时××分××秒”，输出的时间格式为“××日××时××分××秒”。
 */
package demo5;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Scanner;
import java.time.Duration;

public class DateIntervalCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy年MM月dd日HH时mm分ss秒"); // 定义输入日期的格式
        ArrayList<Date> dates = new ArrayList<>(); // 用于存储输入的日期
        // 提示用户输入日期
        System.out.println("请输入5个日期（格式：××××年××月××日××时××分××秒）：");
        for (int i = 0; i < 5; i++) {
            System.out.print("输入第 " + (i + 1) + " 个日期：");
            String input = scanner.nextLine();
            try {
                Date date = dateFormat.parse(input); // 解析用户输入的日期
                dates.add(date); // 存储解析后的日期
            } catch (ParseException e) {
                System.out.println("日期格式错误，请输入正确格式！");
                i--; // 重试当前输入
            }
        }
        scanner.close(); // 关闭输入流
        // 计算相邻日期间隔的时数并输出结果
        System.out.println("\n相邻日期间隔时数：");
        for (int i = 0; i < dates.size() - 1; i++) {
            String formattedInterval = formatInterval(dates.get(i), dates.get(i + 1));
            System.out.println("第 " + (i + 1) + " 个间隔： " + formattedInterval);
        }
    }
    // 格式化时间间隔为“××日××时××分××秒”
    private static String formatInterval(Date date1, Date date2) {
        long diffInMillis = Math.abs(date2.getTime() - date1.getTime()); // 计算时间间隔（单位为毫秒）
        Duration duration = Duration.ofMillis(diffInMillis); // 将时间间隔转换为Duration对象
        // 计算时间间隔的日、时、分、秒
        long days = duration.toDays();
        long hours = duration.toHours() % 24;
        long minutes = duration.toMinutes() % 60;
        long seconds = duration.getSeconds() % 60;

        return String.format("%d日%d时%d分%d秒", days, hours, minutes, seconds);
    }
}
