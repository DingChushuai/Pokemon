# Pokemon_simple

## 项目简介
	
## 项目文件结构
	
## 说明文件
	UML图等文件

## 项目进程
	所有需要补充的代码实现的地方将在底下标出
	多人协作时, 请更改对应任务的状态标记, 在上传代码前, 请先** 同步任务板的状态 **, 以免发生冲突
	** 不要删除我提供的注释 **
	以下解释为任务状态标记
	- (T,score) 表示TODO, 表示该任务需要完成, score为任务难度评分(1-5)
	- (F) 表示Finish, 表示该任务已完成
	- (P,name) 表示Processing, 表示该任务正在处理中, name为处理该任务的人名(可以使用任何喜欢的标记名称)
	- (?,name) 表示任务遇到问题, 或者需要讨论
	- (D) 表示Discard, 表示该任务被废弃

## 代码任务
	0. (F,2) 完成tools.h 里的Split函数, 用于字符串分割, 读取文件时需要用到
	1. (T,2) 完成Text类的SetColor,Print函数, 用于控制台输出颜色, 需要了解彩色控制台输出原理
	2. (T,1) 补充SoundID和音乐路径的声明, 需要资源组提供内容后完成
	3. (T,4) SoundPlayer类的三个函数, 需要调用系统的声音播放库, 实现播放音乐, 播放音效, 暂停音乐, 需要查阅相关资料
    4. (T,2) 完成Prop类的构造函数
    5. (T,3) 完成Backpack类的各个功能函数
    6. (T,2) 完成Map类的构造函数和getExit函数
	7. (T,4) 完成tools内的各个函数, 需要了解相关算法和资料
    8. (T,5) 完成NPC类的各个功能函数
	9. (T,3) 完成SceneDrawer类的各个场景的绘制, 场景较多, 可以多人共同完成


## 资源收集任务
	** 所有包含ID的文件, ID必须从1开始, 按照顺序递增, 保证行序号和ID一致 **
	** 所有包含文字描述的文件, 必须使用UTF-8编码, 描述中不能有"," ,以防出现错误的分隔符, 可以使用全角符号"，"代替 **
	音乐资源: (T,2) 需要至少收集到: 主要背景音乐, 战斗背景音乐, 打击音效
					还可以收集: 各个地图的背景音乐, 改变选择器的音效, 胜利音效, 失败音效, 捕捉音效, 等等
	gamebar: (T,1) 游戏菜单界面的标题, 使用文本化的方式描述图片, 可以是大字标题

## 资源文件具体格式
	统一存放在resources文件夹下
	cd ./resources
	./music/xxx.mp3 (具体格式可以根据需求更改)
	./gamebar.txt (游戏菜单界面图片)
	./NPC_Info.csv (NPC信息文件, CSV格式)
	./Skill_Info.csv (宝可梦技能信息, CSV格式)
    ./Pokemon_Info.csv (宝可梦信息, CSV格式)
	./Prop_Info.csv (道具信息, CSV格式)
    ./Battle_Info.csv (战斗信息, CSV格式)
	./maps/map_{mapID}.txt (多个地图文件, TXT格式)

### NPC_Info文件具体格式
	格式为(每一项以逗号分隔):
		NPC_ID,
		NPC_Name,
		NPC_DefultPosition(MapID,PositionX,PositionY),		//NPC的初始位置,每一项以"/"分隔
		NPC_States.

		NPC_States(每一项以"/"分隔):
			每一项包括(以"|"分隔):
			NPC_state默认为1, 然后跳转到其他状态, 每个状态包括:
			stateID:状态ID
			stateTalk:处于状态时NPC的对话(状态完成时)
			stateNotFinishTalk:处于状态时NPC的对话(检查状态,状态未完成时)
			stateAction:该状态下NPC的行为类型
			stateNext:该状态下如果判断状态完成,NPC的下一个状态(可以回到之前的状态,进行循环)

			stateAction:不同的行为有不同的参数,每个参数用"\分隔":
				0:无行为, 对话完成后直接跳转到下一个状态
				1:移动到指定位置(MapID,PositionX,PositionY)
				2:触发特定战斗(BattleID, 位于Battle_Info.csv), 战斗胜利视为状态完成
				3.检查其他NPC状态(NPC_ID,State_ID), 如果NPC_ID的NPC处于State_ID状态, 则状态完成
				4.检查玩家是否拥有指定物品(PropID), 如果拥有, 则状态完成
				5.提交物品(PropID,PropCount), 将玩家拥有的PropID物品,数量为Prop个提交给NPC, 然后状态完成
				6.检查玩家是否拥有指定宝可梦(PokemonID), 如果拥有, 则状态完成
				7.将某个宝可梦(PokemonID, level)交给玩家, 然后状态完成
				8.将某个道具(PropID,PropCount)交给玩家


		例如:
		某个名为小智的NPC(ID为1),他的行为为:
		0.初次对话后说"你好,我是小智"
		1.然后后,小智会要你去找大木博士(假设ID为2,对话完成后stateID为3)对话, 然后小智移动到其他地图位置
		2.当你找到大木博士后, 大木博士会告诉你, 小智的位置, 
			并将一只皮卡丘(假设PokemonID = 1,  )交给你, 然后大木博士移动到其他地图位置
		3.当你找到小智后,他会和你展开一场战斗(假设BattleID为1)
		4.完成战斗后他会给你一个道具(PropID = 1,PropCount = 2), 然后小智移动到其他地图位置

		对应的csv内容为(实际的csv文件中不会进行分行,此处为了演示分行):

		1,小智,1/15/20,		(小智的ID为1,初始位置为mapID=1,x=15,y=20的位置)
		0|你好,我是小智||0|1 /		(初次对话后说"你好,我是小智",然后跳转到状态1)
		1|请你去找大木博士吧,他有一只皮卡丘可以给你||1\2\18\18|2 /		(小智会要你去找大木博士对话, 然后移动到mapID=2,x=18,y=18的位置,然后跳转到状态2)
		2|很好,你现在有了一只宝可梦了|你还没找到大木博士啊|6\1|3 /		(当状态未完成时, 小智会告诉你还没找到大木博士, 当状态完成时, 跳转到状态3)
		3|恭喜你,现在我们来打一场战斗吧|你现在还太弱了|2\1|4 /			(触发战斗ID为1的战斗, 战胜后跳转到状态4,否则保持在3)
		4|很好,你现在变得更强大了,我送你两个精灵球吧||8\6|4				(战斗胜利后, 小智会夸奖你, 然后给你两个精灵球ID=6, 然后跳转到状态4)

### Map_\{mapID\}.txt具体格式
	第一行: 地图名称
    第二行: 地图大小(地图宽x,地图高y)
	第三行: 地图说明信息(说明信息仅供展示,不会影响实际地图):
		每一项以逗号分隔,每一项包括: 符号/颜色/文字说明
        	例如:□/0/空地,█/1/岩石,█/2/水域,▃/3/草地,≡/4/门
	第四行: 地图出口信息(地图出口信息不会影响实际地图):
    		每一项以逗号分隔,每一项包括: 出口X坐标/出口Y坐标/出口地图ID/出口地图X坐标/出口地图Y坐标 (坐标以左上角开始)
	第五行: 地图草地可能遇到的宝可梦信息(ID/Level,ID/Level,...)
	接下来的y行: 地图显示的符号
	接下来的y行: 地图每一格的颜色(颜色数字)
	接下来的y行: 地图每一格的类型(数字), 每一项以逗号分隔

	//颜色数字
	const enum Color
    {
        None = 0,	//控制台默认输出应该是白色
        RED,
        GREEN,
        BLUE,
        YELLOW,
        CYAN,		//浅蓝色
        MAGENTA,	//紫色
		GRAY,		//灰色
    };

	地图方格类型:
	 enum BlockType
    {
        EMPTY = 0,  //可以行走的道路
        WALL,       //障碍物
        GRASS,      //草地,可以行走,可能遇到野生的宝可梦
        EXIT,       //通往其他地图的出口
        SHOP,       //商店
        HOSPITAL,   //医院,可以回复宝可梦体力
        POKEMON_CENTER, //宝可梦中心,可以交换仓库中的宝可梦
    };

### Skill_Info.csv具体格式
	格式为(每一项以逗号分隔):
    Skill_ID,
	Skill_Name,
	Skill_Description,
	TypeID:
		enum Type {
		NORMAL = 0,
		FIGHTING, //格斗
		FLYING,   //飞行
		POISON,   //毒
		GROUND,   //地面
		ROCK,     //岩石
		BUG,      //虫
		GHOST,    //幽灵
		STEEL,    //钢
		FIRE,     //火
		WATER,    //水
		GRASS,    //草
		ELECTRIC, //电
		PSYCHIC,  //超能力
		ICE,      //冰
		DRAGON,   //龙
		DARK,     //恶
		FAIRY,    //妖精
		};
    Skill_Type
		const enum SkillType{
			PHYSICAL=0,     //物理
			SPECIAL,        //特殊
			CHANGE,         //变化
		};
	power, 
	accuracy, 
	pp, 
	mustHit: 是否为必中技能 
	priority: 技能发动优先级, 优先级高的技能先发动, 优先级相同则按照速度决定
	effectID: 
	effectParam: 以"/"分隔
		const enum SkillEffect {
        ATTACK = 0,       //攻击(无参数)
        MUTI_ATTACK,      //多段攻击(攻击最小次数,攻击最大次数)
        ATTACK_AND_STATE, //攻击并有概率施加异常状态(异常状态1的ID,异常状态1概率,异常状态2的ID,异常状态2概率....)
        ATTACK_AND_BUFF, //攻击并给自己施加buff(buffID_1,改变buff的方式(1为增加,2为设置),改变或设置的值,...)
        ATTACK_AND_DEBUFF,//攻击并给对方施加debuff(参数同上)
        BUFF,            //给自己施加buff(参数同上)
        DEBUFF,          //给对方施加debuff(参数同上)
        STATE,           //施加异常状态(异常状态的ID,异常状态概率)
        HEAL_HP,              //回复(回复的方式(1按照威力回复,2按照百分比回复),回复百分比(如果是2))
        ATTACK_AND_HEAL,        //攻击并回复(回复值占攻击伤害的百分比,例如50表示回复伤害值的一半血量)
        SPECIAL_EFFECT,               //特殊效果(特殊效果函数ID(如果技能不属于以上所有类型,需要单独设计效果函数))
		};
		//能力状态修正值
		/*
		能力变化初始为0，最高可提高至 +6，最低可降低至 -6。当替换宝可梦时，被替换下场的宝可梦能力变化复原为0。
		攻击、特攻、防御、特防和速度,命中率与闪避率的能力值变化, 每一等级的变化为(按百分比)
		-6   -5   -4  -3    -2    -1   0     1     2   3    4     5   6
		25%  28%  33%  40%  50%  66%  100%  150% 200% 250% 300% 350% 400%
		*/
		const struct Buff {
			//id以1开始计数
			int attack;         //攻击
			int defense;        //防御
			int speed;          //速度
			int specialAttack;  //特攻
			int specialDefense; //特防
			int accuracy;       //命中率
			int evasion;        //闪避率
		};
		//异常状态
		enum PokemonStatu {
			None = 0, //无异常状态
			Poison, //中毒, 每回合结束时会损失1/8最大生命值,最多不超过15点
			Paralysis, //麻痹, 每回合25%使攻击失效, 且速度降低50%
			Burn, //灼伤, 每回合结束时会损失1/16最大生命值, 且物理攻击降低50%
			Sleep, //睡眠, 无法行动, 每回合有20%自动解除
			Freeze, //冰冻, 无法使用物理攻击和特殊攻击, 每回合有10%自动解除
			Frostbite   //冻伤, 每回合结束时会损失1/16最大生命值, 且特殊攻击降低50%, 冰属性宝可梦不会被冻伤
		};
	例如:
    1,火花,这是一个火系技能 有10%的概率施加灼烧 也有20%概率使敌方陷入睡眠,2,1,80,100,10,0,1,2,3/10/4/20

### Prop_Info.csv具体格式
	格式为(每一项以逗号分隔):
    Prop_ID,
	Prop_Name,
	Prop_Description,
	Prop_Type,
	price,			//出售价格为0的道具不能出售
	sellPrice,
	canUseInField,
	canUseInBattle,
	effectPara
	//必须明确使用场景, 例如回血道具可以在战斗中使用, 也可以在野外使用, 永久提升属性道具只能在野外使用, 精灵球只能在战斗中使用
	//道具的类型,以及参数
		const enum PROP_TYPE 
		{
			NORMAL=0,         //剧情道具,无效果
			EREASE_STATUS,  //消除自身状态(PokemonStatu(0表示可以消除任何状态))
			CHANGE_POKEMON_ATTRBUTE,  //改变宝可梦属性(ATTRIBUTE,改变值,...)  //在野外使用为永久改变,在战斗中使用为临时改变
			CHANGE_SKILL_ATTRIBUTE,  //改变技能属性(改变条件,条件参数,技能属性,改变值,技能属性,改变值...)     //在野外使用为永久改变,在战斗中使用为临时改变
			/*
			* 改变条件,条件参数:
			* 0.无条件(参数无效)
			* 1.技能类型(SkillType)
			* 2.技能属性(Type)
			技能属性id:
			1.power;              //威力
			2.accuracy;           //命中
			3.PP;                 //pp
			4.maxPP;              //最大pp
			*/
			BUFF,   //改变能力状态修正值(能力状态修正值,改变值,...)  //在战斗中临时改变
			HEAL,  //回复体力(濒死时是否可用,回复方式(0按百分比,1按具体值),百分比/具体值)
			GET_SKILL,   //使宝可梦获得技能(技能ID), 生效前需要判断是否合理
			CAPTURE,    //精灵球类型(捕获率加成,对特定的Type属性的宝可梦,特定捕获率加成)
			};

## 存档文件具体格式
	统一存放在save文件夹下
	cd ./save
	./NPC_State.csv	(记录存档时NPC的信息)



### NPC_State.csv具体格式
	格式为(每一项以逗号分隔):
	NPC_ID,NPC_StateID,MapID,x,y