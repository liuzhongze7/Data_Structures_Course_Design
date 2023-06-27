#ifndef BMT_H_
#define BMT_H_


#include<iostream>
#include<cstdlib>
using namespace std;
#define m 3


typedef int KeyType;

typedef struct BMTNode {
    int keynum;
    BMTNode * parent;

    KeyType   key[m + 1];
    BMTNode * ptr[m + 1];

    BMTNode() : keynum(0), parent(NULL) {
        for (int i = 0; i <= m; ++i) {
            key[i] = 0;
            ptr[i] = NULL;
        }//endfor
    }//endctor
}*BMT;
typedef struct Node{
    int keynum;  //�ؼ��ֵ�����
    Node * parent;  //���׽��
    KeyType key[m + 1]; //��¼�ؼ��֣�����0�ŵ�Ԫ����
    Node *  ptr[m + 1]; //��¼���ӽ���ָ��
    Node() :keynum(0), parent(NULL) {
        for (int i = 0; i <= m; i++)
        {
            key[i] = 0;
            ptr[i] = NULL;
        }//endfor
    }//endcontruct
}Node;
class BTree {
private:
    Node * head;
    int search(Node *& T, KeyType K); //���ҹؼ���
    void insert(Node * & T, int i, KeyType K, Node * rhs); //����ؼ��ֵ�λ��
    bool split(Node *& T, int s, Node * & rhs, KeyType & midK); //������
    bool newroot(Node * & T, Node * & lhs, KeyType midK, Node * & rhs);
    void RotateLeft(Node * parent, int idx, Node * cur, Node * rsilb);
    void RotateRight(Node * parent, int idx, Node * cur, Node * lsilb);
    void Merge(Node * parent, int idx, Node * lsilb, Node * cur);
    void DeleteBalance(Node * curNode);
    void Delete(Node * curNode, int curIdx);
public:
    BTree();
    Node * gethead();
    bool searchKey_BTree(KeyType K, Node * & recNode, int & recIdx);
    bool insert_BTree(KeyType k);
    bool Delete_BTree(KeyType K);
    void Destroy(Node * & T);
    void WalkThrough(Node * & T);

};


#endif /* BMT_H_ */
