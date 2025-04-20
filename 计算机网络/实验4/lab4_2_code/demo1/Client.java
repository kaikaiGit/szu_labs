package demo1;//引入相关模块
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;
//客户端
public class Client {
    public static void main(String[] args) throws IOException {
        //创建socket对象 并 连接服务端
        Socket socket = new Socket("127.0.0.1",6666);
        //创建Scanner对象 以 手动输入数据
        Scanner sc = new Scanner(System.in);
        //从socket中获取输出流、输入流
        OutputStream os = socket.getOutputStream();
        InputStream ins = socket.getInputStream();
        //将字节流进行转化，以防止 中文乱码 问题
        InputStreamReader insReader = new InputStreamReader(ins);
        //接受服务器发来的提示消息
        int ch;
        while ((ch = insReader.read()) != -1) {
            //将依次读取到的字符进行输出
            System.out.print((char)ch);
            if(ch=='\n')break;
        }
        //不断发送信息给服务器
        while (true){
            System.out.print("请输入您想要发送的消息：");
            //手动输入消息
            String str = sc.nextLine();
            //发送消息给 服务端
            os.write((str+"\n").getBytes());
            //接受服务器发来的提示消息
            System.out.print("服务器回复：");
            while ((ch = insReader.read()) != -1) {
                //将依次读取到的字符进行输出
                System.out.print((char)ch);
                if(ch=='\n')break;
            }
            if(str.equals("Bye"))break;
        }
        System.out.println("会话结束！");
        //释放socket资源
        socket.close();
    }
}
