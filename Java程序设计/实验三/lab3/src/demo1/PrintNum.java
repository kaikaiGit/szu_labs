package demo1;

class PrintNum implements Runnable {
    private int lastNum; // The last number to print
    public PrintNum(int n){ // Constructor
        lastNum = n;
    }
    @Override
    public void run(){ // Override the run() method
        for(int i = 1; i <= lastNum; i++) // Print numbers from 1 to lastNum
            System.out.print(" " + i);
    }
}
