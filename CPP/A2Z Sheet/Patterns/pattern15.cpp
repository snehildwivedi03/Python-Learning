#include<iostream>
using namespace std;


int main(){
int n;
cout<<"Enter no of rows: ";
cin>>n;
int num =1;
for(int i=n;i>=1;i--){
    for(char ch= 'A';ch<='A'+i-1;ch++){
       cout<<ch<<" " ;
       num+=1;
    }
 
    cout<<endl;
   
    
}

    return 0;
}


