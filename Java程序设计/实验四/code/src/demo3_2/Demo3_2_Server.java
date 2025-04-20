package demo3_2;

import java.net.*;
import java.nio.ByteBuffer;

// 客户端类，用于封装服务器地址和端口号
class Client {
    InetAddress address;    // 服务器地址
    int port;   // 服务器端口号
    // 有参构造函数
    Client(InetAddress address, int port){
        this.address = address;
        this.port = port;
    }
}

public class Demo3_2_Server {
    private static final int serverPort = 9999; // 服务器端口号
    private static final int clientPort = 999;
    private static String[] questions = {//题库
            //0-9,单选
            "Java嵌入式应用开发平台名称为:\n"+"A.JDK\n" + "B.J2ME\n" + "C.J2SE\n" + "D.J2EE\n",
            "JAVA语言使用的字符集是:\n"+"A.ASCII\n"+"B.EBCDIC\n"+"C.Unicode\n"+"D.BCD",
            "JAVA语言中控制结构包括:\n"+"A.顺序结构、选择结构、循环结构\n"+"B.顺序结构、循环结构\n"+"C.顺序结构、选择结构\n"+"D.选择结构、循环结构",
            "若a是int型变量，表达式a=(int)(25.8/3%3);执行后a的值为:\n"+"A.1\n"+"B.2\n"+"C.3\n"+"D.4\n",
            "下列哪个类声明是正确的?\n"+"A.abstract final class H1{}\n"+"B.abstract private move(){}\n"+"C.protected private number;\n"+"D.public abstract class Car{}\n",
            "以下选项符合对象和类的关系的是:\n"+"A.人和老虎\n"+"B.书和汽车\n"+"C.父亲和儿子\n"+"D.汽车和交通工具\n",
            "下面关于java中类的说法哪个是不正确的?\n"+"A.类体中只能有变量定义、常量定义和成员方法的定义，不能包含“x=3;”这样的语句。\n"+"B.构造函数是类中的特殊方法\n"+"C.主类一定要声明为public。\n"+"D.一个java文件中可以有多个class定义。\n",
            "下列哪项是Java编程所必须的默认引用包?\n"+"A.java.sys包\n"+"B.java.lang包\n"+"C.java.net包\n"+"D.以上都不是\n",
            "在Java中函数main()的返回值是:\n"+"A.String\n"+"B.int\n"+"C.char\n"+"D.void\n",
            "构造方法何时被调用?\n"+"A.类定义时\n"+"B.创建对象时\n"+"C.调用对象方法时\n"+"D.使用对象的变量时\n",
            //10-19,多选
            "下面哪个单词是Java语言的关键字?\n"+"A.Float\n"+"B.this\n"+"C.string\n"+"D.new\n",
            "Java语言有下面一些特点:\n"+"A.面向对象\nB.可移植\nC.不安全性\nD.多线程以及动态性\n",
            "JDK包括哪些:\n"+"A.Java程序\nB.Java运行环境\nC.一堆Java工具\nD.Java基础的类库\n",
            "每一个变量都拥有:\n"+"A.名字\nB.类型\nC.大小\nD.长度\n",
            "设A为已定义的类名,下列声明A类的对象a的语句中错误的是:\n"+"A.float A a;\nB.public A a=A();\nC.A a=new int();\nD.static A a=new A();\n",
            "用来导入已定义好的类或包的语句错误的是:\n"+"A.main\nB.import\nC.public class\nD.class\n",
            "关于类所包含的内容以下说法错误的是:\n"+"A.属性和方法\nB.变量和方法\nC.变量和数据\nD.对象和属性\n",
            "protected可以修饰以下哪项:\n"+"A.变量\nB.方法\nC.类\nD.接口\n",
            "public可以修饰以下哪项:\n"+"A.变量\nB.方法\nC.类\nD.接口\n",
            "以下属于面向对象的特征的是:\n"+"A.重载\nB.重写\nC.封装\nD.继承\n",
            //20-29,判断题
            "静态初始化,就是在定义数组的同时为数组的每个元素赋值。\n"+"A.正确\nB.错误\n",
            "二进制是由数字0和1组成的数字序列。\n"+"A.正确\nB.错误\n",
            "Java不区分大小写的。\n"+"A.正确\nB.错误\n",
            "Java中比较两个数是否相等可以使用“=”。\n"+"A.正确\nB.错误\n",
            "二维数组有两个索引。\n"+"A.正确\nB.错误\n",
            "用static修饰的变量是类变量。\n"+"A.正确\nB.错误\n",
            "在Java程序中，可以使用protected来修饰一个类。\n"+"A.正确\nB.错误\n",
            "对于abstract类，不能创建该类的对象。\n"+"A.正确\nB.错误\n",
            "有的类定义时可以不定义构造函数，所以构造函数不是必需的。\n"+"A.正确\nB.错误\n",
            "一个Java类可以有多个父类。\n"+"A.正确\nB.错误\n",
            ""
    };
    Demo3_2_Server() {

    }

    public static void main(String[] args) throws UnknownHostException {
        DatagramSocket datagramSocket = null;
        InetAddress serverAddress = InetAddress.getByName("localhost");
        try {
            datagramSocket = new DatagramSocket(serverPort);// 创建数据报送套接字
            System.out.println("服务器已启动！！！");
            byte[] receiveData = new byte[1024*64];    // 创建接收数据缓存
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            // 创建客户端对象
            Client client = null;
            while (true){
                // 接收客户端发送的信息
                datagramSocket.receive(receivePacket);
                client = new Client(receivePacket.getAddress(), receivePacket.getPort());

                // 将接收到的字节数组转换为整数
                int questionNumber = ByteBuffer.wrap(receiveData).getInt();
                if(questionNumber>=questions.length)questionNumber = questions.length-1;
                String question = questions[questionNumber];  // 获取对应题目
                question = "题目：" + question;
                // 发送题目给客户端
                DatagramPacket sendPacket = new DatagramPacket(question.getBytes(), question.getBytes().length, serverAddress, clientPort);
                datagramSocket.send(sendPacket);
            }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}