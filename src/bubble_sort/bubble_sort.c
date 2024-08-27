#include <stdio.h>

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void bubbleSort(int array[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[])  
{  
    int array[] = {64, 34, 25, 12, 22, 11, 90};  
    int length = sizeof(array) / sizeof(array[0]);  

    printf("Unsorted array: \n");  
    printArray(array, length);  

    bubbleSort(array, length);  

    printf("Sorted array: \n");  
    printArray(array, length);  

    return 0;  
} 