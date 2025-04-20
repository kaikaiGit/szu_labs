/*
思路：使用最小堆来解决问题，首先将数组中的前5个元素放入最小堆中，然后遍历数组中的元素，
如果元素大于堆顶元素，则将堆顶元素出堆，将该元素入堆，最后将堆中的元素出堆即可得到最大的5个数。
*/
import java.util.Arrays;
import java.util.PriorityQueue;

public class demo4 {
    public static void main(String[] args) {
        int size = 100; //二维数组大小
        double[][] arr = new double[size][size];

        //对数组中的元素进行随机赋值为0-1之间的浮点数
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                arr[i][j] = Math.random();
            }
        }

        //记录程序开始时间
        long startTime = System.nanoTime();

        //找到该数组中最大的5个数并从大到小输出
        //1.使用一个大小为5的最小堆来存储前5大的数
        PriorityQueue<Double> minHeap = new PriorityQueue<>(5); // 默认是最小堆
        //2.遍历二维数组
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (minHeap.size() < 5) {// 如果堆的大小小于5，直接添加
                    minHeap.add(arr[i][j]);
                } else if (arr[i][j] > minHeap.peek()) {
                    // 如果堆已经有5个元素，并且当前元素大于堆顶，替换堆顶
                    minHeap.poll(); // 移除最小元素
                    minHeap.add(arr[i][j]); // 添加当前元素
                }
            }
        }
        // 3.将堆中的元素按从大到小的顺序输出
        System.out.println("The top 5 largest numbers are:");
        Double[] top5 = minHeap.toArray(new Double[0]); // 转换成数组
        Arrays.sort(top5); // 从小到大排序
        for (int i = top5.length - 1; i >= 0; i--) {
            System.out.println(top5[i]);
        }

        //记录程序结束时间
        long endTime = System.nanoTime();

        //计算并输出程序耗时
        long duration = endTime - startTime;
        System.out.println("Time taken: " + duration + " nanoseconds");
    }
}
