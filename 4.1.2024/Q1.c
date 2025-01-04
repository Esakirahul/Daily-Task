//Evaluate an expression given in prefix notation using a stack.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int applyOperator(int operand1,int operand2,char operator){
    switch (operator)
    {
    case '+':return operand1 + operand2;
    case '-':return operand1 - operand2;
    case '*':return operand1 * operand2;
    case '/':return operand1 / operand2;
    
    default:
        return 0;
    }
}
int evaluatePrefix(char *expr){
    int stackSize=100;
    int *stack=(int*)malloc(stackSize * sizeof(int));
    int top=-1;

    for(int i=strlen(expr)-1;i>=0;i--){
        char ch=expr[i];
        if(ch==' '){
            continue;
        }
        if(isdigit(ch)){
            stack[++top]=ch-'0';
        }
        else if(ch=='+' || ch=='-' || ch=='*' || ch== '/'){
            int operand1=stack[top--];
            int operand2=stack[top--];
            int result=applyOperator(operand1,operand2,ch);
            stack[++top]=result;

        }
    }
    int result=stack[top];
    free(stack);
    return result;
}
int main(){
    char expression[100];
    fgets(expression,sizeof(expression),stdin);
    size_t len=sizeof(expression);
    if(len>0 && expression[len-1]=='\n'){
        expression[len-1]='\0';
    }
    int result=evaluatePrefix(expression);
    printf("%d",result);

}