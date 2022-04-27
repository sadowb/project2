//
//  main.c
//  version4
//
//  Created by abdelhadi marjane on 25/4/2022.
//
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node             // this data structure will be used for calculating and converting to postfix
{
    char operator;
    struct node *next;
    int data;
}stack;
stack *top = NULL;
int isOperand(char);        // this is to check if the current character is a (+,-,/,*,^) or just any other expression it returns 1 for (+,-,/,*,^) and 0 for any other variable
int pre(char);                  // this is to check for the precedence value in the current top of the stack (+,-,/,*,^) is bigger than the current operand for expample if we have in the top of the stack a * sign and the current index at the expression is pointing at + then we will pop all of the content stack if it was in inverse then we push it to the stach then repaeat
char* InfixToPostfix(char*);        // this is the fucntion that changes to postfix expression the explanation is given above it sends the expression and recieves the postfix expression
char pop(void);             // these are for poping function and push sends the character to be pushed
void push(char x);
void pushcomputing(int x);      // thesse are special for computing the expression they use the stack to compute it
int popcomputing(void);         // also the same
int Computing(char*);           // this is the function for computing the postfix expression
char* removeSpaces(char*);
                    // this is for removing the spaces from the expression
int checkbalence(char*);
int checkparenthesis(char*);
char* InfixToPostfixParantheses(char*);
char *postfixincrement(char*);
char* post(char* infix);
int convertchar(char);
int add(int);
int main()
{
    
    int choice ;
    char temporary;         // this is to hold the \n by the gets
    char infix[100];
    char *postfix;          // this will hold the expression
   long int eraseIntial;        // this is to erase the # character that i must add to the stack intially then i remove it
    int result;// this holds the computation
 
    do
    {
        printf("\n MENU\n");
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
            
            
            
            printf("enter the postfix expression that you would like to see \n");
              
                gets(infix);
               // scanf("%c",&temporary);// this is to prevent taht the expression get a \'n'
              postfix = removeSpaces(infix);            // calling the function and sending the expression to remove the spaces
                printf("first expression %s \n",postfix);
                postfix = post(infix);
                printf("second expression %s \n",postfix);
           // postfix = postfixincrement(infix);
               //check = checkparenthesis(infix);
               // if (check == 1) {
                 //   checkbalence(infix);
                //  postfix = InfixToPostfixParantheses(infix);
                
                   // printf("here is the postfix %s \n",postfix);
              //  }
              /* else {
                 */
                
                    push('#');                          // very important my alghorithm is based that the stack must be full at the start so i pushed any character then i remove it at the end because i know always it would be at the end
                    postfix = InfixToPostfix(postfix);            // this is to hold the postfix expression it is a pointer
                        
                        eraseIntial = strlen(postfix);      // this is to remove the initial variable that i added at the top
                        
                        postfix[--eraseIntial] = '\0';
                
           
                
            printf("her is the psotfix expression \n");
                printf("%s",postfix);
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
        printf("this is the postfix expression that would compute the result");
               result = Computing(postfix);         // here i send the expression that i will calculate
                printf("here is the result\n");
                printf("%d",result);
            break;
        default:
        printf("ERROR YOU ENTERD THE WRONG INPUT \n");
                
            break;
        }
    } while (choice!= 6);

    return 0;

}
int pre(char x)
{
    if (x == '(')
    {
        return 0;
    }
    if(x == '+' || x == '-')
    {
        return 1;                       // this is used for determening the precedence of the operand
    }
    else if(x == '*' || x == '/')
    {
        return 2;
    }
    else if(x == '^')
    {
        return 3;
    }
    
    return 0;
}

int isOperand(char x)
{
          // this is to check if the expression is a number or a sign

    if(x == '*' || x == '/'  || x == '-'  || x == '+' || x == '^' || x == '(' || x == ')')
    {
        return 0;
    }
    else       // this is to check if we have arrived at the end of the expression
    {
        return 1; // this is if it was another charcter then just send back that it is an alphabet or a number
    }

}
char* InfixToPostfix(char *infix)
{
    int i = 0 , j = 0;
    char *postfix;                          // this is the core function it doesnt deal with paranthesis or unary operators
    long int len = strlen(infix);
    postfix = (char*)malloc((len+2)*sizeof(char));
    while(infix[i]!='\0')
    {
        
        if(isOperand(infix[i]))
        {
            postfix[j++] = infix[i++];          // i added the the number ot the expression
        }
        
        else{
          
            if (pre(infix[i]) > pre(top->operator))
            {                                       // i added the + or * sign depending on the value of the cureent top is it a multiple sign
                push(infix[i++]);               // then i added to to the push function then i increment the i
            }
            else{
                postfix[j++] = pop();           // if not then i pop the operand
            }
            
        }
        printf("\n%s\n",postfix);
        printf("\n");
    }
    while(top!=NULL)
    {                               // if there are any remaning (+,-,/,*,^) pop all of them and i added them to the expression
        postfix[j++] = pop();
       
    }
    
    postfix[j] = '\0';          // then i added the null charcter and i send it back to the postfix expression

    return postfix;
}
void push(char x)
{
    stack* new = NULL;
    new = (stack*)malloc(sizeof(stack));
    if(new == NULL )                                        // this is for pushing any (+,-,^,/,*) sign
    {
        printf("the stack is full no memory left\n");

    }
    if (top == NULL)
           {
             new->operator = x ;
                new->next = NULL;
                  top = new;
            }
            else
             {
                new->operator = x ;
                   new->next = top;
                    top = new;
             }
}
char pop()
{
    char x = -1;
                                    // this is for pop in the operand
    stack*temp;
    
    temp = NULL;
    
    if(top == NULL)
    {
        printf("stack is empty\n");
    }
    else
    {
        temp = top;
        top = top->next;
        x = temp->operator;
        free(temp);
        temp = NULL;
    }
    return x;           // i return the expression
}

void pushcomputing(int x)
{
    stack* new = NULL;
    new = (stack*)malloc(sizeof(stack));
    if(new == NULL )
    {
        printf("the stack is full no memory left\n");
                                                            // this is special for the case of computing the expression
    }                                                           // i give it the integer
    if (top == NULL)
           {
             new->data = x ;
                new->next = NULL;
                  top = new;
            }
            else
             {
                new->data = x ;
                   new->next = top;
                    top = new;
            }
    printf("%d",x);
}
int popcomputing()
{
    int x = -1;
    
    stack*temp;
    
    temp = NULL;                    // same as the fucntion pop but i send back the intger when i pop it
    
    if(top == NULL)
    {
        printf("stack is empty\n");
    }
    else
    {
        temp = top;
        top = top->next;
        x = temp->data;
        free(temp);
        temp = NULL;
    }
    return x;
}

int Computing(char*postfix)
{
              // this only works if i have the postexpression
    int result = 0;
    int x1 = 0,x2 = 0;
    for (int i = 0; postfix[i]!='\0'; i++)
    
    {
        if (isOperand(postfix[i]))
        {
            
            pushcomputing(postfix[i] - '0');            // this is to transform a char (+,-,^,/,*) sign to an integer using ascci code
        }
        else
        
        {
            x2 = popcomputing();
            x1 = popcomputing();        // this for poping the two numbers from the stack to compute them
            switch (postfix[i])
            
            {
                case '+':
                    result = x1 + x2;
                    break;
                case '-':
                    result = x1-x2;
                    break;
                case '*':
                    result = x1*x2;
                    break;
                case '/':
                    if(x2 == 0)
                    {
                        fprintf(stderr, "divisionby zero! exiting...\n ");      // this is for checking the runtime error
                        exit(-1);
                    }
                    else
                    {
                        result = x1/x2;
                    }
                    break;
                case '^':
                    result = pow(x2,x1);        // this is the pow function coming from the math library
                    
                default:
                    break;
            }
            pushcomputing(result);              // then i push it back to the stack then repeat until i traverse the expression
            
        }
    }
    return top->data;           // when done i return back the result of the calculations
}
char* removeSpaces(char* check) // this is to check for spaces
{
    
    int i = 0, j = 0;           // j is used to keep track of the index of the expression that we are revising
    while(check[i]!='\0')
    {
        if (check[i] != ' ')        // if it founds a space then it will skip it
        {
            check[j++] = check[i];      // it keeps adding to the expression only the variables then it incremets the index of the expression that would tell it where is the next index it should add to
        }
        i++;
    }
    check[j] = '\0';            // this is to add the null terminator
    return check;
}
/*
int checkbalence(char*exp)
{
   
    for (int i = 0 ; exp[i]!='\0';i++)
    {
        if (exp[i] == '(')
            {
                push(exp[i]);
               
            }
            else if(exp[i] == ')')
            {
                if (top == NULL)
                {
                    return 0; // this only happens in rare expression like (c-d)) where there is an extra paranthesis then it will send 0 i mean if it gets  to the end then it sees that there is a closing bracket but the stack is empty no opening bracket then that means that there is an extra operand
                }
                else
                {
                    pop();
                }
                
        }
        
            
    }
    if (top == NULL)
    {
        return 1;               // in order for this to work the stacj should be empty
    }
    else
    {
        return 0;
    }
}
 */
/*
int checkparenthesis(char* check)
{
    for (int i = 0; check[i]!='\0'; i++)
    
    {
        if (check[i] == '(' )
        {
            printf("there are parentiesis");
            return 1;
        }
    }
    
    return 0;
    
}
 */
char* InfixToPostfixParantheses( char *infix)
{
    int i = 0 , j = 0;
    char *postfix;                          // this is the core function it doesnt deal with paranthesis or unary operators
    long int len = strlen(infix);
    postfix = (char*)malloc((len+2)*sizeof(char));
    while (infix[i]!='\0')
    
    {
        if (isOperand(infix[i]))
        {
            postfix[j++] = infix[i++];
        }
        if(top== NULL && infix[i] == '(')
        {
            push(infix[i++]);
            
            if (isOperand(infix[i]))
            {
                postfix[j++] = infix[i++];
            }
        }
        else if(pre(infix[i]) > pre(top->operator))
        {
            push(infix[i]);
            
            if (isOperand(infix[i]))
            {
                postfix[j++] = infix[i++];
            }
        }
        else if(infix[i] == ')')
        {
           postfix[j++] = pop();
            pop();
        }
    }
   
    
    return infix;
    
} /*
char* postfixincrement(char *infix)
{
    char *postfix;                          // this is the core function it doesnt deal with paranthesis or unary operators
    long int len = strlen(infix);
    postfix = (char*)malloc((len+1)*sizeof(char));
    int i = 0, j = 0 ;
    
    int increment;
    infix[len] = '\0';
    char expression;
    for(int t = 0 ; t<len ; t++)
    {
        if (isOperand(infix[i]))
        {
            postfix[j++] = infix[i];
        }
        else if((infix[i] == '+' && infix[++i] == '+') || (infix[i] == '-' && infix[++i] == '-'))
        {
            if (infix[i] == '+')
            {
                
                printf("here is the expression for infix index 0 %c ",infix[0]);
                printf("here is the expression for infix index 1 %c ",infix[1]);
                printf("here is the expresion for index i %c",postfix[j-1]);
                expression = postfix[j-1];
               increment = convertchar(expression);
                printf("her is the increment %d",increment);
                increment++;
            }
            else if(infix[i] == '-')
            {
                pushcomputing(infix[i]-'0');
                expression = infix[i];
                printf("here is the expression \n");
              increment = convertchar(expression);
                printf("her is the the data %d ",top->data);
                increment--;
            }
            
            expression = increment + '0';
            postfix[j-1] = increment + '0';
            j++;
            printf("here is the postfix expression %s\n",postfix);
            
        }
        printf("here is the postfix expression %s \n",postfix);
    }
    return postfix;
}
   */
/*
int add(int x)
{
    printf("x is %d",x);
    return x;
}
int convertchar(char x)
{
     int b;
    printf("x is %c",x);
        b = x - '0';
        return b;
}
 */
char* post(char* infix)
{
    int integer;
    char temp;
    char *expression;
    long int len = strlen(infix);
    expression  = (char*)malloc((len+1)*sizeof(char));
    int i = 0 , j = 2;
    int z = 0;
    for (i = 0; i<len + 1; i++)
    
    {
        /*if ((infix[i] == infix[j] && infix[j] == '+' )&&(isOperand(infix[i])) )
        {
            integer = infix[i-1] - '0';
            integer++;
            temp = integer + '0';
            expression[z++] = temp;
            printf("here is the expression at index %d is %c",z,expression[z]);
            
        }
         */
        if ( ( ( (isOperand(infix[i]) == 1) && (infix[j] == '+' ) &&(infix[j-1] == '+') ) ) )
        {
            integer = infix[i] - '0';
            integer++;
            temp = integer + '0';
            expression[z++] = temp;
            
            i = i+2;
        }
        else if ( ( ( (isOperand(infix[i]) == 1) && (infix[j] == '-' ) &&(infix[j-1] == '-') ) ) )
        {
            integer = infix[i-1] - '0';
            integer--;
            temp = integer + '0';
            expression[--z] = temp;
            i = i + 2;
        }
        else
        {
            expression[z++] = infix[i];
        }
        j++;
    }
    
    printf("here is the expression %s \n",expression);
    
    return expression;
}
