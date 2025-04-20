//引入相关模块
import java.io.*;
import java.net.Socket;
import java.util.Scanner;
//客户端
public class Client {
    public static void main(String[] args) throws IOException {
        //创建socket对象 并 连接服务端
        Socket socket = new Socket("127.0.0.1",6666);
        System.out.println("已连接到服务端！");

        //从socket中获取输入流
        InputStream ins = socket.getInputStream();
        //将字节流进行转化，以防止 中文乱码 问题，同时，方便读取整行数据
        BufferedReader inReader = new BufferedReader(new InputStreamReader(ins));
        //将接收到的文件命名为myReceive.txt
        String fileName = "myReceive.txt";
        //创建文件输出流用于写文件
        FileWriter fileWriter = new FileWriter("src/"+fileName);
        //每读取一行的字符数据
        String oneline;
        int index = 1;
        while ((oneline=inReader.readLine()) != null){
            if(index==1){
                //接收服务端发送来的文件名
                System.out.println("接收到的文件名为："+oneline);
                System.out.println("将保存为："+fileName);
                index++;
            }
            else{
                fileWriter.write(oneline+"\n");
            }
        }
        //关闭文件输出流
        fileWriter.close();
        //释放socket资源
        socket.close();
    }
}