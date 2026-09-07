#include<iostream>
using namespace std;


int main(){
int n;
cout<<"Enter no of rows: ";
cin>>n;
int num =1;
for(int i=0;i<n;i++){
    for(char ch= 'A';ch<='A'+i;ch++){
       cout<<ch<<" " ;
       num+=1;
    }
 
    cout<<endl;
   
    
}

    return 0;
}


