# Pokemon_simple

## ��Ŀ���
	
## ��Ŀ�ļ��ṹ
	
## ˵���ļ�
	UMLͼ���ļ�

## ��Ҫ��ɵĹ���:
	��Ҫ��ɵ����ݵĵط�����ע��:"//TODO:"
	��ʼд����ǰ,������ͬ��git !!!
	ѡ��Ҫд�Ĺ�����,��ɾ��ע��"TODO:" ,��ʾ�����Ѿ���ռ��
	ɾ��ע��"TODO:"��,�������ύ��ͬ��git !!!
	���ÿ��TODO��,�������ύ��ͬ��git !!!
	ȷ��ĳ���ļ��Ĵ����Ѿ���ɺ�,��������Finished�ļ���
	�����Ҫ����ĳЩ��������������ɹ���,���԰�������������ļ�,����Finished�ļ����е��ļ�
	
	һЩ�Ƚ�����,��ɢ�Ĵ�����������:
	//TODO:	1.��Game::Run()��ÿһ��������,������ʾ��ǰ������Ϣ�Ĳ�ɫ�ı���ʾ,�Լ���ǰ�������Խ��еĲ�������ʾ
			(����:{��ͼ����}{�������},��ʾ����"��WASD���ƶ�,E�鿴����,ESC������,...",���Խ��еĲ�����ÿ�������ж����߼�����)

## ��Դ�ļ������ʽ
	ͳһ�����resources�ļ�����
	cd ./resources
	./music/xxx.wav 
	./gamebar.txt (��Ϸ�˵�����ͼƬ)
	./worldmap.txt (�����ͼͼƬ)
	./NPC_Info.csv (NPC��Ϣ�ļ�, CSV��ʽ)
	./Skill_Info.csv (�����μ�����Ϣ, CSV��ʽ)
    ./Pokemon_Info.csv (��������Ϣ, CSV��ʽ)
	./Prop_Info.csv (������Ϣ, CSV��ʽ)
    ./Battle_Info.csv (ս����Ϣ, CSV��ʽ)
	./maps/map_{mapID}.txt (�����ͼ�ļ�, TXT��ʽ)
	./save/BackPack_State.csv (����״̬�ļ�, csv��ʽ)
    ./save/PokemonLib_State.csv (������״̬�ļ�, csv��ʽ)
	./save/Game_State.txt (��Ϸ״̬�ļ�, txt��ʽ)
	./save/NPC_State.csv (NPC״̬�ļ�, csv��ʽ)


### NPC_Info�ļ������ʽ
	��ʽΪ(ÿһ���Զ��ŷָ�):
	NPC_ID,NPC_Name,(NPC_DefultPosition :)MapID/PositionX/PositionY,NPC_States:
	NPC_States:NPC_State1/NPC_State2/NPC_State3/...
	NPC_State(Ĭ��״̬id=0):stateID|stateTalk|stateNotFinishTalk|stateAction|stateNext
		stateID:״̬ID
		stateTalk:����״̬ʱNPC�ĶԻ�(״̬���ʱ)
		stateNotFinishTalk:����״̬ʱNPC�ĶԻ�(���״̬,״̬δ���ʱ)
		stateAction:��״̬��NPC����Ϊ����
		stateNext:��״̬������ж�״̬���,NPC����һ��״̬(���Իص�֮ǰ��״̬,����ѭ��)
		stateAction:��ͬ����Ϊ�в�ͬ�Ĳ���: stateActionType\stateActionParam1\stateActionParam2\...
		stateActionType:��Ϊ����,��Ӧ�Ĳ�������:
			0:����Ϊ, �Ի���ɺ�ֱ����ת����һ��״̬
			1:�ƶ���ָ��λ��(MapID,PositionX,PositionY)
			2:�����ض�ս��(BattleID, λ��Battle_Info.csv), ս��ʤ����Ϊ״̬���
			3.�������NPC״̬(NPC_ID,State_ID), ���NPC_ID��NPC����State_ID״̬, ��״̬���
			4.�������Ƿ�ӵ��ָ����Ʒ(PropID), ���ӵ��, ��״̬���
			5.�ύ��Ʒ(PropID,PropCount), �����ӵ�е�PropID��Ʒ,����ΪProp���ύ��NPC, Ȼ��״̬���
			6.�������Ƿ�ӵ��ָ��������(PokemonID), ���ӵ��, ��״̬���
			7.��ĳ��������(PokemonID, level)�������, Ȼ��״̬���
			8.��ĳ������(PropID,PropCount)�������

	����:
	ĳ����ΪС�ǵ�NPC(IDΪ1),������ΪΪ:
	0.���ζԻ���˵"���,����С��"
	1.Ȼ���,С�ǻ�Ҫ��ȥ�Ҵ�ľ��ʿ(����IDΪ2,�Ի���ɺ�stateIDΪ3)�Ի�, Ȼ��С���ƶ���������ͼλ��
	2.�����ҵ���ľ��ʿ��, ��ľ��ʿ�������, С�ǵ�λ��, 
		����һֻƤ����(����PokemonID = 1,  )������, Ȼ���ľ��ʿ�ƶ���������ͼλ��
	3.�����ҵ�С�Ǻ�,�������չ��һ��ս��(����BattleIDΪ1)
	4.���ս�����������һ������(PropID = 1,PropCount = 2), Ȼ��С���ƶ���������ͼλ��

	��Ӧ��csv����Ϊ(ʵ�ʵ�csv�ļ��в�����з���,�˴�Ϊ����ʾ����):
	1,С��,1/15/20,		(С�ǵ�IDΪ1,��ʼλ��ΪmapID=1,x=15,y=20��λ��)
	0|���,����С��||0|1 /		(���ζԻ���˵"���,����С��",Ȼ����ת��״̬1)
	1|����ȥ�Ҵ�ľ��ʿ��,����һֻƤ������Ը���||1\2\18\18|2 /		(С�ǻ�Ҫ��ȥ�Ҵ�ľ��ʿ�Ի�, Ȼ���ƶ���mapID=2,x=18,y=18��λ��,Ȼ����ת��״̬2)
	2|�ܺ�,����������һֻ��������|�㻹û�ҵ���ľ��ʿ��|6\1|3 /		(��״̬δ���ʱ, С�ǻ�����㻹û�ҵ���ľ��ʿ, ��״̬���ʱ, ��ת��״̬3)
	3|��ϲ��,������������һ��ս����|�����ڻ�̫����|2\1|4 /			(����ս��IDΪ1��ս��, սʤ����ת��״̬4,���򱣳���3)
	4|�ܺ�,�����ڱ�ø�ǿ����,�����������������||8\6|4				(ս��ʤ����, С�ǻ�佱��, Ȼ���������������ID=6, Ȼ����ת��״̬4)

### Map_\{mapID\}.txt�����ʽ
	��һ��: ��ͼ����
    �ڶ���: ��ͼ��С:��ͼ��x/��ͼ��y
	������: ��ͼ˵����Ϣ(˵����Ϣ����չʾ,����Ӱ��ʵ�ʵ�ͼ):
			ÿһ���Զ��ŷָ�,ÿһ�����: ����/��ɫ/����˵��
        	����:��/0/�յ�,��/1/��ʯ,��/2/ˮ��,�z/3/�ݵ�,��/4/��
	������: ��ͼ������Ϣ(��ͼ������Ϣ����Ӱ��ʵ�ʵ�ͼ):
    		ÿһ���Զ��ŷָ�,ÿһ�����: ����X����/����Y����/���ڵ�ͼID/���ڵ�ͼX����/���ڵ�ͼY���� (���������Ͻǿ�ʼ)
	������: ��ͼ�ݵؿ��������ı�������Ϣ(ID/Level/Rate,ID/Level/Rate,...), RateΪΪ����,ʵ�ʸ���Ϊ1/Rate
	��������y��: ��ͼ��ʾ�ķ���
	��������y��: ��ͼÿһ�����ɫ(��ɫ����)
	��������y��: ��ͼÿһ�������(����), ÿһ���Զ��ŷָ�

### Skill_Info.csv�����ʽ
	��ʽΪ(ÿһ���Զ��ŷָ�):
    Skill_ID,Skill_Name,Skill_Description,TypeID,Skill_Type,power, accuracy, pp, mustHit,priority,effectID,effectParam.
	mustHit: �Ƿ�Ϊ���м��� 
	priority: ���ܷ������ȼ�, ���ȼ��ߵļ����ȷ���, ���ȼ���ͬ�����ٶȾ���
	effectID: 
	effectParam: ��"/"�ָ�
		const enum SkillEffect {
        ATTACK = 0,       //����(�޲���)
        MUTI_ATTACK,      //��ι���(������С����,����������)
        ATTACK_AND_STATE, //�������и���ʩ���쳣״̬(�쳣״̬1��ID,�쳣״̬1����,�쳣״̬2��ID,�쳣״̬2����....)
        ATTACK_AND_BUFF, //���������Լ�ʩ��buff(buffID_1,�ı�buff�ķ�ʽ(1Ϊ����,2Ϊ����),�ı�����õ�ֵ,...)
        ATTACK_AND_DEBUFF,//���������Է�ʩ��debuff(����ͬ��)
        BUFF,            //���Լ�ʩ��buff(����ͬ��)
        DEBUFF,          //���Է�ʩ��debuff(����ͬ��)
        STATE,           //ʩ���쳣״̬(�쳣״̬��ID,�쳣״̬����)
        HEAL_HP,          //�ظ�(�ظ��ķ�ʽ(1���������ظ�,2���հٷֱȻظ�),�ظ��ٷֱ�(�����2))
        ATTACK_AND_HEAL,  //�������ظ�(�ظ�ֵռ�����˺��İٷֱ�,����50��ʾ�ظ��˺�ֵ��һ��Ѫ��)
        SPECIAL_EFFECT,   //����Ч��(����Ч������ID(������ܲ�����������������,��Ҫ�������Ч������))
		};
		//����״̬����ֵ
		const struct Buff {
			//id��1��ʼ����
			int attack;         //����
			int defense;        //����
			int speed;          //�ٶ�
			int specialAttack;  //�ع�
			int specialDefense; //�ط�
			int accuracy;       //������
			int evasion;        //������
		};
		//�쳣״̬
		enum PokemonStatu {
			None = 0, //���쳣״̬
			Poison, //�ж�, ÿ�غϽ���ʱ����ʧ1/8�������ֵ,��಻����15��
			Paralysis, //���, ÿ�غ�25%ʹ����ʧЧ, ���ٶȽ���50%
			Burn, //����, ÿ�غϽ���ʱ����ʧ1/16�������ֵ, ������������50%
			Sleep, //˯��, �޷��ж�, ÿ�غ���20%�Զ����
			Freeze, //����, �޷�ʹ�������������⹥��, ÿ�غ���10%�Զ����
			Frostbite   //����, ÿ�غϽ���ʱ����ʧ1/16�������ֵ, �����⹥������50%, �����Ա����β��ᱻ����
		};
	����:
    1,��,����һ����ϵ���� ��10%�ĸ���ʩ������ Ҳ��20%����ʹ�з�����˯��,2,1,80,100,10,0,1,2,3/10/4/20

### Prop_Info.csv�����ʽ
	��ʽΪ(ÿһ���Զ��ŷָ�):
    Prop_ID,Prop_Name,Prop_Description,Prop_Type,price,sellPrice,canUseInField,canUseInBattle,effectPara.
	price,sellPrice: ����۸�ͳ��ۼ۸�,Ϊ0��ʾ���ɹ���/����
    canUseInField,canUseInBattle: �Ƿ������Ұ��ʹ��,�Ƿ������ս����ʹ��
	//���ߵ�����,�Լ�����(������'/'�ָ�)
	const enum PROP_TYPE 
	{
		NORMAL=0,         //�������,��Ч��
		EREASE_STATUS,  //��������״̬(PokemonStatu(0��ʾ���������κ�״̬))
		CHANGE_POKEMON_ATTRBUTE,  //�ı䱦��������(ATTRIBUTE,�ı�ֵ,...)  //��Ұ��ʹ��Ϊ���øı�,��ս����ʹ��Ϊ��ʱ�ı�
		CHANGE_SKILL_ATTRIBUTE,  //�ı似������(�ı�����,��������,��������,�ı�ֵ,��������,�ı�ֵ...)     //��Ұ��ʹ��Ϊ���øı�,��ս����ʹ��Ϊ��ʱ�ı�
		/*
		* �ı�����,��������:
		* 0.������(������Ч)
		* 1.��������(SkillType)
		* 2.��������(Type)
		��������id:
		1.power;              //����
		2.accuracy;           //����
		3.PP;                 //pp
		4.maxPP;              //���pp
		*/
		BUFF,   //�ı�����״̬����ֵ(����״̬����ֵ,�ı�ֵ,...)  //��ս������ʱ�ı�
		HEAL,  //�ظ�����(����ʱ�Ƿ����,�ظ���ʽ(0���ٷֱ�,1������ֵ),�ٷֱ�/����ֵ)
		GET_SKILL,   //ʹ�����λ�ü���(����ID), ��Чǰ��Ҫ�ж��Ƿ����
		CAPTURE,    //����������(�����ʼӳ�,���ض���Type���Եı�����,�ض������ʼӳ�)
		SPECIAL_PROP,  //�������(���⺯��id,��������1,��������2...)
		};
### Pokemon_Info.csv�����ʽ
	��ʽΪ(ÿһ���Զ��ŷָ�):
    Pokemon_ID,Pokemon_Name,Type1,Type2,growthRate,captureRate,basicExperience,ethnicValue,defaultSkills.
	Type1,Type2: �����ε�����, ������Ϊ-1
    growthRate: �����εĳɳ�����,0-5,�ֱ�Ϊ����,��,����,�Ͽ�,��,���
    captureRate: ����������,1-255,255Ϊ100%����,
    basicExperience: ��������ֵ,��ʾ�����ܺ��õľ���ֵ
	ethnicValue:����ֵ,��'/'�ָ�,�ֱ�Ϊ(HP,����,����,�ع�,�ط�,�ٶ�)
	defaultSkills(��'/'�ָ�):skillID/Level/skillID/Level...		,levelΪ0��ʾĬ�ϼ���,��0��ʾѧϰ���ܵĵȼ�
### Battle_Info.csv�����ʽ
	BattleID,OpponentName,Pokemons.
    Pokemons:PokemonID|Level / PokemonID|Level ...
	OpponentName: ���ֵ�����
    
## �浵�ļ������ʽ
	ͳһ�����save�ļ�����
	./save/BackPack_State.csv (����״̬�ļ�, csv��ʽ)
    ./save/PokemonLib_State.csv (������״̬�ļ�, csv��ʽ)
	./save/Game_State.txt (��Ϸ״̬�ļ�, txt��ʽ)
	./save/NPC_State.csv (NPC״̬�ļ�, csv��ʽ)

### NPC_State.csv�����ʽ
	��ʽΪ(ÿһ���Զ��ŷָ�):
	NPC_ID,NPC_StateID,MapID,x,y

### BackPack_State.csv�����ʽ
	��ʽΪ(ÿһ���Զ��ŷָ�):
    Prop_ID,Prop_Num

### Game_State.txt�����ʽ
	��һ��:playerX,playerY,currentMapID
	�ڶ���:money

### PokemonLib_State.csv�����ʽ
	ǰ6��Ϊ����ı�����,����Ϊ�����еı�����
	��ʽΪ(ÿһ���Զ��ŷָ�):
	ID,name,type1,type2,level,experience,experienceToNextLevel,statu,attribute,evolutionLevel,evolutionID,captureRate,growthRate,basicExperience,
	ethnicValue,individualValue,basicValue,skills.

	attribute: hp/maxHP/attack/defense/speed/specialAttack/specialDefense
	ethnicValue,individualValue,basicValue(��Ϊ:):hp/attack/defense/specialAttack/specialDefense/speed
	skills:skill_1/skill_2/skill_3...
    skill_x:skillID|skillName|skillDescription|type|skillType|power|accuracy|PP|maxPP|skillEffect|effectParam|mustHit|priority
    skillEffect: Ч������,��'\'�ָ�