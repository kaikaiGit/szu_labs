package demo3;

public class NumberLetterPrinter {
    private static final Object lock = new Object(); // 用于同步的锁对象
    private static boolean numberTurn = true; // 用于控制输出顺序
    public static void main(String[] args) {
        // 创建数字输出线程
        Thread numberThread = new Thread(new NumberPrinter());
        // 创建字母输出线程
        Thread letterThread = new Thread(new LetterPrinter());
        // 启动线程
        numberThread.start();
        letterThread.start();
    }
    // 线程一：输出数字的线程
    private static class NumberPrinter implements Runnable {
        @Override
        public void run() {
            for (int i = 1; i <= 26; i++) { // 从 1 到 26 输出数字
                synchronized (lock) { // 获取锁
                    while (!numberTurn) {
                        try {
                            lock.wait(); // 等待字母线程的通知
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    }
                    System.out.print(i); // 输出数字
                    numberTurn = false;  // 切换到字母线程
                    lock.notify();       // 通知字母线程
                }
            }
        }
    }
    // 线程二：输出字母的线程
    private static class LetterPrinter implements Runnable {
        @Override
        public void run() {
            for (char c = 'A'; c <= 'Z'; c++) { // 从 A 到 Z 输出字母
                synchronized (lock) { // 获取锁
                    while (numberTurn) {
                        try {
                            lock.wait(); // 等待数字线程的通知
                        } catch (InterruptedException e) {
                            Thread.currentThread().interrupt();
                        }
                    }
                    System.out.print(c); // 输出字母
                    numberTurn = true;   // 切换到数字线程
                    lock.notify();       // 通知数字线程
                }
            }
        }
    }
}
