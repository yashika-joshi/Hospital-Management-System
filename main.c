
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a patient
struct Patient {
    int priority;  // Higher value means higher priority
    char name[50];
    char gender [15];
    char disease[50];
    int age;
    struct Patient *next;
};

// Function to create a new patient node
struct Patient* createPatient(char name[],char gender[], char disease[],int age, int priority) {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    strcpy(newPatient->name, name);
    strcpy(newPatient->disease, disease);
    strcpy(newPatient->gender, gender);
    newPatient->age=age;
    newPatient->priority = priority;
    newPatient->next = NULL;
    return newPatient;
}

// Function to insert a patient based on priority
void insertPatient(struct Patient** head, char name[],char gender[],char disease[],int age, int priority) {
    struct Patient* newPatient = createPatient(name, gender,disease,age, priority);

    // If the list is empty or the new patient has higher priority
    if (*head == NULL || (*head)->priority < priority) {
        newPatient->next = *head;
        *head = newPatient;
    } else {
        struct Patient* current = *head;

        // Traverse to find the right position
        while (current->next != NULL && current->next->priority >= priority) {
            current = current->next;
        }

        newPatient->next = current->next;
        current->next = newPatient;
    }
}

// Function to remove and return the patient with the highest priority
void servePatient(struct Patient** head) {
    if (*head == NULL) {
        printf("No patients in the queue.\n");
        return;
    }

    struct Patient* temp = *head;
    printf("Serving patient: %s (Priority: %d)\n", temp->name, temp->priority);
    *head = (*head)->next;
    free(temp);
}

// Display the patient list
void displayPatients(struct Patient* head) {
    if (head == NULL) {
        printf("No patients in the queue.\n");
        return;
    }

    printf("Patient Queue (Higher Priority First):\n");
    while (head != NULL) {
        printf("Name: %s,Gender:%s, Disease: %s, Age: %d, Priority: %d\n", head->name,head->gender, head->disease, head->age, head->priority);
        head = head->next;
    }
}

int main() {
    struct Patient* patientQueue = NULL;
    int choice, priority,age;
    char name[50];
    char gender[15];
    char disease[50];

    while (1) {
        printf("\nHospital Patient Management System\n");
        printf("1. Add Patient\n");
        printf("2. Serve Patient\n");
        printf("3. Display Patients\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter patient name: ");
                scanf("%s", name);
                printf("enter gender of patient :");
                scanf("%s", gender);
                printf("Enter the disease: ");
                scanf("%s", disease);
                printf("Enter the age of patient: ");
                scanf("%d", &age);
                printf("Enter priority (Higher number means higher priority): ");
                scanf("%d", &priority);
                insertPatient(&patientQueue, name,gender,disease,age, priority);
                break;

            case 2:
                servePatient(&patientQueue);
                break;

            case 3:
                displayPatients(patientQueue);
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}