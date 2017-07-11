# 788A. Functions again - dp
## 链接
[788A. Functions again](http://codeforces.com/problemset/problem/788/A)
## 题解
1. 动态规划  
   设d(i,j)表示区间[l, i]的函数的最大值，且当l为偶数时，j=0；当l为奇数时，j=1。状态转移方程为  
$$
d(i, 0) =
       \begin{cases}
       max\{d(i-1, 0) + b[i], b[i]\}, & \text{if i is even} \\
       d(i-1, 0) - b[i], & \text{if i is odd} 
       \end{cases}
       \\
       d(i, 1) =
       \begin{cases}
       d(i-1, 1) - b[i], & \text{if i is even} \\
       max\{d(i-1, 1) + b[i], b[i]\}, & \text{if i is odd}
       \end{cases}
$$
2. 时间复杂度  
   状态数*O(n)*，决策数*O(1)*，状态转移时间*O(1)*，时间复杂度*O(n)=O(10$^5$)*。  
3. 空间复杂度  
   数组开销*O(n)*，总开销*O(n)=O(10$^5$)*。
## 注意事项
1. 最大值的初始化  
   最大值应该初始化为b[0]，而不是0，否则将漏掉b[0]的情况。
