/*
编写Java应用程序实现如下功能：创建工作线程，模拟银行现金账户存款操作。
多个线程同时执行存款操作时，如果不使用同步处理，会造成账户余额混乱，
要求使用syncrhonized关键字同步代码块，以保证多个线程同时执行存款操作时，银行现金账户存款的有效和一致。
要求采用实现Runnable接口和Thread类的构造方法的方式创建线程，而不是通过Thread类的子类的方式。
 */
package demo4;

public class BankAccountDemo {
    public static void main(String[] args) {
        // 创建银行账户对象
        BankAccount account = new BankAccount();
        // 创建三个线程，模拟多线程存款操作
        Thread depositor1 = new Thread(new DepositTask(account, 100));
        Thread depositor2 = new Thread(new DepositTask(account, 200));
        Thread depositor3 = new Thread(new DepositTask(account, 300));
        // 启动线程
        depositor1.start();
        depositor2.start();
        depositor3.start();
    }
}

// 银行账户类
class BankAccount {
    private int balance = 0; // 账户余额
    // 获取账户余额
    public int getBalance() {
        return balance;
    }
    // 存款操作，使用synchronized关键字保证线程安全
    public void deposit(int amount) {
        synchronized (this) { // 同步代码块
            int newBalance = balance + amount;
            System.out.println(Thread.currentThread().getName() + " 存入 " + amount + " 元，新的余额是：" + newBalance);
            balance = newBalance; // 更新余额
        }
    }
}

// 存款任务类，实现Runnable接口
class DepositTask implements Runnable {
    private final BankAccount account; // 银行账户对象
    private final int amount; // 存款金额
    // 构造方法
    public DepositTask(BankAccount account, int amount) {
        this.account = account;
        this.amount = amount;
    }
    // 重写run方法
    @Override
    public void run() {
        account.deposit(amount); // 执行存款操作
    }
}

