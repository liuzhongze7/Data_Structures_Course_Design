**在fork或者需要参考代码之前，欢迎大家star和follow，谢谢！**
## 需求分析报告
#### 一、课题内容分析
* 设计内容：设计一个**大学校园导游程序，为来访的客人提供各种信息查询服务。
* 具体功能有：
 * (1)设计**大学的校园平面图，以图中顶点表示校内各景点，存放景点名称、代号、简介等信息；以边表示路径，存放路径长度等相关信息。
 
 * (2)为来访客人提供图中任意景点相关信息的查询。
 
 * (3)为来访客人提供图中任意景点的问路查询，即查询任意两相景点之间的一条最短的简单路径。
 
 * (4)提供图中任意景点问路查询，即求任意两个景点之间的所有路径。
 
 * (5)提供校园图中多个景点的最佳访问路线查询，即求途经这多个景点的最佳路径。
 
#### 二、设计思路
* 校园导游咨询系统模型是由景点和景点之间的路径组成的，所以可以用图的数据结构来实现。用图的结点代表景点，用图的边代表景点之间的路径。首先设计一个图类，结点值代表景点信息，边的权值代表景点间的距离。结点值及边的权值使用文件存储，通过读取文件来获取景点信息和景点之间的距离。计算任意两景点之间的最短路径可以使用Floyd算法实现，使用深度优先遍历算法来实现两景点之间的所有路径。最后用switch选择语句来执行不同编号的功能。

#### 三、系统模块划分
![Image Text](https://raw.github.com/wangyufei1006/Java-Design-patterns/master/Image/11.png)
#### 四、需求分析
##### 3.1 所需知识点
 * (1) 图的各种遍历算法
 * (2) 单源最短路径(Dijkstra算法)
 * (3) 所有顶点对的最短路径(Floyd算法)
 * (4) 图的基本存储结构(邻接矩阵)
 * (5) 文件的读取存储操作
 * (6) 界面交互
 
##### 3.2 数据结构
 * 本课题用到的数据结构是图的数据结构，其中用到的是图的邻接矩阵存储结构。
 
```c
typedef struct {                             /*存放景点信息的结构体*/
	int num;                                      /*景点代号*/
	char name[20];                                /*景点名称*/
	char intro[200];                              /*景点简介*/
}vertextype;

typedef int edgtype;                            /*权值类型*/
typedef struct {                                /*校园景点图结构体*/
	vertextype vexs[M];                           /*顶点信息域*/
	edgtype edge[M][M];                           /*邻接矩阵*/
	int vexNum, edgNum;                           /*图中顶点数和边数*/
}mgraphtype;
```

##### 3.3 基本算法实现
```c
int menu();                                /*主菜单*/
void Create_Map(mgraphtype *g);            /*从文件读取信息建立图*/
void Print_Map();                          /*显示校园景点地图*/
int Judge_Input(int num);                   /*判断输入的编号是否合理*/
void Search_Location(mgraphtype *g);       /*景点信息查询*/
void ShortPath(mgraphtype *g);             /*求景点间最短路径*/
void Floyd_Print(mgraphtype *g, int sNum, int eNum);/*递归打印两点间最短路径*/
void Shortpath_Print(mgraphtype *g);    /*输出并打印两点间的最短路径*/
void Dfs_Print(mgraphtype *g, int sNum, int eNum);/*深度优先遍历查询两景点间所有路径*/
void Allpath_Print(mgraphtype *g);    /*查询两顶点间的所有路径并打印*/
void BestPath(mgraphtype *g);        /*多顶点间求最佳路径*/
void System_Exit(int *q);            /*退出系统*/
```
##### 3.4 系统开发平台要求
* 基于 Visual Studio 2017的C语言进行系统开发。

##### 3.5 参考书籍
* [1] 李云清，杨庆红.数据结构（C语言版）.北京：人民邮电出版社，2014.
* [2] 严蔚敏,吴伟民.数据结构（C语言版）.北京：清华大学出版.1997.
* [3] 周海英，马巧梅，靳雁霞.数据结构与算法设计.北京：国防工业出版社，2009.

#### 五、项目附加功能
* 1. 登录系统，保障校园导游咨询系统的安全运行。
* 2. 公告栏，使游客及时了解学校动态，便于游客的游览。
* 3. 管理员系统，及时发布公告信息和对景点的有效管理。
