#include "bits/stdc++.h"
using namespace std;

static vector<int>arr;
const int PARTITION_LIMIT=10;

static int count_loop=0;

void insertSort(int start,int end){
    for(int i=start+1;i<=end;i++){
        for(int j=i;j>start;j--){
            if(arr[j]<arr[j-1]){
                swap(arr[j],arr[j-1]);
            }
            else break;
            count_loop++;
        }
        // for(auto n:arr) cout<<n<<" ";
        // cout<<endl;
    }
}

int partition(int start,int end){

    int pivotElement=arr[end];
    int storeIndex=start;
    for(int i=start;i<end;i++){
        if(pivotElement>=arr[i]){
            swap(arr[i],arr[storeIndex++]);
        }
        count_loop++;
    }
    swap(arr[storeIndex],arr[end]);
    return storeIndex;

}

void quickSort(int start,int end){
    if(start>=end) return ;
    // if(start-end<=PARTITION_LIMIT) {
    //     insertSort(start,end);
    //     return ;
    // }
    int pivot=partition(start,end);
    quickSort(start,pivot-1);
    quickSort(pivot+1,end);
}

int main(){

      arr={52, 37, 63, 14, 17, 8, 6, 25,27,3,6,29,67,30,20,40,100,35};
      quickSort(0,arr.size()-1);

      cout<<count_loop<<endl;

      for(auto n:arr){
          cout<<n<<" ";
      }
}