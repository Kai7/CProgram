#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
struct thread_data {
    unsigned long thread_id;
    unsigned long thread_count;
};
 
void *Hello(void* rank) {
    printf("Hello from thread %ld of %ld\n", ((struct thread_data*) rank) -> thread_id, ((struct thread_data*) rank) -> thread_count);
         
    return NULL;
}
 
int main(int argc, char* argv[]) {
    unsigned long thread;
    unsigned long thread_count = strtoul(argv[1], NULL, 10);
    struct thread_data* thread_array = (thread_data*)malloc(thread_count * sizeof(struct thread_data));
    pthread_t* thread_handles = (pthread_t*)malloc(thread_count * sizeof(pthread_t));
                     
    /* 呼叫 argc，避免 -Wextra 編譯警告 */
    printf("Input argument numbers: %d\n", argc);
                         
    /* 分流 thread */
    for (thread = 0; thread < thread_count; thread++) {
        thread_array[thread].thread_id = thread;
        thread_array[thread].thread_count = thread_count;
        pthread_create(&thread_handles[thread], NULL, Hello, (void*) &thread_array[thread]);
    }
  
     /* 合流 thread */
    for (thread = 0; thread < thread_count; thread++)
        pthread_join(thread_handles[thread], NULL);
      
    free(thread_handles);
    free(thread_array);
    return 0;
}
