class Lader {
    double above,bottom,height; //定义梯形的上底、下底和高
    Lader(){} //无参构造方法
    Lader(double a, double b, double h){ //有参构造方法
        above = a; //初始化上底
        bottom = b; //初始化下底
        height = h; //初始化高
    }
    public void setAbove(double a){ //设置上底
        above = a; // 将参数a赋值给above
    }
    public void setBottom(double b){ //设置下底
        bottom = b; // 将参数b赋值给bottom
    }
    public void setHeight(double h){ //设置高
        height = h; // 将参数h赋值给height
    }
    double computeArea(){ //计算梯形面积的方法
        return (above + bottom) * height / 2.0; //梯形面积计算公式：(上底+下底)*高/2
    }
}

public class demo9_2 {
    public static void main(String[] args) {
        double area1=0,area2=0; //定义两个梯形的面积变量
        Lader laderOne,laderTwo; //定义两个梯形对象
        laderOne=new Lader(); //通过new关键字创建一个梯形对象
        laderTwo=new Lader(10,88,20); //通过new关键字创建另一个梯形对象
        laderOne.setAbove(16); //设置梯形1的上底
        laderOne.setBottom(26); //设置梯形1的下底
        laderOne.setHeight(100); //设置梯形1的高
        laderTwo.setAbove(300); //设置梯形2的上底
        laderTwo.setBottom(500); //设置梯形2的下底
        area1=laderOne.computeArea(); //计算梯形1的面积
        area2=laderTwo.computeArea(); //计算梯形2的面积
        System.out.println(area1); //输出梯形1的面积
        System.out.println(area2); //输出梯形2的面积
    }
}
