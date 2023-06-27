#include<iostream>
using namespace std;
#include<fstream>
#include<stdlib.h>
#define m 3
typedef int KeyType;
typedef int Record;
typedef struct BTNode{
	int   keynum;//����йؼ��ָ����������Ĵ�С
	struct BTNode  *parent;		//ָ��˫�׽��
	KeyType  key[m+1];			//�ؼ���������0�ŵ�Ԫδ��
	struct BTNode *ptr[m+1];    //����ָ������
	Record   *recptr[m+1];		//��¼ָ��������0�ŵ�Ԫδ�� 
}BTNode,*BTree;					//B-������B-������
typedef struct {
	BTNode *pt;					//ָ���ҵ��Ľ��
	int      i;					//1...m�ڽ���еĹؼ������
	int    tag;					//1:���ҳɹ���0������ʧ�� 
}Result;						//B-���Ĳ��ҽ������
 
int Search(BTNode *p,KeyType K){
	for(int i=0;i<p->keynum-1;i++){
		if(p->key[i]==K){
			return i;//����ҵ���Kֵ��ͬ�Ĺؼ��������������� 
		}
		if(p->key[i]<K&&K<p->key[i+1])
			return i;//�ҵ�һ����㣬����ǰֵ��KС����ֵ��K��
		if(i+1==p->keynum&&K>p->key[i+1])//���K�����һ��ֵ��Ҫ��
				return i+1; 
	}
}

Result SearchBTree(BTree T,KeyType K){
	//��m��B-��T�ϲ��ҹؼ���K�����ؽ��(pt,i,tag)�������ҳɹ���������ֵ
	//tag=1��ָ��pt��ָ����е�i���ؼ��ֵ���K����������ֵtag=0������K�Ĺؼ���Ӧ
	//������ָ��pt��ָ�Ľڵ��е�i�͵�i+1���ؼ���֮��
	BTNode *p,*q;
	Result re;
	bool found=false;
	int i=0;
	p=T;q=NULL;				//��ʼ����pָ������ҽ�㣬qָ��p��˫��
	while(p!=NULL&&!found){
		i=Search(p,K);		//��p->key[1...keynum]�в��ң�
							//ʹ�ã�p->key[i]<=K<p->key[i+1]
		if(i>0&&p->key[i]==K) found=true;//�ҵ������ҹؼ���
		else {
			q=p;  p=p->ptr[i];
		}					 
	}//while
	if(found) {				//���ҳɹ� 
		re.pt=p;
		re.i=i;
		re.tag=1;
		return re;
	}
	else {				//���Ҳ��ɹ�������K�Ĳ���λ����Ϣ 
		re.pt=q;
		re.i=i;
		re.tag=0;
		return re;
	}
}

void Insert(BTree &q,int i,KeyType x,BTNode *ap){
	int j;
	for(j=q->keynum;j>i;j--){
		q->key[j+1]=q->key[j];//������ƣ�������ֵ�ճ�һ��λ�� 
		q->ptr[j+1]=q->ptr[j]; 
	}
	q->ptr[i+1]=ap;//��ptr[i+1]�������ָ��ָ��ap 
	q->key[i+1]=x;//��x���ֵ����key[i+1] 
	if(ap!=NULL){
		ap->parent=q;//��ap ��˫��ָ�룬ָ��q 
	}
	q->keynum++;//����һ��ֵ���ý���ϵ�ֵ��������
}

void split(BTree &q,int s,BTree &ap){
	//��q->key[s+1..m],q->ptr[s..m]��q->recptr[s+1..m]�����½��*ap
	int i;
	ap=new BTNode;//�����ap����ռ�
	ap->ptr[1]=q->ptr[s];//��qָ��ָ��ĺ�һ��ռ�����������q 
	for(i=1;s+i<=m;i++){
		ap->key[i]=q->key[s+i];//��q->key[s+1...m]���뵽 ap->key[1..m-s]��
		ap->recptr[i]=q->recptr[s+i];//��q->recptr[s+1..m]���뵽ap->[1..m-s]�� 
		ap->ptr[i-1]=q->ptr[s+i];
	}
	ap->keynum=q->keynum-s;
	ap->parent=q->parent;;//��q�м��keynumֵ��Ϊs�� 
	for(i=0;i<=q->keynum-s;i++){
		//�޸�ʣ��ָ���˫�׽��
		if(ap->ptr[i]!=NULL)
			ap->ptr[i]->parent=ap;
		q->keynum=s-1;			//���q�ڵ�keynumֵ�����ı�	 
	}
}

void NewRoot(BTree &T,BTNode *q,KeyType K,BTNode *ap){
	//	T�ǿ���(����q��ֵΪNULL)���߸�����ѷ���Ϊ���*q��*ap 
	// ���ɺ���Ϣ(T,x,ap)���µĸ����*T��ԭT��apΪ����ָ�� 
	T=new BTNode;
	T->keynum=1;
	T->ptr[0]=q;
	T->ptr[1]=ap;
	T->key[1]=K;
	if(q!=NULL){
		q->parent=T;
	}
	if(ap!=NULL)
		ap->parent=T;
	T->parent=NULL;
			
}//NewRoot

int InsertBTree(BTree &T,KeyType K,BTree q,int i){
	//��m��B-��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��
	//���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B-����
	KeyType x=K;
	BTNode *ap=NULL;
	int s;
	bool finished=false;
	if(T==NULL){
		NewRoot(T,NULL,K,NULL);
	}
	while(q!=NULL&&!finished){
		Insert(q,i,x,ap);   //��x��ap�ֱ���뵽q->key[i+1]��q->ptr[i+1]x��key[i]��һ��ֵ��q��BTree һ��ָ�룬ap�������ָ��
		if(q->keynum<m) finished=true;//������� 
		else {			//���ѽ��*q
		 	s=(m+1)/2;//s��m/2����ȡ���������ֵm�����������г��Զ���һ����
			 					//m��ż�����������Զ�
			split(q,s,ap);
			x=q->key[s];		//��q->key[s+1,..m],q->ptr[s...m]��q->recptr[s+1..m]�����½��*ap
			q=q->parent;
			if(q!=NULL) i=Search(q,x);		//��˫�׽��*q�в���x�Ĳ���λ��	 
	
		}//else
	}//while
	if(!finished)			//	T�ǿ���(����q��ֵΪNULL)���߸�����ѷ���Ϊ���*q��*ap 
		NewRoot(T,q,x,ap); 	// ���ɺ���Ϣ(T,x,ap)���µĸ����*T��ԭT��apΪ����ָ�� 
	return 1; 
}//InsertBTree
void  deletechild(BTNode *p,int i){
	int j;
	for(j=i+1;j<=p->keynum;j++){
		p->key[j-1]=p->key[j];
		p->ptr[j-1]=p->ptr[j];
	}
	p->keynum--;//ɾ��һ�����key[i],ͬʱɾ����֮��ص�ptr[i]��� 
}
void findsub(BTNode *p,int i){
	//Ѱ���ܹ�������һ�����ֵ
	BTNode *q;
	for(q=p->ptr[i];q->ptr[0]!=NULL;q=q->ptr[1]);
	p->key[i]=q->key[1];//���ƹؼ��� 
}

void Restore(BTree &T,BTree &p){
	BTNode *parent,*leftBrother,*rightBrother;//��ɾ���Ľ��ĸ��׽��������ֵ�
	parent=p->parent;
	if(parent!=NULL){
		//����㲻Ϊ�� 
	} 
}

void MoveRight(BTNode *p,int i){
/*��˫�׽��p�е����һ���ؼ��������ҽ��q��
������aq�е����һ���ؼ�������˫�׽��p��*/ 
    int j;
    BTNode *q=p->ptr[i];
    BTNode *aq=p->ptr[i-1];

    for(j=q->keynum;j>0;j--){                       //�����ֵ�q�����йؼ�������ƶ�һλ
        q->key[j+1]=q->key[j];
        q->ptr[j+1]=q->ptr[j];
    }

    q->ptr[1]=q->ptr[0];                            //��˫�׽��p�ƶ��ؼ��ֵ����ֵ�q��
    q->key[1]=p->key[i];
    q->keynum++;

    p->key[i]=aq->key[aq->keynum];                  //�����ֵ�aq�����һ���ؼ����ƶ���˫�׽��p��
    p->ptr[i]->ptr[0]=aq->ptr[aq->keynum];
    aq->keynum--;
}


void MoveLeft(BTNode *p,int i){
/*��˫�׽��p�еĵ�һ���ؼ�����������aq�У�
���ҽ��q�еĵ�һ���ؼ�������˫�׽��p��*/ 
    int j;
    BTNode *aq=p->ptr[i-1];
    BTNode *q=p->ptr[i];

    aq->keynum++;                                   //��˫�׽��p�еĹؼ����ƶ������ֵ�aq��
    aq->key[aq->keynum]=p->key[i]; 
    aq->ptr[aq->keynum]=p->ptr[i]->ptr[0];

    p->key[i]=q->key[1];                            //�����ֵ�q�еĹؼ����ƶ���˫�׽ڵ�p��
    q->ptr[0]=q->ptr[1];
    q->keynum--;

    for(j=1;j<=aq->keynum;j++){                     //�����ֵ�q�����йؼ�����ǰ�ƶ�һλ
        aq->key[j]=aq->key[j+1];
        aq->ptr[j]=aq->ptr[j+1];
    }
}


void Combine(BTNode *p,int i){
/*��˫�׽��p���ҽ��q�ϲ�������aq��
������˫�׽��p�е�ʣ��ؼ��ֵ�λ��*/ 
    int j;
    BTNode *q=p->ptr[i];                            
    BTNode *aq=p->ptr[i-1];

    aq->keynum++;                                  //��˫�׽��Ĺؼ���p->key[i]���뵽����aq     
    aq->key[aq->keynum]=p->key[i];
    aq->ptr[aq->keynum]=q->ptr[0];

    for(j=1;j<=q->keynum;j++){                      //���ҽ��q�е����йؼ��ֲ��뵽����aq 
        aq->keynum++;
        aq->key[aq->keynum]=q->key[j];
        aq->ptr[aq->keynum]=q->ptr[j];
    }

    for(j=i;j<p->keynum;j++){                       //��˫�׽��p�е�p->key[i]������йؼ�����ǰ�ƶ�һλ 
        p->key[j]=p->key[j+1];
        p->ptr[j]=p->ptr[j+1];
    }
    p->keynum--;                                    //�޸�˫�׽��p��keynumֵ 
    free(q);                                        //�ͷſ��ҽ��q�Ŀռ�
}


void AdjustBTree(BTNode *p,int i){
//ɾ�����p�еĵ�i���ؼ��ֺ�,����B��
    int Min=(m-1)/2;
	if(i==0)                                        //ɾ����������߹ؼ���
        if(p->ptr[1]->keynum>Min)                   //�ҽ����Խ�
            MoveLeft(p,1);
        else                                        //���ֵܲ����� 
            Combine(p,1);
    else if(i==p->keynum)                           //ɾ���������ұ߹ؼ���
        if(p->ptr[i-1]->keynum>Min)                 //������Խ� 
            MoveRight(p,i);
        else                                        //���㲻���� 
            Combine(p,i);
    else if(p->ptr[i-1]->keynum>Min)                //ɾ���ؼ������в������㹻�� 
        MoveRight(p,i);
    else if(p->ptr[i+1]->keynum>Min)                //ɾ���ؼ������в����ҽ�㹻�� 
        MoveLeft(p,i+1);
    else                                            //ɾ���ؼ������в������ҽ�㶼������
        Combine(p,i);
}


int FindBTNode(BTNode *p,KeyType k,int &i){
//��ӳ�Ƿ��ڽ��p���Ƿ���ҵ��ؼ���k 
    if(k<p->key[1]){                                //���p�в��ҹؼ���kʧ�� 
        i=0;
        return 0;
    }
    else{                                           //��p����в���
        i=p->keynum;
        while(k<p->key[i]&&i>1)
            i--;
        if(k==p->key[i])                            //���p�в��ҹؼ���k�ɹ� 
            return 1;
    }
}


int BTNodeDelete(BTNode *p,KeyType k){
//�ڽ��p�в��Ҳ�ɾ���ؼ���k
	int Min=(m-1)/2;
    int i;
    int found_tag;                                  //���ұ�־ 
    if(p==NULL)                                     
        return 0;
    else{
        found_tag=FindBTNode(p,k,i);                //���ز��ҽ�� 
        if(found_tag==1){                           //���ҳɹ� 
            if(p->ptr[i-1]!=NULL){                  //ɾ�����Ƿ�Ҷ�ӽ��
                findsub(p,i);                  //Ѱ�����ڹؼ���(����������С�Ĺؼ���) 
                BTNodeDelete(p->ptr[i],p->key[i]);  //ִ��ɾ������ 
            }
            else
                deletechild(p,i);                        //�ӽ��p��λ��i��ɾ���ؼ���
        }
        else
            found_tag=BTNodeDelete(p->ptr[i],k);    //�غ��ӽ��ݹ���Ҳ�ɾ���ؼ���k
        if(p->ptr[i]!=NULL)
            if(p->ptr[i]->keynum<Min)               //ɾ����ؼ��ָ���С��MIN
                AdjustBTree(p,i);                   //����B�� 
        return found_tag;
    }
}

void BTreeDelete(BTree &t,KeyType k){
//����ɾ����ܣ�ִ��ɾ������  
    BTNode *p;
    int a=BTNodeDelete(t,k);                        //ɾ���ؼ���k 
    if(a==0)                                        //����ʧ�� 
        cout<<"�����ڸô�\n"<<endl; 
    else if(t->keynum==0){                          //���� 
        p=t;
        t=t->ptr[0];
        free(p);
    }
}

void DestroyBTree(BTree &t){
    int i;  
    BTNode* p=t;  
    if(p!=NULL){                                    //B����Ϊ��  
        for(i=0;i<=p->keynum;i++){                  //�ݹ��ͷ�ÿһ����� 
            DestroyBTree(*&p->ptr[i]);  
        }  
        free(p);  
    }  
    t=NULL;  
}  
void BTreeTraverse(BTree T){
	if(T){
		for(int i=1;i<=T->keynum;i++){
			cout<<T->key[i]<<" ";
		}
		for(int i=0;i<=T->keynum;i++)
			BTreeTraverse(T->ptr[i]);
	}
}
