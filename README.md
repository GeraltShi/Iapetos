# WheelCreator Group DEMO

## Issac Game

Microelectronic Science and Engineering, Fudan University

- 施葹 15307130017
- 蔡俊哲 15307130076
- 王渝 15307130258

### Environment

cocos2dx 3.16

- Window 10 1803
  - Visual Studio 2017
- macOS Sierra 10.12
  - Xcode 9.2

### Main features realized

- Swap between rooms
- Complete Single level map and plot
- Multiple monsters
- Tear animation and Monster dead animation
- Complete close-loop boss logic
- Debug mode map and maze mode map
- Issac dead animation
- Object system on the ground
- BOMBS!

### Snapshots

- Windows

<p align="center">
<img src="./Img/capture1.png" width="444">

<img src="./Img/capture2.png" width="444">

<img src="./Img/capture3.png" width="444">
</p>

- macOS

<p align="center">
<img src="./Img/capture4.png" width="444">

<img src="./Img/capture5.png" width="444">

<img src="./Img/capture6.png" width="444">
</p>

## Reference

### MVC Framework

[cocos2d 里面如何实现 mvc](http://www.cnblogs.com/andyque/archive/2012/03/11/2390814.html)

- Scene 中负责界面的加载，界面的更新，事件注册
- Controller 中负责控制，监听事件
- Model 负责 Controller 与 Scene 之间传递信息

> Controller 负责初始化 Model 和 View

    View负责显示Model
    View负责接收用户touch事件，然后传递给controller来处理。
    Controller实现view的代理，同时可以操作Model。
    model则执行一些游戏逻辑处理并通知view它的状态改变。
    View根据model的当前状态来更新它里面的所有对象，比如精灵。

- Controller 持有 Service 引用，将服务性质的代码放在 Service 类中，例如访问数据库、管理地图。

- TODO：最后应使用 IOC/DI 管理所有 Scene、Controller、Service。目前阶段直接例化也可以。

### Texture & SpriteFrame

[cocos2d 随手记(11)——纹理贴图集为什么必须满足“2 的 n 次方规则”*朝寒雨晚来风*新浪博客](http://blog.sina.com.cn/s/blog_623ed7840100yz1d.html)

[cocos2dx Texture、SpriteFrame、Sprite 的区别 - CSDN 博客](http://blog.csdn.net/hanbingfengying/article/details/37653675)

[Cocos2d-x 学习笔记（九）纹理 CCTexture2D 和精灵 CCSprite - 移动开发其他类 - 红黑联盟](https://www.2cto.com/kf/201408/328980.html)

### Sprite inheritance

[关于在 cocos2dx 中继承 Sprite 的分析与技巧 - CSDN 博客](http://blog.csdn.net/while0/article/details/25615685)

### Frame animation

[cocos2dx 3.x(实现帧动画(人物动画,跑马灯效果)的几种方法) - 罗任德 - 博客园](https://www.cnblogs.com/luorende/p/5998893.html)

### Related resources

素材网站（第三方提取） https://tieba.baidu.com/p/3628520349?red_tag=2076293033

各版本资源合集 [【导航】以撒各版本资源、攻略、工具、MOD 等总目录【以撒的结合吧】\_百度贴吧](https://tieba.baidu.com/p/5049486526)

Rebirth 版本资源合集 [【次级目录】重生（Rebirth）相关导航【以撒的结合吧】\_百度贴吧](https://tieba.baidu.com/p/4974178821?red_tag=2114258115)

解包教程 [【图片】【重生 Mod 制作】Mod has appeared in the basement！【以撒的结合吧】\_百度贴吧](https://tieba.baidu.com/p/3535767744?red_tag=2122773341) 解包工具 [Rebirth Mod.zip\_免费高速下载|百度网盘-分享无限制](https://pan.baidu.com/s/1pJ6xlXp) 地图提取工具 [【图片】【神器】【MOD 制作工具】地下室改造器 Basement Renovator+小教程【以撒的结合吧】\_百度贴吧](https://tieba.baidu.com/p/3561739396?red_tag=2936181129)
