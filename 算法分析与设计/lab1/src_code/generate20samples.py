import numpy as np

upper_bound, size = 1e8, int(1e6) # 随机数的最大值为1e8，随机数个数为1e6

for index in range(20):
    # 生成一组随机数样本
    arr = np.random.randint(1, upper_bound, size)
    # 写入文件中
    with open(f'20pieces_of_samples/sample_{index+1}.txt', 'w') as f:
        for num in arr:
            f.write(str(num)+'\n')