class Lader_2
{
    double above,height; //实例变量
    static double bottom; //静态变量
    void setAbove(double a) //用于设置above的方法
    {
        above=a; //将参数a赋值给above
    }
    void setBottom(double b) //用于设置bottom的方法
    {
        bottom=b; //将参数b赋值给bottom
    }
    double getAbove() //获取above的方法
    {
        return above; //返回above的值
    }
    double getBottom() //获取bottom的方法
    {
        return bottom; //返回bottom的值
    }
}

public class demo9_3
{
    public static void main(String args[]) {
        Lader_2.bottom = 60; //设置静态变量bottom的值为60
        Lader_2 laderOne, laderTwo; //定义两个梯形对象
        System.out.println(Lader_2.bottom); //输出静态变量bottom的值
        laderOne = new Lader_2();//创建一个梯形对象
        laderTwo = new Lader_2();//创建另一个梯形对象
        System.out.println(laderOne.getBottom());//输出梯形1的bottom值
        System.out.println(laderTwo.getBottom());//输出梯形2的bottom值
        laderOne.setAbove(11);//设置梯形1的above值
        laderTwo.setAbove(22);//设置梯形2的above值
        laderTwo.setBottom(100);//设置梯形2的bottom值
        System.out.println(Lader_2.bottom);//输出静态变量bottom的值
        System.out.println(laderOne.getAbove()); //输出梯形1的above值
        System.out.println(laderTwo.getAbove()); //输出梯形2的above值
    }
}