#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct node
{
    int data;
    struct node *left, *right;
    int ht;
} node;

node *insert(node *, int);
node *Delete(node *, int);
void preorder(node *);
void inorder(node *);
int height(node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int BF(node *);
void menuPrincipal();
void tutorialAVL();
void operacoesAVL();

int main()
{
    menuPrincipal();
    return 0;
}

void menuPrincipal()
{
    system("clear");
    int opcao;

    do
    {

        cout << "=========  Menu  =========" << endl;
        cout << "| 1 - Tutorial           |" << endl;
        cout << "| 2 - Operações AVL      |" << endl;
        cout << "| 0 - Sair               |" << endl;
        cout << "==========================" << endl;

        cin >> opcao;

        switch (opcao)
        {
        case 1:
            system("clear");
            tutorialAVL();
            break;
        case 2:
            system("clear");
            operacoesAVL();
            break;
        case 0:
            system("clear");
            break;

        default:
            system("clear");
            cout << "Alternativa incorreta" << endl;
            break;
        }
    } while (opcao);
}

void tutorialAVL()
{
    //Matheus
}

void operacoesAVL()
{
    system("clear");
    node *root = NULL;
    int opcao, num;
    char resposta;

    do
    {

        cout << "=========  Menu  =========" << endl;
        cout << "| 1 - Criar Árvore       |" << endl;
        cout << "| 2 - Inserir elemento   |" << endl;
        cout << "| 3 - Deletar elemento   |" << endl;
        cout << "| 4 - Imprimir           |" << endl;
        cout << "| 0 - Voltar             |" << endl;
        cout << "==========================" << endl;

        cin >> opcao;

        switch (opcao)
        {
        case 1:
            system("clear");
            root = NULL;
            while (resposta != 'n')
            {
                cout << "Digite o elemento: ";
                cin >> num;
                root = insert(root, num);
                cout << "Deseja inserir outro elemento sim(s) ou nao(n): ";
                cin >> resposta;
            }
            system("clear");
            break;
        case 2:
            system("clear");
            cout << "Digite o elemento: ";
            cin >> num;
            root = insert(root, num);
            break;
        case 3:
            system("clear");
            cout << "Digite o elemento: ";
            cin >> num;
            root = Delete(root, num);
            break;
        case 4:
            system("clear");
            cout << "Pré Ordem: " << endl;
            preorder(root);
            cout << "\n Em Ordem:" << endl;
            inorder(root);
            cout << endl;
            break;
        case 0:
            system("clear");
            break;

        default:
            system("clear");
            cout << "Alternativa incorreta" << endl;
            break;
        }
    } while (opcao);
}

node *insert(node *T, int x)
{
    if (T == NULL)
    {
        T = (node *)malloc(sizeof(node));
        T->data = x;
        T->left = NULL;
        T->right = NULL;
    }
    else if (x > T->data) // insert in right subtree
    {
        T->right = insert(T->right, x);
        if (BF(T) == -2)
            if (x > T->right->data)
                T = RR(T);
            else
                T = RL(T);
    }
    else if (x < T->data)
    {
        T->left = insert(T->left, x);
        if (BF(T) == 2)
            if (x < T->left->data)
                T = LL(T);
            else
                T = LR(T);
    }

    T->ht = height(T);

    return (T);
}

node *Delete(node *T, int x)
{
    node *p;

    if (T == NULL)
    {
        return NULL;
    }
    else if (x > T->data) // insert in right subtree
    {
        T->right = Delete(T->right, x);
        if (BF(T) == 2)
            if (BF(T->left) >= 0)
                T = LL(T);
            else
                T = LR(T);
    }
    else if (x < T->data)
    {
        T->left = Delete(T->left, x);
        if (BF(T) == -2) //Rebalance during windup
            if (BF(T->right) <= 0)
                T = RR(T);
            else
                T = RL(T);
    }
    else
    {
        //data to be deleted is found
        if (T->right != NULL)
        { //delete its inorder succesor
            p = T->right;

            while (p->left != NULL)
                p = p->left;

            T->data = p->data;
            T->right = Delete(T->right, p->data);

            if (BF(T) == 2) //Rebalance during windup
                if (BF(T->left) >= 0)
                    T = LL(T);
                else
                    T = LR(T);
        }
        else
            return (T->left);
    }
    T->ht = height(T);
    return (T);
}

int height(node *T)
{
    int lh, rh;
    if (T == NULL)
        return (0);

    if (T->left == NULL)
        lh = 0;
    else
        lh = 1 + T->left->ht;

    if (T->right == NULL)
        rh = 0;
    else
        rh = 1 + T->right->ht;

    if (lh > rh)
        return (lh);

    return (rh);
}

node *rotateright(node *x)
{
    node *y;
    y = x->left;
    x->left = y->right;
    y->right = x;
    x->ht = height(x);
    y->ht = height(y);
    return (y);
}

node *rotateleft(node *x)
{
    node *y;
    y = x->right;
    x->right = y->left;
    y->left = x;
    x->ht = height(x);
    y->ht = height(y);

    return (y);
}

node *RR(node *T)
{
    T = rotateleft(T);
    return (T);
}

node *LL(node *T)
{
    T = rotateright(T);
    return (T);
}

node *LR(node *T)
{
    T->left = rotateleft(T->left);
    T = rotateright(T);

    return (T);
}

node *RL(node *T)
{
    T->right = rotateright(T->right);
    T = rotateleft(T);
    return (T);
}

int BF(node *T)
{
    int lh, rh;
    if (T == NULL)
        return (0);

    if (T->left == NULL)
        lh = 0;
    else
        lh = 1 + T->left->ht;

    if (T->right == NULL)
        rh = 0;
    else
        rh = 1 + T->right->ht;

    return (lh - rh);
}

void preorder(node *T)
{
    if (T != NULL)
    {
        printf("%d(Fb=%d)", T->data, BF(T));
        preorder(T->left);
        preorder(T->right);
    }
}

void inorder(node *T)
{
    if (T != NULL)
    {
        inorder(T->left);
        printf("%d(Fb=%d)", T->data, BF(T));
        inorder(T->right);
    }
}