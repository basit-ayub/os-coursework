//i233018_SE4B_OS_A1_Q1
#include <stdio.h>
#include <stdbool.h>
struct PCB
{
    int PID;            // Process ID
    char* state;        // State of the process
    int burstTime;      // Time required by the process to complete its execution
    bool IO_req;         // If the process requires I/O operation
    bool interrupt;     // If the process is interrupted
    bool completedIO;
    struct PCB *next;   // Pointer to the next PCB
};
// Ready Queue and its functions
struct readyQueue        //linkedList based ReadyQueue
{
    struct PCB *front;
    struct PCB*rear;
};
    void init_readyQueue(struct readyQueue* q)
    {
        q->front=NULL;
        q->rear=NULL;
    }
    void insertReadyQueue(struct readyQueue* q,struct PCB* p)
    {
        p->next=NULL;
        printf("Process %d moved to READY queue\n",p->PID); // print statement for process moved to ready queue
        if(q->front==NULL)
        {
            q->front=p;
            q->rear=p;
        }
        else
        {
            q->rear->next=p;
            q->rear=p;
        }
    }
    void printReadyQueue(struct readyQueue* const q)
    {
        struct PCB* temp=q->front;
        while(temp!=NULL)
        {
            printf("PID: %d\n",temp->PID);
            printf("State: %s\n",temp->state);
            printf("Burst Time: %d\n",temp->burstTime);
            printf("IO Request: %d\n",temp->IO_req);
            printf("Interrupt: %d\n",temp->interrupt);
            temp=temp->next;
        }
    }
    struct PCB* removeReadyQueue(struct readyQueue* q)
    {
        struct PCB* temp=q->front;
        q->front=q->front->next;
        return temp;
    }
    struct PCB* peekReadyQueue(struct readyQueue* q)
    {
        return q->front;
    }
// Waiting Queue and its functions
struct waitingQueue
    {
        struct PCB *front;
        struct PCB*rear;
    };
    void init_waitingQueue(struct waitingQueue* q)
    {
        q->front=NULL;
        q->rear=NULL;
    }
    void insertWaitingQueue(struct waitingQueue* q,struct PCB* p)
    {
        //printf("Process %d moved to WAITING queue\n",p->PID); // print statement for process moved to waiting queue
        p->next=NULL;
        if(q->front==NULL)
        {
            q->front=p;
            q->rear=p;
        }
        else
        {
            q->rear->next=p;
            q->rear=p;
        }
    }
    void printWaitingQueue(struct waitingQueue* const q)
    {
        struct PCB* temp=q->front;
        while(temp!=NULL)
        {
            printf("PID: %d\n",temp->PID);
            printf("State: %s\n",temp->state);
            printf("Burst Time: %d\n",temp->burstTime);
            printf("IO Request: %d\n",temp->IO_req);
            printf("Interrupt: %d\n",temp->interrupt);
            temp=temp->next;
        }
    }
    struct PCB* removeWaitingQueue(struct waitingQueue* q)
    {
        struct PCB* temp=q->front;
        q->front=q->front->next;
        return temp;
    }
    struct PCB* peekWaitingQueue(struct waitingQueue* q)
    {
        return q->front;
    }
int main()
{
        // Creating PCBs
        struct PCB P1 ={1,"New",7,true,false,false,NULL};
        struct PCB P2 ={2,"New",4,false,true,false,NULL};
        struct PCB P3 ={3,"New",5,true,false,false,NULL};
        struct PCB P4 ={4,"New",6,false,false,false,NULL};

        // Initializing Ready Queue and Waiting Queue
        struct readyQueue readyQ;
        struct waitingQueue waitingQ;

        init_readyQueue(&readyQ);
        init_waitingQueue(&waitingQ);

        insertReadyQueue(&readyQ,&P1);
        insertReadyQueue(&readyQ,&P2);
        insertReadyQueue(&readyQ,&P3);
        insertReadyQueue(&readyQ,&P4);

            while (peekReadyQueue(&readyQ))
            {
                struct PCB * temp = removeReadyQueue(&readyQ);
                if (temp->completedIO)
                    printf("Process %d completed I/O operation\n",temp->PID); // print statement for process completed I/O operation

                printf("Process %d is running\n",temp->PID); // print statement for process running
                temp->state="Running";
                if (temp->IO_req)
                {
                    printf("Process %d requires I/O operation\n",temp->PID); // print statement for process requiring I/O operation
                    temp->state="Waiting";
                    insertWaitingQueue(&waitingQ,temp);
                }
                else if (temp->interrupt)
                {
                    printf("Interrupted Process %d moved BACK to READY queue\n",temp->PID); // print statement for interrupted process moved to ready queue
                    temp->state="Ready";
                    temp->interrupt=false;
                    insertReadyQueue(&readyQ,temp); // sent back to ready Queue
                }
                else
                {
                    printf("Process %d completed and moved to terminated\n",temp->PID); // print statement for process completed
                    temp->state="Terminated";
                }
                if (peekWaitingQueue(&waitingQ))
                {
                    struct PCB * temp2 = removeWaitingQueue(&waitingQ);
                    temp2->state="Ready";
                    temp2->completedIO=true;
                    temp2->IO_req=false;
                    insertReadyQueue(&readyQ,temp2);
                }
            }
    return 0;
}
