#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int priority;
    int burstTime;
    int remainingTime;
};

void enqueue(struct Process *queue, int *rear, struct Process process)
{
    queue[(*rear)++] = process;
}

struct Process dequeue(struct Process *queue, int *front)
{
    struct Process process = queue[*front];
    (*front)++;
    return process;
}

int main()
{
    int timeQuantum = 2;

    struct Process queue1[100], queue2[100];
    int front1 = 0, rear1 = 0, front2 = 0, rear2 = 0;
    struct Process p1 = {1, 0, 6, 6};
    struct Process p2 = {2, 1, 8, 8};
    struct Process p3 = {3, 0, 4, 4};
    struct Process p4 = {4, 2, 7, 7};
    enqueue(queue1, &rear1, p1);
    enqueue(queue1, &rear1, p2);
    enqueue(queue1, &rear1, p3);
    enqueue(queue1, &rear1, p4);

    int currentTime = 0;
    while (front1 < rear1 || front2 < rear2)
    {

        if (front1 < rear1)
        {
            struct Process current = dequeue(queue1, &front1);
            int timeSlice = (current.remainingTime < 2) ? current.remainingTime : 2;
            printf("Running process P%d from Queue 1 for %d units of time.\n", current.pid, timeSlice);
            currentTime += timeSlice;
            current.remainingTime -= timeSlice;
            if (current.remainingTime > 0)
            {
                enqueue(queue1, &rear1, current);
            }
            else
            {
                printf("Process P%d from Queue 1 completed.\n", current.pid);
            }
        }
        else
        {
            if (front2 < rear2)
            {
                struct Process current = dequeue(queue2, &front2);
                int timeSlice = (current.remainingTime < timeQuantum) ? current.remainingTime : timeQuantum;
                printf("Running process P%d from Queue 2 for %d units of time.\n", current.pid, timeSlice);
                currentTime += timeSlice;
                current.remainingTime -= timeSlice;
                if (current.remainingTime > 0)
                {
                    enqueue(queue2, &rear2, current);
                }
                else
                {
                    printf("Process P%d from Queue 2 completed.\n", current.pid);
                }
            }
        }

        if (front1 == rear1 && front2 < rear2)
        {

            struct Process current = dequeue(queue2, &front2);
            if (current.priority == 0)
            {
                enqueue(queue1, &rear1, current);
            }
            else
            {
                enqueue(queue2, &rear2, current);
            }
        }
    }

    return 0;
}
