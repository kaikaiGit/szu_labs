import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

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

// 服务器类
public class Servers {
    private static final int serverPort = 9999;
    public static void main(String[] args) {
        try {
            DatagramSocket datagramSocket = new DatagramSocket(serverPort);// 创建数据报送套接字
            System.out.println("服务器已启动！！！");
            byte[] receiveData = new byte[1024];    // 创建接收数据缓存
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            // 创建客户端对象 1
            datagramSocket.receive(receivePacket);
            System.out.println("客户1已准备好了！");
            Client client1 = new Client(receivePacket.getAddress(), receivePacket.getPort());
            // 创建客户端对象 2
            datagramSocket.receive(receivePacket);
            System.out.println("客户2已准备好了！");
            Client client2 = new Client(receivePacket.getAddress(), receivePacket.getPort());
            while (true){
                // 接收客户端发送的信息
                datagramSocket.receive(receivePacket);
                String clientMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
                System.out.println("收到来自 " + receivePacket.getAddress() + " 的消息：" + clientMessage);
                // 发送信息给对应的客户端
                if(!client1.address.equals(receivePacket.getAddress()) || client1.port != receivePacket.getPort()){
                    DatagramPacket sendPacket = new DatagramPacket(receivePacket.getData(), receivePacket.getLength(), client1.address, client1.port);
                    datagramSocket.send(sendPacket);
                    System.out.println("已将信息发送给客户1。");
                }
                else {
                    DatagramPacket sendPacket = new DatagramPacket(receivePacket.getData(), receivePacket.getLength(), client2.address, client2.port);
                    datagramSocket.send(sendPacket);
                    System.out.println("已将信息发送给客户2。");
                }
            }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}
