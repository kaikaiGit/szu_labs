/*
编写Java应用程序实现如下功能：第一个线程生成一个随机数，
第二个线程每隔一段时间读取第一个线程生成的随机数，并判断它是否是奇数。
要求采用实现Runnable接口和Thread类的构造方法的方式创建线程，而不是通过Thread类的子类的方式。
 */
package demo2;
import java.util.Random;

public class RandomNumberChecker {
    // 共享资源：用来存放随机数
    private static volatile int randomNumber;
    public static void main(String[] args) {
        // 创建生成随机数的线程
        Thread generatorThread = new Thread(new RandomNumberGenerator());
        // 创建检查奇偶性的线程
        Thread checkerThread = new Thread(new OddNumberChecker());
        // 启动线程
        generatorThread.start();
        checkerThread.start();
    }

    // 第一个线程：生成随机数
    private static class RandomNumberGenerator implements Runnable {
        private Random random = new Random();
        @Override
        public void run() { // 重写run()方法
            while (true) {
                randomNumber = random.nextInt(100); // 生成 0 到 99 之间的随机数
                System.out.println("Generated Random Number: " + randomNumber);
                try {
                    Thread.sleep(1000); // 每隔一秒生成一个随机数
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    // 第二个线程：判断随机数是否为奇数
    private static class OddNumberChecker implements Runnable {

        @Override
        public void run() { // 重写run()方法
            while (true) {
                if (randomNumber % 2 != 0) { // 判断随机数是否为奇数
                    System.out.println("The number " + randomNumber + " is odd.");
                } else {
                    System.out.println("The number " + randomNumber + " is even.");
                }
                try {
                    Thread.sleep(2000); // 每隔 2 秒检查一次随机数
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}

