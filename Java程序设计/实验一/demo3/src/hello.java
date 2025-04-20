class A {
    void f() {
        System.out.println("I am A");
    }
}

class B {}

public class hello {
    public static void main(String[] args) {
        System.out.println("你好，很高兴学习Java");
        A a = new A(); // 创建一个 A类的实例
        a.f(); // 调用 A类的方法,输出 "I am A"
    }
}
