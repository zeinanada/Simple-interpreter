#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define max 50
#define Type double

typedef struct
{
    char variable[max];
    Type value;
    struct node *next;

} node;
typedef struct
{
    node *head;
    node *tail;
} linkedlist;
typedef struct
{
    Type items[max];
    int top;
} stack;
void initialize( stack*s)
{
    s->top=-1;
}

void initializestack( stack*s)
{
    s->top=-1;
}

double pop(stack*s)
{
    double a;
    a=s->items[s->top];
    s->top-=1;
    return a;
}
void push(stack*s, double value)
{
    s->top+=1;
    s->items[s->top]=value;

}
double checktop(stack*s)
{
    return s->items[s->top];
}

int stackisempty(stack*s)
{
    if(s->top==-1)
        return 1;
    else
        return 0;
}
int getsize(char s[] )
{
    int count,i=0;
    for(count=0; s[count]!='\0'; count++)
    {
        i++;
    }
    return i;

}
int isfull(stack*s)
{
    if(s->top==max)
        return 1;
    else return 0;

}
void initializelist(linkedlist *l)
{
    l->head=NULL;
    l->tail=NULL;

}
int isEmpty(node *n)
{
    if(n==NULL)
        return 1;
    else
        return 0;
}

node *newnode(char c[] ,Type val)
{
    node*n=malloc(sizeof(node));
    n->value=val;
    strcpy(n->variable,c);
    n->next=NULL;
    return n;
}
void addhead(linkedlist *l,char c[] ,Type val)
{
    node *temp=l->head;
    int flag=0;

    while(temp!=NULL)
    {
        if(strcasecmp(temp->variable,c) == 0)
        {
            temp->value=val;
            flag=1;

        }
        temp=temp->next;
    }
    if(flag==1)
        return;
    else
    {
        node*n=newnode(c,val);

        if(isEmpty(l->head))
        {
            l->head=l->tail=n;
        }
        else
        {
            n->next=l->head;
            l->head=n;
        }
    }

}
int checkpriority (char ch)
{
    switch(ch)
    {
    case '(':
    case')':
        return 2;
    case'/':
    case'*':
        return 1;
    case'+':
    case'-':
        return 0;
    default:
        return-1;


    }


}
int isoprator(char c)
{
    if(c=='+'||c=='/'||c=='-'||c=='*'||c=='%')
        return 1;
    else
        return 0;
}

int infixtopostfix(char infix[],char postfix[])
{
    stack s;
    initializestack(&s);
    char ch1=NULL,c;
    int i=0,j=0,flag=1;
    int countbo=0,countbrcl=0;
    while (infix[i]!='\0')
    {
        if(infix[i]=='(')
        {
            countbo++;
        }

        if(infix[i]==')')
        {
            countbrcl++;
        }
        if(isoprator(infix[i]))
        {
            if(!isdigit(infix[i+1])&&infix[i+1]!='(')
            {
                return 0;
            }
            //printf("%c",infix[i]);
            i++;
            if(isoprator(infix[i]))
            {
                //printf("%c",infix[i++]);
                flag=0;
                i--;
            }
            else
            {
                flag=1;
                i--;
            }
        }


        c = infix[i];
        if (isdigit(c)||c=='.')
        {
            if(infix[i+1]=='(')
            {
                //printf("hena");
                return 0;

            }
            postfix[j]=c;
            j++;
        }
        else if(c=='(')
        {
            push(&s,c);

        }

        else if(c==')')
        {
            while((char)checktop(&s)!='(')
            {
                postfix[j]=' ';
                j++;
                postfix[j]=(char)pop(&s);
                j++;
            }

            pop(&s);

        }


        else if(stackisempty(&s))
        {
            postfix[j]=' ';
            j++;
            push(&s,c);

        }
        else
        {
            while (!stackisempty(&s)&&checkpriority(checktop(&s))>=checkpriority(c)&&(char)checktop(&s)!='(')
            {
                ch1=(char)pop(&s);
                postfix[j]=' ';
                j++;
                postfix[j]=ch1;
                j++;


            }

            postfix[j]=' ';
            j++;
            push(&s,c);
        }
        i++;
    }
    while (!stackisempty(&s))
    {
        ch1=pop(&s);
        postfix[j]=' ';
        j++;
        postfix[j]=ch1;
        j++;

    }

    postfix[j]='\0' ;
    //printf(" \n>post fix:%s<",postfix);

    if(countbo==countbrcl && flag==1)
    {
        return 1;
    }
    else if(countbo!=countbrcl || flag==0)
        return 0;

}
Type evaluatePostfix(char postfix[])
{
    stack s1;
    initialize(&s1);
    int i,k=0,j;
    char x[max];
    double c;
    double char1 ,char2,result;
    for(i=0; i<(getsize(postfix)); i++)
    {
        if((postfix[i]>='0'&&postfix[i]<='9')||postfix[i]=='.' )
        {

            if((postfix[i+1]=='\0'))
            {
                x[k]=postfix[i];
                k++;
                x[k]='\0';
                c= atof(x);

                push(&s1,(c));
            }
            x[k]=postfix[i];
            k++;


        }
        else if( postfix[i]==' ')
        {
            if(isoprator(postfix[i-1])) {}
            else
            {
                x[k]='\0';
                c= atof(x);
                push(&s1,(c));

                k=0;
            }


        }
        else
        {
            char1= pop(&s1);

            char2=pop(&s1);


            switch(postfix[i])
            {
            case'+':
                result=char2+char1;
                push(&s1,result);
                break;
            case '-':
                result=char2-char1;
                push(&s1,result);
                break;
            case '*':
                result=char2*char1;
                push(&s1,result);
                break;
            case '/':
                result=char2/char1;
                push(&s1,result);
                break;

            }

        }
    }

    return (pop(&s1));


}
void getvar(char e[],char var[],int *c)
{
    int i=*c;
    if(isalpha(e[0]))
    {
        var[i]=e[0];
        i++;
    }

    while(e[i]!='='&&e[i]!='\0')
    {
        var[i]=e[i];
        i++;

    }

    if (e[i]=='\0'&&(strcasecmp(e,"end")!=0))
    {
        *c = -1;
        printf("INVALD Expression\n");

    }
    if(*c!=-1)
        *c=i+1;

    var[i]='\0';


}
int replace(char e[],char r[],linkedlist *l)
{
    node *temp;
    char word[max];
    int i=0,k,j=0,flag,w;
    char value[max];
    Type val;
    while((e[i]!='\0'))

    {

        if((isdigit(e[i]))|| (e[i]=='.')|| isoprator(e[i])||(e[i]=='(')||e[i]==')'||(e[i]=='='))
        {
            if(e[i]=='=')
            {

                return 0;
            }
            r[j]=e[i];
            j++;
            i++;
        }
        else if(isalpha(e[i]))
        {
            temp =l->head;
            flag=0;
            w=0;
            while(!isoprator(e[i])&&e[i]!='\0'&&e[i]!=')'&&e[i]!='(')
            {
                word[w]=e[i];
                i++;
                w++;
            }
            word[w]='\0';
            //printf("%s",word);

            while(temp!=NULL&&flag==0)
            {

               // printf("\n %s,%s \n ",temp->variable,word);

                if(strcasecmp(temp->variable,word) == 0)
                {

                    //printf(" \n done \n");
                    val=temp->value;
                    flag = 1;
                    //printf(" Value= %lf\n",val);
                    sprintf(value,"%0.2lf",val);
                    if(val<0)
                    {
                        r[j++]='(';
                        r[j++]='0';
                        k=0;
                        while(value[k]!='\0')
                        {
                            r[j]=value[k];
                            j++;
                            k++;
                        }
                        r[j++]=')';

                    }
                    else
                    {
                        k=0;
                        while(value[k]!='\0')
                        {
                            r[j]=value[k];
                            j++;
                            k++;
                        }
                    }

                }
                temp=temp->next;

            }
            if(temp==NULL&&flag==0)
            {
                printf("Variable %s not initialized",word);
            }
        }
    }
    r[j]='\0';
    return 1;

}
int main()
{

    linkedlist *l=malloc(sizeof(linkedlist));
    initializelist(l);
    int c,i,j;
    char exp[max];
    char var[max];
    char temp[max];
    char rep[max];
    char pos[max];
    int flag,hint;
    Type val;
    do
    {
        c=0;
        printf("Enter the expression or \"end\" to exit:\n");
        gets(exp);
        getvar(exp,var,&c);
        if(strcasecmp(exp,"end")== 0)
        {
            exit(0);

        }
        if(c == -1)
        {
            continue;
        }
        i=c;
        j=0;
        while(exp[i]!='\0')
        {
            temp[j]=exp[i];
            j++;
            i++;

        }

        temp[j]= '\0' ;
        //printf(" temp %s \n",temp);
        hint=replace(temp,rep,l);
        if(hint==1)
        {
           // printf ("rep is %s \n",rep);
            flag = infixtopostfix(rep,pos);
            if(flag==1)
            {
                val = evaluatePostfix(pos);
                addhead(l,var,val);
                printf("\nThe value of entered expression= %.2lf \n",val);

            }
            else
            {
                printf("\nerror in expression \n");
            }
        }
        else
        {
            printf("\nerror in expression \n");
        }
    }

    while(strcasecmp(exp,"end")!=0);
    return 0;
}
