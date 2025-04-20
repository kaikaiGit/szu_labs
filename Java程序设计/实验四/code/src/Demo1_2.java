/**
 * 根据review.txt进行计算，并得到以下文件：
 * userNeighborhood.txt：每行11列，以分号作为分隔符，
 * 第1列是userID，第2-10列是与该用户最相似的10个用户的userID，按相似度值从大到小排列，
 * 其中相似度是通过review.txt中的前两列计算得到的Jaccard index值。
 * 该文件中不同行之间的顺序，按照第1列的userID从小到大排列。
 * 注：如果没有使用多线程实现扣5分，如果没有按相似度从大到小排列扣5分。
 */
import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class Demo1_2 {
    public static void main(String[] args) throws IOException {
        String inputFilePath = "result_data/review.txt";    // 输入文件路径
        String outputFilePath = "result_data/userNeighborhood.txt"; // 输出文件路径
        // 从文件中读取数据
        Map<String, Set<String>> userReviews = readUserReviews(inputFilePath);
        // 计算每对用户的Jaccard指数
        Map<String, List<UserSimilarity>> userSimilarities = calculateJaccardIndex(userReviews);
        // 排序并选择每个用户最相似的10个用户
        sortAndSelectTopUsers(userSimilarities);
        // 将结果写入输出文件
        writeResultsToFile(userSimilarities, outputFilePath);
    }
    /* 从文件中读取数据，并返回一个Map，其中键是userID，值是该用户的所有评论 */
    private static Map<String, Set<String>> readUserReviews(String filePath) throws IOException {
        Map<String, Set<String>> userReviews = new HashMap<>(); // 使用HashMap存储用户评论
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {   // 使用缓冲读取器读取文件
            String line;
            while ((line = br.readLine()) != null) {    // 逐行读取文件
                String[] parts = line.split(";");
                if (parts.length >= 2) {
                    String userId = parts[0];
                    String productId = parts[1];
                    userReviews.computeIfAbsent(userId, k -> new HashSet<>()).add(productId);// 将评论添加到对应的用户集合中
                }
            }
        }
        return userReviews;
    }
    /* 利用线程池并行计算每对用户的Jaccard指数，并将结果存储在Map中 */
    private static Map<String, List<UserSimilarity>> calculateJaccardIndex(Map<String, Set<String>> userReviews) {
        Map<String, List<UserSimilarity>> userSimilarities = new ConcurrentHashMap<>(); // 使用ConcurrentHashMap存储结果
        ExecutorService executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors()); // 创建线程池
        List<String> userIds = new ArrayList<>(userReviews.keySet()); // 获取所有用户的ID
        // 遍历所有用户，计算每个用户的相似度
        for (int i = 0; i < userIds.size(); i++) {
            String userId1 = userIds.get(i);
            executor.submit(() -> { // 使用Lambda表达式创建任务
                List<UserSimilarity> similarities = new ArrayList<>();
                for (String userId2 : userIds) {
                    if (!userId1.equals(userId2)) {
                        double jaccardIndex = computeJaccardIndex(userReviews.get(userId1), userReviews.get(userId2));
                        similarities.add(new UserSimilarity(userId2, jaccardIndex));
                    }
                }
                userSimilarities.put(userId1, similarities);
            });
        }
        executor.shutdown();    // 等待所有任务完成
        // 等待所有任务完成或超时
        try {
            if (!executor.awaitTermination(1, TimeUnit.MINUTES)) {
                executor.shutdownNow();
            }
        } catch (InterruptedException e) {
            executor.shutdownNow();
            Thread.currentThread().interrupt();
        }
        return userSimilarities;
    }
    /* 计算两个集合的Jaccard指数 */
    private static double computeJaccardIndex(Set<String> set1, Set<String> set2) {
        Set<String> intersection = new HashSet<>(set1);
        intersection.retainAll(set2);   // 求交集
        Set<String> union = new HashSet<>(set1);
        union.addAll(set2);             // 求并集
        return (double) intersection.size() / union.size(); // 利用公式计算Jaccard指数
    }
    /* 使用List内置排序API对每个用户的相似度列表进行排序，并选择前10个 */
    private static void sortAndSelectTopUsers(Map<String, List<UserSimilarity>> userSimilarities) {
        for (List<UserSimilarity> similarities : userSimilarities.values()) {
            similarities.sort(Comparator.comparingDouble(UserSimilarity::getSimilarity).reversed());
            if (similarities.size() > 10) { // 如果相似度列表的长度超过10，则删除后面的元素
                similarities.subList(10, similarities.size()).clear();
            }
        }
    }
    /* 将结果写入输出文件 */
    private static void writeResultsToFile(Map<String, List<UserSimilarity>> userSimilarities, String filePath) throws IOException {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(filePath))) {
            List<String> sortedUserIds = new ArrayList<>(userSimilarities.keySet());
            Collections.sort(sortedUserIds);    // 按userID排序
            // 将每行结果（11列）写入文件
            for (String userId : sortedUserIds) {
                StringBuilder sb = new StringBuilder(userId);
                for (UserSimilarity similarity : userSimilarities.get(userId)) {
                    sb.append(";").append(similarity.getUserId());
                }
                bw.write(sb.toString());
                bw.newLine();
            }
        }
    }
    /* 定义一个内部类，用于存储用户间相似度 */
    static class UserSimilarity {
        private final String userId;    // 用户ID
        private final double similarity;// 相似度
        // 构造函数
        public UserSimilarity(String userId, double similarity) {
            this.userId = userId;
            this.similarity = similarity;
        }
        // getter方法
        public String getUserId() {
            return userId;
        }
        public double getSimilarity() {
            return similarity;
        }
    }
}

