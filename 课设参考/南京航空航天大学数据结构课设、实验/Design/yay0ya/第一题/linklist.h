#include"goods.h"
#define Max 50 
#define Inscrent 10 
typedef goodlink SElemType;
typedef struct shop{
	int id;
	string name;
	int credit;
	SElemType goods;
	struct shop *next;//ָ��ָ����һ������ 
}sNode,*Shop;
bool Initlinklist(Shop &S){
	sNode *p,*head;
	head=NULL; 
	for(int i=0;i<Max;i++){
		p=new sNode;
		p->next=head;
		head=p;
	}
	S=head;
	return 1;//����max�����
}
bool goodfilein(sNode *p,fstream &file){
	int n=p->goods.numbers;//����¼��Ʒ������
	goods *goodp;//��Ʒָ��
	goodp=p->goods.data;//���ָ����Ʒ�ĵ�һ��ֵ 
	file<<n;//������Ʒ������ 
	for(int i=0;i<n;i++){
		file<<goodp->name;//���ļ���������Ʒ������
		file<<goodp->price;//������Ʒ�ļ۸�
		file<<goodp->sold;//������Ʒ������ 
	}//���һ������������¸�������Ʒ���� 
	return 1; 
}
bool goodfileout(sNode *p,fstream f){
	int n;
	f>>n;//������Ʒ������
	goods *goodp;
	goodp=p->goods.data;//����ָ��ָ�����p����Ʒ���������� 
	p->goods.data=new goods[n];//Ϊ��Ʒ��goods�Ľ������n���ռ�
	p->goods.numbers=n;//����Ʒ��������ֵ��p����е�����
	for(int i=0;i<n;i++){
		file>>goodp.name;
		file>>goodp.price;
		file>>goodp.sold;
		goodp++;//����ļ��е�������������̶��� 
	}
	return 1; 
}
bool filein(Shop S){
	fstream file("data.txt",ios::in);
	if(!file.is_open()){
		cout<<"�ļ���ʧ��\n";
		return 0;
	}
	sNode *p=S;//��p����Ϊ 
	while(p!=NULL){
		file<<p->name;
		file<<p->credit;
		goodfilein(p,file);//����Ʒ����Ϣд���ļ� 
		p=p->next;
	}//������������д���ļ�
	file.close();
	return 1; 
}
bool createlinklist(Shop &S){
	fstream file;
	file.open("data.txt",ios::in|ios::out);//����������ķ�ʽ��һ���ļ�
	sNode *p;
	p=S;
	if(!file,is_open())
		{
			cout<<"file open ERROR\n";
			exit(0);
		}//����ļ���ʧ��
	for(int i=0;i<Max;i++){
		p->id=i+1;
		if(!file.eof())
			break;
		file>>p->name;
		file>>p->credit; 
		p=p->next;//�����е�id���� ���� 
	}
	file.close();
	return 1;	 
}
bool AddOneShop(Shop &S){
	sNode *p;
	p=S;
	if(p==NULL){
	//�������S��������в������κε�������Ϣ
		p=new sNode;
		p->id=1;
		cout<<"�������̵�����\n";
		cin>>p->name;
		cout<<"�������̵�����\n";
		cin>>p->credit;
		p->next=S;
		S=p;	
	}
	else{
		while(p->next!=NULL){
			p=p->next;
			}
		sNode q;
		p->next=q;
		q.next=NULL;
		q.id=p->id+1;
		cout<<"�������̵�����\n";
		cin>>q.name;
		cout<<"�������̵�����\n";
		cin>>q.credit;
		}	
		if(!filein(S)){
			cout<<"�ļ�д��ʧ��\n";
			return 0;
		}
		return 1;

}//AddOneShop

bool DeleteOneShop(Shop &S,int id){
	sNode *p,*q;
	q=S;
	p=S;
	while(p!=NULL){
		if(p->id==id)
			break;
		q=p;	
		p=p->next;
	}
	if(p==NULL){
		cout<<"�����ڴ�����\n";
		return 0;
	}
	if(q==p){
		//�ж��������Ƿ���ͷ���
		q=p->next;//�����ͷ��㣬��ɾ��ͷ��
		S=q;
		free(p);//�ͷŽ��ռ� 
	}
	else{//����ͷ��� 
		q->next=p->next;//��������ɾ��
		free(p);//�ͷ�p������ 
	}
	p=S;
	int count=1;
	while(p!=NULL){
		p->id=count;
		count++;
		p=p->next;//����Ϊ���̵�id��ֵ 
	}
	//������������д���ļ� 
	if(!filein(S)){
			cout<<"�ļ�д��ʧ��\n";
			return 0;
	}
		return 1;
}
bool deletegoods(Shop &S,int number,string name)
//SΪ���̵�����ͨ�����number��λ���̵�λ�ã�stringƥ�䣬�ҵ���Ҫɾ������Ʒ
{
	sNode *p;
	int count=0; 
	p=S;
	if(S==NULL){
		cout<<"û�����̴���\n";
		return 0;//�����˳� 
	}
	while(p!=NULL){//ָ�벻Ϊ�� 
		if(p->id==number)//���p��ָ������id����Ҫ��
		{
			break;
		 }
		 p=p->next;
		 count++; 
	}
	if(number<1||number>count&&p==NULL){
		cout<<"������idΪ"<<number<<"������\n";
		return 0;//�˳� 
	}
	goods *goodp,*goodq;
	if(p->id==number)//���̵ĵ���id��numberƥ��
	{
		count=0;
		goodp=p->goods.data;//goodpָ��ָ��goods������ 
		for(int i=0;i<p->goods.numbers;i++)//��������Ԫ��С�������д��ڵ�Ԫ��ʱ
		{
			if(goodp.name==name)//��Ʒ�����������д��ڵ���Ʒ������ƥ��
			{
				free(goodp);//������ռ�Ķ����ͷ� 
				break;//
			 }
			 count++; 
		 }
		 if(count==p->goods.numbers){
		 	cout<<"���޴���Ʒ\n";
		 	return 0;//���� 
		 }
		 
	 }//���ɾ������
	 //���ļ����½���д��
	 filein(S);
	 return 1;//���ɾ������ 
 }
bool addgoods(Shop &S,int number){
		sNode *p;
	int count=0; 
	p=S;
	if(S==NULL){
		cout<<"û�����̴���\n";
		return 0;//�����˳� 
	}
	while(p!=NULL){//ָ�벻Ϊ�� 
		if(p->id==number)//���p��ָ������id����Ҫ��
		{
			break;
		 }
		 p=p->next;
		 count++; 
	}
	if(number<1||number>count&&p==NULL){
		cout<<"������idΪ"<<number<<"������\n";
		return 0;//�˳� 
	}
	//������̵Ĳ��ҹ������澡�Ĳ�����Ʒ�Ĳ���
	goods *goodp;
	if(p->id==number)//�������id��Ҫ���ҵ�id��ͬ
	{
		goodp=p->goods.data;
		goodp=(goods*)realloc((p->goods.numbers+1)*goods);
		for(int i=0;i<p->goods.numbers;i++){
			goodp++;
		}
		cout<<"��������Ʒ������\n";
		cin>>goodp->name;
		cout<<"��������Ʒ�ļ۸�\n";
		cin>>goodp->price;
		cout<<"��������Ʒ����������\n";
		cin>>goodp->sold;
		filein(S);//���������Ʒ�Ĳ���; 
	 }
	 return 1; 
}

