package demo3_2;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.Random;

class JavaTest extends JFrame{//继承JFrame类，实现Runnable接口
    int score,Total_time,time;//分数、总时间、答题时间
    int sg,multi,tf;//单选，多选，判断数量
    int T_sg,T_multi,T_tf;//单选，多选，判断正确数量
    JLabel scoreLabel,Total_timeLabel,timeLabel;//分数、总时间、答题时间标签
    JLabel singleLabel,multiLabel,tfLabel;//单选，多选，判断数量标签
    JLabel T_singleLabel,T_multiLabel,T_tfLabel;//单选，多选，判断正确数量标签
    JRadioButton ARadio,BRadio,CRadio,DRadio;//单选A,B,C,D选项
    JCheckBox ABox,BBox,CBox,DBox;//多选A,B,C,D选项
    JRadioButton T,F;//判断题按钮
    JButton submitButton;//提交按钮
    JTextArea print,result;//题目文本组件、答题结果
    GiveQuestion giveQuestion;//出题类对象
    Timer timer;//计时器
    /*作为是否是显示答案时间的标志，
    为0时，是答题时间，总时间正常++，
    为1时，是显示答案时间，总时间不计数*/
    int flag;

    private static final int serverPort = 9999; // 服务器端口号
    private static final String serverHost = "localhost";

    JavaTest() throws SocketException, UnknownHostException {//无参构造
        //创建窗口界面
        setSize(680,680);//设置窗口大小
        setTitle("Java机考");//设置界面标题
        setLocationRelativeTo(null);//窗口居中
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭窗口时结束程序运行
        setLayout(null);//取消默认居中布局
        //开始考试界面
        setVisible(false);//开始考试前不显示机考窗口
        new StartFrame(this);
        //分数、时间,单选，多选，判断数量初始化
        score=Total_time=sg=multi=tf=0;
        time=T_sg=T_multi=T_tf=0;
        //创建giveQuestion线程
        giveQuestion=new GiveQuestion(this);
        Thread giveQuestionThread=new Thread(giveQuestion);
        giveQuestionThread.start();

        //提交
        submitButton=new JButton("提交");
        submitButton.addActionListener(new ActionListener() {
            //按下按钮后，判断是否做对题，然后继续下一题
            @Override
            public void actionPerformed(ActionEvent e) {
                giveQuestion.Check();//判断是否做对题
                giveQuestionThread.interrupt();//唤醒线程
            }
        });
        submitButton.setBounds(290,500,100,50);//给这个标签设置位置
        getContentPane().add(submitButton);//存入容器
        //flag初始化为0
        flag=0;
        //设置Timer，每1s触发一次
        timer = new Timer(1000, e -> {
            timer.stop();
            time++;
            if (flag == 0) Total_time++;
            Loading();
            repaint();
            timer.start();
        });

        DatagramSocket socket = new DatagramSocket(999);;  // 创建UDP套接字
        InetAddress serverAddress = InetAddress.getByName(serverHost);  // 服务器地址
        try {
            byte[] sendData = ByteBuffer.allocate(4).putInt(giveQuestion.getP()).array();;
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("localhost"), 9999);
            socket.send(sendPacket);    //发送数据

            // 创建线程用于接受服务端发来的题目
            Thread receiveThread = new Thread(() -> {   // 使用Lambda表达式创建线程
                try {
                    byte[] receiveData = new byte[1024*64];    // 创建接收数据缓冲区
                    DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                    while (true) {
                        socket.receive(receivePacket);    // 接收数据
                        String receiveMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
                        if(receiveMessage.startsWith("题目")){
                            System.out.println("收到来自服务器发来的题目：\n" + receiveMessage.substring(3));
                        }
                        else if(receiveMessage.startsWith("判断结果")){
                            System.out.println("服务器的判定结果：\n" + receiveMessage.substring(5));
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });
            receiveThread.start(); // 启动接收线程
        } catch (Exception e){
            e.printStackTrace();
        }
    }
    void Loading(){//加载分数,时间,单选，多选，判断数量
        //移除所有加载组件
        RemoveLoading();
        //分数
        scoreLabel=new JLabel("Score:"+score);//将文本和分数填入标签
        scoreLabel.setBounds(10,10,100,20);//给这个标签设置位置
        getContentPane().add(scoreLabel);//存入容器
        //总时间
        Total_timeLabel=new JLabel("TotalTime:"+Total_time);//将文本和时间填入标签
        Total_timeLabel.setBounds(580,10,100,20);////给这个标签设置位置
        getContentPane().add(Total_timeLabel);//存入容器
        //答题时间
        timeLabel=new JLabel("Time:"+time);//将文本和时间填入标签
        timeLabel.setBounds(310,10,50,20);////给这个标签设置位置
        getContentPane().add(timeLabel);//存入容器
        //单选
        singleLabel=new JLabel("当前单选题数:"+sg);//将文本和单选题数填入标签
        singleLabel.setBounds(10,580,100,20);//给这个标签设置位置
        getContentPane().add(singleLabel);//存入容器
        //多选
        multiLabel=new JLabel("当前多选题数:"+multi);//将文本和多选题数填入标签
        multiLabel.setBounds(295,580,100,20);//给这个标签设置位置
        getContentPane().add(multiLabel);//存入容器
        //判断
        tfLabel=new JLabel("当前判断题数:"+tf);//将文本和判断题数填入标签
        tfLabel.setBounds(570,580,100,20);//给这个标签设置位置
        getContentPane().add(tfLabel);//存入容器
        //正确单选
        T_singleLabel=new JLabel("正确单选题数:"+T_sg);//将文本和正确单选题数填入标签
        T_singleLabel.setBounds(10,610,100,20);//给这个标签设置位置
        getContentPane().add(T_singleLabel);//存入容器
        //正确多选
        T_multiLabel=new JLabel("正确多选题数:"+T_multi);//将文本和正确多选题数填入标签
        T_multiLabel.setBounds(295,610,100,20);//给这个标签设置位置
        getContentPane().add(T_multiLabel);//存入容器
        //正确判断
        T_tfLabel=new JLabel("正确判断题数:"+T_tf);//将文本和正确判断题数填入标签
        T_tfLabel.setBounds(570,610,100,20);//给这个标签设置位置
        getContentPane().add(T_tfLabel);//存入容器
    }
    void RemoveLoading(){//移除加载组件
        try{
            remove(scoreLabel);
            remove(Total_timeLabel);
            remove(timeLabel);
            remove(singleLabel);
            remove(multiLabel);
            remove(tfLabel);
            remove(T_singleLabel);
            remove(T_multiLabel);
            remove(T_tfLabel);
        }catch (Exception e){}
        repaint();
    }
    void Single(){//加载单选按钮组件
        //移除单选组件
        RemoveSingle();
        //单选方法
        //设置选项按钮
        ARadio=new JRadioButton("A");
        BRadio=new JRadioButton("B");
        CRadio=new JRadioButton("C");
        DRadio=new JRadioButton("D");
        //设置坐标、大小
        ARadio.setBounds(100,400,40,20);
        BRadio.setBounds(250,400,40,20);
        CRadio.setBounds(400,400,40,20);
        DRadio.setBounds(550,400,40,20);
        getContentPane().add(ARadio);
        getContentPane().add(BRadio);
        getContentPane().add(CRadio);
        getContentPane().add(DRadio);
        //bottonGroup控制为单选
        ButtonGroup optionGroup = new ButtonGroup();
        optionGroup.add(ARadio);
        optionGroup.add(BRadio);
        optionGroup.add(CRadio);
        optionGroup.add(DRadio);
    }
    void RemoveSingle(){//移除单选组件
        try{
            remove(ARadio);
            remove(BRadio);
            remove(CRadio);
            remove(DRadio);
        }catch (Exception e){}
        repaint();
    }
    void Multiple(){//加载多选按钮组件
        //移除多选组件
        RemoveMultiple();
        //设置选项按钮
        ABox=new JCheckBox("A");
        BBox=new JCheckBox("B");
        CBox=new JCheckBox("C");
        DBox=new JCheckBox("D");
        //设置坐标、大小
        ABox.setBounds(100,400,40,20);
        BBox.setBounds(250,400,40,20);
        CBox.setBounds(400,400,40,20);
        DBox.setBounds(550,400,40,20);
        getContentPane().add(ABox);
        getContentPane().add(BBox);
        getContentPane().add(CBox);
        getContentPane().add(DBox);
    }
    void RemoveMultiple(){//移除多选组件
        try{
            remove(ABox);
            remove(BBox);
            remove(CBox);
            remove(DBox);
        }catch (Exception e){}
        repaint();
    }
    void TrueFalse(){//加载判断按钮组件
        //移除判断组件
        RemoveTrueFalse();
        //设置选项按钮
        T=new JRadioButton("A");
        F=new JRadioButton("B");
        //bottonGroup控制为单选
        ButtonGroup optionGroup = new ButtonGroup();
        optionGroup.add(T);
        optionGroup.add(F);
        //设置坐标、大小
        T.setBounds(250,400,40,20);
        F.setBounds(400,400,40,20);
        getContentPane().add(T);
        getContentPane().add(F);
    }
    void RemoveTrueFalse(){//移除判断组件
        try{
            remove(T);
            remove(F);
        }catch (Exception e){}
        repaint();
    }
    void RemovePrint(){//移除题目文本
        try{
            remove(print);
        }catch (Exception e){}
        repaint();
    }
    void ShowAnswer(Boolean b,String ans){//每答完一题，显示一次结果
        result=new JTextArea();
        if(b){//b==true，回答正确
            result.setText("Perfect! Answer:"+ans);
            result.setForeground(Color.red);//字体设为红色
        }
        else{//b==false，回答错误
            result.setText("Next Try! Answer:"+ans);
            result.setForeground(Color.red);//字体设为红色
        }
        result.setBounds(0,360,680,20);
        getContentPane().add(result);
        Loading();//加载组件
        repaint();
    }
    void RemoveShowAnswer(){//移除题目答案组件
        try{
            remove(result);
        }catch (Exception e){}
        repaint();
    }
}

class StartFrame extends JFrame{//开始界面
    JButton start;//开始考试按钮
    StartFrame(JavaTest javaTest){
        //创建窗口
        setSize(680,680);//设置窗口大小
        setTitle("Java机考");//设置界面标题
        setLocationRelativeTo(null);//窗口居中
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//关闭窗口时结束程序运行
        setLayout(null);//取消默认居中布局
        // 设置背景图
        JLabel background = new JLabel(new ImageIcon("javaBgI.jpg"));
        background.setBounds(0, -50, getWidth(), getHeight());
        getContentPane().add(background);
        //开始按钮
        start=new JButton("开始考试");
        start.addActionListener(new ActionListener() {
            //按下开始考试后，关闭开始窗口，打开机考窗口
            @Override
            public void actionPerformed(ActionEvent e) {
                setVisible(false);//关闭开始窗口
                javaTest.setVisible(true);//打开机考窗口
            }
        });

        // 设置按钮样式
        start.setFocusPainted(false);
        // 设置按钮位置和大小，使其居中
        int x = (getWidth() - 100) / 2;
        int y = getHeight() - 120;
        start.setBounds(x, y, 100, 50);
        getContentPane().add(start);//存入容器
        //显示开始窗口
        setVisible(true);
    }
}
class GiveQuestion implements Runnable{
    static String[] questions = {//题库
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
            "一个Java类可以有多个父类。\n"+"A.正确\nB.错误\n"
    };
    String[] answer={//答案
            "B","C","A","B","D","D","C","B","D","B",
            "BD","ABD","BCD","AB","ABC","ACD","BCD","AB","ABCD","CD",
            "A","B","B","B","A","A","A","A","B","B"
    };
    int p;//作为抽到的题目的下标
    int lp;//作为上次抽到的题目的下标
    Boolean[] visited;//布尔类，判断该题是否访问过
    JavaTest javaTest;//机考类对象
    GiveQuestion(JavaTest javaTest){
        this.javaTest=javaTest;
        //visited一共30个元素，并初始化为false，表示未访问过
        visited=new Boolean[30];
        for(int i=0;i<30;i++) visited[i]=false;
    }
    void Check(){
        String ans="";//用户提交的答案
        boolean flag = false;    //true代表回答正确,false代表错误
        if(p<10){//抽到单选
            if(javaTest.ARadio.isSelected()) ans+="A";
            if(javaTest.BRadio.isSelected()) ans+="B";
            if(javaTest.CRadio.isSelected()) ans+="C";
            if(javaTest.DRadio.isSelected()) ans+="D";
            //判断是否回答正确
            if(ans.equals(answer[p])){//回答正确
                javaTest.score++;//加1分
                javaTest.T_sg++;//单选正确数+1
                javaTest.ShowAnswer(true,answer[p]);
                flag = true;
            }
            else javaTest.ShowAnswer(false,answer[p]);//回答错误
        }
        else if(p<20){//抽到多选
            if(javaTest.ABox.isSelected()) ans+="A";
            if(javaTest.BBox.isSelected()) ans+="B";
            if(javaTest.CBox.isSelected()) ans+="C";
            if(javaTest.DBox.isSelected()) ans+="D";
            //判断是否回答正确
            if(ans.equals(answer[p])){//回答正确
                javaTest.score+=2;//加2分
                javaTest.T_multi++;//多选正确数+1
                javaTest.ShowAnswer(true,answer[p]);
                flag = true;
            }
            else javaTest.ShowAnswer(false,answer[p]);//回答错误
        }
        else{//抽到判断
            if(javaTest.T.isSelected()) ans+="A";
            if(javaTest.F.isSelected()) ans+="B";
            //判断是否回答正确
            if(ans.equals(answer[p])){//回答正确
                javaTest.score++;//加1分
                javaTest.T_tf++;//判断正确数+1
                javaTest.ShowAnswer(true,answer[p]);
                flag = true;
            }
            else javaTest.ShowAnswer(false,answer[p]);//回答错误
        }
        if (flag) System.out.println("服务器判断客户端的回答为：true\n");
        else System.out.println("服务器判断客户端的回答为：false\n");
    }
    @Override
    public void run() {
        Random random=new Random();//创建一个随机数对象，用于抽取题目

        for (int i=1;i<=15;i++) {//一共出15道题
            //每提交一题，就暂停2s显示答案
            if(i!=1){
                javaTest.flag=1;//此时是显示答案时间
                javaTest.time=0;//当前题目时间归零
                javaTest.Total_time++;
                javaTest.timer.start();//启动计时器
                javaTest.Loading();//加载分数,时间,单选，多选，判断数量
                javaTest.repaint();
                try {
                    Thread.sleep(2000);
                }catch (Exception e1){}
                javaTest.RemoveShowAnswer();//移除显示答案组件
            }
            //检查同类型题目是否已经抽取5道
            if(javaTest.sg>=5){
                //如果已经出了5题，将所有单选设为已访问，防止再抽到单选
                for(int j=0;j<10;j++) visited[j]=true;
            }
            if(javaTest.multi>=5){
                //如果已经出了5题，将所有多选设为已访问，防止再抽到多选
                for(int j=10;j<20;j++) visited[j]=true;
            }
            if(javaTest.tf>=5){
                //如果已经出了5题，将所有判断设为已访问，防止再抽到判断
                for(int j=20;j<30;j++) visited[j]=true;
            }
            //只有没被选过的题能被选择
            while(true){
                p=random.nextInt(30);//30以内的随机数

                // 发送数据给服务器
                byte[] sendData = ByteBuffer.allocate(4).putInt(p).array();
                DatagramPacket sendPacket = null;
                DatagramSocket socket = null;
                try {
                    // 创建UDP套接字
                    socket = new DatagramSocket(998);
                    sendPacket = new DatagramPacket(sendData, sendData.length, InetAddress.getByName("localhost"), 9999);
                    socket.send(sendPacket);    //发送数据
                } catch (Exception e) {
                    e.printStackTrace();
                } finally {
                    socket.close();
                }

                if(visited[p]==false) break;
            }
            //将当前抽到的题目设置为已访问过
            visited[p]=true;
            //移除上一题的按钮组件
            if(lp<10) javaTest.RemoveSingle();
            else if(lp<20) javaTest.RemoveMultiple();
            else javaTest.RemoveTrueFalse();
            //移除上一题文本，设置新文本
            javaTest.RemovePrint();
            javaTest.print=new JTextArea();
            javaTest.print.setEditable(false);
            javaTest.print.setLineWrap(true);
            //显示题目，并让抽到的题型数+1
            if(p<10){
                javaTest.print.setText("单选题\n"+i+". "+questions[p]);
                javaTest.sg++;
                javaTest.Single();//调用javaTest的单选方法
            }
            else if(p<20){
                javaTest.print.setText("多选题\n"+i+". "+questions[p]);
                javaTest.multi++;
                javaTest.Multiple();//调用javaTest的多选方法
            }
            else{
                javaTest.print.setText("判断题\n"+i+". "+questions[p]);
                javaTest.tf++;
                javaTest.TrueFalse();//调用javaTest的判断题方法
            }
            javaTest.print.setBounds(150,100,400,250);
            javaTest.getContentPane().add(javaTest.print);
            javaTest.flag=0;//此时是答题时间
            javaTest.time=0;//当前题目时间归零
            javaTest.timer.start();//启动计时器
            javaTest.Loading();//加载分数,时间,单选，多选，判断数量
            javaTest.repaint();
            lp=p;
            try {//20s自动提交
                Thread.sleep(20000);
                Check();
            } catch (Exception e) {}
        }
        //15题出完后，调取结束界面
        javaTest.setVisible(false);//关闭考试界面
        new EndFrame(javaTest);//打开结束界面
    }
    public int getP(){  //获取当前题目的索引
        return p;
    }
}
class EndFrame extends JFrame{//考试结束界面
    JLabel final_time;//时间标签
    JLabel final_score;//成绩标签
    JButton end;//关闭按钮
    EndFrame(JavaTest javaTest){
        //创建窗口
        setSize(680,680);//设置窗口大小
        setTitle("Java机考");//设置界面标题
        setLocationRelativeTo(null);//窗口居中
        setDefaultCloseOperation(3);//关闭窗口时结束程序运行
        setLayout(null);//取消默认居中布局
        //创建时间标签
        final_time=new JLabel("Total_time:"+javaTest.Total_time);
        final_time.setBounds(290,210,100,20);
        getContentPane().add(final_time);
        //创建成绩标签
        final_score=new JLabel("Score:"+javaTest.score);
        final_score.setBounds(290,230,100,20);
        getContentPane().add(final_score);
        //结束考试按钮
        end=new JButton("结束考试");
        end.addActionListener(new ActionListener() {
            //按下结束考试后关闭界面
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);//结束程序
            }
        });
        end.setBounds(290,400,100,50);//给这个标签设置位置
        getContentPane().add(end);//存入容器
        //显示窗口
        setVisible(true);
    }
}

public class Demo3_2 {
    public static void main(String[] args) throws SocketException, UnknownHostException {
        JavaTest javaTest = new JavaTest();//创建机考窗口
    }
}