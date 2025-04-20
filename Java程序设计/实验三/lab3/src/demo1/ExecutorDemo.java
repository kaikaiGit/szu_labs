package demo1;

import java.util.concurrent.*;

public class ExecutorDemo {
    public static void main(String[] args) {
        // Create a fixed thread pool with maximum three threads
        ExecutorService executor = Executors.newFixedThreadPool(3);
        // Submit runnable tasks to the executor
        executor.submit(new PrintChar('a', 100));
        executor.submit(new PrintChar('b', 100));
        executor.submit(new PrintNum(100));
        // Shut down the executor
        executor.shutdown();
    }
}
