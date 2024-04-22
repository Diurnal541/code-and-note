#include"iostream" 
#include"cmath"  
#include"cstdio"  
using namespace std;
float x1,x2,a,b,c,z;
void func1(){ 
    x1=( -b+sqrt(z) )/( 2*a );
    x2=( -b-sqrt(z) )/( 2*a );
}
 
void func2(){  
    x1=x2=( -b )/( 2*a );
}
 
void func3(){  
    z=sqrt(-z);
    printf("x1=%.3f+%.3fi x2=%.3f-%.3fi\n",-b/(2*a),z/(2*a),-b/(2*a),z/(2*a));
}
 
int main(){
    cin>>a>>b>>c;
    z=b*b-4*a*c;
    if(z>0){
        func1();
    }else if(z<0){
        func3();
        return 0;
    }else{
        func2();
    }
    printf("x1=%.3f x2=%.3f\n",x1,x2);
    return 0;
}