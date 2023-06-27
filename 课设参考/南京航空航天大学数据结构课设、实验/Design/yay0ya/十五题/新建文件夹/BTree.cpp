#include"BTree.h"
BTree::BTree() {
    this->head = NULL;
}
//����У����ҹؼ������У��Ƿ����k��˽�з���
int BTree::search(Node * & t,KeyType k) {
    int i = 0;
    for (int j = 1; j <= t->keynum; ++j) {
        if (t->key[j] <= k) {
            i = j;
        }
    }
    return i;
}

//���������������Ҷ�Ӧ�Ĺؼ��֣����з�����
bool BTree::searchKey_BTree(KeyType k, Node * & recNode, int & recIdx) {
    if (!head) {
        //cerr << "��Ϊ��" << endl;
        return false;
    }
    Node * p = head;
    Node * q = NULL;
    bool found = false;
    int i=0;
    while (p && !found) {
        i = this->search(p, k); //��סi���������������һ�����ҵ���Ӧ�Ĺؼ���
        //�ڶ������ҵ������һ��С��k�Ĺؼ����±꣨��Ҫ���������ʱ��
        if (i > 0 && p->key[i] == k) {
            //�ҵ��˼�¼���ͽ���йؼ��ֵ��±�
            recIdx = i;
            recNode = p;
            return true;
        }//endif
        else {
            recNode = p;         // ��¼p��ֵ�����㷵��
            recIdx = i;
            p = p->ptr[recIdx]; // ������һ����㣬
        }//endelse

    }//endw
    return false;
}
//�����ڽ��Ĺؼ��������У�����һ�����ؼ��֣�˽�з���
void BTree::insert(Node * & t, int i, KeyType k, Node * rhs) {
    //������Ҫ�ѹؼ������������ƶ���Ȼ������µĹؼ���
    for (int j = t->keynum; j >= i + 1; --j) {
        t->key[j + 1] = t->key[j];
        t->ptr[j + 1] = t->ptr[j];
    }
    //�����µĹؼ���
    t->key[i + 1] = k;
    t->ptr[i + 1] = rhs;
    ++t->keynum;
}

//�Զ�Ӧ�Ľ����з��Ѵ���,��t�����з��Ѵ���˽�з���
bool BTree::split(Node * & t, int s, Node * & rhs, KeyType & midk) {
    rhs = new Node;
    //rhsΪ�½��Ľ�㣬���ڱ����Ұ벿�ֵġ�
    if (!rhs) {
        exit(0);
        return false;
    }
    //�����ǰ�t���ѵģ�����rhs��t���ֵܽ�㣬����ͬ�ĸ�ĸ
    rhs->parent = t->parent;

    //���йؼ������е��м�ֵΪ
    midk = t->key[s];
    t->key[s] = 0;
    //���ͨ����ͼ���Ϳ���֪��rhs��0�ź��ӵ�ָ�룬����t��s�Ž��ָ��
    rhs->ptr[0] = t->ptr[s];

    //���ԭ����t��s�ź���ָ�룬���ڵ�rhs��0�ź���ָ�벻Ϊ�գ�����Ҫ�ı亢�ӵĵĸ��׽��
    if (rhs->ptr[0]) {
        rhs->ptr[0]->parent = rhs;
    }//endif
    t->ptr[s] = NULL;
    for (int i = 1; i <= m - s; ++i) {
        //�����ǰ��Ұ벿��ȫ�����Ƶ���rhs��
        rhs->key[i] = t->key[s + i]; t->key[s + i] = 0;
        rhs->ptr[i] = t->ptr[s + i]; t->ptr[s + i] = NULL;
        //���ɺ͸ղŵ�����һ��
        if (rhs->ptr[i]) {
            rhs->ptr[i]->parent = rhs;
        }//endif
    }//endfor
    rhs->keynum = m - s;
    t->keynum = s - 1;
    return true;
}
//�½�һ���µĽ�㣬˽�з���
bool BTree::newroot(Node * & t, Node * & lhs, KeyType midk, Node * & rhs) {
    Node * temp = new Node;
    if (!temp) {
        exit(0);
        return false;
    }
    temp->keynum = 1;
    temp->key[1] = midk;

    temp->ptr[0] = lhs;
    //���Ӳ�Ϊ��
    if (temp->ptr[0]) {
        temp->ptr[0]->parent = temp;
    }
    temp->ptr[1] = rhs;
    //�Һ��Ӳ�Ϊ��
    if (temp->ptr[1]) {
        temp->ptr[1]->parent = temp;
    }
    t = temp;
    return true;

}
//����һ��k��public������
bool BTree::insert_BTree(KeyType k) {
    Node * curNode = NULL;
    int preIdx = 0;
    if (this->searchKey_BTree(k, curNode, preIdx)) {
        cout << "�ؼ��Ѿ�����" << endl;
        return false;
    }
    else {
        //û���ҵ��ؼ���
        KeyType curk = k;
        Node * rhs = NULL;
        bool finished = false;
        while (!finished && curNode) {
            //�����Ƿ�Ϸ���ֱ���Ȳ���ղ��ҵ����Ǹ��ؼ���������
            this->insert(curNode, preIdx, curk, rhs);
            if (curNode->keynum < m) {//����������ֱ���˳�
                finished = true;
            }
            else {
                int s = (m + 1) / 2;  //sΪ�м�ֵ���±�
                if (!this->split(curNode, s, rhs, curk)) {
                    //����ʧ�ܣ�ֱ�ӷ���
                    return false;
                }
                if (curNode->parent == NULL) {
                    //���curNode�Ѿ��Ǹ��ڵ��ˣ������ֱ���˳���
                    break;
                }
                else {
                    //������Ǹ����׽��Ļ�����ʱcurkָ�����ԭ���������м�ֵ
                    //������Ҫ�͸��׽���ں�
                    curNode = curNode->parent;
                    preIdx = this->search(curNode, curk);
                }
            }
        }
        //���headΪ���������߸�����Ѿ�����Ϊ���curNode��rhs�ˣ���ʱ�ǿ϶�����
        //�������
        if (!finished && !this->newroot(head, curNode, curk, rhs)) {
            cerr << "failed to create new root" << endl;
            exit(EXIT_FAILURE);
        }
    }
}

//ɾ�����k���ҵ����ʵĽ�㣨public������
bool BTree::Delete_BTree(KeyType k) {
    Node * curNode = NULL;
    int curIdx = 0;
    if (this->searchKey_BTree(k, curNode, curIdx)) {
        this->Delete(curNode, curIdx);
        return true;
    }
    else {
        return false;
    }
}

//ɾ����Ӧ�Ľ����㣬ȥɾ���ؼ���
void BTree::Delete(Node * curNode, int curIdx) {
    //curIdx���Ϸ���ʱ��ֱ�ӷ���
    if (curIdx<0 || curIdx>curNode->keynum) {
        return;
    }
    while (true) {//����Ĳ��費�Ǻ����������������
        //��ʱ˵�������Ǵ��ڷ�Ҷ�ӽ��
        if (curNode->ptr[curIdx - 1] && curNode->ptr[curIdx]) {

            //ʹ������������С�Ĺؼ����滻��Ӧ��ǰ�Ĺؼ��ģ�Ȼ��ɾ���Ǹ���С�Ĺؼ���
            Node * p1 = curNode->ptr[curIdx];
            while (p1->ptr[0]) {
                p1 = p1->ptr[0];
            }
            int res = p1->key[1];
            this->Delete_BTree(p1->key[1]);

            curNode->key[curIdx] = res;

            break;
        }
        else if (!curNode->ptr[curIdx - 1] && !curNode->ptr[curIdx])
        {   // is leaf
            for (int i = curIdx; i <= curNode->keynum; ++i) {
                curNode->key[i] = curNode->key[i + 1];
                // all ptr are NULL , no need to move.
            }//end for.
            --curNode->keynum;
            this->DeleteBalance(curNode);
            break;
        }
        else { //debug
            cerr << "Error" << endl;
        }
    }//endw
}
//ɾ����Ӧ�ؼ��ֺ�������Ҫ��ɾ����������е���
void BTree::DeleteBalance(Node * curNode) {
    int lb = (int)m / 2;  
    Node * parent = curNode->parent;
    while (parent && curNode->keynum < lb) {//˵��ɾ���˹ؼ��ֺ�ԭ�����Ǹ�����Ѿ���
        //����B-������С���Ҫ������������Ի�ȥ��������
        int idx = 0;
        //�ҵ�curNode���丸�׽ڵ��е�λ��
        for (int i = 0; i <= parent->keynum; ++i) {
            if (parent->ptr[i] == curNode) {
                idx = i;
                break;
            }
        }
        Node * lsilb = NULL; Node * rsilb = NULL;
        if (idx - 1 >= 0) {//�����ǰ��������ֵ�
            lsilb = parent->ptr[idx - 1];
        }
        if (idx + 1 <= parent->keynum) {//˵����ǰ��������ֵ�
            rsilb = parent->ptr[idx + 1];
        }
        //ֻҪ���ֵܴ��ڣ���������rsilb->keynum > lb������ɾ���ĵ��������2
        if (rsilb && rsilb->keynum > lb) {
            this->RotateLeft(parent, idx, curNode, rsilb);
            break;
        }//������ֵܲ����㣬�����ֵ����㣬ͬ������
        else if (lsilb && lsilb->keynum > lb) {
            this->RotateRight(parent, idx, curNode, lsilb);
            break;
        }//��������ֵܶ������㣬�Ǿ������3�ˣ�
        else {
            //�ϲ������ֵܣ�
            if (lsilb)
                this->Merge(parent, idx, lsilb, curNode);
            else//û�����ֵܣ��ϲ������ֵ�
                this->Merge(parent, idx + 1, curNode, rsilb);
            // potentially causing deficiency of parent.
            curNode = parent;
            parent = curNode->parent;
        }
    }
    if (curNode->keynum == 0) {
        // root is empty,��ʱ��Ϊ��
        head = curNode->ptr[0];
        delete curNode;
    }//endif
}
void BTree::RotateLeft(Node * parent, int idx, Node * cur, Node * rsilb) {
    //����������ֵܴ��ڵ�����£���������rsilb->keynum > lb����������Ҫ�Ӱ�
    //���ֵܽ���е���С�ؼ����ƶ������׽�㣬�����׽����С�ڸ����ֵܵĹؼ��ֵĹؼ���
    //��Ҫ���Ƶ��ո�ɾ�����Ǹ�����С�

    //���׽����ĳ���������
    cur->key[cur->keynum + 1] = parent->key[idx + 1]; 
    cur->ptr[cur->keynum + 1] = rsilb->ptr[0];  //
    if (cur->ptr[cur->keynum + 1]) {
        cur->ptr[cur->keynum + 1]->parent = cur;    
    }
    rsilb->ptr[0] = NULL;

    ++cur->keynum;

    parent->key[idx + 1] = rsilb->key[1];
    rsilb->key[idx] = 0;
    //���ֵ�����һ����㵽���׽�㣬
    for (int i = 0; i <= rsilb->keynum; ++i) {//ɾ����ҵ��Ǹ����
        rsilb->key[i] = rsilb->key[i + 1];
        rsilb->ptr[i] = rsilb->ptr[i + 1];
    }
    rsilb->key[0] = 0;
    --rsilb->keynum;
}
void BTree::RotateRight(Node * parent, int idx, Node * cur, Node * lsilb) {

    //����������ֵܴ��ڵ�����£���������lsilb->keynum > lb����������Ҫ�Ӱ�
    //���ֵܽ���е����ؼ����ƶ������׽�㣬�����׽���д��ڸ����ֵܵĹؼ��ֵĹؼ���
    //��Ҫ���Ƶ��ո�ɾ�����Ǹ�����С�

    //��Ϊ������߲���
    for (int i = cur->keynum; i >= 0; --i) {//��Ϊ��ߵĶ����ұ�С������Ҫ�����һ��λ��
        cur->key[i + 1] = cur->key[i];
        cur->ptr[i + 1] = cur->ptr[i];
    }
    //�ڵ�һ��λ�ò��븸�׽�����������Ľ��
    cur->key[1] = parent->key[idx];
    cur->ptr[0] = lsilb->ptr[lsilb->keynum];

    if (cur->ptr[0])
        cur->ptr[0]->parent = cur;
    lsilb->ptr[lsilb->keynum] = NULL;
    ++cur->keynum;

    // from lsilb to parent.
    parent->key[idx] = lsilb->key[lsilb->keynum];
    lsilb->key[lsilb->keynum] = 0;
    --lsilb->keynum;

}
void BTree::Merge(Node * parent, int idx, Node * lsilb, Node * cur) {

    //����ʵ�ֶ�����lsilb�Ϻϲ����������Ȱ�cur�е�ʣ�ಿ�֣�ȫ���ϵ����ֵ��и���
    for (int i = 0; i <= cur->keynum; ++i) {
        lsilb->key[lsilb->keynum + 1 + i] = cur->key[i];
        lsilb->ptr[lsilb->keynum + 1 + i] = cur->ptr[i];
        if (lsilb->ptr[lsilb->keynum + 1 + i])
            lsilb->ptr[lsilb->keynum + 1 + i] = lsilb;
   }
    //Ȼ���ٰѸ��׽���е�idx��Ӧ��������ӵ����ֵ�
    lsilb->key[lsilb->keynum + 1] = parent->key[idx];
    lsilb->keynum = lsilb->keynum + cur->keynum + 1;
    delete cur;
    //Ȼ��������ǵĸ��׽������
    for (int i = idx; i <= parent->keynum; ++i) {
        parent->key[i] = parent->key[i + 1];
        parent->ptr[i] = parent->ptr[i + 1];
    }//end for.
    --parent->keynum;
}
void BTree::Destroy(Node * & T) { //�Ƿ�ռ�
    if (!T) { return; }
    for (int i = 0; i <= T->keynum; ++i)
        Destroy(T->ptr[i]);
    delete T;
    T = NULL;
    return;
}
void BTree::WalkThrough(Node * &T) {
    if (!T) return;
    static int depth = 0;
    ++depth;
    int index = 0;

    bool running = true;

    while (running) {
        int ans = 0;
        if (index == 0) {
            ans = 2;
        }
        else {
            cout << "������ȣ�" << depth << endl;
            cout << "���ڵĽ��: " << (void*)T << ";  "
                << "�����ֵΪ: " << T->keynum << "; " << endl;
            cout << "�����: " << index << ";  ֵΪ: " << T->key[index] << endl;

            do {
                cout<< "1.ǰֵ; 2.��ֵ; 3.����; 4.�Һ���; 5.������һ�� " << endl;
                cin>>ans;
                if (1 <= ans && ans <= 5)
                    break;
            } while (true);
        }


        switch (ans) {
        case 1:
            if (index == 1)
                cout << "Failed." << endl;
            else
                --index;
            break;
        case 2:
            if (index == T->keynum)
                cout << "Failed" << endl;
            else
                ++index;
            break;
        case 4:
            if (index > 0 && T->ptr[index])
                WalkThrough(T->ptr[index]);
            else
                cout << "Failed" << endl;
            break;
        case 3:
            if (index > 0 && T->ptr[index - 1])
                WalkThrough(T->ptr[index - 1]);
            else
                cout << "Failed" << endl;
            break;
        case 5:
            running = false;
            break;
        }//endsw
    }//endw

    --depth;
}
Node * BTree::gethead() {
    return this->head;
}
