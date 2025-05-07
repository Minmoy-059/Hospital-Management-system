#include <stdio.h>
#include <string.h>

void remove_newline(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

void update_status(char status[20])
{
    printf("\n Update patient status: ");
    fgets(status, 20, stdin);
    remove_newline(status);
    printf("Updated status: %s\n", status);
}

int patientIds[100];
char patientNames[100][50];
char patientAges[100][4];
char patientAilments[100][50];
char patientDoctors[100][50];
char patientStatus[100][20];
char admittedDates[100][11];
char dischargedDates[100][11];
char patientTypes[100][20];

int patientCount = 0;
int nextId = 1;

int PatientRecords()
{
    char name[50], ageStr[10], ailment[50], doctor[50], status[20], admittedDate[11], dischargedDate[11] = "", type[20];
    int age;

    printf("Enter patient name: ");
    fgets(name, sizeof(name), stdin);
    remove_newline(name);

    printf("Enter age: ");
    fgets(ageStr, sizeof(ageStr), stdin);
    remove_newline(ageStr);
    scanf(ageStr, "%d", &age);

    printf("Enter ailment: ");
    fgets(ailment, sizeof(ailment), stdin);
    remove_newline(ailment);
    printf("Enter doctor assigned: ");
    fgets(doctor, sizeof(doctor), stdin);
    remove_newline(doctor);

    printf("Enter status (Admitted/Discharged): ");
    fgets(status, sizeof(status), stdin);
    remove_newline(status);

    printf("Enter patient type (Inpatient/Outpatient/Emergency/ICU): ");
    fgets(type, sizeof(type), stdin);
    remove_newline(type);

    printf("Enter admission date (YYYY-MM-DD): ");
    fgets(admittedDate, sizeof(admittedDate), stdin);
    remove_newline(admittedDate);

    if (strcmp(status, "Discharged") == 0)
    {
        printf("Enter discharge date (YYYY-MM-DD): ");
        fgets(dischargedDate, sizeof(dischargedDate), stdin);
        remove_newline(dischargedDate);
    }

    patientIds[patientCount] = nextId++;
    strcpy(patientNames[patientCount], name);
    strcpy(patientAges[patientCount], ageStr);
    strcpy(patientAilments[patientCount], ailment);
    strcpy(patientDoctors[patientCount], doctor);
    strcpy(patientStatus[patientCount], status);
    strcpy(admittedDates[patientCount], admittedDate);
    strcpy(dischargedDates[patientCount], dischargedDate);
    strcpy(patientTypes[patientCount], type);

    printf("\n--- Patient Details ---\n");
    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("Ailment: %s\n", ailment);
    printf("Doctor: %s\n", doctor);
    printf("Status: %s\n", status);
    printf("Type: %s\n", type);
    printf("Admitted on: %s\n", admittedDate);
    if (strlen(dischargedDate) > 0)
        printf("Discharged on: %s\n", dischargedDate);

    patientCount++;
    return 0;
}

int compare_dates(const char *date1, const char *date2)
{
    int y1, m1, d1, y2, m2, d2;
    scanf(date1, "%d-%d-%d", &y1, &m1, &d1);
    scanf(date2, "%d-%d-%d", &y2, &m2, &d2);
    if (y1 != y2) return y1 - y2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}
int SearchFunctionality()
{
    char name[50];
    printf("\n Search Patient by Name:\n");

    printf("Enter patient name: ");
    fgets(name, sizeof(name), stdin);
    remove_newline(name);

    printf("\nResults:\n");
    int found = 0;

    for (int i = 0; i < patientCount; i++)
    {
        if (strlen(name) == 0 || strstr(patientNames[i], name))
        {
            printf("ID: %d | Name: %s | Age: %s | Ailment: %s | Doctor: %s | Status: %s | Type: %s | Admitted: %s",
                   patientIds[i], patientNames[i], patientAges[i],
                   patientAilments[i], patientDoctors[i], patientStatus[i], patientTypes[i], admittedDates[i]);

            if (strlen(dischargedDates[i]) > 0)
                printf(" | Discharged: %s", dischargedDates[i]);
            printf("\n");

            found = 1;
        }
    }

    if (!found)
    {
        printf("No patients found with the name '%s'.\n", name);
    }

    return 0;
}
int DailyReport() {
    char date[11];
    printf("\nEnter Date for Report (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin);
    remove_newline(date);
    int admittedFound = 0, dischargedFound = 0;
    printf("\nAdmitted on %s:\n", date);
    for (int i = 0; i < patientCount; i++) {
        if (compare_dates(admittedDates[i], date) == 0) {
            printf("ID: %d | Name: %s | Ailment: %s | Doctor: %s | Room Type: %s\n",
                   patientIds[i], patientNames[i], patientAilments[i], patientDoctors[i], patientTypes[i]);
            admittedFound = 1;
        }
    }
    if (!admittedFound) {
        printf("No patients admitted on %s.\n", date);
    }

    printf("\nDischarged on %s:\n", date);
    for (int i = 0; i < patientCount; i++) {
        if (strlen(dischargedDates[i]) > 0 && compare_dates(dischargedDates[i], date) == 0) {
            printf("ID: %d | Name: %s | Reason: %s | Doctor Remarks: %s\n",
                   patientIds[i], patientNames[i], "Recovered", patientDoctors[i]);  // Assuming discharged patients' reason is "Recovered"
            dischargedFound = 1;
        }
    }
    if (!dischargedFound) {
        printf("No patients discharged on %s.\n", date);
    }

    printf("\nBed Availability:\nTotal Beds: 100 | Beds Occupied: %d | Beds Available: %d\n", patientCount, 100 - patientCount);

    return 0;
}

int BillingSystem()
{
    char input[20];
    printf("\nCalculate Bill for Patient ID: ");
    fgets(input, sizeof(input), stdin);
    remove_newline(input);
    int id;
    sscanf(input, "%d", &id);

    for (int i = 0; i < patientCount; i++)
    {
        if (patientIds[i] == id)
        {
            char start[11], end[11];
            strcpy(start, admittedDates[i]);

            if (strlen(dischargedDates[i]) > 0)
            {
                strcpy(end, dischargedDates[i]);
            }
            else
            {
                printf("Enter today's date (YYYY-MM-DD): ");
                fgets(end, sizeof(end), stdin);
                remove_newline(end);

            int y1, m1, d1, y2, m2, d2;
            scanf(start, "%d-%d-%d", &y1, &m1, &d1);
            scanf(end, "%d-%d-%d", &y2, &m2, &d2);
            int days = (y2 - y1) * 365 + (m2 - m1) * 30 + (d2 - d1);
            if (days < 1) days = 1;

            int roomCharge = days * 500;
            printf("Days: %d\nRoom Charge: %d\nTotal: %d\n", days, roomCharge, roomCharge);
            return 0;
        }
    }
    printf("Patient not found.\n");
    return 0;
}
}
int login()
{
    char username[20], password[20];
    const char validUser[] = "admin";
    const char validPass[] = "admin123";
    int attempts = 3;

    while (attempts--)
    {
        printf("Login\nUsername: ");
        fgets(username, sizeof(username), stdin);
        remove_newline(username);

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        remove_newline(password);
        if (strcmp(username, validUser) == 0 && strcmp(password, validPass) == 0)
        {
            printf("Login successful!\n");
            return 1;
        }
        else
        {
            printf("Invalid credentials. Attempts left: %d\n", attempts);
        }
    }
    printf("Too many failed attempts. Exiting.\n");
    return 0;
}

void DisplayAllPatients()
{
    if (patientCount == 0)
    {
        printf("\nNo patient records available.\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");
    for (int i = 0; i < patientCount; i++)
    {
        printf("ID: %d | Name: %s | Age: %s | Ailment: %s | Doctor: %s | Status: %s | Type: %s | Admitted: %s",
               patientIds[i], patientNames[i], patientAges[i], patientAilments[i],
               patientDoctors[i], patientStatus[i], patientTypes[i], admittedDates[i]);
        if (strlen(dischargedDates[i]) > 0)
            printf(" | Discharged: %s", dischargedDates[i]);
        printf("\n");
    }
}

int main()
{
    if (!login())
    {
        return 1;
    }

    char input[20];
    int choice;

    while (1)
    {
        printf("\nHospital Patient Management System\n");
        printf("1. Patient Records\n2. Search Functionality\n3. Daily Report\n4. Billing System\n5. Exit\n6. Show All Patients\n");

        printf("Select: ");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &choice);

        switch (choice)
        {
            case 1:
                PatientRecords();
                break;
            case 2:
                SearchFunctionality();
                break;
            case 3:
                DailyReport();
                break;
            case 4:
                BillingSystem();
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            case 6:
                DisplayAllPatients();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }


    return 0;

}
