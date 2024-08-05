#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct String
{
    char* data;
    int len;
}String;

String* initString()
{
    String* string = (String*)malloc(sizeof(String));

    string->data = NULL;
    string->len = 0;

    return string;
}

void stringAssign(String* string, const char* data)
{
    if(string->data)
    {
        free(string->data);
    }

    int len = 0;
    const char* temp = data;
    while (*temp)
    {
        temp++;
        len++;
    }
    
    if(len == 0)
    {
        string->data = NULL;
    }
    else
    {
        string->data = (char*)malloc(sizeof(char) * (len + 1));

        for (int i = 0; i < len; i++)
        {
            string->data[i] = data[i];
        }
        string->data[len] = '\0';
    }
    string->len = len;
}

void printString(String* string)
{
    for (int i = 0; i < string->len; i++)
    {
        printf(i == 0 ? " %c" : " -> %c", string->data[i]);
    }
    printf("\n");
}

void printNext(int* next, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf(i == 0 ? " %d" : " -> %d", next[i]); // %d 读取数据
    }
    printf("\n");
}

int* getNext(String* string)
{
    int* next = (int*)malloc(sizeof(int) * string->len);

    int i = 0;
    int j = -1;

    next[i] = j;

    while (i < (string->len - 1))
    {
        if(j == -1 || string->data[i] == string->data[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }

    return next;
}

void kmpMatch(String* master, String* sub, int* next)
{
    int i = 0;
    int j = 0;
    while (i < master->len && j < sub->len)
    {
        if (j == -1 || master->data[i] == sub->data[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }

    if (j == sub->len)
    {
        printf("KMP match success!\n");
    }
    else
    {
        printf("KMP match fail!\n");
    }
}

int main()
{
    // 初始化主串和子串
    String* master = initString();
    String* sub = initString();

    // 给主串和子串分配值
    stringAssign(master, "ab abc abc acb ab");
    stringAssign(sub, "abc ac");

    // 打印主串和子串
    printf("主串：\n");
    printString(master);

    printf("子串：\n");
    printString(sub);

    // 生成next数组并打印
    int* next = getNext(sub);
    printf("Next数组：\n");
    printNext(next, sub->len);

    // 执行KMP匹配
    kmpMatch(master, sub, next);

    // 释放内存
    free(master->data);
    free(master);
    free(sub->data);
    free(sub);
    free(next);

    return 0;
}