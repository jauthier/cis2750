#include <stdio.>

class B {
    int b;
    
    int add(int c){
        int d;
        printf("%d\n",b+c+d)
    }
}

int main(){
    int num = 1;
    class B myB;
    
    myB.add(num);

    if (num == 2)
        printf("The number is 2");
    else
        printf("The number is %d",num);

     return 0;
}
