import numpy as np

upper_bound, size = 1e7, int(1e6) # 随机数的最大值为1e7，随机数个数为1e6

for index in range(10):
    # 生成一组随机数样本，样本类型均为整型，范围为1~1e8
    arr_X = np.random.randint(1, upper_bound, size)
    arr_Y = np.random.randint(1, upper_bound, size)
    # 写入文件中
    with open(f'10groupsOfSample/samples{index+1}.txt', 'w') as f:
        for i in range(size):
            f.write(str(arr_X[i])+' '+str(arr_Y[i])+'\n')