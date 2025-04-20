import java.net.InetAddress;
import java.net.UnknownHostException;

public class demo2 {
    public static void main(String[] args) throws UnknownHostException {
        //创建www.csdn.net的InetAddress实例
        InetAddress []csdnAddressArr = InetAddress.getAllByName("www.csdn.net");
        System.out.println("All the addressIP of CSDN:");
        for(InetAddress csdnAddress:csdnAddressArr){
            //逐个打印IP
            System.out.println(csdnAddress.getHostAddress());
        }
    }
}
