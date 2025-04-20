/*
编写Java应用程序，实现稀疏矩阵的加法和乘法运算，
其中稀疏矩阵是指矩阵中的大部分元素的值为0。
用户在命令行输入矩阵时矩阵的大小可能有错，因此需要使用异常处理。
 */
package demo6;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class SparseMatrix {
    private int rows; // 矩阵的行数
    private int cols; // 矩阵的列数
    private Map<String, Integer> elements; // 用于存储非零元素
    // 构造函数
    public SparseMatrix(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        this.elements = new HashMap<>();
    }
    // 设置矩阵元素
    public void setElement(int row, int col, int value) {
        if (value != 0) {
            elements.put(row + "," + col, value);
        }
    }
    // 获取矩阵元素
    public int getElement(int row, int col) {
        return elements.getOrDefault(row + "," + col, 0);
    }
    // 矩阵相加
    public SparseMatrix add(SparseMatrix other) throws IllegalArgumentException {
        if (this.rows != other.rows || this.cols != other.cols) {
            throw new IllegalArgumentException("矩阵大小不一致，无法进行加法运算。");
        }
        SparseMatrix result = new SparseMatrix(this.rows, this.cols); // 创建结果矩阵
        // 添加当前矩阵的非零元素
        for (Map.Entry<String, Integer> entry : this.elements.entrySet()) {
            String key = entry.getKey();
            result.setElement(
                    Integer.parseInt(key.split(",")[0]),
                    Integer.parseInt(key.split(",")[1]),
                    entry.getValue()
            );
        }
        // 添加other矩阵的非零元素
        for (Map.Entry<String, Integer> entry : other.elements.entrySet()) {
            String key = entry.getKey();
            int row = Integer.parseInt(key.split(",")[0]);
            int col = Integer.parseInt(key.split(",")[1]);
            result.setElement(row, col, result.getElement(row, col) + entry.getValue());
        }
        return result;
    }
    // 矩阵相乘
    public SparseMatrix multiply(SparseMatrix other) throws IllegalArgumentException {
        if (this.cols != other.rows) {
            throw new IllegalArgumentException("矩阵维度不匹配，无法进行乘法运算。");
        }
        SparseMatrix result = new SparseMatrix(this.rows, other.cols); // 创建结果矩阵
        for (Map.Entry<String, Integer> entry : this.elements.entrySet()) {
            int row = Integer.parseInt(entry.getKey().split(",")[0]);
            int col = Integer.parseInt(entry.getKey().split(",")[1]);
            int value = entry.getValue();
            for (int k = 0; k < other.cols; k++) {
                int otherValue = other.getElement(col, k);
                if (otherValue != 0) {
                    result.setElement(row, k, result.getElement(row, k) + value * otherValue);
                }
            }
        }
        return result;
    }
    // 打印矩阵
    public void printMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(getElement(i, j) + " ");
            }
            System.out.println();
        }
    }
}
// 主程序
public class SparseMatrixDemo {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        try {
            // 创建矩阵A
            System.out.print("请输入矩阵A的行数和列数（空格分隔）：");
            int rowsA = scanner.nextInt(); int colsA = scanner.nextInt();
            SparseMatrix matrixA = new SparseMatrix(rowsA, colsA);
            System.out.println("请输入矩阵A的非零元素（格式：行 列 值），输入-1结束：");
            while (true) { // 循环读取非零元素
                int row = scanner.nextInt();
                if (row == -1) break;
                int col = scanner.nextInt();
                int value = scanner.nextInt();
                matrixA.setElement(row, col, value);
            }
            // 创建矩阵B
            System.out.print("请输入矩阵B的行数和列数（空格分隔）：");
            int rowsB = scanner.nextInt(); int colsB = scanner.nextInt();
            SparseMatrix matrixB = new SparseMatrix(rowsB, colsB);
            System.out.println("请输入矩阵B的非零元素（格式：行 列 值），输入-1结束：");
            while (true) { // 循环读取非零元素
                int row = scanner.nextInt();
                if (row == -1) break;
                int col = scanner.nextInt();
                int value = scanner.nextInt();
                matrixB.setElement(row, col, value);
            }
            // 计算并输出矩阵相加的结果
            System.out.println("矩阵A+B结果：");
            try {
                SparseMatrix sumMatrix = matrixA.add(matrixB); // 计算矩阵相加
                sumMatrix.printMatrix(); // 输出结果
            } catch (IllegalArgumentException e) {
                System.out.println("加法错误: " + e.getMessage());
            }
            // 计算并输出矩阵相乘的结果
            System.out.println("矩阵A*B结果：");
            try {
                SparseMatrix productMatrix = matrixA.multiply(matrixB); // 计算矩阵相乘
                productMatrix.printMatrix(); // 输出结果
            } catch (IllegalArgumentException e) {
                System.out.println("乘法错误: " + e.getMessage());
            }
        } catch (Exception e) {
            System.out.println("输入错误: " + e.getMessage());
        } finally {
            scanner.close();
        }
    }
}

