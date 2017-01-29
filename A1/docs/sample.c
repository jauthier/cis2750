#include <stdio.>

class B {
    int a;
    int b;

    void add(int c){
        int d;
        printf("%d\n",b+c+d);
    }

    int add(){
        int d;
		return b+a+d;
    }
    
    char *character(){
        char *name;
        strcpy(name,"Jessica");
        return name;
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
