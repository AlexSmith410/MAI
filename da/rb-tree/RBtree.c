#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBtree.h"

void Insertion(char* name, unsigned long long int key)
{
    TNode *current, *parent, *tmp;
    tmp=(TNode*)malloc(sizeof(TNode));
    current = root;
    parent = 0;
    int status;
    while (current != NIL)
    {
        status=strcmp(name, current->name);

        if (status==0)
        {
            printf("Exist\n");
            return;
        }
        parent = current;

        if(status>0)
            current = current->right;
        else
            current = current->left;
    }

    tmp->name = name;
    tmp->key=key;
    tmp->parent = parent;
    tmp->left = NIL;
    tmp->right = NIL;
    tmp->color = RED;

    if(parent)
    {
        if(strcmp(name, parent->name)<0)
            parent->left = tmp;
        else
            parent->right = tmp;
    } else
        root = tmp;

    InsertFixUp(tmp);
    printf("OK\n");
}

void InsertFixUp(TNode *node)
{
    while (node != root && node->parent->color == RED) {

        if (node->parent == node->parent->parent->left)
        {
            TNode *tmp = node->parent->parent->right;
            if (tmp->color == RED)
            {
                node->parent->color = BLACK;
                tmp->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {

                if (node == node->parent->right) {
                    node = node->parent;
                    LeftRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                RightRotate(node->parent->parent);
            }
        } else {

            TNode *tmp = node->parent->parent->left;
            if (tmp->color == RED) {

                node->parent->color = BLACK;
                tmp->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {

                if (node == node->parent->left) {
                    node = node->parent;
                    RightRotate(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                LeftRotate(node->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void DeleteNode(TNode *delet)
{
    TNode *tmp_1, *tmp_2;
    
    if (!delet || delet == NIL) return;
    
    if (delet->left == NIL || delet->right == NIL)

        tmp_2 = delet;
    else
    {
        tmp_2 = delet->right;
        while (tmp_2->left != NIL) tmp_2 = tmp_2->left;
    }

    if (tmp_2->left != NIL)
        tmp_1 = tmp_2->left;
    else
        tmp_1 = tmp_2->right;


    tmp_1->parent = tmp_2->parent;
    if (tmp_2->parent)
        if (tmp_2 == tmp_2->parent->left)
            tmp_2->parent->left = tmp_1;
        else
            tmp_2->parent->right = tmp_1;
    else
        root = tmp_1;

    if (tmp_2 != delet)
    {
        delet->name = tmp_2->name;
        delet->key = tmp_2->key;
    }


    if (tmp_2->color == BLACK)
        DeleteFixUp (tmp_1);
    free (tmp_2);
    printf("OK\n");
}

void DeleteFixUp(TNode *node) {

    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            TNode *tmp = node->parent->right;
            if (tmp->color == RED) {
                tmp->color = BLACK;
                node->parent->color = RED;
                LeftRotate (node->parent);
                tmp = node->parent->right;
            }
            if (tmp->left->color == BLACK && tmp->right->color == BLACK) {
                tmp->color = RED;
                node = node->parent;
            } else {
                if (tmp->right->color == BLACK) {
                    tmp->left->color = BLACK;
                    tmp->color = RED;
                    RightRotate (tmp);
                    tmp = node->parent->right;
                }
                tmp->color = node->parent->color;
                node->parent->color = BLACK;
                tmp->right->color = BLACK;
                LeftRotate (node->parent);
                node = root;
            }
        } else {
            TNode *tmp = node->parent->left;
            if (tmp->color == RED) {
                tmp->color = BLACK;
                node->parent->color = RED;
                RightRotate (node->parent);
                tmp = node->parent->left;
            }
            if (tmp->right->color == BLACK && tmp->left->color == BLACK) {
                tmp->color = RED;
                node = node->parent;
            } else {
                if (tmp->left->color == BLACK) {
                    tmp->right->color = BLACK;
                    tmp->color = RED;
                    LeftRotate (tmp);
                    tmp = node->parent->left;
                }
                tmp->color = node->parent->color;
                node->parent->color = BLACK;
                tmp->left->color = BLACK;
                RightRotate (node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}

TNode *Search(char* name)
{
    TNode *current = root;
    int status;

    while(current != NIL)
    {
        status=strcmp(name, current->name);
        if(status==0)
            return (current);
        else
        if(current->left==NIL && current->right==NIL)
        {
            return (NIL);
        }
        else
        {
            if(status<0)
                current = current->left;
            else
                current = current->right;
        }
    }
    return NIL;
}

void freeNode (TNode* node)
{
    free(node->name);
    free(node);
}

void freeTree (TNode* node)
{
    if (node==NIL)
        return;
    freeTree(node->left);
    freeTree(node->right);
    freeNode(node);
}

void RightRotate(TNode *node){
    TNode *tmp = node->left;

    node->left = tmp->right;
    if (tmp->right != NIL) tmp->right->parent = node;

    if (tmp != NIL) tmp->parent = node->parent;
    if (node->parent) {
        if (node == node->parent->right)
            node->parent->right = tmp;
        else
            node->parent->left = tmp;
    } else {
        root = tmp;
    }

    tmp->right = node;
    if (node != NIL)
        node->parent = tmp;
}

void LeftRotate(TNode *node){
    TNode *tmp = node->right;

    node->right = tmp->left;
    if (tmp->left != NIL) tmp->left->parent = node;

    if (tmp != NIL) tmp->parent = node->parent;
    if (node->parent) {
        if (node == node->parent->left)
            node->parent->left = tmp;
        else
            node->parent->right = tmp;
    } else {
        root = tmp;
    }

    tmp->left = node;
    if (node != NIL)
        node->parent = tmp;
}

void Save(const char* filename)
{
    FILE* fd = fopen(filename, "w+b");
    if (!fd)
        printf ("ERROR: Couldn't create file\n");
    else
    {
        SaveRec(root, fd);
        fclose(fd);
        printf("OK\n");
    }
}


void SaveRec(TNode* cur, FILE* stream)
{
    if(cur==NIL)
        return;

    char name[257];
    int i;

    for(i=0; i<257-1; i++)
        name[i]=cur->name[i];
    name[i+1]='\0';

    fwrite(name, sizeof(char)*257, 1, stream);
    fwrite(&cur->key, sizeof(unsigned long long int), 1, stream);

    char r = 'r';
    char l = 'l';
    char red = 'r';
    char black='b';
    char empty = 'n';

    if(cur->color==RED)
        fwrite(&red, sizeof(char), 1, stream);
    else
        fwrite(&black, sizeof(char), 1, stream);

    if(cur->left != NIL)
        fwrite(&l, sizeof(char), 1, stream);
    else
        fwrite(&empty, sizeof(char), 1, stream);

    if(cur->right!= NIL)
        fwrite(&r, sizeof(char), 1, stream);
    else
        fwrite(&empty, sizeof(char), 1, stream);

    SaveRec(cur->left, stream);
    SaveRec(cur->right, stream);
}

int Load(const char* filename)
{
    FILE* fd = fopen(filename, "rb");
    if (!fd)
    {
        printf ("ERROR: Couldn't open file\n");
        return 0;
    }
    else
    {
        freeTree(root);
        root=NULL;
        TNode* NilToLoad=NIL;
        LoadRec(&root, &NilToLoad, fd);
        fclose(fd);
        printf("OK\n");
        return 1;
    }
}


void LoadRec(TNode** node, TNode** Parent, FILE* stream)
{
    (*node)=(TNode*)malloc(sizeof(TNode));
    (*node)->name=(char*)malloc(sizeof(char)*257);

    if(fread((*node)->name, sizeof(char)*257, 1, stream)!=1)
    {
        (*node)->parent = NIL;
        (*node)->left = sentinel.right = NIL;
        (*node)->color = BLACK;
        (*node)->name = NULL;
        (*node)->key = 0;
        (*node)=NIL;
    }
    else
    {
        (*node)->name=(char *)realloc((*node)->name, strlen((*node)->name)*sizeof(char)+1);
        fread(&(*node)->key, sizeof(unsigned long long int), 1, stream);
        (*node)->parent=NIL;
        (*node)->left=NIL;
        (*node)->right=NIL;

        char l;
        char r;
        char color;
        fread(&color, sizeof(char), 1, stream);
        fread(&l, sizeof(char), 1, stream);
        fread(&r, sizeof(char), 1, stream);

        (*node)->parent = (*Parent);

        if(color=='r')
            (*node)->color=RED;
        else
            (*node)->color=BLACK;

        if(l == 'l')
        {
            LoadRec(&(*node)->left, node, stream);
        }
        else
            (*node)->left = NIL;
        if(r == 'r')
        {
            LoadRec(&(*node)->right, node, stream);
        }
        else
            (*node)->right = NIL;
    }

}
