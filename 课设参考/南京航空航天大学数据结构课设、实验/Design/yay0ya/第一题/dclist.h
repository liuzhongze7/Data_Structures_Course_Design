//����һ��˫��ѭ���б�������ݵĴ洢
#include"linklist.h"
typedef struct record{
	sNode store;//���ݽ�� 
	int sales;//�������� 
	struct record *pre;
	struct record *next;//preָ��ǰ����nextָ���� 
}record,*head;
bool createdclist(head &L){
//����һ��˫������
	head=new record;
	if(head==NULL)
	exit(0);
	head->next=head;
	head->pre=head;
	return 1;
}
bool insertlist(head &L,int id,string name,int credit,int sales){
	//����һ�������β��
	record *p,*s;
	s=new record;
	if(s==NULL)
	{
		cout<<"����ռ�ʧ��\n";
		return 0; 
	}
	p=L->pre;//pָ��β���
	s->store.id=id;
	s->store.name=name;
	s->store.credit=credit;//��ʱ�Ƚ�����Ʒ��Ϣ��������Ϣ�洢����������
	s->sales=sales;
	p->next=s;
	s->pre=p;
	s->next=L;//�� s �嵽β����Ժ� 
	return 1;//��ɲ������  
}
bool lineuplist(head &L,string name,Shop S){
	//�����ŶӲ������
	 sNode *p;
	 p=S;
	 goods goodp;//������Ʒָ�� 
	 while(p!=NULL){
	 	goodp=p->goods.data;
	 	for(int i=0;i<p->goods.numbers;i++){
	 		if(goodp.name==name){
	 			insertlist(L,p->id,p->name,p->credit,goodp.sold);
	 			//�������Ʒ���д�����Ҫ�������Ʒ
				  //����Ʒ���봴�����Ʒ����
			  
			 }
			 	p++; 
		 }
		 p=p->next;
	 }//�����а�������Ʒ�����̲��������У������˫������ 
} 
