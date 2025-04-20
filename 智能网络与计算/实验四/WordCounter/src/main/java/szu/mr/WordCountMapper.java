package szu.mr;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;
import java.io.IOException;
public class WordCountMapper extends Mapper<LongWritable,Text,Text, IntWritable>{
    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        // 获取行内容
        String line = value.toString();
        // 按空格拆分得到单词数组
        String[] words = line.split(" "); //regex正则表达式
        // 遍历单词数组，生成输出键值对
        for (String word : words) {
            // 过滤特殊字符、数字，只保留字母
            if (word.matches("[a-zA-Z]+"))
                context.write(new Text(word), new IntWritable(1));
        }

    }
}
