## QueDemap用户指南

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

### 常用操作指令

#### 管理员权限操作指令

1. ls_user
   查看当前有效用户
2. del_member
   删除用户
3. add_city
   添加城市，连续添加，输入end后结束
4. del_city
   删除城市
5. add_path
   手工添加城市路线，添加前请先添加城市
6. add_path_auto
   机器自动推荐生成城市路线
7. del_path
   删除城市路线
8. 其他插件操作

#### 用户权限操作指令

1. login
   登录账户
   
2. regist
   注册用户
   
   [^注册用户]: permission==2即拥有管理员权限，permission==1即拥有用户权限，permission==0或其他即为游客权限
   
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

更多信息请浏览本人的[博客](https://grimoire.cn/project/qdmap.html)或者[项目文档](https://qd.grimoire.cn/)了解
