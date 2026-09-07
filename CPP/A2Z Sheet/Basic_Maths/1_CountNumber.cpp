#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main(){
int n;
cout<<"Enter the number: ";
cin>>n;
// int count = 0;
// while(n>0){
//     count++;
//     n = n/10;
// }
// cout<<"The digits are: "<<count<<endl;

int cnt = (int)log10(n)+1;
cout<<"The digits are: "<<cnt<<endl;



    return 0;
}