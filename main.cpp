//
//  main.cpp
//  sorting
//
//  Created by Mohamad El Mokdad and Elio Tannoury on 11/30/20.
// CSC 313- Khalil Challita
//

#include <iostream>
#include <time.h>
#include <iomanip>

using namespace std;


//This function creates an array with the desired size, the elements are randomly generated according to the srand library. The values of the elements are between 1 and 99.
void CreateArray(int arr[], int size)
{
    srand(time(0));
    for ( int i=0;  i < size; i++)
    {
        arr[i] = rand()% 99 +1;
    }
}


//This function returns the size of the array passed, the way to do this is a for loop keeps on running until it finds a value which is lower than 1 or greater than 99, The reason for that is when we try accessing an element in an array with an out of range index the compiler will spit a random number from memory which is always greater than 99 or less than 1 (negative value)
int sizeArr(int array[])
{
    int s=0;
    
    while (array[s] < 100 && array[s]>0)
        s++;
    
    return s;
}


//This function simply iterates the index of the array and displays them on the screen
void PrintArray(int arr[])
{
    int size = sizeArr(arr);
    
    for (int i=0; i<size; i++)
    {
        cout<<arr[i]<<" ";
        
    }
    cout<<endl;
}


//This function is heavily used in partitioning where we want to swap two values in an array with each other. The function simply holds the values temporarily and switches them accordingly.
void swap(int array[], int i, int j)
{
    int fori = array[i];
    int forj = array[j];
    
    array[i] = forj;
    array[j] = fori;
    
}



//This is a simple insertion sort code where we pass to it the array and its size, it creates two integers key and inc where they are used to indicate the index where are working on. We started the for loop for i = 1 so that inc can be used to indicate the index. The key is the value we are working on right now. We compare it to the next value, this runs until the value is no more greater than the key. This function works directly on the array so it doesnt create any extra memory space.
void insertion(int array[], int size)
{
    int key;
    int inc;
    
    for (int i=1; i<size;i++)
    {
        key = array[i];
        inc=i-1;
        
        while( array[inc] > key && inc >= 0 )
        {
            swap(array, inc, inc+1);
            inc = inc-1;
        }
        
        array[inc+1] = key;
    }
    
}


//This pivot function finds the pivot of an array through the median of three technique, it compares the first, last and center of an array to find the middle. We had some troubles with arrays of size 2, we fixed it here but then we decided to let the quicksort function handle arrays which are of size 2 or less.

int pivot(int arr[],int  begin, int  end)
{
        int first, center, last;
        first = begin;
        last = end;
        center = (begin+end)/2 ;
        
        int a = arr[first];
        int b = arr[center];
        int c = arr[last];
        
        if ( (a<b && a>c) || (a>b && a<c) )
            return first;
        
        else if ((b<c && b>a) || (b>c && b<a))
                 return center;
                 
        else
                 return last;
    
        
}

//The partitionArr function purpose is to find the pivot of the array we passed according the the starting and ending indeces. Then the pivot is moved to the end of the array and two counter i (increments) and j(decrements) start moving.

int partitionArr(int arr[], int begin, int end)
{
    
    int end1 = end - 1;
    bool first, second;
    
    int indexPiv = pivot(arr, begin, end);
    int piv = arr[indexPiv];
    
    swap(arr, indexPiv, end);
    
//We opted to use two bool values to indicate if the value of the array we are on is making any trouble, in i's case if it is larger than the pivot or in j's case if it is smaller than the pivot. This function keeps on working until the i and j overlap then the function stops and it retrns the index of the pivot.
    

    while (begin < end1)
    {
        
        if ( arr[begin] < piv)
        {
            ++begin;
            first = false;
        }
        else
            first = true;
        
        if ( arr[end1] > piv)
        {
            --end1;
            second = false;
        }
        else
            second = true;
        
        if ( second & first)
        {
            swap(arr, begin, end1);
            ++begin;
            --end1;
            first = false;
            second = false;
            
        }
        
        
    }
    
//Sometimes i and j overlap but still there are values in the wrong place thats why we decided that if the function stops and k's value is wrong we would swap the pivot with j.
        
    if(second == true)
        begin = end1;
    
   
    
        swap(arr, begin , end);
    
  return begin;
                         
    
    
}


//THis is the star of the show, the quicksort, the way this works is that first it partitions the given array into two arrays according to the pivot and then recursively calls quicksort again on both of the arrays. This is how divide and conquer strategy works.
//We also added a condition for arrays of size 2 where they will be sorted in a simple way, the reason for that is if these arrays are passed to partition function the pivot function wont be able to find the pivot, a messs will happen thats why we chose to solve it right here.
void quickSort(int arr[], int p, int r)
{
    int sizearray = r-p+1;
    if (sizearray == 2)
    {
        if (arr[p] > arr[r])
            swap(arr, p, r);
    }
    
    
     else if (p<r)
    {
        int q = partitionArr(arr, p,r);
        quickSort(arr, p, q - 1);
        quickSort(arr, q + 1, r);
    }
        
    
}

//This function's purpose is to duplicate an array in order for us to pass the same array twice for the two sorting functions, otherwise we risk passing the unsorted array.
void duplicate(int arr1[], int arr2[])
{
    int size = sizeArr(arr1);
    for (int i=0; i<size;i++)
    {
        arr2[i] = arr1[i];
    }
}


//It is a simple driver for all the functions, here we used the clock() function two times, to save the time before the function executes and after the function executes, a simple substraction of the two values leads to the elapsed time of the function, in this case for the quicksort and insertion sort.
int main()
{
    int size;
    clock_t start1, end1, start2, end2;
    cout<<"Please enter the desired size of the array, and the program will output the time required to sort this random array using insertion sort and quick sort:  "<<endl;
    
    cin>>size;
    
    int* array1 = new int[size];
    int* array2= new  int[size];
    
    CreateArray(array1, size);
    duplicate(array1, array2);
  
    
    start1 = clock();
    insertion(array1, size);
    end1 = clock();
  
    // Calculating total time taken by the program.
    double time_taken1 = double(end1 - start1) / double(CLOCKS_PER_SEC);
    cout << "Time taken by insertion sort : " << fixed
         << time_taken1 << setprecision(5);
    cout << " sec " << endl;
    
    
    start2 = clock();
    quickSort(array2, 0, size-1);
    end2 = clock();
  
    // Calculating total time taken by the program.
    double time_taken2 = double(end2 - start2) / double(CLOCKS_PER_SEC);
    cout << "Time taken by quick sort : " << fixed
         << time_taken2 << setprecision(5);
    cout << " sec " << endl;
    
    
    
    
    
    
    
    

   
    return 0;
}
