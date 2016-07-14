#include "threads.h"
extern int scheduling_type;
extern thread_queue_t *ready_list;

void thread_enqueue(thread_t *t, thread_queue_t *q){
    //put down your own code

    thread_node_t *add_this = malloc(sizeof(thread_node_t));
    add_this->thread = t;
    add_this->next = NULL;

    if ((q->size == 0)){
        q->head = add_this;
        q->tail =add_this;
        q->size = q->size + 1;
    }else{
        q->tail->next = add_this;
        q->tail = q->tail->next;
        q->size = q->size + 1;
    }
}

thread_t *thread_dequeue(thread_queue_t *q){
    //put down your own code
    if ((q->size == 0)){
        return NULL;
    }
    if ((q->size == 1)){
        q->tail = NULL;
  	  }
        thread_node_t *tmp = q->head;
        q->head = q->head->next;
        q->size = q->size - 1;
        return tmp->thread;
   
    // You need to return real thread pointer
}

thread_t* scheduler(){
    switch(scheduling_type)
    {
        case 0:          // Round Robin
            /* Write your code here*/
             return  thread_dequeue(ready_list); // Return pointer of the next thread
        case 1: {         // Lottery
            /*Write your code here*/
            thread_node_t *p = ready_list->head;
        
            int total = 0;
            while (p != NULL)
            {
                total += p->thread->priority;
                p = p->next;
            }
            int aim;
            srand((int)time(NULL));
            aim = rand()%total+1;
            p = ready_list->head;
            while (p != NULL)
            {
                aim = aim - p->thread->priority;
                if (aim > 0) {
                    p = p->next;
                }
                else {
                    return p->thread;
                }
            }
        }
        case 2:          //First come first serve
            return ready_list->head->thread;
        default:
            return NULL;
    }
}
