import java.net.InetAddress;
import java.net.UnknownHostException;

public class demo1 {
    public static void main(String[] args) throws UnknownHostException {
        //创建InetAddress的实例
        InetAddress myInetAddress = InetAddress.getLocalHost();
        System.out.println("本机名："+myInetAddress.getHostName()+"\t"
                +"本机IP："+myInetAddress.getHostAddress());
    }
}
