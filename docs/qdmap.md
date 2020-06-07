<!--
 * @Author: Mr.Sen
 * @LastEditTime: 2020-06-06 01:22:55
 * @Website: https://grimoire.cn
 * @Mr.Sen All rights reserved
--> 
## QueDemap用户指南

### 概述

本程序结合了客户端和管理端，通过管理员账号和用户账号来对用户的行为进行区分

#### 权限分类

在注册账号时，会要求输入权限等级

##### 等级表：

1. PERMISSION == 1 普通用户权限
2. PERMISSION == 2 管理员权限
3. PERMISSION == 0 游客权限

##### 三种权限的区别在于：

![普通用户权限](https://picstay.oss-cn-chengdu.aliyuncs.com/img/image-20200606103349933.png)

普通用户和管理员用户登录后，命令提示栏会显示用户名称，而游客用户则不会显示名称

![管理员权限](https://picstay.oss-cn-chengdu.aliyuncs.com/img/image-20200606103222593.png)

管理员用户登录后，命令提示栏变成黄色，表示拥有最高权限

![游客权限](https://picstay.oss-cn-chengdu.aliyuncs.com/img/image-20200606103247081.png)

普通用户实际权限和游客权限差不多，区别就在于是否显示名称

### 常用操作指令

#### 管理员权限操作指令

1. ls_user  查看当前有效用户

2. del_member   删除用户

3. add_city     添加城市，连续添加，输入end后结束

4. del_city     删除城市

5. add_path     手工添加城市路线，添加前请先添加城市

6. add_path_auto    机器自动推荐生成城市路线
7. del_path 删除城市路线
8. 其他插件操作

#### 用户权限操作指令

1. login
   登录账户

2. regist
   注册用户

3. ls_city
   查看城市地图

4. ls_path
   查看所有城市路线

5. path
   智能规划最近路线

6. logout
   登出账户

7. help
   查看帮助

8. --help
   一个彩蛋（彩虹帮助）


### 目录结构树

```
D:.
│  list.txt
│  main.cpp
│  main.exe
│  
├─.dist
├─.vscode
│      settings.json
│      
├─blocks
│      store.exe
│      
├─block_sourse
│      store.py
│      web.py
│      
├─dat
│      uer_infomation
│      
└─headers
        about.h
        city.h
        login.h
        path.h
        store.h
```
### 算法相关

本程序所声明的智能算法其实并不是真正的智能算法，是通过 Dijkstra算法 实现的简单的最短路径计算

路径的智能生成也是利用暴力遍历的方式生成的临时路径，不建议使用

### 界面相关

软甲使用了TUI界面，相比图形界面，TUI界面更加节省资源

使用命令行操作，可以一步直达想要的功能，相比通过选择的方式，效率更高

### 插件相关

通过插件，程序可以实现多客户端互联，举个例子：

管理员甲在A设备上添加了n个数据，如果管理员甲将数据上传发布，管理员乙便可以选择下载管理员甲的数据
实现多个设备之间的数据同步，发布的数据将会以时间分开存储

但是这个功能也有不足的地方，比如：
1. 不能实现像git一样的数据管理，现在同步别人的数据时会丢失自己的数据

2. 因为数据只是用上传时间加以区分，因此不能显示文件上传者，无法避免用户恶意上传文件

#### 插件功能实现原理

1. web.exe 通过webdav技术，同步指定文件夹下的所有文件，实现文件的备份与发布

2. store.exe 同样是通过webdav技术，同步云盘下的插件，实现了在线插件功能

插件的开发时使用了Python，但是插件功能不仅仅支持python，一切能被打包为可执行文件的程序都能作为插件的编写语言

所有插件的源码都放在block_source文件夹下了

### 插件开发手册

暂无内容


更多信息请浏览本人的博客了解
[https://grimoire.cn/project/qdmap.html](https://grimoire.cn/project/qdmap.html)