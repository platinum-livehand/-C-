#include <stdio.h>

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int partition(int array[], int i, int j)
{
    int data = array[i];

    while (i < j)
    {
        while (i < j && array[j] > data)
        {
            j--;
        }

        if (i < j)
        {
            array[i] = array[j];
            i++;
        }
        
        while (i < j && array[i] < data)
        {
            i++;
        }
        
        if (i < j)
        {
            array[j] = array[i];
            j--;
        }
    }
    
    array[i] = data;

    return i;
}

void quickSort(int array[], int i, int j)
{
    if (i < j)
    {
        int index = partition(array, i, j);

        quickSort(array, i, index - 1);

        quickSort(array, index + 1, j);
    }
}

int main(int argc, char* argv[])  
{  
    int array[] = {34, 7, 23, 32, 5, 62};  
    int length = sizeof(array) / sizeof(array[0]);  

    printf("Original array: ");  
    printArray(array, length);  

    quickSort(array, 0, length - 1);  

    printf("Sorted array: ");  
    printArray(array, length);  

    return 0;  
}