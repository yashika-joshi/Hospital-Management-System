
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros for formatting
#define CENTER_SPACES "                                            "  // spaces for centering
#ifdef _WIN32
    #define CLEAR_SCREEN() system("cls")
#else
    #define CLEAR_SCREEN() system("clear")
#endif

// Structure to represent a patient
struct Patient {
    int priority;  // Higher value means higher priority
    char name[50];
    char gender[15];
    char disease[50];
    int age;
    struct Patient *next;
};

// Function to display the hospital management logo
void displayLogo() {
    CLEAR_SCREEN();
    printf(CENTER_SPACES "\n");
    printf(CENTER_SPACES "* * * * * * * * * * * * * * * * * * *\n");
    printf(CENTER_SPACES "*                                   *\n");
    printf(CENTER_SPACES "*    HOSPITAL MANAGEMENT SYSTEM     *\n");
    printf(CENTER_SPACES "*       Caring for Every Life       *\n");
    printf(CENTER_SPACES "*                                   *\n");
    printf(CENTER_SPACES "* * * * * * * * * * * * * * * * * * *\n");
    printf(CENTER_SPACES "\n\n");
}

// Function to create a new patient node
struct Patient* createPatient(char name[], char gender[], char disease[], int age, int priority) {
    struct Patient* newPatient = (struct Patient*)malloc(sizeof(struct Patient));
    strcpy(newPatient->name, name);
    strcpy(newPatient->disease, disease);
    strcpy(newPatient->gender, gender);
    newPatient->age = age;
    newPatient->priority = priority;
    newPatient->next = NULL;
    return newPatient;
}

// Function to insert a patient based on priority
void insertPatient(struct Patient** head, char name[], char gender[], char disease[], int age, int priority) {
    struct Patient* newPatient = createPatient(name, gender, disease, age, priority);

    if (*head == NULL || (*head)->priority < priority) {
        newPatient->next = *head;
        *head = newPatient;
    } else {
        struct Patient* current = *head;
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
        printf(CENTER_SPACES "No patients in the queue.\n");
        return;
    }

    struct Patient* temp = *head;
    printf(CENTER_SPACES "Serving patient: %s (Priority: %d)\n", temp->name, temp->priority);
    *head = (*head)->next;
    free(temp);
}

// Function to delete a specific patient by name
void deletePatient(struct Patient** head, char name[]) {
    if (*head == NULL) {
        printf(CENTER_SPACES "No patients in the queue.\n");
        return;
    }

    struct Patient* temp = *head;
    struct Patient* prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf(CENTER_SPACES "Patient with name '%s' not found.\n", name);
        return;
    }

    if (prev == NULL) {
        // Deleting head
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    printf(CENTER_SPACES "Deleted patient: %s\n", temp->name);
    free(temp);
}

// Display the patient list
void displayPatients(struct Patient* head) {
    if (head == NULL) {
        printf(CENTER_SPACES "No patients in the queue.\n");
        return;
    }

    printf("\n\n");
    printf(CENTER_SPACES "PATIENT QUEUE (Higher Priority First):\n\n");
    while (head != NULL) {
        printf(CENTER_SPACES "Name     : %s\n", head->name);
        printf(CENTER_SPACES "Gender   : %s\n", head->gender);
        printf(CENTER_SPACES "Disease  : %s\n", head->disease);
        printf(CENTER_SPACES "Age      : %d\n", head->age);
        printf(CENTER_SPACES "Priority : %d\n", head->priority);
        printf(CENTER_SPACES "------------------------------\n");
        head = head->next;
    }
}

// Count the total number of patients
int countPatients(struct Patient* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Free the entire patient list (memory cleanup)
void freePatients(struct Patient* head) {
    while (head != NULL) {
        struct Patient* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Patient* patientQueue = NULL;
    int choice, priority, age;
    char name[50];
    char gender[15];
    char disease[50];

    displayLogo();  // Show logo at start

    while (1) {
        printf("\n\n");
        printf(CENTER_SPACES "HOSPITAL PATIENT MANAGEMENT SYSTEM\n");
        printf("\n");
        printf(CENTER_SPACES "1. Add Patient\n");
        printf(CENTER_SPACES "2. Serve Patient\n");
        printf(CENTER_SPACES "3. Display Patients\n");
        printf(CENTER_SPACES "4. Count Total Patients\n");
        printf(CENTER_SPACES "5. Delete Patient by Name\n");
        printf(CENTER_SPACES "6. Exit\n");
        printf("\n\n");
        printf(CENTER_SPACES "--Enter your choice : ");
        scanf("%d", &choice);
        getchar();  // To consume newline left by scanf

        switch (choice) {
            case 1:
                printf("\n");
                printf(CENTER_SPACES "Enter patient name: ");
                scanf(" %[^\n]%*c", name);
                printf(CENTER_SPACES "Enter gender of patient: ");
                scanf(" %[^\n]%*c", gender);
                printf(CENTER_SPACES "Enter the disease: ");
                scanf(" %[^\n]%*c", disease);
                printf(CENTER_SPACES "Enter the age of patient: ");
                scanf("%d", &age);
                printf(CENTER_SPACES "Enter priority (Higher number means higher priority): ");
                scanf("%d", &priority);
                getchar();  // Clear buffer
                insertPatient(&patientQueue, name, gender, disease, age, priority);
                break;

            case 2:
                servePatient(&patientQueue);
                break;

            case 3:
                displayPatients(patientQueue);
                break;

            case 4:
                printf(CENTER_SPACES "Total patients in the queue: %d\n", countPatients(patientQueue));
                break;

            case 5:
                printf(CENTER_SPACES "Enter the name of the patient to delete: ");
                scanf(" %[^\n]%*c", name);
                deletePatient(&patientQueue, name);
                break;

            case 6:
                printf(CENTER_SPACES "Exiting the system. Stay healthy!\n");
                freePatients(patientQueue);
                exit(0);

            default:
                printf(CENTER_SPACES "Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

