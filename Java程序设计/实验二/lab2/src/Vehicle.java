public abstract class Vehicle {
    protected float speed; // 速度
    protected String color; // 颜色
    protected String brand; // 品牌
    protected int passengerNum; // 核载数量
    // 构造方法
    public Vehicle() {
    }
    public Vehicle(float speed, String color, String brand, int passengerNum) {
        this.speed = speed;
        this.color = color;
        this.brand = brand;
        this.passengerNum = passengerNum;
    }
    // 抽象方法
    public float getSpeed() { // 获取当前速度
        return speed;
    }
    public void accelerate(int increment) { // 加速
        speed += increment;
    }
    public void decelerate(int decrement) { // 减速
        speed -= decrement;
    }

    public String getColor() { // 获取车辆颜色
        return color;
    }
    public void setColor(String color) { // 设置车辆颜色
        this.color = color;
    }

    public String getBrand() { // 获取车辆品牌
        return brand;
    }
    public int getPassengerNum() { // 获取限客数量
        return passengerNum;
    }
}

