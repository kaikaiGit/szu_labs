package demo1;//引入相关模块
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

//服务端
public class Sever {
    public static void main(String[] args) throws IOException {
        //创建服务端对象 并 绑定 6666端口
        ServerSocket serverSocket = new ServerSocket(6666);
        //监听等待客户端连接
        Socket socket = serverSocket.accept();
        System.out.println("连接已建立！");
        //从socket中获取输入流、输出流
        InputStream ins = socket.getInputStream();
        OutputStream os = socket.getOutputStream();
        //将字节流进行转化，以防止 中文乱码 问题
        BufferedReader insReader = new BufferedReader(new InputStreamReader(ins));
        //向客户端发送通知，告知通信连接已建立
        os.write("尊敬的用户，连接已建立，可以向本地服务器发送信息！\n".getBytes());
        //不断接收客户端发送的消息，并给予相应的反馈
        while (true){
            String str = insReader.readLine();//读取客户端发送的一条消息
            System.out.println("用户发来消息："+str);
            if(str.equals("Time")){
                //反馈当前时间
                os.write(("当前时间为"+new Date()+"\n").getBytes());
            } else if (str.equals("Bye")) {
                os.write(("Byebye\n").getBytes());
                break;
            }else{
                os.write(("已接收到您的消息！\n").getBytes());
            }
        }
        System.out.println("连接已关闭！");
        //释放socket和服务器资源
        socket.close();
        serverSocket.close();
    }
}
