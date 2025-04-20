import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;

public class demo3 {
    public static void main(String[] args) throws IOException {
        //构造szu网站的url对象
        URL szuURL = new URL("https://www.szu.edu.cn/");
        //建立连接 用于读取或写入szuURL引用的资源
        URLConnection urlConnection = szuURL.openConnection();
        //获取输入流
        InputStream ins = urlConnection.getInputStream();
        //创建文件对象
        File szuFile = new File("./szu.html");
        //使用文件输出流创建文件
        FileOutputStream fileOuts = new FileOutputStream(szuFile);
        //将szu网站引用的相关资源写入新建的文件中
        int ch;
        while((ch=ins.read())!=-1){
            fileOuts.write(ch);
        }
        //统计下载得到网页文件的大小
        System.out.println("szu网页文件的大小为：" + szuFile.length()/1024 + "KB");
    }
}
