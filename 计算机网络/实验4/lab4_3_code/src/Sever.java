//引入相关模块
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
//服务端
public class Sever {
    public static void main(String[] args) throws IOException {
        //创建服务端对象 并 绑定 6666端口
        ServerSocket serverSocket = new ServerSocket(6666);
        //监听等待客户端连接
        Socket socket = serverSocket.accept();
        System.out.println("TCP连接已建立，服务端已就绪！");
        //从socket中获取输出流
        OutputStream os = socket.getOutputStream();
        //要发送的文件名
        String fileName = "myTest.txt";
        System.out.println("要传输的文件为："+fileName);
        //向客户端发送文件名
        os.write((fileName+"\n").getBytes());
        //读取文件数据
        BufferedReader in = new BufferedReader(new FileReader("src/"+fileName));
        String data = "", oneLine;
        while ((oneLine = in.readLine()) != null){
            data += oneLine+"\n";
        }
        System.out.println("开始传输文件···");
        //发送文件数据
        os.write(data.getBytes());
        System.out.println("文件传输结束！");

        //释放socket和服务器资源
        socket.close();
        serverSocket.close();
    }
}