#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

typedef struct Commodity
{
	int sales;
	double price;
	char name[20];
}commodity;
//��Ʒ

typedef struct Shop
{
	int id;
	int num;
	char name[20];
	int credibility;
	commodity * cmdt;
	//ָ�����̶�Ӧ����Ʒ�б� 
}shop;
//����

typedef struct ShopList
{
	shop sp;
	struct ShopList * next;
	//�������� 
}shopList;
//�����б�

typedef struct ShopListOfCommodity
{
	int id;
	int sales;
	char name[20];
	int credibility;
	struct ShopListOfCommodity * next;
	struct ShopListOfCommodity * last;
	//˫������ 
}shopListOfCommodity;
//��Ӧ��Ʒ�������б���

typedef struct CommodityShopList
{
	commodity cmdt;
	shopListOfCommodity * spl;
	//�������� 
}commodityShopList;
//��Ӧ��Ʒ�������б�

shopList * head,* tail;
//�����б��ͷ��β 
commodityShopList cmdt[10000];
//����һ��˳��ṹ������Ʒ��Hash�����ַ���洢��ǰÿ����Ʒ������������� 
int num;
//��ǰ������������������id 

void clear()
{
	head = tail = NULL;
	memset(cmdt,0,10000 * sizeof(commodityShopList));
	num = 0; 
}
//�����ǰ״̬�� 

int hash(char * p)
{
	int x = 1,y;
	char * name = p;
	
	for(;*p;p++)
	{
		x *= *p;
		x -= *p / 2;
		x %= 10000;
	}
	y = x;
	//���ڷ��ֿ����������� 
	
	while(cmdt[x].cmdt.name[0] && strcmp(cmdt[x].cmdt.name,name))
	//���������ײ���������һλ 
	{
		x++;
		x %= 10000;
		if(x == y)
		{
			printf("Error hash,memery is out!!!\n");
			system("pause"); 
			exit(0);
		}
		//��ֹ��� 
	}
	
	return x;
}
//hash���� 

void Init()
{
	FILE * file;
	shopList * now = NULL;
	shopList buf;
	
	file = fopen("1.dat","rb");
	if(!file)
	{
		printf("error: fopen(\"1.dat\",\"rb\")");
		exit(1);
	}
	//���ļ����ж�ȡ���������� 
	
	int flag = 1;
	//���ڱ�ʶ�Ƿ��ǵ�һ��fread 
	int i = 0,j = 1;
	//ǰ�����ڼ��������������ж��Ƿ��µĽڵ����ڵ�һ�� 
	
	while(1)
	{
		fread(&buf,sizeof(shopList),1,file);
		//��ȡ�������� 
		
		if(!feof(file))
		//�ж��Ƿ��ļ�ĩβ 
		{
			num++;
			//ÿ��ȡ��һ��������������һ 
			if(flag)
			//��һ������ 
			{
				flag = 0;
				head = now = (shopList *)malloc(sizeof(shopList));
				//��ʼ������ͷ
				memcpy(now,&buf,sizeof(shopList)); 
				now->sp.id = num;
				//����id 
				now->sp.cmdt = (commodity *)malloc(sizeof(commodity) * now->sp.num);
				//��ȡ���̶�Ӧ����Ʒ�б� 
				fread(now->sp.cmdt,sizeof(commodity),now->sp.num,file);
			}
			else
			//��������� 
			{
				now->next = (shopList *)malloc(sizeof(shopList));
				memcpy(now->next,&buf,sizeof(shopList));
				now->next->sp.id = num;
				now = now->next;
				now->sp.cmdt = (commodity *)malloc(sizeof(commodity) * now->sp.num);
				fread(now->sp.cmdt,sizeof(commodity),now->sp.num,file);
				//�����µĽ�㲢�����ݸ��ƽ�ȥ 
			}
			for(i = 0;i < now->sp.num;i++)
			//��ʼ����Ʒ��Ӧ�������б� 
			{
				if(cmdt[hash(now->sp.cmdt[i].name)].cmdt.name[0])
				//�ж��Ƿ��ǵ�һ����������Ʒ 
				{
					//������ǵ�һ����������Ʒ 
					shopListOfCommodity * now2 = cmdt[hash(now->sp.cmdt[i].name)].spl;
					//��ʼ��һ��ָ�����������б���в������� 
					cmdt[hash(now->sp.cmdt[i].name)].cmdt.sales += now->sp.cmdt[i].sales;
					//������������ 
					while(now2->credibility > now->sp.credibility || (now2->credibility == now->sp.credibility && now2->sales > now->sp.cmdt[i].sales))
					//�ж��������Ƿ�ȵ�ǰ���̸����� 
					{
						now2 = now2->next;
						//����ǣ������� 
						if(now2 == cmdt[hash(now->sp.cmdt[i].name)].spl)
						{
							j = 0;
							//��ʾ�ν�������ѭ������Ӧ����ĩβ��ͷ�ڵ㲻�� 
							break;
						}
					}
					now2 = now2->last;
					shopListOfCommodity * temp = now2->next;
					now2->next = (shopListOfCommodity *)malloc(sizeof(shopListOfCommodity));
					now2->next->credibility = now->sp.credibility;
					now2->next->sales = now->sp.cmdt[i].sales;
					now2->next->id = now->sp.id;
					strcpy(now2->next->name,now->sp.name);
					//�����µĽ�㲢�����ݸ��ƽ�ȥ
					now2->next->last = now2;
					now2->next->next = temp;
					temp->last = now2->next;
					//˫��ѭ������Ľ����� 
					if(now2->next->next == cmdt[hash(now->sp.cmdt[i].name)].spl && j)
					//�����ǰΪͷ�ڵ㣬��j����0��˵�����ͷ�ڵ㡰�� 
					{
						cmdt[hash(now->sp.cmdt[i].name)].spl = now2->next;
						j = 1; 
					}
				}
				else
				//��һ������ 
				{
					cmdt[hash(now->sp.cmdt[i].name)].cmdt = now->sp.cmdt[i];
					cmdt[hash(now->sp.cmdt[i].name)].spl = (shopListOfCommodity *)malloc(sizeof(shopListOfCommodity));
					cmdt[hash(now->sp.cmdt[i].name)].spl->credibility = now->sp.credibility;
					cmdt[hash(now->sp.cmdt[i].name)].spl->sales = now->sp.cmdt[i].sales;
					cmdt[hash(now->sp.cmdt[i].name)].spl->id = now->sp.id;
					strcpy(cmdt[hash(now->sp.cmdt[i].name)].spl->name,now->sp.name);
					cmdt[hash(now->sp.cmdt[i].name)].spl->next = cmdt[hash(now->sp.cmdt[i].name)].spl;
					cmdt[hash(now->sp.cmdt[i].name)].spl->last = cmdt[hash(now->sp.cmdt[i].name)].spl;
					//��ʼ��������˫��ѭ������ 
				}
			}
		}
		else if(!flag)
		//��������ļ�β�Ҷ�������� 
		{
			now->next = NULL;
			tail = now;
			break;
		}
		//��������ļ�β��Ϊ�������� 
		else
		{
			head = tail = NULL;
			break;
		}
	}
	
	fclose(file);
	//�ر��ļ�
	return;
}
//��ʼ�������б��������Ʒ��Ӧ������������б� 

void Save()
{
	FILE * file;
	int nums = 1;
	//����idָʾ�� 
	shopList * now = head;
	//��ʼ��ͷָ�����ڱ��� 
	
	file = fopen("1.dat","wb");
	if(!file)
	{
		printf("error: fopen(\"1.dat\",\"wb\")");
		exit(1);
	}
	
	while(now)
	{
		shopList * temp = now; 
		now->sp.id = nums++;
		fwrite(now,sizeof(shopList),1,file);
		fwrite(now->sp.cmdt,sizeof(commodity),now->sp.num,file);
		now = now->next;
		//ѭ��д���ļ� 
		free(temp->sp.cmdt);
		free(temp);
		//�ͷ��ڴ� 
	}
	
	fclose(file);
	//�ر��ļ� 
	return;
}
//��������Ϣ�Ͷ�Ӧ����Ʒ��Ϣ�Զ�������ʽ�������ļ��� 

void add()
{
	shopList now;
	//�����û����� 
	int x = 0;
	//���ڶ����ݺͳ䵱������ 
	
	now.sp.id = ++num;
	//����id 
	now.next = NULL;
	
	printf("Please input name of shop(length < 20):");
	fgets(now.sp.name,20,stdin);
	int l = strlen(now.sp.name);
	if(l != 19)
	{
		now.sp.name[l - 1] = '\0';
	}
	//���fgets���µĻ��з� 
	
	printf("Please input credibility of shop(0-5):");
	scanf("%d",&x);
	fflush(stdin);
	//ˢ�»����� 
	if(x < 0||x > 5)
	{
		printf("Error number!!!\n");
		system("pause"); 
		return;
	}
	now.sp.credibility = x;
	
	x = 0;
	printf("Please input number of shop commodity:");
	scanf("%d",&now.sp.num);
	fflush(stdin);
	now.sp.cmdt = (commodity *)malloc(now.sp.num * sizeof(commodity));
	
	while(x++ < now.sp.num)
	{
		printf("Please input name of commodity %d(length < 20):",x);
		fgets(now.sp.cmdt[x - 1].name,20,stdin);
		l = strlen(now.sp.cmdt[x - 1].name);
		if(l != 19)
		{
			now.sp.cmdt[x - 1].name[l - 1] = '\0';
		}
		printf("Please input price of commodity %d:",x);
		scanf("%lf",&now.sp.cmdt[x - 1].price);
		fflush(stdin);
		printf("Please input sales of commodity %d:",x);
		scanf("%d",&now.sp.cmdt[x - 1].sales);
		fflush(stdin);
	}
	//�����Ӧ����Ʒ��Ϣ 
	
	if(head)
	//����Ѿ���ͷָ�� 
	{
		tail->next = (shopList *)malloc(sizeof(shopList));
		tail = tail->next;
		memcpy(tail,&now,sizeof(shopList));
	}
	else
	//û�����ʼ�� 
	{
		head = tail = (shopList *)malloc(sizeof(shopList));
		memcpy(tail,&now,sizeof(shopList));
	}
	
	system("cls");
	//�����Ļ 
	return;
}
//�����û������������̣�����Զ���һ����������β���� 

void del()
{
	printf("-----------------------------------");
	printf("Welcome to cws's shop manage system");
	printf("-----------------------------------\n");
	printf("-----------------------------------");
	printf("--what shop do you want to delete?-");
	printf("-----------------------------------\n");
	
	shopList * now = head,* last = NULL;
	
	while(now)
	{
		printf("%d:%s\n",now->sp.id,now->sp.name);
		now = now->next;
	}
	//��������ӡ����id������ 
	
	printf("Please input the shop id:");
	int x;
	scanf("%d",&x);
	
	now = head;
	while(now && now->sp.id != x)
	{
		last = now;
		now = now->next;
	}
	//�ҵ���Ӧid����
	 
	if(!now)
	//û���ҵ�����nowΪNULL 
	{
		printf("Error id of shop!!!\n");
		system("pause");
		return;
	}
	
	if(last)
	//����ͷָ�� 
	{
		last->next = now->next;
		if(!last->next)
		//���Ϊβָ�� 
		{
			tail = last;
		}
		free(now->sp.cmdt);
		free(now);
		while(last->next)
		//�������ָ���Ӧ������id��һ��һ 
		{
			last = last->next;
			last->sp.id--;
		}
	}
	else
	//ɾ����Ϊͷָ�� 
	{
		if(head == tail)tail = NULL;
		head = head->next;
		free(now->sp.cmdt);
		free(now);
	}
	
	system("cls");
	//�����Ļ 
	return;
}
//ɾ�����̣��Ա��Ϊ׼�����޸ĺ������ı�ţ����ֱ�������ԡ� 

void buy()
{
	printf("-----------------------------------");
	printf("Welcome to cws's shop manage system");
	printf("-----------------------------------\n");
	printf("-----------------------------------");
	printf("-what commodity do you want to buy?");
	printf("-----------------------------------\n");
	
	printf("Please input commodity name:");
	char name[20];
	
	fgets(name,20,stdin);
	int l = strlen(name),m;
	if(l != 19)
	{
		name[l - 1] = '\0';
	}
	//������Ʒ���� 
	
	commodityShopList x = cmdt[hash(name)];
	if(!(x.cmdt.name[0]))
	//�ж��Ƿ��������д���Ʒ 
	{
		printf("no sale of %s!!!\n",name);
		system("pause");
		return;
	}
	
	shopListOfCommodity * y = x.spl;
	
	printf("%d:%s,credibility: %d,sales: %d\n",y->id,y->name,y->credibility,y->sales);
	y = y->next;
	while(y != x.spl)
	{
		printf("%d:%s,credibility: %d,sales: %d\n",y->id,y->name,y->credibility,y->sales);
		y = y->next; 
	}
	//������Ʒ��Ӧ�������б���ӡ��Ӧ������id�����֣������ȣ����� 
	
	printf("Please input shop id and number to buy like (1 4):");
	scanf("%d %d",&l,&m);
	
	shopList * now = head;
	while(now && now->sp.id != l)
	{
		now = now->next;
	}
	//�ҵ���Ӧ�����̽��
	 
	if(now)
	{
		int i = 0;
		for(;i < now->sp.num;)
		{
			if(!strcmp(now->sp.cmdt[i].name,name))
			{
				now->sp.cmdt[i].sales += m;
				break;
				//�ҵ���Ӧ��Ʒ���������� 
			}
		}
	}
	else
	{
		printf("Error id!!!\n");
		system("pause");
		return;
	}
	
	system("cls");
	//�����Ļ 
	return;
}
//��ѯĳһ����Ʒ���ƣ�����һ��˫��ѭ�����������Ϣ�ǰ�������Ʒ���������̱�š��������������ȡ���Ʒ���ơ��۸��������������ȴӸ����ͣ������������򣬲���һ��ʾ��
//����ĳһ���̵���Ʒ���޸ĵ�����������Ʒ����Ϣ�������� 
 
void menu()
{
	while(1)
	{
		printf("-----------------------------------");
		printf("Welcome to cws's shop manage system");
		printf("-----------------------------------\n");
		printf("-----------------------------------");
		printf("------what do you want to do?------");
		printf("-----------------------------------\n");
		printf("1.add shop\n");
		printf("2.delete shop\n");
		printf("3.buy\n");
		printf("4.exit\n");
	
		int x;
		scanf("%d",&x);
		fflush(stdin);
		system("cls");
	
		switch(x)
		{
			case 1:
				add();
				break;
			case 2:
				del();
				break;
			case 3:
				buy();
				break;
			case 4:
				return;
			default:
				printf("valid choice!!!\n");
				break;
		}
		
		Save();
		clear();
		Init();
		//�κε�������Ϣ�仯��ʵ���ļ��洢��
		
		system("cls");
		//�����Ļ 
	}
	
	return;
}
//���ڽ����Ĳ˵����� 

int main()
{
	Init();
	//ͨ���ļ���ʼ�� 
	
	menu();
	
	return 0;
}
