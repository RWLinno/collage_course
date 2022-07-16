#include<iostream>
using namespace std;

struct Complex{
	double real; //ʵ�� 
	double img; //�鲿
	Complex operator +(Complex b)const{
		return (Complex){real+b.real,img+b.img};
	}
	Complex operator -(Complex b)const{
		return (Complex){real-b.real,img-b.img};
	}
	Complex operator *(Complex b)const{ //�����˷� 
		return (Complex){real*b.real-img*b.img,real*b.img+img*b.real};
	}
	Complex operator /(Complex b)const{ //�������� 
		double x=b.real*b.real+b.img*b.img;
		double y=real*b.real+img*b.img;
		double z=img*b.real-real*b.img;
		return (Complex){y/x,z/x};
	}
}s[105];

signed main(){
	cout<<"�����һ��������ʵ�����鲿"<<endl; 
	cin>>s[1].real>>s[1].img;
	cout<<"����ڶ���������ʵ�����鲿"<<endl;
	cin>>s[2].real>>s[2].img;
	s[3]=s[1]+s[2];
	s[4]=s[1]-s[2];
	s[5]=s[1]*s[2];
	s[6]=s[1]/s[2];
	cout<<"�������ӷ��������:"<<s[3].real<<" "<<s[3].img<<endl;
	cout<<"�����������������:"<<s[4].real<<" "<<s[4].img<<endl;
	cout<<"�������˷��������:"<<s[5].real<<" "<<s[5].img<<endl;
	cout<<"�����������������:"<<s[6].real<<" "<<s[6].img<<endl; 
	return 0;
}



