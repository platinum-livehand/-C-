#include <stdio.h>

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void shellSort(int array[], int length)
{
    // 使用步长逐渐递减的方式进行排序
    for (int gap = length / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < length; i++)
        {
            int temp = array[i];

            int j;
            
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
            {
                array[j] = array[j - gap];
            }

            array[j] = temp;
        }
    }
}

int main(int argc, char* argv[])
{
    int array[] = {12, 34, 54, 2, 3, 23, 45, 11, 67, 1, 7, 16};
    int length = sizeof(array) / sizeof(array[0]);

    printf("Original Array:\n");
    printArray(array, length);

    shellSort(array, length);

    printf("Sorted Array:\n");
    printArray(array, length);

    return 0;
}