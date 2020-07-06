#include "bits/stdc++.h"
using namespace std;

static vector<int>arr;

void insertSort(int start,int end){
    for(int i=start+1;i<=end;i++){
        for(int j=i;j>start;j--){
            if(arr[j]<arr[j-1]){
                swap(arr[j],arr[j-1]);
            }
            else break;
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
    }
    swap(arr[storeIndex],arr[end]);
    return storeIndex;

}

void quickSort(int start,int end){
    if(start>=end) return ;
    if(start-end<=10) {
        insertSort(start,end);
        return ;
    }
    int pivot=partition(start,end);
    quickSort(start,pivot-1);
    quickSort(pivot+1,end);
}

int main(){

      arr={5,2,7,3,4,9,3};
      quickSort(0,arr.size()-1);

      for(auto n:arr){
          cout<<n<<" ";
      }

}