#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "RBtree.h"

int size=sizeof(char)*257;

void Insert(){
    char* name=(char*)malloc(size);
    unsigned long long int key;

    

    scanf(" %s %llu", name, &key);
    getchar();
    name=(char *)realloc(name, strlen(name)*sizeof(char)+1);
    int length = strlen(name);
    for (int i = 0; i < length; i++)
        name[i] = tolower (name[i]);

    Insertion(name, key);
}

void Deletion(){
    TNode* find;
    char* delete=(char*)malloc(size);
    scanf(" %s", delete);
    int length = strlen(delete);
    for (int i = 0; i < length; i++)
        delete[i] = tolower (delete[i]);

    getchar();
    find = Search(delete);
    if(find==NIL) printf("NoSuchWord\n");
    DeleteNode(find);
    free(delete);

}

void LoadFile(){
    char path[100];
    char c;
    for(int a=0; a<4; a++)
        getchar();
    int i=0;

    c=getchar();
    while(c!='\n')
    {
        path[i]=c;
        c=getchar();
        i++;
    }
    path[i]='\0';

    Load(path);
}

void SaveFile(){
    char path[100];
    char c;

    for(int a=0; a<4; a++)
        getchar();
    int i=0;

    c=getchar();
    while(c!='\n')
    {
        path[i]=c;
        c=getchar();
        i++;
    }
    path[i]='\0';

    Save(path);
}

void Find(char c){
    char* name;
    TNode* find;

    name=(char*)malloc(size);

    name[0]=c;
    int i=1;
    while((c=getchar())!='\n' && c!=EOF)
    {
        name[i]=c;
        i++;
    }
    name[i]='\0';
    int length = strlen(name);
    for (int i = 0; i < length; i++)
        name[i] = tolower (name[i]);

    find = Search(name);
    if(find==NIL)
        printf("NoSuchWord\n");
    else
        printf("OK: %llu\n", find->key);

    free(name);
}

int main()
{
    sentinel.parent = NIL;
    sentinel.left = sentinel.right = NIL;
    sentinel.color = BLACK;
    sentinel.name = NULL;
    sentinel.key = 0;
    root = NIL;

    char c;

    c=getchar();
    while(c!=EOF)
    {
        if(c=='+')
            Insert();
        else
            if(c=='-')
                Deletion();
        else {
            if(c=='!')
            {
                getchar();
                c=getchar();
                if(c == 'S')
                    SaveFile();
                else if(c == 'L')
                    LoadFile();
            }
            else
                Find(c);
        }
        c=getchar();
    }
    return 0;
}
