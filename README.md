# Kalah-Game
對於經典遊戲”撿金豆”定義狀態空間、狀態轉移函式、目標狀態，最後實作並且提供實力不同的AI模型和玩家進行對戰(也可以看AI對決)。

Details


## How to use?
1. Download and execute "第八組_演算法效能評比_2021.jar"
2. Choose your problem: "sort" or "matrix multiplication"
3. Choose the way you generate test data, there are 4 ways of "I/O Read", "Example", "Random", ".txt Read" to generate the data you want.
4. Don't forget to click "Generate Array/Matrix".
5. Choose the algorithm you want to use to solve the problem.
6. GoGo!

## Preview
<img src="README_IMG/Step2.png" width="30%"> <img src="README_IMG/Sort_EX.png" width="25%"> <img src="README_IMG/Mul_EX.png" width="25%">

## Research results
Since JAVA's recursive call is call by value, a divide-and-conquer algorithm such as 2D matrix multiplication like Strassen [O(n^2.807)] is actually better than Naïve [O(n^3)] is even slower (the n range is within the acceptable range for the system).

As for algorithms with the same time complexity, such as Insertion/Bubble/Selection Sort [O(n^2)], the speed under the influence of constants is Bubble << Insertion < Selection (random measurement, n>=10000).
