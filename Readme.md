# 从Mediasoup缩略出来的一份nodejs与C++程序配合运行的最小demo

nodejs以子程序的方式创建worker程序，实现nodejs与worker程序之间的互相通讯。

1. `npm run worker:build`命令编译mediasoup-worker C++程序
2. `npm run typescript:build`命令编译typescript代码
3. `npm run test`命令测试

note: 更具体的可以参考mediasoup完整项目。
wrap因网络问题下载失败时，可尝试手动下载每个wrap链接，并把下载文件放到worker/subprohects/packagecache文件夹下。