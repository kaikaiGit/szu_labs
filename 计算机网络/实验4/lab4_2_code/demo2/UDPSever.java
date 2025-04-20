package demo2;

import java.io.*;
import java.net.*;

class UDPServer {
    public static void main(String args[]) throws Exception
    {
        //在端口9876生成服务端数据报套接字
        DatagramSocket ServerSocket = new DatagramSocket(9876);
        //准备字节数组用于存储数据
        byte[] receiveData = new byte[1024];
        byte[] sendData  = new byte[1024];
        //不断接收客户端的数据，将之转为大写之后返回给客户端
        while(true) {
            //打包数据报 并 从客户端接收数据
            DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
            ServerSocket.receive(receivePacket);
            //将从客户端接收到的数据转为 字符串
            String sentence = new String(receivePacket.getData());
            //获得发送方的 IP 地址，端口号
            InetAddress IPAddress = receivePacket.getAddress();
            int port = receivePacket.getPort();
            //将字符串转成 大写字符格式
            String capitalizedSentence = sentence.toUpperCase();
            sendData = capitalizedSentence.getBytes();
            //打包数据报 并 发送给客户端
            DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
            ServerSocket.send(sendPacket);
        }
    }
}