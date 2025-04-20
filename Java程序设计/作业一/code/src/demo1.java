public class demo1 {
    public static void main(String[] args) {
        boolean flag = true;
        for (int i = 1; i <= 1024 ; i++) {
            if(!isKalaz(i)){
                System.out.println("1024以内不满足卡拉兹猜想的数：" + i);
                flag = false;
            }
        }
        if (flag) System.out.println("1024以内所有数都满足卡拉兹猜想");
    }
    public static boolean isKalaz(int n){
        while (n!=1){
            if (n % 2 == 0){
                n /= 2;
            }else {
                n = (3 * n + 1) / 2;
            }
        }
        return true;
    }
}
