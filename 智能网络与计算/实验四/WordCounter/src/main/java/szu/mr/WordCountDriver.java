package szu.mr;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import java.net.URI;
import java.util.*;

public class WordCountDriver {
    public static void main(String[] args) throws Exception {
        // 创建配置对象
        Configuration conf = new Configuration();
        // 设置数据节点主机名属性
        conf.set("dfs.client.use.datanode.hostname", "true");

        // 获取作业实例
        Job job = Job.getInstance(conf);
        // 设置作业启动类
        job.setJarByClass(WordCountDriver.class);

        // 设置Mapper类
        job.setMapperClass(WordCountMapper.class);
        // 设置map任务输出键类型
        job.setMapOutputKeyClass(Text.class);
        // 设置map任务输出值类型
        job.setMapOutputValueClass(IntWritable.class);

        // 设置Reducer类
        job.setReducerClass(WordCountReducer.class);
        // 设置reduce任务输出键类型
        job.setOutputKeyClass(Text.class);
        // 设置reduce任务输出值类型
        job.setOutputValueClass(IntWritable.class);

        // 选择小文件还是大文件：1.小文件 2.大文件
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入模式：1.小文件 2.大文件");
        int mode = sc.nextInt();
        String fileName = "test1.txt";
        if (mode == 1){
            // 设置分区数量（reduce任务的数量、结果文件的数量,默认为 1）
            job.setNumReduceTasks(1);
        } else if (mode == 2){
            // 设置分区数量（reduce任务的数量、结果文件的数量,默认为 1）
            job.setNumReduceTasks(6);
            fileName = "test2.txt";
        }

        // 定义文件夹路径
        String dicRoot = "C:\\Users\\24312\\Desktop\\智能网络\\实验四\\WordCounter";
        // 创建输入目录
        Path inputPath = new Path(dicRoot + "/data/" + fileName);
        // 创建输出目录
        Path outputPath = new Path(dicRoot + "/result" + mode);

        // 获取文件系统
        FileSystem fs = FileSystem.getLocal(conf);
        // 删除输出目录（第二个参数设置是否递归）
        fs.delete(outputPath, true);

        // 给作业添加输入目录（允许多个）
        FileInputFormat.addInputPath(job, inputPath);
        // 给作业设置输出目录（只能一个）
        FileOutputFormat.setOutputPath(job, outputPath);

        // 等待作业完成
        job.waitForCompletion(true);

        /// 输出统计结果
        System.out.println("======统计结果======");
        FileStatus[] fileStatuses = fs.listStatus(outputPath);

        Map<String, Integer> wordCountMap = new HashMap<>();// 用于存储统计结果
        // 读取结果文件
        for (int i = 0; i < fileStatuses.length; i++) {
            if (fileStatuses[i].isFile()) { // 确保是文件
                FSDataInputStream in = fs.open(fileStatuses[i].getPath());
                Scanner scanner = new Scanner(in);
                while (scanner.hasNextLine()) {
                    String line = scanner.nextLine();
                    String[] parts = line.split("\t");
                    if (parts.length == 2) {
                        String word = parts[0];
                        int count = Integer.parseInt(parts[1]);
                        wordCountMap.put(word, count);
                    }
                }
                scanner.close();
                in.close();
            }
        }

        // 对结果排序
        List<Map.Entry<String, Integer>> sortedEntries = new ArrayList<>(wordCountMap.entrySet());
        sortedEntries.sort((o1, o2) -> o2.getValue().compareTo(o1.getValue())); // 降序排序

        // 将排序结果写回文件
        Path sortedResultPath = new Path(outputPath + "/Sta_" + fileName);
        FSDataOutputStream out = fs.create(sortedResultPath);

        for (Map.Entry<String, Integer> entry : sortedEntries) {
            out.writeBytes(entry.getKey() + "\t" + entry.getValue() + "\n");
        }
        out.close();

        System.out.println("排序结果写入：" + sortedResultPath);
    }
}
