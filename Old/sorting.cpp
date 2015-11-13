/* Number of data-related comparisons
+-----------+--------------------------------------------------------------------------------------------------------------------+
|           |         N=100             |           N=1000          |         N=10000           |        N=50000                 |
|           | Random | Reverse | Sorted | Random | Reverse | Sorted | Random | Reverse | Sorted |  Random  |  Reverse |   Sorted |    
+-----------+----------------------------------------------------------------------------------------------|----------|----------+
| Selection | 4950      4950      4950  | 499500   499500   499500  |49995000|49995000 |49995000|1249975000|1249975000|1249975000|
| Insertion | 2640      5049      99    | 253179   500499   999     |25070210|50004999 |9999    |623408687 |1250024999|49999     |
| Bubble    | 4950      4950      4950  | 499500   499500   499500  |49995000|49995000 |49995000|1249975000|1249975000|1249975000|
| Quick     | 844       610       606   | 12438    9016     9009    |187655  |125452   |125439  |1051215   |750028    |750015    |
| Merge     | 549       316       356   | 8695     4932     5044    |120404  |64608    |69008   |718091    |382512    |401952    |
+-----------+--------------------------------------------------------------------------------------------------------------------+
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


//swap two locations
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;	
}


//All sort methods have the same interface:
//Input: array to be sorted and the size of the array
//Output: number of comparisons during sort operation
//Note: comparisons include only operations on the array

//selection sort
int selectionsort(int *array,int n)
{
    int comps=0; //number of comparisons

    for(int pass=0;pass<n-1;pass++) 
    {
 	int min=pass;  // min is an index
	for(int i=pass+1;i<n;i++) //Find next element to move
        {
            comps++;
	    if(array[i]<array[min]) 
                min = i; 
	}
	swap(&array[min],&array[pass]);
    }
    return comps;
}

int insertionsort(int *array,int n)
{
    int key;
    int comps=0; //number of comparisons
    int i;

    for(int pass=1;pass<n;pass++) 
    {
        key=array[pass];
        comps++;
	for(i=pass-1;i>=0 && array[i]>=key;i--) 
        {
            comps++;
            array[i+1]=array[i];
        }
        array[i+1]=key;
    }
    return comps;
}

int bubblesort(int *array,int n)
{
    int comps=0;

    for(int pass=0;pass<n-1;pass++) 
    {
	for(int i=0; i<n-pass-1;i++) 
        {
            comps++;
	    if(array[i+1]<array[i]) 
            { 
	        swap(&array[i],&array[i+1]);
            }
	}
    }
    return comps;
}

//Auxilary sorting function for quick sort - recursive
int quickSortAux(int *array,int lo,int hi)
{
    int i=lo;
    int j=hi;
    int y=0;
    int z=array[(lo+hi)>>1]; //pivot element in the middle
    int comps=0;

    do
    {
        comps++;
        while(array[i]<z)  //check all elements smaller than pivot
        {
            comps++;
            i++;
        }
        comps++;
        while(array[j]>z) //check all elements larger than pivot
        {
            comps++;
            j--;
        }
        if(i<=j)
        {
            swap(array[i],array[j]);
            i++;
            j--;
        }
    } 
    while(i<=j);
    //partitioning
    if(lo<j)
        comps+=quickSortAux(array,lo,j);
    if(i<hi)
        comps+=quickSortAux(array,i,hi);
    return comps;
}
 
int quicksort(int *array,int n)
{
    return quickSortAux(array,0,n-1);
}


//Auxilary function for merge sort, does merging of the partitions
int merge(int* array,int p,int r)
{
    int mid=(p+r)>>1; //mid element
    int i1=0;
    int i2=p;
    int i3=mid+1;
    int comps=0;

    // Temp array
    int temp[r-p+1];

    // Merge in sorted form the 2 arrays
    while(i2<=mid && i3<=r)
    {
        comps++;
        if(array[i2]<array[i3])
            temp[i1++]=array[i2++];
        else
            temp[i1++]=array[i3++];
    }
    // Merge the remaining elements in left array
    while(i2<=mid)
    {
        temp[i1++]=array[i2++];
    }

    // Merge the remaining elements in right array
    while(i3<=r)
    {
        temp[i1++]=array[i3++];
    }

    // Move from temp array to master array
    for(int i=p;i<=r;i++)
    {
        array[i]=temp[i-p];
    }
    return comps;
}

//Auxilary merge sort function, recursive
int mergeSortAux(int* array, int p, int r)
{
    int comps=0;

    if(p<r)
    {
        int mid=(p+r)>>1;
        comps+=mergeSortAux(array,p,mid);
        comps+=mergeSortAux(array,mid+1,r);
        comps+=merge(array,p,r);
    }
    return comps;
}

int mergesort(int *array,int n)
{
    return mergeSortAux(array,0,n-1);
}


int main(int argc,char** argv)
{
    int N;
    int *array;
    int *array_orig;
    ifstream input_file;

    if(argc==3) 
    {
        N=atoi(argv[1]);
        array_orig=new int[N]; 
        array=new int[N]; 
        memset(array_orig,0,sizeof(array));
        input_file.open(argv[2]);
    }
    else 
    {
        printf("The program needs a counter and a filename as argument \n");
        exit(0);
    }
    int i=0;
    while(i<N && !input_file.eof())
    {
	input_file >> array_orig[i++];
    }
    //Selection sort
    {
        memcpy(array,array_orig,N*sizeof(int));
        int comps=selectionsort(array,N);
        printf("Selection sort: number of comparisons:\t\t\t%d\n",comps);
    }
    //Insertion
    {
        memcpy(array,array_orig,N*sizeof(int));
        int comps=insertionsort(array,N);
        printf("Insertion sort: number of comparisons:\t\t\t%d\n",comps);
    }
    //Bubble
    {
        memcpy(array,array_orig,N*sizeof(int));
        int comps=bubblesort(array,N);
        printf("Bubble sort: number of comparisons:\t\t\t%d\n",comps);
    }
    //Quicksort
    {
        memcpy(array,array_orig,N*sizeof(int));
        int comps=quicksort(array,N);
        printf("Quick sort: number of comparisons:\t\t\t%d\n",comps);
    }
    //Merge sort
    {
        memcpy(array,array_orig,N*sizeof(int));
        int comps=mergesort(array,N);
        printf("Merge sort: number of comparisons:\t\t\t%d\n",comps);
    }
    return 0;
}
