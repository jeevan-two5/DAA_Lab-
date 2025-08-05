Lomuto Partition:
int Lomuto_Partition(int arr[], int l, int h)
{  
    int pivot=arr[h];
    int i=l-1;
    for(int j=l;j<=h-1;j++){
        if(arr[j]<pivot){
            i++;
            swap(arr[i],arr[j]);
        }
    }
    swap(arr[i+1],arr[h]);
    return i+1;
}

void qSort(int arr[],int l,int h){
    if(l<h){
        int p=Lumuto_Partition(arr,l,h);
        qSort(arr,l,p-1);
        qSort(arr,p+1,h);
    }
}
 
Hoares partition

#include <bits/stdc++.h>
using namespace std;

int Hoares_partition(int arr[], int l, int h)
{  
    int pivot=arr[l];
    int i=l-1,j=h+1;
    while(true){
        do{
            i++;
        }while(arr[i]<pivot);
        do{
            j--;
        }while(arr[j]>pivot);
        if(i>=j)return j;
        swap(arr[i],arr[j]);
    }
}

void qSort(int arr[],int l,int h){
    if(l<h){
        int p=Hoares_partition(arr,l,h);
        qSort(arr,l,p);
        qSort(arr,p+1,h);
    }
}
 
int main() {
    int arr[]={8,4,7,9,3,10,5};
int n=sizeof(arr)/sizeof(arr[0]);
qSort(arr,0,n-1);
for(int x: arr)
   cout<<x<<" ";
}
