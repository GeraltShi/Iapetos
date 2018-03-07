# WheelCreator
## 仿制 Issac
### 复旦大学微电子科学与工程系

## TODO

### Step0: 数据结构封装
character class
    生命值
    道具系统（物品栏）
    其他属性
    贴图（不同走路方向贴图不同——需要每帧刷新：eg：头的方向会转）
monster class
    类型／属性
    生命值
    贴图
room property
    room有哪些对象？
    贴图
    边界？
    难度
    ……

### Step1: 单个房间
#### character 相关
##### 多个bullet
bullet 的生命周期：内存管理
bullet 和 monster 的碰撞触发效果

###### character 状态管理
受伤：生命值变化
道具：攻击，攻速……变化

#### monster 相关
monster的属性和生成

#### 房间空间逻辑层 — 需要抓包
边界
陷阱，可破坏物品（可能内含道具）
限制
门
贴图

#### 物品
monster 销毁后生成；随机性
物品效果

### Step2: 多个房间
多个房间随机组成一张地图
地图房间进入顺序管理
成就系统？
房间内存管理：不是完全销毁

### Step3: 多个character
不同character的property

### Step4: 多个地图
难度管理：通过一张地图后难度升级

## 相关教程及资源链接
### 贴图纹理相关：Texture、SpriteFrame
[cocos2d随手记(11)——纹理贴图集为什么必须满足“2的n次方规则”_朝寒雨晚来风_新浪博客](http://blog.sina.com.cn/s/blog_623ed7840100yz1d.html)

[cocos2dx Texture、SpriteFrame、Sprite的区别 - CSDN博客](http://blog.csdn.net/hanbingfengying/article/details/37653675)

[Cocos2d-x学习笔记（九）纹理CCTexture2D和精灵CCSprite - 移动开发其他类 - 红黑联盟](https://www.2cto.com/kf/201408/328980.html)

### 库Sprite的继承
[关于在cocos2dx中继承Sprite的分析与技巧 - CSDN博客](http://blog.csdn.net/while0/article/details/25615685)

### 相关资源
素材网站（第三方提取）
https://tieba.baidu.com/p/3628520349?red_tag=2076293033

各版本资源合集
[【导航】以撒各版本资源、攻略、工具、MOD等总目录【以撒的结合吧】_百度贴吧](https://tieba.baidu.com/p/5049486526)

Rebirth版本资源合集
[【次级目录】重生（Rebirth）相关导航【以撒的结合吧】_百度贴吧](https://tieba.baidu.com/p/4974178821?red_tag=2114258115)

解包教程
[【图片】【重生Mod制作】Mod has appeared in the basement！【以撒的结合吧】_百度贴吧](https://tieba.baidu.com/p/3535767744?red_tag=2122773341)
解包工具
[Rebirth Mod.zip_免费高速下载|百度网盘-分享无限制](https://pan.baidu.com/s/1pJ6xlXp)
地图提取工具
[【图片】【神器】【MOD制作工具】地下室改造器Basement Renovator+小教程【以撒的结合吧】_百度贴吧](https://tieba.baidu.com/p/3561739396?red_tag=2936181129)
