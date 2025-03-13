#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI Color Codes for Stylish Output
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"
#define BOLDWHITE "\033[1;37m"

#define MAX_SYMPTOMS 10
#define MAX_DISEASES 5

typedef struct {
    char name[50];
    char symptoms[MAX_SYMPTOMS][30];
    int symptom_count;
    char diagnosis[200];
} Patient;

typedef struct {
    char name[50];
    char symptoms[MAX_SYMPTOMS][30];
    int symptom_count;
    char diagnosis[200];
} Disease;

// Disease Database
Disease diseaseDB[MAX_DISEASES] = {
    {"Flu", {"fever", "cough", "fatigue", "body pain"}, 4, "Possible Flu. Rest, drink fluids, and take paracetamol."},
    {"COVID-19", {"fever", "cough", "shortness of breath", "loss of taste"}, 4, "Possible COVID-19. Isolate and get tested."},
    {"Migraine", {"headache", "nausea", "sensitivity to light"}, 3, "Possible Migraine. Rest in a dark room and stay hydrated."},
    {"Food Poisoning", {"vomiting", "diarrhea", "stomach pain"}, 3, "Possible Food Poisoning. Stay hydrated and eat light foods."},
    {"Dengue", {"fever", "rash", "joint pain", "bleeding gums"}, 4, "Possible Dengue. Seek medical attention immediately."}
};

// Function to display the main menu
void displayMenu() {
    printf(BOLDWHITE "\n========================================\n" RESET);
    printf(BLUE "        AI-Based Health & Medical System       \n" RESET);
    printf(BOLDWHITE "========================================\n" RESET);
    printf(GREEN "1. Enter Symptoms (Medical Diagnosis)\n" RESET);
    printf(YELLOW "2. Check BMI\n" RESET);
    printf(CYAN "3. Check Heart Rate\n" RESET);
    printf(BLUE "4. Check Blood Pressure\n" RESET);
    printf(YELLOW "5. View Medical History\n" RESET);
    printf(RED "6. Exit\n" RESET);
    printf(BOLDWHITE "========================================\n" RESET);
    printf(BOLDWHITE "Enter your choice: " RESET);
}

// Function to diagnose based on symptoms
void diagnose(Patient *p) {
    int maxMatches = 0;
    int matchedDiseaseIndex = -1;

    for (int i = 0; i < MAX_DISEASES; i++) {
        int matches = 0;

        for (int j = 0; j < p->symptom_count; j++) {
            for (int k = 0; k < diseaseDB[i].symptom_count; k++) {
                if (strstr(p->symptoms[j], diseaseDB[i].symptoms[k])) {
                    matches++;
                }
            }
        }

        if (matches > maxMatches) {
            maxMatches = matches;
            matchedDiseaseIndex = i;
        }
    }

    if (matchedDiseaseIndex != -1) {
        strcpy(p->diagnosis, diseaseDB[matchedDiseaseIndex].diagnosis);
        printf(GREEN "\nDiagnosis: %s\n" RESET, p->diagnosis);
    } else {
        strcpy(p->diagnosis, "Symptoms not recognized. Consult a doctor.");
        printf(RED "\nDiagnosis: %s\n" RESET, p->diagnosis);
    }
}

// Function to check BMI
void checkBMI() {
    float weight, height, bmi;
    printf("\nEnter weight (kg): ");
    scanf("%f", &weight);
    printf("Enter height (m): ");
    scanf("%f", &height);

    bmi = weight / (height * height);
    printf(GREEN "Your BMI: %.2f\n" RESET, bmi);

    if (bmi < 18.5)
        printf(RED "Underweight - Eat more nutritious food!\n" RESET);
    else if (bmi >= 18.5 && bmi < 24.9)
        printf(GREEN "Normal weight - Keep up the good work!\n" RESET);
    else if (bmi >= 25 && bmi < 29.9)
        printf(YELLOW "Overweight - Consider regular exercise!\n" RESET);
    else
        printf(RED "Obese - Seek medical advice for a healthy plan!\n" RESET);
}

// Function to check heart rate
void checkHeartRate() {
    int heartRate;
    printf("\nEnter your heart rate (BPM): ");
    scanf("%d", &heartRate);

    if (heartRate < 60)
        printf(RED "Low heart rate - Consider medical advice!\n" RESET);
    else if (heartRate >= 60 && heartRate <= 100)
        printf(GREEN "Normal heart rate - Keep it up!\n" RESET);
    else
        printf(YELLOW "High heart rate - Avoid stress and exercise regularly!\n" RESET);
}

// Function to check blood pressure
void checkBloodPressure() {
    int systolic, diastolic;
    printf("\nEnter systolic pressure: ");
    scanf("%d", &systolic);
    printf("Enter diastolic pressure: ");
    scanf("%d", &diastolic);

    if (systolic < 90 || diastolic < 60)
        printf(RED "Low BP - Stay hydrated and eat healthy!\n" RESET);
    else if (systolic >= 90 && systolic <= 120 && diastolic >= 60 && diastolic <= 80)
        printf(GREEN "Normal BP - Great job!\n" RESET);
    else
        printf(YELLOW "High BP - Reduce salt intake and manage stress!\n" RESET);
}

// Function to view medical history
void viewHistory() {
    char ch;
    FILE *file = fopen("medical_history.txt", "r");
    if (file == NULL) {
        printf(RED "No medical history found.\n" RESET);
        return;
    }
    printf(CYAN "\n=== Medical History ===\n" RESET);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
}

int main() {
    int choice;
    Patient patient;

    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();  // Handle buffer issue

        switch (choice) {
            case 1:
                printf(BOLDWHITE "Enter your name: " RESET);
                fgets(patient.name, sizeof(patient.name), stdin);
                patient.name[strcspn(patient.name, "\n")] = '\0';

                printf(BOLDWHITE "How many symptoms do you have? (Max %d): " RESET, MAX_SYMPTOMS);
                scanf("%d", &patient.symptom_count);
                getchar();

                if (patient.symptom_count > MAX_SYMPTOMS) patient.symptom_count = MAX_SYMPTOMS;

                for (int i = 0; i < patient.symptom_count; i++) {
                    printf(CYAN "Enter symptom %d: " RESET, i + 1);
                    fgets(patient.symptoms[i], sizeof(patient.symptoms[i]), stdin);
                    patient.symptoms[i][strcspn(patient.symptoms[i], "\n")] = '\0';
                }

                diagnose(&patient);
                break;

            case 2:
                checkBMI();
                break;

            case 3:
                checkHeartRate();
                break;

            case 4:
                checkBloodPressure();
                break;

            case 5:
                viewHistory();
                break;

            case 6:
                printf(YELLOW "Exiting Health Monitoring System...\n" RESET);
                break;

            default:
                printf(RED "Invalid choice! Try again.\n" RESET);
        }
    } while (choice != 6);

    return 0;
}
