#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

int reverseNumber(int n){
    long int revNum = 0;
while(n>0){

long int lastDigit  =n % 10;
revNum  = revNum*10 + lastDigit;
n = n/10;

}
return revNum;
}


int main(){
    int n;
    cout<<"Enter the number: ";
    cin>>n;
    cout<<"The reverse number is: "<<reverseNumber(n)<<endl;





    return 0;
}