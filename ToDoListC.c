#include <stdio.h>  //standard I/O library for input and output operations.
#include <stdlib.h> //standard library for memory allocation and process control.
#include <string.h> //string library for string manipulation functions.

typedef struct
{
    char *task;    // a string representing the task description.
    int completed; // integer flag indicating whether the task is completed (1 for completed(true), 0 for not completed(false)).
} Task;

Task *tasks = NULL; // pointer to an array of Task structures, representing the list of tasks.
int taskCount = 0;  // integer to keep track of the number of tasks.
void addTask(const char *task)
{
    // Allocate memory for a new task
    tasks = (Task *)realloc(tasks, (taskCount + 1) * sizeof(Task));
    tasks[taskCount].task = (char *)malloc(strlen(task) + 1); // Allocate memory for the task description
    tasks[taskCount].completed = 0;                           // Set the task as not completed
    strcpy(tasks[taskCount].task, task);                      // Copy the task description into the allocated memory
    taskCount++;                                              // Increment the task count;
    printf("Task added\n");
}
void listTask()
{
    char status;
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].completed == 1)
        {
            status = 'd';
        }
        else
        {
            status = 'n';
        }
        printf("%d. %s [%c]\n", i + 1, tasks[i].task, status); //%d is used to print the task number(integer), %s for the task description(string), and %c for the status character(character).
    }
}
void completeTask(int index)
{
    if (index <= taskCount && index > 0)
    {
        tasks[index - 1].completed = 1; // Mark the task as completed
        printf("Task %d marked as completed.\n", index);
    }
    else
    {
        printf("Invalid index.\n");
    }
}
void deleteTask(int index)
{
    if (index <= taskCount && index > 0)
    {
        index = index - 1;                          // Adjust index to be zero-based
        free(tasks[index].task);                    // Free the memory allocated for the task description
        for (int i = index; i < taskCount - 1; i++) // Shift remaining tasks to fill the gap
        {
            tasks[i] = tasks[i + 1];
        }
        taskCount--;                                              // Decrement the task count
        tasks = (Task *)realloc(tasks, taskCount * sizeof(Task)); // Resize the tasks array
        printf("Task %d deleted.\n", index + 1);
    }
    else
    {
        printf("Invalid index.\n");
    }
}
void editTask(int index, const char *task)
{
    if (index <= taskCount && index > 0)
    {
        index = index - 1;

        char *newTask = (char *)realloc(tasks[index].task, strlen(task) + 1);
        if (newTask != NULL)
        {
            tasks[index].task = newTask;     // Reallocate memory for the task
            strcpy(tasks[index].task, task); // Copy the new task description into the allocated memory
            printf("Task %d edited.\n", index + 1);
        }
        else
        {
            printf("Memory allocation failed.\n");
        }
    }
    else
    {
        printf("Invalid index.\n");
    }
}
int main()
{
    int choice;
    int indexInput;
    int running = 1;

    char taskInput[254];
    printf("\nOptions:\n");
    printf("1. Add Task\n");
    printf("2. List Tasks\n");
    printf("3. Complete Task\n");
    printf("4. Edit Task\n");
    printf("5. Delete Task\n");
    printf("6. Exit\n");

    while (running)
    {
        printf("\nEnter choice (1, 2, 3, 4, 5, 6): ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf

        switch (choice)
        {
        case 1:
            printf("Enter task: ");
            getchar();
            fgets(taskInput, sizeof(taskInput), stdin);
            taskInput[strcspn(taskInput, "\n")] = '\0;';
            addTask(taskInput);
            break;
        case 2:
            listTask();
            break;
        case 3:
            printf("Enter index: ");
            scanf("%d", &indexInput);
            completeTask(indexInput);
            break;
        case 4:
            printf("Enter index: ");
            scanf("%d", &indexInput);
            printf("Enter edited task: ");
            fgets(taskInput, sizeof(taskInput), stdin);
            taskInput[strcspn(taskInput, "\n")] = 0;
            editTask(indexInput, taskInput);
            break;
        case 5:
            printf("Enter index: ");
            scanf("%d", &indexInput);
            deleteTask(indexInput);
            break;
        case 6:
            running = 0;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
    free(tasks); // Free the allocated memory for tasks before exiting
    return 0;
}