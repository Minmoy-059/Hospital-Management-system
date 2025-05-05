#include <stdio.h>
#include <string.h>

void update_status(char status[20])
{
    printf("\nUpdate patient status: ");
    fgets(status, 20, stdin);
    status[strcspn(status, "\n")] = '\0';
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
    name[strcspn(name, "\n")] = '\0';

    printf("Enter age: ");
    fgets(ageStr, sizeof(ageStr), stdin);
    ageStr[strcspn(ageStr, "\n")] = '\0';
    sscanf(ageStr, "%d", &age);

    printf("Enter ailment: ");
    fgets(ailment, sizeof(ailment), stdin);
    ailment[strcspn(ailment, "\n")] = '\0';

    printf("Enter doctor assigned: ");
    fgets(doctor, sizeof(doctor), stdin);
    doctor[strcspn(doctor, "\n")] = '\0';

    printf("Enter status (Admitted/Discharged): ");
    fgets(status, sizeof(status), stdin);
    status[strcspn(status, "\n")] = '\0';

    printf("Enter patient type (Inpatient/Outpatient/Emergency/ICU): ");
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = '\0';

    printf("Enter admission date (YYYY-MM-DD): ");
    fgets(admittedDate, sizeof(admittedDate), stdin);
    admittedDate[strcspn(admittedDate, "\n")] = '\0';

    if (strcmp(status, "Discharged") == 0)
    {
        printf("Enter discharge date (YYYY-MM-DD): ");
        fgets(dischargedDate, sizeof(dischargedDate), stdin);
        dischargedDate[strcspn(dischargedDate, "\n")] = '\0';
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

    //update_status(status);
    patientCount++;
    return 0;
}

int compare_dates(const char *date1, const char *date2)
{
    int y1, m1, d1, y2, m2, d2;
    sscanf(date1, "%d-%d-%d", &y1, &m1, &d1);
    sscanf(date2, "%d-%d-%d", &y2, &m2, &d2);
    if (y1 != y2) return y1 - y2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}

int SearchFunctionality()
{
    char name[50], ailment[50], doctor[50], type[20];
    printf("\nSearch Patients (leave blank to skip):\n");

    printf("Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';



    printf("\nResults:\n");
    for (int i = 0; i < patientCount; i++)
    {
        if ((strlen(name) == 0 || strstr(patientNames[i], name)) &&
            (strlen(ailment) == 0 || strstr(patientAilments[i], ailment)) &&
            (strlen(doctor) == 0 || strstr(patientDoctors[i], doctor)) &&
            (strlen(type) == 0 || strstr(patientTypes[i], type)))
        {
            printf("ID: %d | Name: %s | Age: %s | Ailment: %s | Doctor: %s | Type: %s | Status: %s\n",
                   patientIds[i], patientNames[i], patientAges[i],
                   patientAilments[i], patientDoctors[i], patientTypes[i], patientStatus[i]);
        }
    }
    return 0;
}

int DailyReport()
{
    char date[11];
    printf("\nEnter Date for Report (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = '\0';

    printf("\nAdmitted on %s:\n", date);
    for (int i = 0; i < patientCount; i++)
    {
        if (compare_dates(admittedDates[i], date) == 0)
            printf("ID: %d | Name: %s\n", patientIds[i], patientNames[i]);
    }

    printf("\nDischarged on %s:\n", date);
    for (int i = 0; i < patientCount; i++)
    {
        if (compare_dates(dischargedDates[i], date) == 0)
            printf("ID: %d | Name: %s\n", patientIds[i], patientNames[i]);
    }
    return 0;
}

int BillingSystem()
{
    char input[20];
    printf("\nCalculate Bill for Patient ID: ");
    fgets(input, sizeof(input), stdin);
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
                end[strcspn(end, "\n")] = '\0';
            }

            int y1, m1, d1, y2, m2, d2;
            sscanf(start, "%d-%d-%d", &y1, &m1, &d1);
            sscanf(end, "%d-%d-%d", &y2, &m2, &d2);
            int days = (y2 - y1) * 365 + (m2 - m1) * 30 + (d2 - d1);  // Rough estimate
            if (days < 1) days = 1;  // At least 1 day

            int roomCharge = days * 500;
            printf("Days: %d\nRoom Charge: %d\nTotal: %d\n", days, roomCharge, roomCharge);
            return 0;
        }
    }
    printf("Patient not found.\n");
    return 0;
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
        username[strcspn(username, "\n")] = '\0';

        printf("Password: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';

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
