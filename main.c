#include <stdio.h>
#include <string.h>


typedef struct {
    int id;
    char name[50];
    int age;
    char ailment[50];
    char doctor[50];
    char status[20];
    char admissionDate[11];
    char dischargeDate[11];
} Patient;

void update_status(char status[20]) {
    printf("\nUpdate patient status: ");
    scanf(" %[^\n]", status);
    printf("Updated status: %s\n", status);
}

int searchPatients(Patient patients[], int count, const char *key, const char *type) {
    int matchCount = 0;
    printf("\n--- Search Results for '%s' in '%s' ---\n", key, type);
    for (int i = 0; i < count; i++) {
        if ((strcmp(type, "name") == 0 && strstr(patients[i].name, key)) ||
            (strcmp(type, "ailment") == 0 && strstr(patients[i].ailment, key)) ||
            (strcmp(type, "doctor") == 0 && strstr(patients[i].doctor, key))) {
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Ailment: %s\n", patients[i].ailment);
            printf("Doctor: %s\n", patients[i].doctor);
            printf("Status: %s\n", patients[i].status);
            printf("Admission Date: %s\n", patients[i].admissionDate);
            printf("Discharge Date: %s\n", patients[i].dischargeDate);
            printf("\n");
            matchCount++;
        }
    }
    if (matchCount == 0) {
        printf("No patients found matching your criteria.\n");
    }
    return matchCount;
}

int generateDailyReport(Patient patients[], int count, const char *date) {
    printf("\n--- Daily Report for: %s ---\n", date);
    int matchCount = 0;
    for (int i = 0; i < count; i++) {
        if ((strcmp(patients[i].status, "Admitted") == 0 && strcmp(patients[i].admissionDate, date) == 0) ||
            (strcmp(patients[i].status, "Discharged") == 0 && strcmp(patients[i].dischargeDate, date) == 0)) {
            printf("ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Ailment: %s\n", patients[i].ailment);
            printf("Doctor: %s\n", patients[i].doctor);
            printf("Status: %s\n", patients[i].status);
            printf("Admission Date: %s\n", patients[i].admissionDate);
            printf("Discharge Date: %s\n", patients[i].dischargeDate);
            printf("\n");
            matchCount++;
        }
    }
    if (matchCount == 0) {
        printf("No patients admitted or discharged on %s.\n", date);
    }
    return matchCount;
}

int calculateDays(int y1, int m1, int d1, int y2, int m2, int d2) {
    if (y1 > y2 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2)) {
        return 0; // Invalid date range
    }
    int days = 0;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((y1 % 4 == 0 && y1 % 100 != 0) || (y1 % 400 == 0)) daysInMonth[2] = 29;
    while (y1 < y2 || m1 < m2 || d1 < d2) {
        days++;
        d1++;
        if (d1 > daysInMonth[m1]) {
            d1 = 1;
            m1++;
            if (m1 > 12) {
                m1 = 1;
                y1++;
                if ((y1 % 4 == 0 && y1 % 100 != 0) || (y1 % 400 == 0)) daysInMonth[2] = 29;
                else daysInMonth[2] = 28;
            }
        }
    }
    return days;
}

int BillingSystem(Patient patients[], int patientCount) {
    char input[20];
    int id;

    printf("\n--- Billing System ---\n");
    printf("Enter Patient ID to calculate bill: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        if (sscanf(input, "%d", &id) == 1) {
            for (int i = 0; i < patientCount; i++) {
                if (patients[i].id == id) {
                    char end[11];
                    int y1, m1, d1, y2, m2, d2;

                    if (sscanf(patients[i].admissionDate, "%d-%d-%d", &y1, &m1, &d1) != 3) {
                        printf("Error: Invalid admission date format for patient ID %d.\n", id);
                        return 1;
                    }

                    if (strlen(patients[i].dischargeDate) > 0) {
                        if (sscanf(patients[i].dischargeDate, "%d-%d-%d", &y2, &m2, &d2) != 3) {
                            printf("Error: Invalid discharge date format for patient ID %d.\n", id);
                            return 1;
                        }
                    } else {
                        printf("Enter today's date (YYYY-MM-DD): ");
                        if (fgets(end, sizeof(end), stdin) != NULL) {
                            end[strcspn(end, "\n")] = '\0';
                            if (sscanf(end, "%d-%d-%d", &y2, &m2, &d2) != 3) {
                                printf("Error: Invalid date format.\n");
                                return 1;
                            }
                        } else {
                            printf("Error reading input.\n");
                            return 1;
                        }
                    }

                    int days = calculateDays(y1, m1, d1, y2, m2, d2);
                    int roomCharge = days * 500;
                    int totalTreatCost = 0; // You would typically fetch treatment costs from another data structure

                    printf("\n--- Bill for Patient ID: %d ---\n", id);
                    printf("Days of Admission: %d\n", days);
                    printf("Room Charge ($500/day): $%d\n", roomCharge);
                    printf("Total Treatment Cost: $%d (Treatment details not implemented)\n", totalTreatCost);
                    printf("-----------------------------\n");
                    printf("Total Bill: $%d\n", roomCharge + totalTreatCost);
                    printf("-----------------------------\n");
                    return 0;
                }
            }
            printf("Patient with ID %d not found.\n", id);
        } else {
            printf("Invalid input. Please enter a valid Patient ID.\n");
        }
    } else {
        printf("Error reading input.\n");
    }
    return 1;
}

int main() {
    Patient patients[MAX_PATIENTS];
    int patientCount = 0;
    char name[50];
    int age;
    char ailment[50];
    char doctor[50];
    char status[20];
    char admissionDate[11];
    char dischargeDate[11] = ""; // Initialize as empty string

    printf("Enter patient name: ");
    scanf(" %[^\n]", name);
    strcpy(patients[patientCount].name, name);

    printf("Enter age: ");
    scanf("%d", &age);
    patients[patientCount].age = age;

    printf("Enter ailment: ");
    scanf(" %[^\n]", ailment);
    strcpy(patients[patientCount].ailment, ailment);

    printf("Enter doctor assigned: ");
    scanf(" %[^\n]", doctor);
    strcpy(patients[patientCount].doctor, doctor);

    printf("Enter status (Admitted/Discharged): ");
    scanf(" %[^\n]", status);
    strcpy(patients[patientCount].status, status);

    printf("Enter admission date (YYYY-MM-DD): ");
    scanf(" %s", admissionDate);
    strcpy(patients[patientCount].admissionDate, admissionDate);

    if (strcmp(status, "Discharged") == 0) {
        printf("Enter discharge date (YYYY-MM-DD): ");
        scanf(" %s", dischargeDate);
        strcpy(patients[patientCount].dischargeDate, dischargeDate);
    } else {
        strcpy(patients[patientCount].dischargeDate, ""); // Ensure it's empty if not discharged
    }

    patients[patientCount].id = patientCount + 1; // Assign a simple ID
    patientCount++;

    printf("\n--- Patient Details ---\n");
    printf("ID: %d\n", patients[0].id);
    printf("Name: %s\n", patients[0].name);
    printf("Age: %d\n", patients[0].age);
    printf("Ailment: %s\n", patients[0].ailment);
    printf("Doctor: %s\n", patients[0].doctor);
    printf("Status: %s\n", patients[0].status);
    printf("Admission Date: %s\n", patients[0].admissionDate);
    printf("Discharge Date: %s\n", patients[0].dischargeDate);

    update_status(patients[0].status);
    printf("Updated Status in main: %s\n", patients[0].status);

    searchPatients(patients, patientCount, name, "name");
    searchPatients(patients, patientCount, ailment, "ailment");
    searchPatients(patients, patientCount, doctor, "doctor");

    generateDailyReport(patients, patientCount, admissionDate); // Example using admission date as 'daily' date

    // Simulate adding another patient for testing daily report
    if (patientCount < MAX_PATIENTS) {
        strcpy(patients[patientCount].name, "Jane Doe");
        patients[patientCount].age = 35;
        strcpy(patients[patientCount].ailment, "Flu");
        strcpy(patients[patientCount].doctor, "Dr. Smith");
        strcpy(patients[patientCount].status, "Admitted");
        strcpy(patients[patientCount].admissionDate, "2025-05-04");
        strcpy(patients[patientCount].dischargeDate, "");
        patients[patientCount].id = patientCount + 1;
        patientCount++;
    }
    generateDailyReport(patients, patientCount, "2025-05-04");

    BillingSystem(patients, patientCount);

    return 0;
}
