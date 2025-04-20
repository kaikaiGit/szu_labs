/**
 * 编写一个秒表类StopWatch，成员变量和方法自定。
 * 编写一个支持快速排序算法的类QuickSort，成员变量和方法自定。
 * 对100000, 1000000, …等不同长度的数组中的元素（元素的值随机给定）进行排序，并用秒表对象来记录排序所用的时间。
 */
class QuickSort {
    // 快速排序
    public static void quickSort(int []arr, int low, int high) {
        if (low < high) {
            int pivot = partition(arr, low, high); // 获取枢轴的位置
            quickSort(arr, low, pivot - 1); // 对左边的子数组进行快速排序
            quickSort(arr, pivot + 1, high); // 对右边的子数组进行快速排序
        }
    }
    // 划分
    private static int partition(int[] arr, int low, int high) {
        int pivot = arr[low]; // 定义枢轴
        // 从数组的两端交替向中间扫描
        while (low < high) {
            while (low < high && arr[high] >= pivot) {
                high--;
            }
            arr[low] = arr[high];
            while (low < high && arr[low] <= pivot) {
                low++;
            }
            arr[high] = arr[low];
        }
        arr[low] = pivot; // 枢轴元素存放到最终位置
        return low;
    }
}

public class StopWatch {
    private long startTime; // 开始时间
    private long endTime; // 结束时间
    private String unit = "毫秒"; // 时间单位
    public StopWatch() { // 初始化秒表
        startTime = System.currentTimeMillis(); // 获取系统当前时间，单位为毫秒
    }
    public void start() { // 开始计时
        startTime = System.currentTimeMillis();
    }
    public void stop() { // 结束计时
        endTime = System.currentTimeMillis();
    }
    public long getElapsedTime() { // 获取经过的时间
        return endTime - startTime;
    }
    public static void main(String[] args) {
        StopWatch stopWatch = new StopWatch();
        // 随机生成100000个元素的数组
        int[] arr = new int[10000000];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = (int) (Math.random() * 10000000);
        }
        stopWatch.start();
        // 使用自定义的QuickSort类进行排序
        QuickSort.quickSort(arr, 0, arr.length - 1);
        stopWatch.stop();
        System.out.println("排序10000000个元素所用的时间为：" + stopWatch.getElapsedTime() + "毫秒");
    }
}