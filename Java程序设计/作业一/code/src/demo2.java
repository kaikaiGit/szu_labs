class NumberPrinter implements Runnable {
    @Override
    public void run() {
        Object lock = demo2.class;
        synchronized (lock) {
            for (int i = 1; i <= 13; i++) {
                System.out.print(i);
                lock.notify();
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            lock.notify();
        }
    }
}
class LetterPrinter implements Runnable {
    @Override
    public void run() {
        Object lock = demo2.class;
        synchronized (lock) {
            for (int i = 65; i <= 90;) {
                System.out.print((char)i++);
                System.out.print((char)i++);
                lock.notify();
                try {
                    lock.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            lock.notify();
        }
    }
}

public class demo2 {
    public static void main(String[] args) {
        Thread t1 = new Thread(new NumberPrinter());
        Thread t2 = new Thread(new LetterPrinter());
        t1.start();
        t2.start();
    }
}
