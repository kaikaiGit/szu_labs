class Tom
{
    final int MAX=100; // 定义final修饰的实例变量MAX
    final static int MIN=20; // 定义final修饰的静态变量MIN
}
public class demo9_4
{
    public static void main(String args[]) {
        System.out.println(Tom.MIN); //直接访问静态变量MIN
//        System.out.println(Tom.MAX); // Error
        Tom cat = new Tom(); // 创建Tom类的实例对象cat
        System.out.println(cat.MAX); // 通过实例对象访问实例变量MAX
    }
}
