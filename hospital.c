#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
struct Doctor {
    int id;
    char name[50];
    char specialty[30];
    char time[20];
};

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[30];
    char room[10];
};

struct Appointment {
    int id;
    int patientId;
    int doctorId;
    char date[20];
};

struct Bill {
    int billId;
    int patientId;
    float amount;
};

// Function declarations
void adminLogin();
void addDoctor();
void viewDoctors();
void searchDoctor();
void exportDoctorsCSV();

void addPatient();
void viewPatients();
void searchPatient();
void updatePatient();
void exportPatientsCSV();

void bookAppointment();
void viewAppointments();

void generateBill();
void viewBills();

// Utility
void clearInput() { while (getchar() != '\n'); }

int main() {
    int choice;

    adminLogin();

    while (1) {
        printf("\n========== HOSPITAL MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Doctor\n");
        printf("2. View Doctors\n");
        printf("3. Search Doctor by Name\n");
        printf("4. Export Doctors to CSV\n");
        printf("5. Add Patient\n");
        printf("6. View Patients\n");
        printf("7. Search Patient by Name\n");
        printf("8. Update Patient Details\n");
        printf("9. Export Patients to CSV\n");
        printf("10. Book Appointment\n");
        printf("11. View Appointments\n");
        printf("12. Generate Bill\n");
        printf("13. View Bills\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1: addDoctor(); break;
            case 2: viewDoctors(); break;
            case 3: searchDoctor(); break;
            case 4: exportDoctorsCSV(); break;
            case 5: addPatient(); break;
            case 6: viewPatients(); break;
            case 7: searchPatient(); break;
            case 8: updatePatient(); break;
            case 9: exportPatientsCSV(); break;
            case 10: bookAppointment(); break;
            case 11: viewAppointments(); break;
            case 12: generateBill(); break;
            case 13: viewBills(); break;
            case 0: exit(0);
            default: printf("Invalid choice!\n");
        }
    }

    return 0;
}

// ------------------ ADMIN LOGIN ---------------------
void adminLogin() {
    char username[20], password[20];
    int tries = 3;

    while (tries--) {
        printf("Admin Username: ");
        scanf("%s", username);
        printf("Admin Password: ");
        scanf("%s", password);

        if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
            printf("Login successful!\n");
            return;
        } else {
            printf("Incorrect credentials. Attempts left: %d\n", tries);
        }
    }

    printf("Too many failed attempts. Exiting...\n");
    exit(1);
}

// ------------------ DOCTOR FUNCTIONS ---------------------
void addDoctor() {
    struct Doctor d;
    FILE *f = fopen("doctors.dat", "ab");

    printf("Enter Doctor ID: ");
    scanf("%d", &d.id);
    clearInput();
    printf("Enter Name: ");
    fgets(d.name, 50, stdin); strtok(d.name, "\n");
    printf("Enter Specialty: ");
    fgets(d.specialty, 30, stdin); strtok(d.specialty, "\n");
    printf("Enter Timing (e.g., 10am-2pm): ");
    fgets(d.time, 20, stdin); strtok(d.time, "\n");

    fwrite(&d, sizeof(d), 1, f);
    fclose(f);
    printf("Doctor added successfully.\n");
}

void viewDoctors() {
    struct Doctor d;
    FILE *f = fopen("doctors.dat", "rb");

    printf("\n--- List of Doctors ---\n");
    while (fread(&d, sizeof(d), 1, f)) {
        printf("ID: %d | Name: %s | Specialty: %s | Time: %s\n", d.id, d.name, d.specialty, d.time);
    }
    fclose(f);
}

void searchDoctor() {
    char name[50];
    struct Doctor d;
    int found = 0;

    printf("Enter doctor name to search: ");
    fgets(name, 50, stdin); strtok(name, "\n");

    FILE *f = fopen("doctors.dat", "rb");
    while (fread(&d, sizeof(d), 1, f)) {
        if (strstr(d.name, name)) {
            printf("Found -> ID: %d | Name: %s | Specialty: %s | Time: %s\n", d.id, d.name, d.specialty, d.time);
            found = 1;
        }
    }
    fclose(f);
    if (!found) printf("Doctor not found.\n");
}

void exportDoctorsCSV() {
    struct Doctor d;
    FILE *f = fopen("doctors.dat", "rb");
    FILE *csv = fopen("doctors.csv", "w");

    fprintf(csv, "ID,Name,Specialty,Time\n");
    while (fread(&d, sizeof(d), 1, f)) {
        fprintf(csv, "%d,%s,%s,%s\n", d.id, d.name, d.specialty, d.time);
    }

    fclose(f);
    fclose(csv);
    printf("Doctors exported to doctors.csv\n");
}

// ------------------ PATIENT FUNCTIONS ---------------------
void addPatient() {
    struct Patient p;
    FILE *f = fopen("patients.dat", "ab");

    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    clearInput();
    printf("Enter Name: ");
    fgets(p.name, 50, stdin); strtok(p.name, "\n");
    printf("Enter Age: ");
    scanf("%d", &p.age);
    clearInput();
    printf("Enter Disease: ");
    fgets(p.disease, 30, stdin); strtok(p.disease, "\n");
    printf("Enter Room Number (e.g., A101): ");
    fgets(p.room, 10, stdin); strtok(p.room, "\n");

    fwrite(&p, sizeof(p), 1, f);
    fclose(f);
    printf("Patient added successfully.\n");
}

void viewPatients() {
    struct Patient p;
    FILE *f = fopen("patients.dat", "rb");

    printf("\n--- List of Patients ---\n");
    while (fread(&p, sizeof(p), 1, f)) {
        printf("ID: %d | Name: %s | Age: %d | Disease: %s | Room: %s\n", p.id, p.name, p.age, p.disease, p.room);
    }
    fclose(f);
}

void searchPatient() {
    char name[50];
    struct Patient p;
    int found = 0;

    printf("Enter patient name to search: ");
    fgets(name, 50, stdin); strtok(name, "\n");

    FILE *f = fopen("patients.dat", "rb");
    while (fread(&p, sizeof(p), 1, f)) {
        if (strstr(p.name, name)) {
            printf("Found -> ID: %d | Name: %s | Age: %d | Disease: %s | Room: %s\n", p.id, p.name, p.age, p.disease, p.room);
            found = 1;
        }
    }
    fclose(f);
    if (!found) printf("Patient not found.\n");
}

void updatePatient() {
    int id, found = 0;
    struct Patient p;
    FILE *f = fopen("patients.dat", "rb+");

    printf("Enter patient ID to update: ");
    scanf("%d", &id);
    clearInput();

    while (fread(&p, sizeof(p), 1, f)) {
        if (p.id == id) {
            printf("Editing patient %s:\n", p.name);
            printf("Enter new disease: ");
            fgets(p.disease, 30, stdin); strtok(p.disease, "\n");
            printf("Enter new room number: ");
            fgets(p.room, 10, stdin); strtok(p.room, "\n");

            fseek(f, -sizeof(p), SEEK_CUR);
            fwrite(&p, sizeof(p), 1, f);
            found = 1;
            printf("Patient updated.\n");
            break;
        }
    }

    fclose(f);
    if (!found) printf("Patient ID not found.\n");
}

void exportPatientsCSV() {
    struct Patient p;
    FILE *f = fopen("patients.dat", "rb");
    FILE *csv = fopen("patients.csv", "w");

    fprintf(csv, "ID,Name,Age,Disease,Room\n");
    while (fread(&p, sizeof(p), 1, f)) {
        fprintf(csv, "%d,%s,%d,%s,%s\n", p.id, p.name, p.age, p.disease, p.room);
    }

    fclose(f);
    fclose(csv);
    printf("Patients exported to patients.csv\n");
}

// ------------------ APPOINTMENTS ---------------------
void bookAppointment() {
    struct Appointment a;
    FILE *f = fopen("appointments.dat", "ab");

    printf("Enter Appointment ID: ");
    scanf("%d", &a.id);
    printf("Enter Patient ID: ");
    scanf("%d", &a.patientId);
    printf("Enter Doctor ID: ");
    scanf("%d", &a.doctorId);
    clearInput();
    printf("Enter Appointment Date (dd-mm-yyyy): ");
    fgets(a.date, 20, stdin); strtok(a.date, "\n");

    fwrite(&a, sizeof(a), 1, f);
    fclose(f);
    printf("Appointment booked successfully.\n");
}

void viewAppointments() {
    struct Appointment a;
    FILE *f = fopen("appointments.dat", "rb");

    printf("\n--- Appointments ---\n");
    while (fread(&a, sizeof(a), 1, f)) {
        printf("Appointment ID: %d | Patient ID: %d | Doctor ID: %d | Date: %s\n", a.id, a.patientId, a.doctorId, a.date);
    }
    fclose(f);
}

// ------------------ BILLING ---------------------
void generateBill() {
    struct Bill b;
    FILE *f = fopen("bills.dat", "ab");

    printf("Enter Bill ID: ");
    scanf("%d", &b.billId);
    printf("Enter Patient ID: ");
    scanf("%d", &b.patientId);
    printf("Enter Total Amount: ");
    scanf("%f", &b.amount);

    fwrite(&b, sizeof(b), 1, f);
    fclose(f);
    printf("Bill generated successfully.\n");
}

void viewBills() {
    struct Bill b;
    FILE *f = fopen("bills.dat", "rb");

    printf("\n--- Bills ---\n");
    while (fread(&b, sizeof(b), 1, f)) {
        printf("Bill ID: %d | Patient ID: %d | Amount: ₹%.2f\n", b.billId, b.patientId, b.amount);
    }
    fclose(f);
}
