# minimake
练习用

2025.3.19更新：已实现了图，拓扑排序。

2025.3.20更新：实现时间戳检查，完成阶段3。

补充说明：

经过一些测试，./minimake <target> 命令可以实现简单依赖的文件编译，复杂依赖的还没试过，

并且能识别出循环依赖及时退出程序，并且根据时间戳来判断是否跳过某文件的编译。

其中1.c 2.c 3.c为测试c文件，其他.c文件才是源代码
