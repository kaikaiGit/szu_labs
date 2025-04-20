package demo1;

class PrintChar implements Runnable {
    private char charToPrint;// The character to print
    private int times;// The number of times to repeat

    public PrintChar(char c, int t) { // Constructor
        charToPrint = c;
        times = t;
    }

    @Override
    public void run() { // Override the run() method
        for (int i = 0; i < times; i++) // Repeat n times
            System.out.print(charToPrint);
    }
}
