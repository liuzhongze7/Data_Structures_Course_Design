/*
���һ�����򣬶�������Ϣ����������Ϣ���������̱�ţ��������������ȣ�0-5����
����Ʒ����1���۸�1������1��������Ʒ����2���۸�2������2��������Ʒ����3���۸�3������3������
��Ʒ���ư���(ë����ˢ�����࣬����ϴ��ˮ����ԡ¶��6��������Ʒ)��
ÿ�����̾�����������ȷ��������Ʒ���۸����ļ����룬������ʼΪ0��
[����Ҫ��]
��1������һ����������洢����������Ϣ������30�������Ա��Ϊ�򣬱�Ŵ�1��ʼ������
	���ļ��ж�ȡ���ݣ����ܽ����ݴ洢���ļ���������Ϣ�������ݽṹ������ơ�
��2����������ɾ���̡��������̣�����Զ���һ����������β����
	ɾ�����̣��Ա��Ϊ׼�����޸ĺ������ı�ţ����ֱ�������ԡ�������ɾ��Ʒ��
��3����ѯĳһ����Ʒ���ƣ�����һ��˫��ѭ�����������Ϣ�ǰ�������Ʒ��
	�������̱�š��������������ȡ���Ʒ���ơ��۸��������������ȴӸ����ͣ������������򣬲���һ��ʾ��
��4������ĳһ���̵���Ʒ���޸ĵ�����������Ʒ����Ϣ��������
��5������һ��˳��ṹ������Ʒ��Hash�����ַ���洢��ǰÿ����Ʒ������������� 
��6���κε�������Ϣ�仯��ʵ���ļ��洢��
*/
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>

using namespace std;

// ��Ʒ 
typedef struct WareNode 
{
	char wareName[100];	// ��Ʒ���� 
	int price;			// �۸� 
	int sales;			// ���� 
	int shopId;			// ���̱��
	WareNode *pre, *next; 
}*WareList;

// ���� 
typedef struct ShopNode 
{
	int shopId;
	char shopName[100];
	int shopCredit;
	int wareCount;
	WareList wareList;
	ShopNode *next;
}*ShopList;

// hash��Ʒ 
typedef struct 
{
	bool flag;
	char wareName[100];
	int sales;
}HashWare;

// ȫ�ֱ��� 
FILE *fp;
char fileName[] = "shopDate.txt";

ShopList sList;	// �������� 
int shopCount = 0;

WareList wList;	// ��Ʒ�б�˫������ 
HashWare hash[10000];


// ���ļ� 
void fileOpen(char *method) 
{
	if((fp=fopen(fileName,method)) == NULL) 
	{
        printf("file cannot be opened\n");
        return;
    }
    //else printf("file has been opened\n");
}

// �ر��ļ� 
void fileClose() 
{
	if(fclose(fp)!=0) printf("file cannot be closed\n");
    //else printf("file has been closed\n");
    return;
}

// ���ҵ���
ShopNode* FindShop(int shopId) 
{
	ShopNode *sNode = sList->next;
	while (sNode)
	{
		//printf("====shopId:%d\n", sNode->shopId);
		if (sNode->shopId == shopId) 
		{
			return sNode;
		} 
		sNode = sNode->next;
	}
	printf("find shop fail, no this shop, shopId is %d\n", shopId);
	return NULL;
}

// ��ʾ��Ʒ��Ϣ
void ShowWareInfo(WareNode *ware) 
{
	printf("  |------------------------------------\n  |\n");
	printf("  |��Ʒ���֣�%s\n  |��Ʒ�۸�%d    ��Ʒ������%d\n  |\n", ware->wareName, ware->price, ware->sales);
	ShopNode *shop = FindShop(ware->shopId);
	printf("  |�������̱�ţ�%2d\n  |�������֣�%s    ���������ȣ�%d\n  |\n", shop->shopId, shop->shopName, shop->shopCredit);
	printf("  |------------------------------------\n");
} 

// ��ʾ������Ϣ
void ShowShopInfo(ShopNode *shop) 
{
	printf("===============================================\n");
	printf("���̱�ţ�%2d	��������%s	�����ȣ�%d\n\n��ӵ����Ʒ������%d\n\n", shop->shopId, shop->shopName, shop->shopCredit, shop->wareCount);
	printf("������Ʒ���£�\n");
	WareNode *wNode = shop->wareList->next;
	while (wNode) 
	{
		ShowWareInfo(wNode);
		wNode = wNode->next;
	}
	printf("===============================================\n");
}

// ��ʾ��������������������Ϣ
void ShowShopList() 
{
	ShopNode *sNode = sList->next;
	while (sNode) 
	{
		ShowShopInfo(sNode);
		sNode = sNode->next;
	}
}

// ����Ʒ�����й�ϣӳ��
int Hash(char *wareName) 
{
	int pos = (wareName[0] * wareName[1] + 12345678) % 10000;
	//cout<<pos<<endl;
	while (1) 
	{
		if (hash[pos].flag == false || strcmp(hash[pos].wareName, wareName) == 0) break;
		pos++;
		if (pos >= 10000) pos = 0;
	}
	hash[pos].flag = true;
	strcpy(hash[pos].wareName, wareName);
	return pos;
}

// ��ʼ�������ļ��ж�ȡ���� 
void Init() 
{	
	// ��ʼ���������������ļ��ж�ȡ���� 
	fileOpen("r");
	
    sList = (ShopNode*)malloc(sizeof(ShopNode));
    sList->shopId = 0;
    sList->next = NULL;
    ShopNode *sLast = sList;	// ָ�������������һ����� 
    fscanf(fp, "%d", &shopCount);
    for (int i=0; i<shopCount; i++) 
    {
    	// ��ȡ������Ϣ
    	ShopNode *sNode = (ShopNode*)malloc(sizeof(ShopNode));
    	fscanf(fp, "%d%s%d%d", &sNode->shopId, sNode->shopName, &sNode->shopCredit, &sNode->wareCount);
    	sNode->next = NULL;
    	sNode->wareList = (WareNode*)malloc(sizeof(WareNode));
    	sNode->wareList->next = NULL;
    	sNode->wareList->pre = NULL;
    	
    	// ��ȡ������Ʒ��Ϣ 
    	WareNode *wLast = sNode->wareList;	// ָ����Ʒ�������һ������ָ�� 
    	for (int j=0; j<sNode->wareCount; j++) 
    	{
    		WareNode *wNode = (WareNode*)malloc(sizeof(WareNode));
    		fscanf(fp, "%s%d%d", wNode->wareName, &wNode->price, &wNode->sales);
    		wNode->shopId = sNode->shopId;
    		wNode->next = NULL;
    		wLast->next = wNode;
    		wNode->pre = wLast;
    		wLast = wNode;
		}
		
		// ��lastָ���½�� 
		sNode->next = NULL; 
		sLast->next = sNode;
		sLast = sNode;
	}
	fileClose();
	
	//ShowShopList();
	
	// ��ʼ����ϣ�� 
	for (int i=0; i<10000; i++) 
	{
		hash[i].flag = false;
		hash[i].sales = 0;
	}
	// ��������������ʼ��ÿ����Ʒ������ 
	ShopNode *sNode = sList->next;
	while (sNode) 
	{
		// �����õ��̵���Ʒ���� 
		WareNode *wNode = sNode->wareList->next;
		while (wNode) 
		{
			int pos = Hash(wNode->wareName);
			hash[pos].sales += wNode->sales; 
			wNode = wNode->next;
		}
		sNode = sNode->next;
	} 
}

// ��ʼ��Ҫ��ѯ��Ʒ��˫������
void InitWareList() 
{
	wList = (WareNode*)malloc(sizeof(WareNode));
	wList->next = NULL;
	wList->pre = NULL;
}

// ������Ʒ����
void DestroyWareList(WareList &wList) 
{
	WareNode *wNode = wList;
	while (wNode) 
	{
		WareNode *temp = wNode->next;
		free(wNode);
		wNode = temp;
	}
	printf("������Ʒ����ɹ�\n");
}

// �����������ݴ�ص��ļ��� 
void Finish() 
{
	// ���ٵ�������ͬʱ�����ݴ�ص��ļ��� 
	fileOpen("w+");
	ShopNode *sNode = sList->next;
	free(sList);	// freeͷָ��
	fprintf(fp, "%d\n", shopCount);
	while (sNode) 
	{
		//ShowShopInfo(sNode);
		ShopNode *temp = sNode->next;
		// ���������Ϣ���ļ� 
    	fprintf(fp, "%d   %s   %d   %d\n", sNode->shopId, sNode->shopName, sNode->shopCredit, sNode->wareCount);
    	// ���������Ʒ���ļ� 
		WareNode *wNode = sNode->wareList->next; 
		while (wNode) 
		{
    		fprintf(fp, "   %s   %d   %d\n", wNode->wareName, wNode->price, wNode->sales);
    		wNode = wNode->next;
		}
		// ���ٸõ��̵���Ʒ���� 
		DestroyWareList(sNode->wareList);
		// free���̽�� 
		free(sNode);
		sNode = temp;
	}
	fileClose();
	//printf("���ٵ�������ɹ�\n");
}
 
// ���ӵ���
void AddShop(ShopNode *shopNode) 
{
	shopCount++;
	
	// �ҵ����һ�� 
	ShopNode *sNode = sList;
	while (sNode->next) 
	{
		sNode = sNode->next;
	}
	sNode->next = shopNode;
	
	shopNode->shopId = sNode->shopId + 1;
	shopNode->wareCount = 0;
	shopNode->wareList = (WareNode*)malloc(sizeof(WareNode));
	shopNode->wareList->next = NULL;
	shopNode->next = NULL;
	
	printf("���ӵ��̳ɹ�\n");
}

// ɾ������
void DeleteShop(int shopId) 
{
	ShopNode *sNode = sList->next, *sNPre = sList;
	bool isFind = false;
	while (sNode) 
	{
		if (sNode->shopId == shopId) 
		{
			ShowShopInfo(sNode);
			DestroyWareList(sNode->wareList);
			sNPre->next = sNode->next;
			free(sNode);
			
			// ʹ�ñ�ɾ�����̵ĺ�����̵ı�Ŷ���һ 
			sNode = sNPre->next;
			while (sNode) 
			{
				sNode->shopId--;
				// ��Ӧ��Ʒ�����̱��ҲҪ-- 
				WareNode *wNode = sNode->wareList->next;
				while (wNode) 
				{
					wNode->shopId--;
					wNode = wNode->next;
				}
				sNode = sNode->next;
			}
			
			isFind = true;
			break;
		}
		else 
		{
			sNPre = sNode;
			sNode = sNPre->next;
		} 
	}
	if (!isFind) 
	{
		printf("delete shop fail, no this shop, shopId is %d\n", shopId);
	}
	shopCount--;
} 

// ���ӵ�����Ʒ
void AddShopWare(int shopId, WareNode *wNode) 
{
	ShopNode *shop = FindShop(shopId);
	shop->wareCount++;
	
	WareNode *ware = shop->wareList;
	while (ware->next) 
	{
		if (strcmp(ware->wareName, wNode->wareName) == 0) 
		{
			ShowWareInfo(ware);
			printf("����Ʒ�Ѵ���\n");
			return;
		}
		ware = ware->next;
	}

	ware->next = wNode;
	wNode->shopId = shopId;
	wNode->pre = ware;
	wNode->next = NULL;
} 

// ɾ��������Ʒ
void DeleteShopWare(int shopId, char *wareName) 
{
	ShopNode *shop = FindShop(shopId);
	WareNode *ware = shop->wareList->next, *preWare = shop->wareList; 
	
	bool isFind = false; 
	while (ware) 
	{
		if (strcmp(ware->wareName, wareName) == 0) 
		{
			ShowWareInfo(ware);
			preWare->next = ware->next;
			free(ware);
			ware = preWare->next;
			shop->wareCount--;
			isFind = true;
			break;
		}
		else 
		{
			preWare = ware;
			ware = ware->next;
		}
	}
	
	if (!isFind) printf("delete fail, no this ware, ware name is %s", wareName);
}

// ��ʼ������ʾҪ��ѯ��Ʒ��˫������ 
void ShowWareList(char *wareName) 
{
	// ������������ 
	ShopNode *sNode = sList->next;
	while (sNode) 
	{
		// �����õ��̵���Ʒ���� 
		WareNode *wNode = sNode->wareList->next;
		while (wNode) 
		{
			// �������Ʒ��Ҫ��ѯ����Ʒ 
			if (strcmp(wNode->wareName, wareName) == 0) 
			{
				// �����½�㣬����Ҫ������Ʒ�����Ϣ���Ƶ����� 
				WareNode *newWare = (WareNode*)malloc(sizeof(WareNode));
				newWare->shopId = wNode->shopId;
				strcpy(newWare->wareName, wNode->wareName);
				newWare->sales = wNode->sales;
				newWare->price = wNode->price;
				
				// �������ź������Ʒ���� 
				WareNode *ware = wList->next, *preWare = wList;	// ���ź���Ľ�� 
				while (ware) 
				{
					ShopNode *temp = FindShop(newWare->shopId);	// Ҫ����Ľ�� 
					ShopNode *tempCmp = FindShop(ware->shopId);	// �Ѿ��ź���������еĽ�� 
					// ��������������ȸ����ǰ 
					if ((temp->shopCredit > tempCmp->shopCredit)
						|| (temp->shopCredit == tempCmp->shopCredit && ware->sales > wNode->sales)) break;
					preWare = preWare->next;
					ware = ware->next;
				}
				// ���� 
				newWare->next = ware;
				if (ware) ware->pre = newWare;
				preWare->next = newWare;
				newWare->pre = preWare;
				break; 
			}
			wNode = wNode->next;
		}
		sNode = sNode->next;
	}
	
	printf("****************%s******************\n", wareName);
	WareNode *ware = wList->next;
	while (ware) 
	{
		ShowWareInfo(ware);
		ware = ware->next;
	}
	printf("***********************************\n");
} 

// ��ʾѡ��
void choose() 
{
	system("cls");
	printf("\n|---------------------------|\n");
	printf("|0.�˳�                     |\n");
	printf("|1.���ӵ���                 |\n");
	printf("|2.ɾ������                 |\n");
	printf("|3.��ʾ���е���             |\n");
	printf("|4.���ӵ�����Ʒ             |\n");
	printf("|5.ɾ��������Ʒ             |\n");
	printf("|6.��ѯ��Ʒ                 |\n");
	printf("|7.������Ʒ                 |\n");
	printf("|8.��ʾÿ����Ʒ������       |\n");
	printf("|---------------------------|\n");
	printf("\n���������ѡ��(1-8):\n");
}


int main() 
{
	Init();
	
	int n = 0;
	choose();
	scanf("%d", &n);
	while (n) 
	{
		if (0 >= n || n > 8) 
		{
			printf("error! try again\n");
			printf("\n���������ѡ��(1-8):\n");
			scanf("%d", &n);
			continue;
		}
		char wareName[100];
		int shopId = 0;
		switch (n) 
		{
			// ���ӵ��� 
			case 1: 
			{
				ShopNode *sNode = (ShopNode*)malloc(sizeof(sNode)); 
				printf("��������Ҫ���ӵĵ�����Ϣ����������������͵��������ȣ�\n");
				scanf("%s%d", sNode->shopName, &sNode->shopCredit);
				AddShop(sNode);
				break;
			}
			// ɾ������ 
			case 2: 
			{
				printf("��������Ҫɾ���ĵ��̱�ţ�\n");
				scanf("%d", &shopId);
				DeleteShop(shopId);
				break;
			}
			// ��ʾ���е���
			case 3: 
			{
				ShowShopList();
				break;
			} 
			// ���ӵ�����Ʒ
			case 4: 
			{
				WareNode *wNode = (WareNode*)malloc(sizeof(WareNode));
				printf("��������Ҫ���ӵ�����Ʒ�ĵ��̱�ţ�\n");
				scanf("%d", &shopId);
				printf("������Ҫ������Ʒ����Ϣ�������������Ʒ�����۸�������\n");
				scanf("%s%d%d", wNode->wareName, &wNode->price, &wNode->sales);
				AddShopWare(shopId, wNode);
				// ����Ʒ���������� 
				hash[Hash(wareName)].sales += wNode->sales;
				break;
			}
			// ɾ��������Ʒ
			case 5: 
			{
				printf("��������Ҫɾ��������Ʒ�ĵ��̱�ţ�\n");
				scanf("%d", &shopId);
				printf("������Ҫɾ����Ʒ�����֣�\n");
				scanf("%s", wareName);
				DeleteShopWare(shopId, wareName); 
				break;
			}
			// ��ѯ��Ʒ
			case 6: 
			{
				printf("��������Ҫ��ѯ��Ʒ�����֣�\n");
				scanf("%s", wareName);
				InitWareList(); 
				ShowWareList(wareName);
				DestroyWareList(wList);	// ���ٸ���Ʒ��˫������ 
				break;
			}
			// ������Ʒ
			case 7: 
			{
				printf("��������Ҫ�������Ʒ�����ֺ͵��̵ı�ţ�\n");
				scanf("%s%d", wareName, &shopId);
				ShopNode *shop = FindShop(shopId);
				
				// �޸ĸõ��̶�Ӧ��Ʒ�������������õ��̵���Ʒ���� 
				WareNode *ware = shop->wareList->next;
				while (ware) 
				{
					// �������Ʒ��Ҫ��ѯ����Ʒ 
					if (strcmp(ware->wareName, wareName) == 0) 
					{
						ware->sales++;
					}
					ware = ware->next;
				}
				
				// ����Ʒ��������һ 
				hash[Hash(wareName)].sales++;
				break;
			}
			// ��ʾÿ����Ʒ������
			case 8: 
			{
				printf("��������Ҫ��ѯ��Ʒ��������Ʒ����\n");
				scanf("%s", wareName);
				int pos = Hash(wareName);
				//cout<<pos<<endl;
				printf("����Ʒ����Ϊ��%d\n", hash[pos].sales);
				break;
			}
		}
		printf("\n\n\n>>>>>>>>>>>>>>>>>>>>>��Ҫ�������˵���(1�ǵ�/0�˳�)��");
		scanf("%d", &n);
		while (n != 0 && n != 1) 
		{
			printf("sorry, try again.\n");
			printf("\n>>>>>>>>>>>>>>>>>>>>>��Ҫ�������˵���(1�ǵ�/0�˳�)��");
			scanf("%d", &n);
		}
		if (n == 0) break; 
		
		choose();
		scanf("%d", &n);
	}
	printf("\nBye~\n");
	
	Finish(); 
}
