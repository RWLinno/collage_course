//��ҵ10.24 
#include<bits/stdc++.h>
using namespace std;

void insert(int arr[], int temp[], int n){  //2-·�������� 
    int i,first,final,k;
    first=final=0;//�ֱ��¼temp���������ֵ����Сֵ��λ��
    temp[0]=arr[0];
    for(i=1;i<n;i++){ // ������Ԫ�ر���С��Ԫ��С
        if(arr[i]<temp[first]){
            first=(first-1+n)%n;
            temp[first] = arr[i];
        }
        else if(arr[i]>temp[final]){ //������Ԫ�ر����Ԫ�ش�
            final=(final+1+n)%n;
            temp[final]=arr[i];
        }
        else{ // ����Ԫ�ر���С�󣬱����С
            k = (final + 1 + n) % n;
            while (temp[((k - 1) + n) % n] > arr[i]) { //������ֵ�ȵ�ǰֵСʱ����Ҫ�ƶ���ǰֵ��λ��
                temp[(k + n) % n] =temp[(k - 1 + n) % n];
                k = (k - 1 + n) % n;
            }
            temp[(k + n) % n] = arr[i]; //�����ֵ
            final = (final + 1 + n) % n; //��Ϊ���ֵ��λ�øı䣬������Ҫʵʱ����final��λ��
        }
    }
    for (k = 0; k < n; k ++) {    // �������¼���Ƶ�ԭ����˳�����
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

