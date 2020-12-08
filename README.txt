User_Bsp存放底层配置程序
包含CAN、IO、LCD、Serial、Systick、Timer


User_Algorithm存放算法相关程序
包含
algorithm	（用户所需数学相关函数）
pid		（PID计算相关函数）
movebase	（舵轮底盘的运动学算法）


User_App存放用户自定义应用
包含
caster		（舵轮操控系统，负责遥控信息和舵轮机器人的交互）
esc		（车身稳定控制系统，即电机空置任务的配置）
pps		（编码器定位系统的配置即反馈信息）
remote		（遥控器的配置）
task		（任务逻辑）

基于v1.0.2修改
v1.0.3为测试用程序
基本与比赛上车程序相同

B为模式选择，E为遥控模式下模式选择

待添加速度柔化
待添加复位
待添加15s提示