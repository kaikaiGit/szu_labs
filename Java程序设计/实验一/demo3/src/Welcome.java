public class Welcome {
    public static void main(String[] args) {
        // 创建一个字符串数组
        String[] greeting = new String[3];
        greeting[0] = "Welcome to Core Java";
        greeting[1] = "by Cay Horstmann";
        greeting[2] = "and Gary Cornell";

        // 循环遍历输出字符串数组
        for (String g : greeting) {
            System.out.println(g);
        }
    }
}
