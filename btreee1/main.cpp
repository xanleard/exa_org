
#include <QCoreApplication>
#include<iostream>
#include <iostream>
#include <stdlib.h>
#include <QList>
#include <list>

using namespace std;

struct Regalo{
string desc;
char control_parental;
};

struct nino{
string nombre;
int se_porto_bien; //valor del 0 al 10,  0 = Diablillo , 10 = La encarnación del Bien.
QList<Regalo> Regalos;
int longitud;
int latitud;
int edad;
};

class BTreeNode
{
    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;
    nino child;

public:
    BTreeNode(int _t, bool _leaf);   // Constructor

    void insertNonFull(int k, string nom, int status, int log, int lati, int edad);

    void splitChild(int i, BTreeNode *y);


    void traverse();


    BTreeNode *search(int k);
friend class BTree;
};

class BTree
{
    BTreeNode *root;
    int t;
public:

    BTree(int _t)
    {  root = NULL;  t = _t; }


    void traverse()
    {if (root != NULL) root->traverse(); }


    BTreeNode* search(int k)
    { return (root == NULL)? NULL : root->search(k); }


    void insert(string nom,int status,int log,int lati,int edad);
    //hash
    int hashCode(string nom);

    void inserte_gif(string re);
};


BTreeNode::BTreeNode(int t1, bool leaf1)
{
    t = t1;
    leaf = leaf1;
    keys = new int[2*t-1];
    C = new BTreeNode *[2*t];
    n = 0;
}

void BTree::inserte_gif(string re){
    Regalo rega;
    rega.desc=re;

}

int BTree::hashCode(string text){
    int hash = 0, strlen = text.length(), i;
    char character;
    if (strlen == 0)
        return hash;
    for (i = 0; i < strlen; i++) {
        character = text[i];
        hash = (31 * hash) + int(character);
    }
    return hash;
}

void BTreeNode::traverse()
{

    int i;
    for (i = 0; i < n; i++)
    {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (leaf == false)
        C[i]->traverse();
}


BTreeNode *BTreeNode::search(int k)
{

    int i = 0;
    while (i < n && k > keys[i])
        i++;
    if (keys[i] == k)
        return this;


    if (leaf == true)
        return NULL;


    return C[i]->search(k);
}


void BTree::insert(string nom,int status,int log,int lati,int edad)
{

    int k =hashCode(nom);

    if (root == NULL)
    {

        root = new BTreeNode(t, true);
        root->child.nombre=nom;
        root->child.se_porto_bien=status;
        root->child.longitud=log;
        root->child.latitud=lati;
        root->child.edad=edad;
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {

        if (root->n == 2*t-1)
        {

            BTreeNode *s = new BTreeNode(t, false);           
            s->C[0] = root;
            s->child.nombre=nom;
            s->child.se_porto_bien=status;
            s->child.longitud=log;
            s->child.latitud=lati;
            s->child.edad=edad;


            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k,nom,status,log,lati,edad);
            root = s;
        }
        else
            root->insertNonFull(k,nom,status,log,lati,edad);
    }
}


void BTreeNode::insertNonFull(int k,string nom,int status,int log,int lati,int edad)
{
    int i = n-1;
    if (leaf == true)
    {
        while (i >= 0 && keys[i] > k)
        {
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;
        if (C[i+1]->n == 2*t-1)
        {

            splitChild(i+1, C[i+1]);
            if (keys[i+1] < k)
               i++;
        }
        C[i+1]->insertNonFull(k,nom,status,log,lati,edad);
    }
}

void BTreeNode::splitChild(int i, BTreeNode *y)
{

    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;


    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];


    if (y->leaf == false)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    y->n = t - 1;

    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];
    C[i+1] = z;
    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];
    n = n + 1;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    BTree *b;

    cout<<"****************Menu*********"<<endl;
    cout<<"*    1)ingrese un niño      *"<<endl;
    cout<<"*                           *"<<endl;
    cout<<"*                           *"<<endl;
    cout<<"*****************************"<<endl;
    int op;
 do{
    cin>>op;


    switch(op){

        case 1:
           string nom;
           int edad;
           int compo;
           int lon;
           int lat;
           cout<<"*  nombre del niño  :         *"<<endl;
           cin>>nom;
           cout<<"*  comportamiento  del  niño  :         *"<<endl;
           cin>>compo;
           cout<<"*  edad  del  niño  :         *"<<endl;
           cin>>edad;
           cout<<"*  longitud del niño  :         *"<<endl;
           cin>>lon;
           cout<<"*  latitud del niño  :         *"<<endl;
           cin>>lat;
            b->insert(nom,compo,lon,lat,edad);
        break;

    }
  }while(op=4);

    return a.exec();
}
