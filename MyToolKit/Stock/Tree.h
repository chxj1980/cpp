//���ǻ��ں����ֵܱ�ʾ��������Tree�Ķ�����ʵ��(�̲�P.164~P.171)
#ifndef TREE_H
#define TREE_H
#include "stdlib.h"
//#include "iostream.h"

template<class T> class Tree;      //ǰ������,TreeNode��Ҫ������Ϊ��Ԫ��

template<class T> 
class TreeNode           //�������(�ú����ֵܱ�ʾ����)
{
  friend class Tree<T>;
  private:
	  T data;                  //������(ԭ�̲ķ���public��)
	  TreeNode<T> *firstChild;   //ָ���һ������
	  TreeNode<T> *nextSibling;   //ָ����һ���ֵ�
  public:
	  //��������Ϊvalue��һ������fc����һ���ֵ�Ϊns�������
	  TreeNode(T value,TreeNode<T> *fc=NULL, TreeNode<T> *ns=NULL)
	  { data=value; firstChild=fc; nextSibling=ns;  }
	  TreeNode<T>* &FirstChild(void)   //����ָ���һ�����ӵ�ָ������
	  { return firstChild; }
	  TreeNode<T>* &NextSibling(void)//����ָ����һ���ֵܵ�ָ������
	  { return nextSibling; }
	  T Getdata(void) const          //��ȡ��������(ԭ�̲�û�д˳�Ա)
	  { return data; }
	  void Setdata(T val) 
	  { return data = val; }
};

template<class T>
class Tree                  //����Tree�Ķ���
{
private:
	TreeNode<T> *root;     //ָ������
	TreeNode<T> *current;  //ָ��ǰ���

	void PreOrderTree(TreeNode<T>* &t, TreeNode<T>* &parent); //�ȸ�������tΪ���������
	void PostOrderTree(TreeNode<T>* &t, TreeNode<T>* &parent);   //���������tΪ���������
	bool Current(TreeNode<T>* &t)     
	//ʹt��ָ����Ϊ��ǰ��㣺�ɹ�������true;���򷵻�false.
	{ 
		if(t==NULL) return false;
		current=t;
		return true;
	}
	//����root�в��ҽ��s��˫�׽��
	TreeNode<T> *SearchParent(TreeNode<T> * &root, TreeNode<T>* &s);
public:
	Tree()
	{  root=current=NULL;  }

	~Tree()
	{
		DeleteSubTree(root);
	}

	T GetData()     //ȡ��ǰ�������
	{   return current->data;	}

	TreeNode<T>* Root()        
	//ʹ�����Ϊ��ǰ���:�ɹ�������true,���򷵻�false
	{
		current=root;
		return current;
	}

	TreeNode<T>* Current()
	{
		return current;
	}

	bool Parent();               //ʹ��ǰ����˫��Ϊ��ǰ���
	bool FirstChild();       //ʹ��ǰ���ĵ�һ������Ϊ��ǰ���
	bool NextSibling();      //ʹ��ǰ������һ���ֵ�Ϊ��ǰ���

	void InsertChild(T value, bool bUpdateCurrent = true); //��value���뵽��ǰ������һ������֮��
	void DeleteSubTree(TreeNode<T>* &t);//ɾ����tΪ��������
	bool DeleteChild(int i); //ɾ����ǰ���ĵ�i������

    bool Find(TreeNode<T> *root,T item);//��root���в���������Ϊitem�Ľ��
	void DisplayTree(int i);//��������i=1Ϊ�ȸ�������i=2Ϊ�������

	void PreOrderTreeFromCurrentNode();
	int  GetChildNoFromCurrent(TreeNode<T>* t);		// ���� t �ǵ�ǰ�ڵ�ĵڼ�������
	
	virtual void TraverseOutput(TreeNode<T>* &t, TreeNode<T>* &parent){};
};

template<class T>
void Tree<T>::DeleteSubTree(TreeNode<T>* &t)
{//ɾ����tΪ��������:ʵ�������ú����ɾ��
	if(t==NULL)
	{
		cout<<"The tree is empty!"<<endl;
		return;
	}
	TreeNode<T> *q=t->firstChild, *p;
	while(q!=NULL)   //�ݹ���ñ��������ɾ��"��һ������"��"��һ���ֵ�"Ϊ��������
	{
		p=q->nextSibling;
		DeleteSubTree(q);  //�ݹ���ñ�����:ɾ��q��ָ������
		q=p; 
	}
    //cout<<t->data<<"  ";         //�̲�ԭ��û�д˾�
	delete t;  //���ɾ�������
	t=NULL;
}

template<class T>
void Tree<T>::PreOrderTree(TreeNode<T>* &t, TreeNode<T>* &parent)
{//�ȸ�������tΪ���������
	if(t==NULL) return;
	
	//cout<<t->data<<" ";    //�������t������
	TraverseOutput(t, parent);

    //��"�ȸ�����"�Ե�һ�����ӽ��Ϊ��������
	 TreeNode<T> *p = t->firstChild;
	while(p!=NULL)
	{
		 PreOrderTree(p, t);
		 p = p->nextSibling;
	}
}

template<class T>
TreeNode<T>* Tree<T>::SearchParent(TreeNode<T> * &root, TreeNode<T>* &s)
{	
	/*�ȸ����ӷ�����*/

	//���� root �в��ҽ�� s ��˫�׽��
	if((root==NULL)||(root==s)) return NULL;
    TreeNode<T> *p=root->FirstChild();    //pָ���һ������
     //���s���ǵ�һ�����ӻ��һ�����ӵ��ֵܣ����root������
	while(p!=NULL&&p!=s) p=p->NextSibling();//�ڴ˸�����ԭ�̲ĵĴ���
	if(p==s) return root;
	
	//���Ե�һ������Ϊ���������в���s��˫�½��
	TreeNode<T> * pChild = root->FirstChild();
	while(pChild!=NULL)
	{
		p=SearchParent(pChild,s);
		if(p) 
			return p;
		else
			pChild = pChild->NextSibling();
	}
	return NULL;   //����ʧ��

}

template<class T>
bool Tree<T>::Parent()  
//ʹ��ǰ����˫��Ϊ��ǰ���: �ɹ�����true,���򷵻�fase
{
 	if(current==NULL) return false;
	
	TreeNode<T> *p=SearchParent(root,current);   //��root���в���current��˫��
	if(p==NULL) return false;      //����ʧ��
	else return Current(p);   //���ҳɹ��������Ϊ��ǰ���
}

template<class T>
bool Tree<T>::FirstChild()//ʹ��ǰ���ĵ�һ������Ϊ��ǰ���
{
	if(current!=NULL && current->firstChild!=NULL) 
		return Current(current->firstChild);
	else return false;
}

template<class T>
bool Tree<T>::NextSibling()
{//ʹ��ǰ������һ���ֵ�Ϊ��ǰ���
    if(current!=NULL && current->nextSibling!=NULL) 
		return Current(current->nextSibling);
	else return false;
}

template<class T>
void Tree<T>::InsertChild(T value, bool bUpdateCurrent)
{//��value���뵽��ǰ������һ������֮��
	TreeNode<T> *newNode=new TreeNode<T>(value);    //����һ���½��

	if(root==NULL)      //���ԭ��Ϊ�գ����½���Ϊֻ�и���������ɲ������
	{  root=current=newNode;  return;  }

	if(current->firstChild==NULL) current->firstChild=newNode;//��û�е�һ������ʱ
	else  //���е�һ������ʱ
	{
		TreeNode<T> *p=current->firstChild;   //pָ���һ������

		while(p->nextSibling!=NULL) p=p->nextSibling;  //Ѱ�����һ���ֵ�
		p->nextSibling=newNode;    //�½��������һ���ֵ�֮��
	}

	if(bUpdateCurrent)
		Current(newNode);     //���½����Ϊ��ǰ���
	return;
}

template<class T>
bool Tree<T>::DeleteChild(int i)   //ɾ����ǰ���ĵ�i�����ӽ��
{
	TreeNode<T> *r=NULL;       //r������ָ��Ҫɾ���ĺ���

	if(i==1)   //�����ɾ����һ������
	{
		r=current->firstChild;   //ָ���һ������
		if(r==NULL) return false;  //��û�е�һ������ʱɾ��ʧ��
		current->firstChild=r->nextSibling;//Խ��r����
	}
	else    //ɾ����������
	{
		int k=1;
		TreeNode<T> *p=current->firstChild;
		while(p!=NULL && k<i-1)  //Ѱ�ҵ�i������:�ڴ˾�����ԭ�̲ĵĴ���
		{	p=p->nextSibling;  k++;   }

		if(p!=NULL)
		{
			r=p->nextSibling;
			if(r!=NULL) 
			{
				p->nextSibling=r->nextSibling;  //Խ��r����
                r->nextSibling=NULL;
			}
			else return false;   //û�е�i�����ӣ�ɾ��ʧ��
		}
		else return false;  //û���������ӣ�ɾ��ʧ��
	}

		DeleteSubTree(r);    //ɾ��r��ָ������
		cout<<endl;
		return true;     //ɾ���ɹ�
}

template<class T>
bool Tree<T>::Find(TreeNode<T> *root,T item) 
//������������Ϊitem��㣬�ɹ��򷵻�true,�ҵ�ǰָ��ָ��ý�㣬���򷵻�false
{
	if(root==NULL) return false;
	if(root->data==item)
	{
		current=root;   //��ǰָ��ָ���ҵ��Ľ��
		return true;
	}
    bool found=false;
	TreeNode<T> *p=root->FirstChild();
    if(p==NULL) return false;	
    found=Find(p,item);    //����һ��������ָ��������ȥ��
	if(found) return true;   //����ҵ���,�Գɹ�����
   //����һ���ֵ���ָ��������ȥ��
	do{
       p=p->NextSibling();
       found=Find(p,item);
	   if(found) break;
	}while(p!=NULL);
	return found;
}

template<class T>
void Tree<T>::DisplayTree(int i)
{ //��������i=1Ϊ�ȸ�������i=2Ϊ�������
	TreeNode<T>* parent = NULL;
	if(i==1) PreOrderTree(root, parent);//����˽�г�Ա����PreOrderTree
	else PostOrderTree(root, parent);  //����˽�г�Ա����PostOrderTree
	cout<<endl;
}

template<class T>
void Tree<T>::PreOrderTreeFromCurrentNode()
{
	TreeNode<T>* parent = NULL;
	PreOrderTree(current, parent);//����˽�г�Ա����PreOrderTree
}

template<class T>
void Tree<T>::PostOrderTree(TreeNode<T>* &t, TreeNode<T>* &parent)
{//���������tΪ���������
	if(t==NULL) return;
	//��"�������"�Ե�һ�����ӽ��Ϊ���������
	if(t->firstChild!=NULL) PostOrderTree(t->firstChild, t);
    //��ʾ�����������
	//cout<<t->data<<"  ";
	TraverseOutput(t, parent);
    //���"�������"����һ���ֵܽ��Ϊ���������
	if(t->nextSibling!=NULL) PostOrderTree(t->nextSibling, t);
}

template<class T>
int Tree<T>::GetChildNoFromCurrent(TreeNode<T>* t)
{
	int k=1;
	TreeNode<T> *p=current->firstChild;
	while(p!=NULL)  //Ѱ�ҵ�i������:�ڴ˾�����ԭ�̲ĵĴ���
	{
		if(p==t)
			break;
		p=p->nextSibling;  k++;
	}
	
	if(p==NULL)
		return 0;
	else
		return k;
}

#endif //TREE_H

	

