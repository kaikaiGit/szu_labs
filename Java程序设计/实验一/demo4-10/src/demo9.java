class Circle {
    double radius; // 圆的半径
    double getArea() { // 计算圆的面积的函数方法
        double area = 3.14 * radius * radius; //圆形面积公式
        return area; // 返回圆的面积
    }
}

public class demo9 {
    public static void main(String[] args) {
        Circle circle = new Circle(); // 创建一个圆的对象
        circle.radius = 1; // 设置圆的半径为1
        double area = circle.getArea(); // 调用计算面积的方法计算圆的面积
        System.out.println(area); // 输出圆的面积
    }
}
