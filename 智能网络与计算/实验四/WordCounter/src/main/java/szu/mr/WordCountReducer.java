package szu.mr;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

public class WordCountReducer extends Reducer<Text,IntWritable,Text,IntWritable> {
    @Override
    protected void reduce(Text key, Iterable<IntWritable> values, Context context)
            throws IOException, InterruptedException {
        // 定义输出键出现次数
        int count = 0;
        // 遍历输出值迭代对象，统计其出现次数
        for (IntWritable value : values) {
            count = count + value.get();
        }
        // 生成键值对输出
        context.write(key, new IntWritable(count));
    }
}
