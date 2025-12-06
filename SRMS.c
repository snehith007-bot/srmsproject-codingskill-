#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define CREDENTIAL_FILE "credentials.txt"
#define STUDENT_FILE "students.txt"

struct student {
    int roll;
    char name[50];
    float marks;
};

char currentUser[20];
char currentRole[20];

/* Function declarations */
void createCredentials();
int loginSystem();
void mainMenu();
void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void topperStudent();

int rollExists(int roll);
void getMaskedPassword(char *password);

/* ---------------------------------------------------------
   MAIN FUNCTION
--------------------------------------------------------- */
int main() {
    createCredentials();

    if (loginSystem()) {
        mainMenu();
    } else {
        printf("Login failed! Exiting...\n");
    }
    return 0;
}

/* ---------------------------------------------------------
   CREATE CREDENTIAL FILE
--------------------------------------------------------- */
void createCredentials() {
    char choice;
    char user[20], pass[20], role[20];

    printf("Do you want to create login credentials? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {

        printf("Enter new username: ");
        scanf("%s", user);

        printf("Enter new password: ");
        scanf("%s", pass);

        printf("Enter role (admin/staff/user/guest): ");
        scanf("%s", role);

        FILE *fp = fopen(CREDENTIAL_FILE, "w");
        fprintf(fp, "%s %s %s\n", user, pass, role);
        fclose(fp);

        printf("Credentials created successfully!\n");
    }

    FILE *f = fopen(STUDENT_FILE, "r");
    if (!f) {
        f = fopen(STUDENT_FILE, "w");
        fclose(f);
    } else fclose(f);
}

/* ---------------------------------------------------------
   PASSWORD MASKING
--------------------------------------------------------- */
void getMaskedPassword(char *password) {
    char ch;
    int i = 0;

    while (1) {
        ch = getch();

        if (ch == 13) { // ENTER KEY
            password[i] = '\0';
            printf("\n");
            break;
        }
        else if (ch == 8 && i > 0) { // BACKSPACE
            i--;
            printf("\b \b");
        }
        else {
            password[i++] = ch;
            printf("*");
        }
    }
}

/* ---------------------------------------------------------
   LOGIN SYSTEM
--------------------------------------------------------- */
int loginSystem() {
    char username[20], password[20];
    char userFile[20], passFile[20], roleFile[20];

    int attempts = 3;

    while (attempts > 0) {
        printf("\n============== LOGIN SCREEN ============\n");

        printf("Enter username: ");
        scanf("%s", username);

        printf("Enter password: ");
        getMaskedPassword(password);

        FILE *fp = fopen(CREDENTIAL_FILE, "r");
        if (!fp) {
            printf("Credential file missing!\n");
            return 0;
        }

        int success = 0;

        while (fscanf(fp, "%s %s %s", userFile, passFile, roleFile) != EOF) {
            if (strcmp(username, userFile) == 0 &&
                strcmp(password, passFile) == 0) {

                strcpy(currentUser, userFile);
                strcpy(currentRole, roleFile);
                fclose(fp);
                return 1;  // LOGIN SUCCESS
            }
        }

        fclose(fp);

        attempts--;
        printf("\nIncorrect username or password! Attempts left: %d\n", attempts);
    }

    printf("\nToo many failed attempts. Exiting...\n");
    return 0;
}

/* ---------------------------------------------------------
   MAIN MENU (ROLE ROUTING)
--------------------------------------------------------- */
void mainMenu() {

    if (strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if (strcmp(currentRole, "staff") == 0)
        staffMenu();
    else if (strcmp(currentRole, "user") == 0)
        userMenu();
    else
        guestMenu();
}

/* ---------------------------------------------------------
   ADMIN MENU
--------------------------------------------------------- */
void adminMenu() {
    int ch;

    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Display Topper\n");
        printf("7. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: topperStudent(); break;
            case 7: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

/* ---------------------------------------------------------
   STAFF MENU
--------------------------------------------------------- */
void staffMenu() {
    int choice;

    do {
        printf("\n=== STAFF MENU ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: printf("Logging out...\n"); return;
            default: printf("Invalid choice. Try again.\n");
        }

    } while (1);
}

/* ---------------------------------------------------------
   USER MENU
--------------------------------------------------------- */
void userMenu() {
    int ch;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student\n");
        printf("3. Display Topper\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: displayStudents(); break;
            case 2: searchStudent(); break;
            case 3: topperStudent(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }

    } while (1);
}

/* ---------------------------------------------------------
   GUEST MENU
--------------------------------------------------------- */
void guestMenu() {
    int choice;

    do {
        printf("\n=== GUEST MENU ===\n");
        printf("1. Display Students\n");
        printf("2. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: printf("Logging out...\n"); return;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (1);
}

/* ---------------------------------------------------------
   CHECK DUPLICATE ROLL
--------------------------------------------------------- */
int rollExists(int roll) {
    struct student st;
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) return 0;

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (st.roll == roll) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

/* ---------------------------------------------------------
   ADD STUDENT
--------------------------------------------------------- */
void addStudent() {
    struct student st;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter roll number: ");
    scanf("%d", &st.roll);

    if (rollExists(st.roll)) {
        printf("Roll already exists!\n");
        return;
    }

    printf("Enter name: ");
    scanf("%s", st.name);

    printf("Enter marks (0-100): ");
    scanf("%f", &st.marks);

    if (st.marks < 0 || st.marks > 100) {
        printf("Invalid marks!\n");
        return;
    }

    fprintf(fp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    fclose(fp);

    printf("Student added!\n");
}

/* ---------------------------------------------------------
   DISPLAY STUDENTS (AUTO SORTED)
--------------------------------------------------------- */
void displayStudents() {
    struct student arr[200], temp;
    int n = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No records found!\n");
        return;
    }

    while (fscanf(fp, "%d %s %f", &arr[n].roll, arr[n].name, &arr[n].marks) != EOF)
        n++;
    fclose(fp);

    // Sort by roll number
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j].roll > arr[j + 1].roll) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("\n%-10s %-20s %-10s\n", "Roll", "Name", "Marks");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; i++)
        printf("%-10d %-20s %-10.2f\n", arr[i].roll, arr[i].name, arr[i].marks);

    printf("\nTotal Students: %d\n", n);
}

/* ---------------------------------------------------------
   SEARCH STUDENT
--------------------------------------------------------- */
void searchStudent() {
    int roll;
    printf("Enter roll to search: ");
    scanf("%d", &roll);

    struct student st;
    FILE *fp = fopen(STUDENT_FILE, "r");

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (st.roll == roll) {
            printf("\nFound: %d %s %.2f\n", st.roll, st.name, st.marks);
            fclose(fp);
            return;
        }
    }

    printf("Student not found!\n");
    fclose(fp);
}

/* ---------------------------------------------------------
   UPDATE STUDENT
--------------------------------------------------------- */
void updateStudent() {
    int roll;
    printf("Enter roll to update: ");
    scanf("%d", &roll);

    struct student st;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *tmp = fopen("temp.txt", "w");

    int found = 0;

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {

        if (st.roll == roll) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", st.name);
            printf("Enter new marks: ");
            scanf("%f", &st.marks);
        }

        fprintf(tmp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
    fclose(tmp);

    if (found) {
        remove(STUDENT_FILE);
        rename("temp.txt", STUDENT_FILE);
        printf("Record updated!\n");
    } else {
        remove("temp.txt");
        printf("Roll not found!\n");
    }
}

/* ---------------------------------------------------------
   DELETE STUDENT
--------------------------------------------------------- */
void deleteStudent() {
    int roll;
    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    struct student st;
    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *tmp = fopen("temp.txt", "w");

    int found = 0;

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (st.roll == roll) {
            found = 1;
            continue;
        }
        fprintf(tmp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    }

    fclose(fp);
    fclose(tmp);

    if (found) {
        remove(STUDENT_FILE);
        rename("temp.txt", STUDENT_FILE);
        printf("Record deleted!\n");
    } else {
        remove("temp.txt");
        printf("Roll not found!\n");
    }
}

/* ---------------------------------------------------------
   DISPLAY TOPPER
--------------------------------------------------------- */
void topperStudent() {
    struct student st, topper;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("No records!\n");
        return;
    }

    float maxMarks = -1;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &st.roll, st.name, &st.marks) != EOF) {
        if (st.marks > maxMarks) {
            maxMarks = st.marks;
            topper = st;
            found = 1;
        }
    }

    fclose(fp);

    if (found) {
        printf("\n===== TOPPER =====\n");
        printf("Roll : %d\n", topper.roll);
        printf("Name : %s\n", topper.name);
        printf("Marks: %.2f\n", topper.marks);
    } else {
        printf("No students found!\n");
    }
}
