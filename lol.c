#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int global_var = 10;  // Global variable to show different behavior

void demonstrate_memory_copy() {
    int local_var = 5;  // Local variable

    printf("Before fork:\n");
    printf("Address of local_var: %p\n", (void*)&local_var);
    printf("Value of local_var: %d\n", local_var);
    printf("Address of global_var: %p\n", (void*)&global_var);
    printf("Value of global_var: %d\n\n", global_var);

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("Address of local_var: %p\n", (void*)&local_var);
        printf("Value of local_var: %d\n", local_var);
        printf("Address of global_var: %p\n", (void*)&global_var);
        printf("Value of global_var: %d\n\n", global_var);

        // Modify local and global variables
        local_var = 100;
        global_var = 200;

        printf("After modification in child:\n");
        printf("Address of local_var: %p\n", (void*)&local_var);
        printf("Value of local_var: %d\n", local_var);
        printf("Address of global_var: %p\n", (void*)&global_var);
        printf("Value of global_var: %d\n\n", global_var);

        return;
    } else {
        // Parent process
        wait(NULL);  // Wait for child to complete

        printf("Parent Process:\n");
        printf("Address of local_var: %p\n", (void*)&local_var);
        printf("Value of local_var: %d\n", local_var);
        printf("Address of global_var: %p\n", (void*)&global_var);
        printf("Value of global_var: %d\n", global_var);
    }
}

int main() {
    demonstrate_memory_copy();
    return 0;
}