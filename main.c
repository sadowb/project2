//
//  main.c
//  TIRED
//
//  Created by abdelhadi marjane on 24/4/2022.
//

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node
{
    char operator;
    struct node *next;
}stack;
char expression[100];
char postfix[100];
stack *top = NULL;
int StackIsEmpty(void);
int OpeningParantheses(void);
void push(char*,int);
int HigherPrecedence(int,char*);
//void InfixExpression();
//void IN_Order();
//void PRE_Order();
//void Computing();
char ArrayOfPostFixExpressions [100] [100];
void pop(void);
void InfixToPostfix(void);
int check(int);
void CheckErors(int i);
void checkSpecialErors(char*,int i);
int count = 0;

int countpostfix = 0;
int main()
{
    int choice ;
    char temporary;
    do
    {
        printf("MENU\n");
        printf("enter the choice that you would like to make \n");
        printf("press 1 to enter INFIX expression \n");
        printf("enter 2 for IN_ORDER Traversal \n");
        printf("enter 3 for PRE_ORDER traversal \n");
        printf("enter 4 for POST_ORDER traversal \n ");
        printf("enter 5 for computing the expression \n");
        printf("enter 6 to quit the program \n");

        scanf(" %d",&choice);
        scanf("%c",&temporary);
        switch (choice)
        {
        case 1:
            
            InfixToPostfix();
            break;
        case 2:
           // IN_Order();
            break;
        case 3:
           // PRE_ORDER();
            break;
        case 4:
           // POST_Order();
            break;
        case 5:
           // Computing();
            break;
        default:
        printf("ERROR YOU ENTERD THE WRONG INPUT \n");
                
            break;
        }
    } while (choice!= 6);

    return 0;
}
void InfixToPostfix() // this is the function that transforms from infix to postfix
{
    int i = 0;
    int special = i;
    int checkspecial;
    int precedence = 0;
    char temp;
    int j = 0;
    int checkstack;
    printf("enter the infix expression\n");
    scanf("%s",expression);
    for ( i = 0; i <strlen(expression) ;  i++) // this a loop that is for scaning the entire expression based on the lenght of the expression 
    {

        if ( check(i)) // this fucntion checks and the send the id of the openrand that we are looking at and it checks if it is a number or a sign
        {
            temp = expression[i]; // if it is then it appends it to temp will hold the cureent charachter that the program is looking at
            
            postfix[countpostfix++] = temp; // then it will assing it to the postfix expression 
            printf("%c\n",temp); // this is to see the character 

            printf("\n postfix at index %d is %c \n",i,postfix[i]); // this is where i print the postfix expression 
         //   CheckErors(i);
            printf("\n %s\n",postfix);
            //countpostfix++; // this is to tell the program that we have added an expression and to keep track of the expression 
            printf("number of postfix is %d",countpostfix); // this is to tell us the number of expressions not the + or - sign
        }


        else if( ( expression[i] == '+'|| expression[i] == '-' || expression[i] == '*'|| expression[i] == '/'  ) ) // if not then it will check if the current operand that the program is curently lokking at is a + or - sign 
        {
            precedence = HigherPrecedence(i,expression); // precdence is a fucntion that would look at the stack and check for precedence it will return  a number that number would tell us if the current is greater of lees than the currnent one
            if (precedence == 2) { // this is for the case when the stack is empty
                printf("this is the first operand %c \n",top->operator);
            }
            if(precedence == 4) // this is if the stack have + or - sign and the current expression have the same sign then it will push them to the stack 
            {
                push(expression, i);
            }
            if(precedence == 0) // this is to check if the current top is more important that the current character that we are looking at 
            {
                push(expression, i); // push  the operator
            }
            else if(precedence == 1)
            {
                while (top!=NULL)
                {
                    temp = top->operator;
                    postfix[countpostfix++] = temp;
                   
                    pop();
                }
                push(expression,i);
                
               /* for ( j = 0; j <= count ; j++)      // count keeps track of how many are in the stack
                {
                    
                    temp = top->operator;
                    postfix[countpostfix++] = temp;
                   // strcat(postfix,&temp);
                    // checkSpecialErors(&temp, i);
                    pop();
                    
                  //   if(expression[i] == '+' || expression[i] == '-')
                   //     push(expression,i);
                }
                
              checkstack = StackIsEmpty();
                special = i+1;
              checkspecial = check(special);
                if(checkspecial == 1 && checkstack == 1)
                            {
                                
                                push(expression,i);
                                
                                temp = expression[i];
                                postfix[countpostfix] = temp;
                                postfix[countpostfix] = top->operator;
                                pop();
                                printf("here is the postfix notation %s ",postfix);
                            }
                else if(checkspecial == 5 && checkstack == 0)
                {
                    temp = top->operator;
                    strcat(postfix, &temp);
                    pop();
                   
                }
                */
            }
            
           
        }
        
           

    }
    
    for (int j = 0; j < count; j++)
    {
        if (top==NULL)
        {
            printf("the stack is empty\n");
        }
        else
        {
            temp = top->operator;
        strcat(postfix,&temp);
        pop();
        }
    }
    
    printf("here is the postfix expression %s",postfix);
    for (int i = 0; i<strlen(postfix); i++) {
        postfix[i] = '\0';
    }
    printf("the thing that i want to see\n");
   
}
int StackIsEmpty()
{
    if (top == NULL)
    {
        printf("stack is empty");
        return 1;
        
    }
    else
    {
        return 0;
    }
}
int HigherPrecedence(int i,char* variable)
{
    if (top == NULL) {     //this only works if the stack was emmpty
        push(variable,i);
        return 2;
    }

    // thesse two are for checking importance 
    else if( ( top->operator =='+' || top->operator =='-')&& (expression[i] =='*' || expression[i] =='/' ) )
    {
        return 0; // this is to check if the top is more important than the current expression

    }
    else if( ( (top->operator =='*') || (top->operator =='/') ) && ( (expression[i] =='+') || (expression[i] =='-') ) )
    {                   
        return 1; // same thing as above 
    }

    // theses are for checking if the top and the current expressioin have the same sign then we push them

    else if( (  (top->operator =='+') || ( top->operator =='-') )&& ( (expression[i] =='+') || (expression[i] =='-') ) )
    {
    return 4;
    }
    else if( ( (top->operator =='*') || (top->operator =='/') ) && (expression[i] =='*' || expression[i] =='/' ) )
    {
    return 4;
    }
    
    return 4; // this does'nt serve anything
}
void pop()
{                           // this function is used to pop the stack based on the importance
    stack *tempo;
    if(top == NULL)
    {
        printf("stack is empty");
        
    }
    else {

       
                    
                
                        tempo = top;
                        top = top->next;
                        free(tempo);
                        tempo = NULL;
                        count--;           // this is to tell the program that it has less operands 
            }
    
    
    
}
void push(char* e,int i)
{
        char operand ;
        operand = expression[i];
        
        stack *new = NULL;
        new = (stack*)malloc(sizeof(stack));
        if (new == NULL)
        {
         printf("there is not enough memory");
        }
        else
        {
            count++;                // this is for pushing into the stack
            if (top == NULL)
            {
                new->operator = operand ;
                new->next = NULL;
                top = new;
            }
            else
            {
                new->operator = operand ;
                new->next = top;
                top = new;
            }
        }
        
}
int check(int i)            // this is to check if the expression is a number or a sign
{
    if(expression[i] == '0' || expression[i] == '1'  || expression[i] == '2'  || expression[i] == '3' || expression[i] == '4'  || expression[i] == '5'  || expression[i] == '6'  || expression[i] == '7'  || expression[i] == '8'  || expression[i] == '9')
    {
        return 1;
    }
    else if (expression[i] == '\0')       // this is to check if we have arrived at the end of the expression
    {
        return 5;
    }
        
    return 0;
}

/*void CheckErors(int i)
{
    for(int check = 0;check<strlen(postfix);check++)
    {
            if(postfix[i]=='\x02' || postfix[i]=='\x01')
            {
                printf("there is an eror");
                postfix[i] = '\0';
               
            }
    }
    
}
void checkSpecialErors(char* temp,int i)
{
    for(int check = 0;check<strlen(postfix);check++)
    {
            if(postfix[i]=='\x02' || postfix[i]=='\x01')
            {
                printf("there is an eror");
                postfix[i] = *temp;
               
            }
    }
    
}
*/
