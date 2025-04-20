public class Tom {
    int leg;
    String head;
    void cry(String s) {
        System.out.println(s); // 输出传入的字符串
    }
}

class Example {
    public static void main(String[] args) {
        Tom cat = new Tom(); // 创建一个 Tom类的实例
        // 为 Tom类的实例的属性赋值
        cat.leg = 4;
        cat.head = "猫头";
        System.out.println("腿："+cat.leg+"条");
        System.out.println("头："+cat.head);
        cat.cry("我今天要和Jerry拼了"); // 调用 Tom类的方法,输出"我今天要和Jerry拼了"
    }
}
