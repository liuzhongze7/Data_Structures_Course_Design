#include<iostream>
using namespace std;
#include<fstream>
#define m 3
typedef int KeyType;
typedef struct BTNode{
	int keynum;
	struct BTNode *parent;//ָ��˫�׽��
	KeyType key[m+1];//�ؼ�������������0�ŵ�Ԫ
	struct BTNode *ptr[m+1];//����ָ������ 	
}BTNode,*BTree;
typedef struct {
	BTNode *pt;//ָ���ҵ��Ľ�� 
	int i;//1...,m�ڽ���еĹؼ������ 
	int tag;//1.���ҳɹ���0.����ʧ�� 
}Result;
int BTreeSearch(BTree T,KeyType K,BTNode *curNode,int count){
	//��B���в���kֵ
	BTNode *p;
	if(T==NULL) return 0;//����������� 
	p=T;
	int flag=0,i=0;
	while(p!=NULL){
		flag=0;
		for(i=1;i<=p->keynum;i++){
			if(K==p->key[i]){
				curNode=p;
				count=i;
				return 1;//��ʾ�������ֵ�ҵ� 
			}
			
			if(K<p->key[i]){
				//�����ֵ��p,key[i]С����ǰ���������֮ǰ�µ�������ȥ
				p=p->ptr[i-1];
				flag=1;
				break;
			 
			}
		}
		if(K>p->key[i]&&flag==0){
			p=p->ptr[i-1];
		}
		
	}
	return 0; 
}//��������ʾ�Ƿ��ҵ��ý�� 
void Insert(BTree &T,KeyType K,BTree q,int i){
	//k��Ҫ�����ֵ��T��B����bTree 
	int j=0;
	for(j=T->keynum;j>=i+1;--j){
		T->key[j+1]=T->key[j];
		T->ptr[j+1]=T->ptr[j];//�ؼ��ֺ��ƣ������µĹؼ���	 
	}
	T->key[i+1]=K;
	T->ptr[i+1]=q;
	++T->keynum;//��ɲ��� 
}
bool BTreeSplit(BTree &T,int s,BTNode *rhs,KeyType &k){
	rhs=new BTNode;
	//rhsΪ�½��Ľ�㣬���ڱ����Ұ벿�ݵ�
	if(rhs==NULL){
		exit(0);
	} 
	//��t���з��ѣ�����rhs��t���ֵܽ�㣬����ͬ�ĸ�ĸ
	rhs->parent=T->parent;
	//���йؼ������е��м�ֵΪ
	k=T->key[s];
	T->key[s]=0;
	rhs->ptr[0]=T->ptr[s];
	//���ԭ����T��s�ź���ָ�룬����0��ָ�벻Ϊ�գ���Ҫ�ı亢�ӵĸ��׽ڵ�
	if(rhs->ptr[0]!=NULL){
		rhs->ptr[0]->parent=rhs; 
	}//endif;
	T->ptr[s]=NULL;
	for(int i=1;i<=m-s;++i){
		//���Ұ벿��ȫ�����Ƶ�rhs��
		rhs->key[i]=T->key[s+i];
		T->key[s+i]=0;
		rhs->ptr[i]=T->ptr[s+i];
		T->ptr[s+i]=NULL;
		//���ڸı�rhs�ĸ��׽��
		if(rhs->ptr[i]){
			rhs->ptr[i]->parent=rhs;
		}//endif 
	}//endfor
	rhs->keynum=m-s;
	T->keynum=s-1;
	return true; 
}
bool BTreeNewroot(BTree &T,BTree &lhs,KeyType midk,BTree &rhs){
	//����һ���µĽ��
	BTNode *temp=new BTNode;
	if(temp==NULL){
		exit(0);
	}
	temp->keynum=1;
	temp->key[1]=midk;
	
	temp->ptr[0]=lhs;
	//���Ӳ�Ϊ�յ�ʱ��
	if(temp->ptr[0]){
		temp->ptr[0]->parent=temp;
	}
	temp->ptr[1]=rhs;
	//�Һ��Ӳ�Ϊ�յ�ʱ��
	if(temp->ptr[1]){
		temp->ptr[1]->parent=temp;
	} 
	T=temp;
	return true;
} 
//����һ��kֵ 
bool BTreeInsert(KeyType k,BTree &T){
	BTNode *curNode=NULL;
	int preldx=0;
	if(BTreeSearch(T,k,curNode,preldx)){
		cout<<"�ؼ����Ѿ�����"<<endl;
		return false;
	}
	else{
		KeyType curkey=k;
		BTNode *rhs=NULL;
		bool finished=false;
		while(!finished&&curNode){
			Insert(curNode,curkey,rhs,preldx);
			if(curNode->keynum<m)
				finished=true;
			else{
				int s=(m+1)/2;
				if(BTreeSplit(curNode,preldx,rhs,curkey)){
					return false;
				}
				if(curNode->parent==NULL){
					//curNode ��Ϊ�����
					break; 
				}
				else{
					//����и��׽�㣬��ʱcurkeyָ��ԭ����������м�ֵ
					//������Ҫ�͸��׽���ں�
					curNode=curNode->parent;
					BTreeSearch(T,curkey,curNode,preldx); 
				}
			}
				
		}
	} 
}

void BTreeTraverse(BTree T){
	if(T){
		for(int i=0;i<T->keynum;i++){
			cout<<T->key[i]<<" ";
		}
		for(int i=0;i<T->keynum;i++)
			BTreeTraverse(T->ptr[i]);
	}
}
