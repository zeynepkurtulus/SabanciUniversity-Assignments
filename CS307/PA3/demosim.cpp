#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num_students, num_assistants; // global variables to keep track of number of asistants and students
sem_t student_sem, assistant_sem, demo_sem,demo_sem2, mutex; // global semaphore declarations
int waiting_students = 0, waiting_assistants = 0;

// a function that handles the student thread
void *student_thread(void *arg)
{
   // int id = *(int *)arg;
    printf("Thread ID: %ld, Role:Student, I want to enter the classroom.\n",  pthread_self()); // indicate the thread id, and request
    sem_wait(&student_sem);
    printf("Thread ID: %ld, Role:Student, I entered the classroom.\n", pthread_self());
    sem_wait(&mutex); // mutex semaphore is used to ensure that the increment operations can be done atomically 
    waiting_students++;
    if (waiting_students >= 2 && waiting_assistants > 0)
    {
        waiting_students -= 2;
        waiting_assistants--;
        sem_post(&assistant_sem);
        sem_post(&demo_sem);
    }
    sem_post(&mutex);
   
    printf("Thread ID: %ld, Role:Student, I am now participating.\n", pthread_self());
    if(waiting_students<=0){
        sem_post(&demo_sem2);        
    }
    sem_wait(&demo_sem);
    sem_post(&demo_sem);
    sem_wait(&demo_sem);
    printf("Thread ID: %ld, Role:Student, I left the classroom.\n", pthread_self());
    sem_post(&student_sem);
    sem_post(&demo_sem2);
    return NULL;
}

void *assistant_thread(void *arg)
{
   // int id = *(int *)arg;
    printf("Thread ID: %ld, Role:Assistant, I entered the classroom.\n", pthread_self());

    sem_wait(&mutex); // lock the mutex semaphore to access shared variables
    waiting_assistants++; // increment the number of waiting assistants
    if (waiting_students >= 2) // check if there are at least two waiting students and one waiting assistant
    {
        waiting_students -= 2;
        waiting_assistants--;
        sem_post(&assistant_sem);
        sem_post(&demo_sem);
    }
    sem_post(&mutex);

    sem_wait(&assistant_sem);
    printf("Thread ID: %ld, Role:Assistant, I am now participating.\n", pthread_self());
    sem_post(&assistant_sem);
    sem_wait(&demo_sem2);
    printf("Thread ID: %ld, Role:Assistant, demo is over.\n", pthread_self());
    sem_post(&demo_sem);
    sem_wait(&student_sem);
    sem_wait(&student_sem);
    printf("Thread ID: %ld, Role:Assistant, I left the classroom.\n", pthread_self());
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <number_of_assistants> <number_of_students>\n", argv[0]);
        return 1;
    }

    num_assistants = atoi(argv[1]);
    num_students = atoi(argv[2]);

    if (num_assistants <= 0 || num_students != num_assistants * 2)
    {
        printf("Invalid arguments.\n");
        return 1;
    }
    pthread_t students[num_students], assistants[num_assistants];
    int student_ids[num_students], assistant_ids[num_assistants];
     printf("My program complies with all the conditions.\n");
    sem_init(&student_sem, 0, num_assistants * 3);
    sem_init(&assistant_sem, 0, 0);
    sem_init(&demo_sem, 0, 0);
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < num_assistants; i++)
    {
        assistant_ids[i] = num_students + i;
        pthread_create(&assistants[i], NULL, assistant_thread, &assistant_ids[i]);
    }
    for (int i = 0; i < num_students; i++)
    {
        student_ids[i] = i;
        pthread_create(&students[i], NULL, student_thread, &student_ids[i]);
    } 
    for (int i = 0; i < num_students; i++)
    {
        pthread_join(students[i], NULL);
    }
    for (int i = 0; i < num_assistants; i++)
    {
        pthread_join(assistants[i], NULL);
    }
    sem_destroy(&student_sem);
    sem_destroy(&assistant_sem);
    sem_destroy(&demo_sem);
    sem_destroy(&mutex);

    printf("The main terminates.\n");
    return 0;
}
