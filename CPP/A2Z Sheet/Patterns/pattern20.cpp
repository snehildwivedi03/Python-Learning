#include<iostream>
using namespace std;


int main(){
int n;
cout<<"Enter no of rows: ";
cin>>n;

for(int i=0;i<n;i++){
    for(int j = 0;j<=i;j++){
       cout<<"*";
    }
 int space  = 2*n - 2*i -2;
    for(int j = 0;j<space;j++){
        cout<<" ";
    }
    for(int j = 0;j<=i;j++){
       cout<<"*";
    }
    cout<<endl;
   
    
}
//inverted pattern as above
for(int i=0;i<n;i++){
    for(int j = 0;j<n-i;j++){
       cout<<"*";
    }
    int space  = 2*i;   
    for(int j = 0;j<space;j++){
        cout<<" ";
    }
    for(int j = n-i;j>0;j--){
       cout<<"*";
    }
    cout<<endl;
}

    return 0;
}