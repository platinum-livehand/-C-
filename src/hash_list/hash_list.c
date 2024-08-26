#include <stdio.h>
#include <stdlib.h>

#define NUM 5

typedef struct HashList
{
    int num;
    char* data;
} HashList;

HashList* initHashList()
{
    HashList* list = (HashList*)malloc(sizeof(HashList));
    list->num = 0;
    list->data = (char*)malloc(sizeof(char) * NUM);
    for (int i = 0; i < NUM; i++)
    {
        list->data[i] = 0;
    }
    
    return list;
}

int hash(char data)
{
    return (int)data % NUM;
}

void put(HashList* list, char data)
{
    int index = hash(data);

    if (list->data[index] != 0)
    {
        int count = 1;

        while (list->data[index] != 0)
        {
            index = hash(data + count);
            count++;
        }
    }

    list->data[index] = data;
    list->num++;
}

int query(HashList* list, char data)  
{  
    int index = hash(data);  
    int count = 0;  

    while (count <= NUM)  
    {  
        if (list->data[index] == data)  
        {  
            return index; // 找到数据，返回索引  
        }  

        if (list->data[index] == 0)  
        {  
            break; // 找到空位，说明数据不存在  
        }  

        index = hash(data + ++count); // 处理冲突  
    }  

    return -1; // 数据未找到  
}

void freeHashList(HashList* list)  
{  
    free(list->data);  
    free(list);  
}  

void printHashList(HashList* list)  
{  
    for (int i = 0; i < NUM; i++)  
    {  
        if (list->data[i] != 0)  
        {  
            printf("Index %d: %c\n", i, list->data[i]);  
        }  
    }  
}  

int main(int argc, char* argv[])  
{  
    printf("Hello Hash List\n");  

    HashList* list = initHashList();  
    
    put(list, 'A');  
    put(list, 'B');  
    put(list, 'C');  
    put(list, 'D');  
    put(list, 'F');  
    
    printHashList(list);  

    char queryChar = 'F';  
    int index = query(list, queryChar);  
    if (index != -1)  
    {  
        printf("Found '%c' at index %d\n", queryChar, index);  
    }  
    else  
    {  
        printf("'%c' not found in the hash list\n", queryChar);  
    }  

    freeHashList(list);  

    return 0;  
}