import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.*;

public class Client2 {
    private static final String serverHost = "localhost";
    private static final int serverPort = 9999;
    public static void main(String[] args) {
        try {
            // 创建客户端UDP套接字
            DatagramSocket clientSocket = new DatagramSocket(99);
            InetAddress serverAddress = InetAddress.getByName(serverHost);
            // 创建线程用于接受其他客户端的信息
            Thread receiveThread = new Thread(() -> {   // 使用Lambda表达式创建线程
                try {
                    byte[] receiveData = new byte[1024];    // 创建接收数据缓冲区
                    DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                    while (true) {
                        clientSocket.receive(receivePacket);    // 接收数据
                        String receiveMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
                        System.out.println("收到来自服务器的消息：" + receiveMessage);
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            });
            receiveThread.start(); // 启动接收线程
            // 发送消息
            while (true) {
                // 从键盘获取输入并发送给服务器
                BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));// 创建键盘输入流
                String sendMessage = reader.readLine();// 从键盘读取数据
                byte[] sendData = sendMessage.getBytes();// 把输入的数据封装成字节数组
                DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, serverPort);
                clientSocket.send(sendPacket);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
