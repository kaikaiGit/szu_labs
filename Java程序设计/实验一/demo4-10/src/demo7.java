public class demo7 {
    // 判断一个数是否是素数的函数
    public static boolean isPrime(int number) {
        if (number <= 1) {
            return false; // 1不是素数
        }
        if (number == 2) {
            return true; // 2是最小的素数
        }
        if (number % 2 == 0) {
            return false; // 如果是偶数且不是2，则不是素数
        }
        // 试除法检查到平方根
        for (int i = 3; i <= Math.sqrt(number); i += 2) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }
    public static void main(String[] args) {
        int primeCount = 0; // 计数器
        for(int i=1; i<=600; i++) {
            if(isPrime(i)) {
                primeCount++;
                System.out.print(i + " ");
            }
            if(i % 100 == 0) { //格式需要
                System.out.println(); // 换行
            }
        }
        System.out.println("1~600的素数个数：" + primeCount);
    }
}
