## TCF 战斗框架学习笔记

### 1. 一些背景

我是一名想要转到 UE 游戏客户端的软件开发从业者, 从 23 年 11 月开始学习, 在经历了 B站 堪嘉诚的 UE 蓝图入门教程 和 UDemy 的 MultiPlayerShooter 项目之后, 我想要制作一个 APRG 类型的求职 Demo, 在学习了 Udemy 和 Youtube 上的一些开源课程, 我开始着手制作 Demo, 在这个过程中, 我发现不论是 Player 还是 Boss , 状态的变更和技能的释放, 在代码实现上, 使用我学习到的知识去制作, 不仅费时费力, 代码也十分混乱, 不利于拓展, 简单来说就是一坨大便.

基于上面的情况, 我试着寻找解决方法, 由此我接触到了 TCF (Tempest Combat Framework) 框架 , 和 UE 官方的 GAS (Game Ability System) 插件, 以及一些大牛的贴子, 让我意思到游戏框架的重要性, 因此, 我参考了 TCF 的源码和 UE 的源码, 搭建了我的 ARPG Demo 项目. 

下面, 我想以一名初学者的视角书写我从 TCF 框架中学习到的知识.

### 2. 核心内容

在了解到战斗框架时, 我接触的一共有两款, 分别是 ACF (Acent Combat Framework) 和 TCF, 在浏览了宣传视频和手册之后, 我最终选择了 TCF, 理由有两点:

- TCF 相较而言更为精简, 专注于战斗部分.
- TCF 的宣传视频更贴近我想要制作的 Demo.

#### 2.1 战斗组件

在我接触到的术语中, **组件化** 是最能形容我对 TCF 的印象的. 一场战斗中, 可以拆分成: 状态 (State), 能力 (Ability), 属性(Attribute), 运动 (Movement)等战斗因素, 每一个战斗因素由相应的组件进行管理: 

- 状态 (State):  `StateMangerComponent`

- 能力 (Ability): `AbilityComponent`, UE 官方也有提供 GAS 插件

- 属性(Attribute): `AttributeComponent`

- 运动 (Movement): 这个官方提供了 `CharacterMovementComponent` , 此处是引用作为案例.

同时, 战斗因素的生命周期也将由组件负责, 以 State 举例, `StateMangerComponent` 将负责 State 的构建(Construct), 执行(Perform), Tick 等.

> 作为一名初学者, 这引发的思维变更在于, 学会窥探 UE 的源码; 在项目中, 我遇到的一些棘手的 Bug 和 问题, 很多也通过浏览源码得到了解决.
>
> 我曾经接触过韦东山的嵌入式教程, 在此引用韦老师常说的一句话, 内容是: "如果我们不会学, 就去看 Linux 的源码, 参考其实现方式是最好的学习方式."

#### 2.2 战斗因素

组件负责了战斗因素的管理, 具体的执行流程由战斗因素本身负责, 此类内容的编写, 最为贴切的参考就是 `Actor` 类

以 状态 (State) 举例, 可以划分以下的核心函数:

1. `ConstructState`: 构建状态时, 执行必要工作, 对应 `Actor` 的构造函数.
2. `StartState` : 执行状态时的内容, 对应 `Actor` 的 `BeginPlay()`.
3. `TickState`: 状态中, 需要执行的内容, 对应 `Actor` 的 `Tick()`.
4. `EndState`: 状态结束, 需要执行的内容, 对应 `Actor` 的 `Destroy()`.

同理, 其他的构成因素也可以拆分成相似的四个阶段.

如此设计还有一个好处, 对于 C++ 开发和蓝图分工十分清晰.

不同阶段需要执行的逻辑, 可以交由设计师来编写, 也可以交由 C++ 开发来编写, 十分的灵活.

#### 2.4 FGameplayTag

Tag 的引入带来了许多的便利, 组件可以配合标签更好的实现管理, 同时, 能够应对更为复杂的战斗场景. 以能力 (Ability) 举例:

- `Ability.Hit.NormalHit`: 普通受击
- `Ability.Hit.BlockHit`: 格挡受击
- `Ability.Hit.EvadeHit`: 闪避受击

我们可以很方便的针对不同 Tag 的能力, 编写对应的代码逻辑.

#### 2.4 小结

以上是我从 TCF 中学习到的较为深刻的内容. TCF 本身十分的简单, 但是拓展性很高, 也方便 C++ 开发和蓝图设计师进行分工.

### 3. 一些想记录的细节

- `StateManagerComponent` 应当挂载到 Controller 中, 因为 State 决定了 Character 的行为, 而 Controller 控制 对应 Character 的行为. 

> 注: UE 中对于 Controller 的定义: **控制器（Controller）** 是一种可以控制Pawn（或Pawn的派生类，例如 `Character`），从而**控制其动作**的非实体Actor。Player 使用 `PlayerController` 控制Pawn，而 `AIController` 则对它们控制的Pawn实加人工智能效果。

- UI 的变化由 Controller 进行控制. 这是基于 Controller 可以获取到 HUD 对象决定的.

- 上述框架带来的一个问题, 一个敌人身上可能挂载了许多组件和相应的对象, 那么应当控制其加载的时机. 

