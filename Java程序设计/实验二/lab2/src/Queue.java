/**
编写一个队列类Queue，用来存储float型数据，队列中的数据是先进先出的。
 具体要求如下：成员变量float [] elements用来存储float型数据；
 成员变量int size用来表示存储的float型数据的个数；
 构造方法Queue在初始化队列的时候，设置队列的容量为12；
 方法enqueue(float v)用来往队列中添加一个float型数据；
 方法dequeue()用从队列中删除并返回一个float型数据；
 方法getSize()用来返回队列的大小。
 */
public class Queue {
    private float[] elements; // 存储float型数据
    private int size = 0; // 当前存储的float型数据的个数
    private int capacity = 12; // 队列的容量
    public Queue() { // 初始化队列
        elements = new float[capacity];
    }
    public void enqueue(float v) { // 往队列中添加一个float型数据
        if (size < capacity) {
            elements[size++] = v;
        }
    }
    public float dequeue() { // 从队列中删除并返回一个float型数据
        if (size > 0) {
            float v = elements[0];
            // 将队列中的元素往前移动一个位置
            for (int i = 0; i < size - 1; i++) {
                elements[i] = elements[i + 1];
            }
            size--;
            return v;
        }
        return -1;
    }
    public int getSize() { // 返回队列的大小
        return size;
    }

    public static void main(String[] args) {
        Queue queue = new Queue();
        queue.enqueue(1);
        queue.enqueue(2);
        queue.enqueue(3);
        System.out.println("插入3个元素后，队列的大小为：");
        System.out.println(queue.getSize()); // 输出队列的大小
        System.out.println(queue.dequeue());
        System.out.println(queue.dequeue());
        System.out.println(queue.dequeue());
        System.out.println("删除3个元素后，队列的大小为：");
        System.out.println(queue.getSize()); // 输出队列的大小
        System.out.println("队列为空时，删除元素的返回值为：");
        System.out.println(queue.dequeue());
    }
}
