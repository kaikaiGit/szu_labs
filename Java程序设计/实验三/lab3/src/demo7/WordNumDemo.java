package demo7;
import java.util.*;
import java.util.stream.Collectors;

public class WordNumDemo {
    public static void main(String[] args) {
        // 将网页内容复制到content字符串中
        String content =  "About\n" +
                "Shenzhen University (SZU) is committed to excellence in teaching, research and social service. Sticking to the motto of “self-reliance, self-discipline, self-improvement”, the University is dedicated to serving the Shenzhen Special Economic Zone (SEZ), demonstrating China’s reform and opening up and pioneering change in higher education.                                                                                                                                                  \n" +
                "SZU, which is based in Shenzhen, China’s first Special Economic Zone and a key city in the Guangdong-Hong Kong-Macau Greater Bay Area, is distinctively known as an Experimental University in higher education with its reforms in the sector acknowledged in Mainland China.\n" +
                "Established in 1983, SZU received support from top Chinese universities including Peking University, Tsinghua University and Renmin University of China in the founding of new schools. In the past decades, the University has undergone rapid growth and has become a comprehensive university with complete disciplines, top-ranked academic and research institutes and awe-inspiring faculty. SZU faculty members are engaged with teaching and research for the betterment of society. They are devoted to seeking solutions to pressing global challenges and promoting innovation.\n" +
                "SZU offers a wide array of undergraduate and graduate programs and provides students with an interdisciplinary and inclusive multicultural learning environment. Students in SZU enjoy the plenty resources and facilities of both the SEZ and the University, pursue academic excellence and discover new interests and opportunities in a fast-changing era.\n" +
                "SZU is an integral part of the SEZ, a thriving technology and innovation hub. With two campuses in Yuehai and Lihu, the University vigorously conducts leading researches in various fields and collaborates with high-tech enterprises in the community for technology transfer. SZU strives to provide a high-quality and effective education and develop in each SZU member the ability and passion to innovate and contribute to social progress and development, and encourages talented young people to start entrepreneurship in SZU. Our alumni including Tencent have founded dozens of innovative companies with significant influence.\n" +
                "SZU is accelerating its pace toward internationalization, providing a variety of global learning opportunities. The University has established partnerships with numbers of overseas universities to offer exceptional exchange programs, joint degree programs, research collaborations, and a variety of other forms of collaborations with international partners. Students from all over the world are welcomed in SZU. In the city noted for its urban vitality and natural beauty, students can explore the most attractive parts of China, pursue their passion and develop their interests, perspectives and abilities.\n";
        // 1. 清理文本内容，拆分为单词列表（忽略大小写）
        String[] words = content.toLowerCase().split("[^a-z]+");
        // 2. 使用 Map 统计每个单词出现的次数
        Map<String, Integer> wordCountMap = new HashMap<>();
        for (String word : words) {
            if (!word.isBlank()) { // 跳过空字符串
                wordCountMap.put(word, wordCountMap.getOrDefault(word, 0) + 1);
            }
        }
        // 3. 将 Map 转换为按出现次数降序排列的列表
        List<Map.Entry<String, Integer>> sortedWordList = wordCountMap.entrySet()   // 将Map转换为Entry集合
                .stream()   // 使用流处理
                .sorted((e1, e2) -> e2.getValue().compareTo(e1.getValue())) // 按出现次数降序排序
                .limit(50)  // 只取前50个
                .collect(Collectors.toList());  // 转换为列表

        // 4. 输出出现次数最多的前50个单词，每行10个单词
        for (int i = 0; i < sortedWordList.size(); i++) {
            System.out.print(sortedWordList.get(i).getKey() + " ");
            if ((i + 1) % 10 == 0) System.out.println(); // 每10个单词换行
        }
    }
}
