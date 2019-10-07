#ifndef BLACKRED_H_INCLUDED
#define BLACKRED_H_INCLUDED

typedef enum {
    BLACK, RED
} NodeColor;

typedef struct Node {
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    NodeColor color;
    unsigned long long int key;
    char *name;
} TNode;

#define NIL &sentinel
TNode sentinel;
TNode *root;
void RightRotate(TNode *);
void LeftRotate(TNode *);
void InsertFixUp(TNode *x);
void Insertion(char* word, unsigned long long int value);
TNode *Search(char* word) ;
void DeleteFixUp(TNode *x);
void DeleteNode(TNode *y);
void Save(const char* filename);
void SaveRec(TNode* cur, FILE* stream);
int Load(const char* filename);
void LoadRec(TNode** node, TNode** parent, FILE* stream);
void freeNode(TNode* node);
void freeTree(TNode* node);

#endif
