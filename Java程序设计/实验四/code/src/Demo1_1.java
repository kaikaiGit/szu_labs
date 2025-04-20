/**
 * 使用Java语言读取解压后的文件（Watches.txt），并得到以下文件：
 * review.txt：每行3列，以分号作为分隔符，
 * 第1列是userID，第2列是productID，第3列是summary；表示(user, product, summary)三元组。
 * 该文件中不同行之间的顺序按照userID从小到大排列，当userID相同时按照productID从小到大排列。
 * 注：如果没有按照userID或productID从小到大排序扣5分。
 */
import java.io.*;
import java.util.*;

public class Demo1_1 {
    public static void main(String[] args) throws IOException {
        String inputFilePath = "Watches.txt";                // 输入文件路径
        String outputFilePath = "result_data/review.txt";    // 输出文件路径

        List<Review> reviews = new ArrayList<>();   // 使用 ArrayList 容器存储，便于插入、排序

        try (BufferedReader br = new BufferedReader(new FileReader(inputFilePath))) {
            String line;
            Review currentReview = null;
            String productId = "", userId = "", summary = "";
            while ((line = br.readLine()) != null) {
                if (line.startsWith("product/productId")) {
                    productId = line.split(": ")[1];
                } else if (line.startsWith("review/userId")) {
                    userId = line.split(": ")[1];
                } else if (line.startsWith("review/summary")) {
                    summary = line.split(": ")[1];
                    currentReview = new Review(userId, productId, summary); // 此时已经拿到完整的三元组
                    reviews.add(currentReview); // 将该三元组添加到 reviews 容器
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        // 对reviews 进行排序
        Collections.sort(reviews, Comparator.comparing(Review::getUserId).thenComparing(Review::getProductId) );
        // 输出到 review.txt 文件中
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(outputFilePath))) {
            for (Review review : reviews) {
                bw.write(review.getUserId() + ";" + review.getProductId() + ";" + review.getSummary());
                bw.newLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class Review {
    private String userId;      // 用户ID
    private String productId;   // 商品ID
    private String summary;     // 评论
    // 构造函数
    public Review(String userId, String productId, String summary) {
        this.userId = userId;
        this.productId = productId;
        this.summary = summary;
    }
    public String getUserId() {
        return userId;
    }   // 获取用户ID
    public String getProductId() {
        return productId;
    }   // 获取商品ID
    public String getSummary() {
        return summary;
    }   // 获取评论
}

