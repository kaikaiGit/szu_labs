public class Person {
    // 成员变量
    private String name;    // 姓名
    private double weight;  // 体重
    private double height;  // 身高
    // 构造方法
    public Person(String name, double weight, double height) {
        this.name = name;
        this.weight = weight;
        this.height = height;
    }
    // 重写Object类的toString()方法
    @Override
    public String toString() {
        return name + "的体重: " + weight + " kg, 身高: " + height + " cm";
    }
    // 主方法用于运行测试代码
    public static void main(String[] args) {
        // 创建Person对象
        Person person = new Person("小吴", 55, 170);
        // 调用重写的toString()方法
        System.out.println(person);
    }
}
