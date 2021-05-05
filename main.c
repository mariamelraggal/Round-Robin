#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;


typedef struct Node
{
    Process data;
    struct Node* next;
} Node;
/*
 *
 */
typedef struct
{
    Node *head;
    Node *tail;
    /* TODO: ADD YOUR CODE HERE */
} Queue;
/*
 *
 */
Queue* init()
{
    Queue* q =malloc(sizeof(Queue));
    q->head=NULL;
    q->tail=NULL;
    return q;
    /* TODO: ADD YOUR CODE HERE */
}
Node* newNode(Process p)
{
    Node *n =malloc(sizeof(Node));
    n->data=p;
    n->next=NULL;
    return n;
}

int isEmpty(Queue *q)
{

    if(q->head==NULL)
        return 1;
    else
        return -1;
}
/*
 *
 */
Process dequeue(Queue *q)
{
    if(q->head)
    {
        Process p;
        Node*temp=q->head;
        p=temp->data;
        q->head=temp->next;
        free(temp);
        if(q->head==NULL)
            q->tail=NULL;
        return p;
    }
    /* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void enqueue(Queue *q, Process val)
{

    Node* n =newNode(val);
    if(q->head==NULL)
        q->head=q->tail=n;
    else
    {
        q->tail->next=n;
        q->tail=n;
    }
    /* TODO: ADD YOUR CODE HERE */
}
void destroy(Queue *q)
{
    while(isEmpty(q)==-1)
    {
        dequeue(q);
    }
}

void RoundRobin(char *filename)
{
    Process p[100];
    FILE *f;
    int num=0;
    int count=0;
    Queue *q=init();
    f=fopen(filename,"r");
    fscanf(f,"Watching time slots = %d\n",&num);
    while(!feof(f))
    {
        p[count].name=malloc(4*sizeof(char));
        fscanf(f,"%s %d %d\n",p[count].name,&p[count].starting_time,&p[count].remaining_time);
        count++;
    }
    fclose(f);
    int i=0;
    int j=0;
    int x=0;
    for(i=0; i<num; i++)
    {
        for(j=0;j<count;j++)
        {
            if(p[j].starting_time==i)
            {
                enqueue(q,p[j]);
            }
        }

            if(isEmpty(q)==-1)
            {
                Process s=dequeue(q);
                s.remaining_time--;
                if(s.remaining_time!=0)
                {
                    printf("%s (%d->%d)\n",s.name,x,x+1);
                    x++;
                    enqueue(q,s);
                }
                else if (s.remaining_time==0)
                {
                    printf("%s (%d->%d) %s aborts\n",s.name,x,x+1,s.name);
                    x++;
                }
            }
            else
        {
            printf("idle (%d->%d)\n",x,x+1);
            x++;
        }
        if(i==num-1)
        {
            printf("stop\n");
        }
    }

    destroy(q);

}
/*
 *
 */
int main()
{
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }

    return 0;
}
