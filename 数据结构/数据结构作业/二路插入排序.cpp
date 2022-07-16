//作业10.24 
#include<bits/stdc++.h>
using namespace std;

void insert(int arr[], int temp[], int n){  //2-路插入排序 
    int i,first,final,k;
    first=final=0;//分别记录temp数组中最大值和最小值的位置
    temp[0]=arr[0];
    for(i=1;i<n;i++){ // 待插入元素比最小的元素小
        if(arr[i]<temp[first]){
            first=(first-1+n)%n;
            temp[first] = arr[i];
        }
        else if(arr[i]>temp[final]){ //待插入元素比最大元素大
            final=(final+1+n)%n;
            temp[final]=arr[i];
        }
        else{ // 插入元素比最小大，比最大小
            k = (final + 1 + n) % n;
            while (temp[((k - 1) + n) % n] > arr[i]) { //当插入值比当前值小时，需要移动当前值的位置
                temp[(k + n) % n] =temp[(k - 1 + n) % n];
                k = (k - 1 + n) % n;
            }
            temp[(k + n) % n] = arr[i]; //插入该值
            final = (final + 1 + n) % n; //因为最大值的位置改变，所以需要实时更新final的位置
        }
    }
    for (k = 0; k < n; k ++) {    // 将排序记录复制到原来的顺序表里
        arr[k] = temp[(first + k) % n];
    }
}

signed main(){
    int a[8] = {32,1,7,75,24,45,96,61};
    int temp[8];
    insert(a,temp,8);
    for (int i = 0; i < 8; i ++){
        printf("%d ", a[i]);
    }
	return 0;
}

