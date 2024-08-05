#include <stdio.h>
#include <stdlib.h>

typedef struct String
{
    char* data;
    int len;
} String;

String* initString()
{
    String* string = (String*)malloc(sizeof(String));
    string->data = NULL;
    string->len = 0;
    return string;
}

void stringAssign(String* string, const char* data)
{
    if (string->data)
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

    if (len == 0)
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
        string->data[len] = '\0';  // 添加字符串终止符
    }

    string->len = len;
}

void printString(String* string)
{
    for (int i = 0; i < string->len; i++)
    {
        printf(i == 0 ? "%c " : " -> %c", string->data[i]);
    }
    printf("\n");
}

void forceMatch(String* master, String* sub)
{
    int i = 0;
    int j = 0;

    while (i < master->len && j < sub->len)
    {
        if (master->data[i] == sub->data[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j == sub->len)
    {
        printf("force match success!\n");
    }
    else
    {
        printf("force match fail!\n");
    }
}

int main()
{
    // 初始化字符串
    String* master = initString();
    String* sub = initString();

    // 分配字符串值
    stringAssign(master, "Hello, this is a simple string.");
    stringAssign(sub, "simple");

    // 打印字符串
    printf("主字符串: \n");
    printString(master);
    printf("子字符串: \n");
    printString(sub);

    // 强制匹配
    forceMatch(master, sub);

    // 释放内存
    free(master->data);
    free(sub->data);
    free(master);
    free(sub);
    
    return 0;
}
