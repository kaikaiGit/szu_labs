package demo2;

import java.io.*;
import java.net.*;

class UDPClient {
    public static void main(String args[]) throws Exception
    {
        //生成输入流
        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
        //生成客户端套接字
        DatagramSocket ClientSocket = new DatagramSocket();
        //获取本机IP地址
        InetAddress IPAddress = InetAddress.getLocalHost();
        //准备字节数组用于存储数据
        byte[ ] sendData = new byte[1024];
        byte[ ] receiveData = new byte[1024];
        //从控制台里读入一行字符 并 存入字节数组
        System.out.print("请发送一条消息：");
        String sentence = inFromUser.readLine();
        sendData = sentence.getBytes();
        //打包数据报 并 发送给服务端
        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
        ClientSocket.send(sendPacket);
        //打包数据报 并 从服务端接收数据
        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
        ClientSocket.receive(receivePacket);
        //将从服务端接收到的数据转为 字符串
        String modifiedSentence = new String(receivePacket.getData());
        //将从服务端接收的数据打印出来
        System.out.println("FROM Server:" + modifiedSentence.substring(0,sentence.length()));
        ClientSocket.close();
    }
}
