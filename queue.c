//
// Created by admin on 2018/9/29.
//
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR 1
#define OVERFLOW 2

typedef int Status;
//typedef int QElemType;
typedef struct {
    int ArrivalTime;
    int Duration;
}QElemType;

typedef struct QNode{
    struct QNode  *next;
    QElemType     data;
}QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;


Status InitQueue(LinkQueue *Q){
    Q->front = Q->rear = (QNode*)malloc(sizeof(QNode));  //Both point to head node
    if(!Q->rear)
        exit(OVERFLOW);
    Q->front->next = NULL;  //There is only one head node, so its next should be NULL
    return OK;
}

Status DestroyQueue(LinkQueue *Q){
    while (Q->front){
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}

int QueueLength(LinkQueue Q){
    QueuePtr p = Q.front;
    int i;
    for (i = 1; p = p->next; ++i)
        ;
    return i;
}

Status EnQueue(LinkQueue *Q, QElemType e){
    QueuePtr p = (QNode*)malloc(sizeof(QNode));
    p->data = e; p->next = NULL;
    Q->rear = Q->rear->next = p;
    return OK;
}

Status DeQueue(LinkQueue *Q, QElemType *e){
    if (Q->front == Q->rear)
        exit(ERROR);
    QueuePtr p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (p->next == NULL || p == Q->rear)
        Q->rear = Q->front;
    free(p);
    return OK;
}

/* assume C can make a circle sequence queue */
#define MAXSIZE 100
typedef struct {
    QElemType  *base;
    int        front;
    int        rear;
}SqQueue;

Status InitSqQueue(SqQueue Q){
    Q.base = (QElemType*)malloc(MAXSIZE * sizeof(QElemType));
    if (!Q.base)
        exit(OVERFLOW);
    Q.front = Q.rear = 0;
    return OK;
}

int SqQueueLength(SqQueue Q){
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;  // circle!
}

Status SqEnQueue(SqQueue Q, QElemType e){
    if ((Q.rear + 1) % MAXSIZE == Q.front)  // Full!
        exit(ERROR);
    Q.base[Q.rear + 1] = e;
    Q.rear = (Q.rear + 1) % MAXSIZE;
    return OK;
}

Status SqDeQueue(SqQueue Q, QElemType *e){
    if (Q.rear == Q.front)  // Empty!
        exit(ERROR);
    *e = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return OK;
}

/* discrete event simulation */
void OpenForDay();
int MoreEvent();
void EventDriver(int, int);
void Invalid();

void BankSimulation(int CloseTime){
    OpenForDay();
    while (MoreEvent()){
        int OccurTime, EventType;
        EventDriver(OccurTime, EventType);
        switch (EventType){
            case 'A':
                break;
            case 'D':
                break;
            default:Invalid();
                break;
        }
    }
}

typedef struct {
    int OccurTime;
    int NType;  // 0 presents arrival, 1-4 presents departure
}Event, ElemType;

typedef struct LNode{
    ElemType       data;
    struct LNode*  next;
}LNode, *LinkList;

typedef struct {
    int ArrivalTime;
    int Duration;
}QElemType;

typedef LinkList EventList;

EventList ev;
Event     en;
LinkQueue q[5];
QElemType customer;
int TotalTime, CustomerNum;

