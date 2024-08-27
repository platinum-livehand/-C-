#include <stdio.h>

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void insertSort(int array[], int length)
{
    for (int i = 1; i < length; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[j] > array[i])
            {
                int temp = array[i];

                for (int k = i - 1; k >= j; k--)
                {
                    array[k + 1] = array[k];
                }

                array[j] = temp;

                break;
            }
        }
    }
}

int main(int argc, char* argv[])  
{  
    int array[] = {4, 3, 5, 1, 9, 6};  
    int length = sizeof(array) / sizeof(array[0]);  

    printf("原始数组: ");  
    printArray(array, length);  

    insertSort(array, length);  

    printf("排序后的数组: ");  
    printArray(array, length);  

    return 0;  
}  