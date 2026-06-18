/*
-------------------------------------------------------
Name: Syed Jehangir
Course: CS 1436
Assignment 8 - Arrays and Strings
Program: RosterReport
File Name: Chapter8Lab.cpp
-------------------------------------------------------
*/
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace std;

// Part 1 - Data Storage Constants
const int MAX_STUDENTS = 10;
const int NUM_TESTS = 4;

// Part 2 - Required Function Prototypes
void readRoster(char names[][31], int scores[][NUM_TESTS], int& count);
void calcAverages(const int scores[][NUM_TESTS], double averages[], char grades[], int count);
void sortRoster(char names[][31], int scores[][NUM_TESTS], double averages[], char grades[], int count);
int searchRoster(const char names[][31], int count, const char target[]);
void printRoster(const char names[][31], const int scores[][NUM_TESTS], const double averages[], const char grades[], int count);
void printStats(const double averages[], int count);

// Part 3 - Main Menu Loop
int main()
{
    char names[MAX_STUDENTS][31];
    int scores[MAX_STUDENTS][NUM_TESTS];
    double averages[MAX_STUDENTS] = {0.0};
    char grades[MAX_STUDENTS] = {'F'};
    int count = 0;

    int choice = 0;
    char target[31];

    do
    {
        cout << "\n===== Roster Report Menu =====\n";
        cout << "1. Load roster (enter data)\n";
        cout << "2. Calculate averages and grades\n";
        cout << "3. Sort roster alphabetically\n";
        cout << "4. Search for a student\n";
        cout << "5. Print roster\n";
        cout << "6. Print class statistics\n";
        cout << "7. Quit\n";
        cout << "Enter choice: ";
        
        cin >> choice;
        cin.ignore(); // Clear newline after numeric input

        switch (choice)
        {
            case 1:
                readRoster(names, scores, count);
                break;
            case 2:
                calcAverages(scores, averages, grades, count);
                break;
            case 3:
                sortRoster(names, scores, averages, grades, count);
                break;
            case 4:
                if (count == 0)
                {
                    cout << "Roster is empty. Please load data first.\n";
                }
                else
                {
                    cout << "Enter student name to search: ";
                    cin.getline(target, 31);
                    int index = searchRoster(names, count, target);
                    if (index != -1)
                    {
                       cout << "Student \"" << target << "\" found at position " 
     << index + 1 << ".\n";
                    }
                    else
                    {
                        cout << "Student \"" << target << "\" not found.\n";
                    }
                }
                break;
            case 5:
                printRoster(names, scores, averages, grades, count);
                break;
            case 6:
                printStats(averages, count);
                break;
            case 7:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please choose between 1 and 7.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}

// 2a. readRoster
void readRoster(char names[][31], int scores[][NUM_TESTS], int& count)
{
    do
    {
        cout << "Enter number of students (1-10): ";
        cin >> count;
        cin.ignore();
        if (count < 1 || count > MAX_STUDENTS)
        {
            cout << "Invalid count. Must be between 1 and 10.\n";
        }
    } while (count < 1 || count > MAX_STUDENTS);

    for (int i = 0; i < count; i++)
    {
        cout << "\nEnter name for student " << (i + 1) << ": ";
        cin.getline(names[i], 31);

        for (int j = 0; j < NUM_TESTS; j++)
        {
            do
            {
                cout << "  Enter score for Test " << (j + 1) << " (0-100): ";
                cin >> scores[i][j];
                if (scores[i][j] < 0 || scores[i][j] > 100)
                {
                    cout << "  Invalid score. Must be between 0 and 100.\n";
                }
            } while (scores[i][j] < 0 || scores[i][j] > 100);
        }
        cin.ignore(); // Consume left-over newline before the next string read
    }
    cout << "\nRoster data successfully loaded.\n";
}

// 2b. calcAverages
void calcAverages(const int scores[][NUM_TESTS], double averages[], char grades[], int count)
{
    if (count == 0)
    {
        cout << "No data available to calculate. Load roster first.\n";
        return;
    }

    for (int i = 0; i < count; i++)
    {
        double sum = 0.0;
        for (int j = 0; j < NUM_TESTS; j++)
        {
            sum += scores[i][j];
        }
        averages[i] = sum / NUM_TESTS;

        if (averages[i] >= 90.0)      grades[i] = 'A';
        else if (averages[i] >= 80.0) grades[i] = 'B';
        else if (averages[i] >= 70.0) grades[i] = 'C';
        else if (averages[i] >= 60.0) grades[i] = 'D';
        else                          grades[i] = 'F';
    }
    cout << "Averages and letter grades successfully updated.\n";
}

// 2c. sortRoster (Selection Sort)
void sortRoster(char names[][31], int scores[][NUM_TESTS], double averages[], char grades[], int count)
{
    if (count == 0)
    {
        cout << "No data to sort.\n";
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < count; j++)
        {
            if (strcmp(names[j], names[minIndex]) < 0)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            // Swap Names
            char tempName[31];
            strcpy(tempName, names[i]);
            strcpy(names[i], names[minIndex]);
            strcpy(names[minIndex], tempName);

            // Swap Rows in 2D Scores Array
            for (int k = 0; k < NUM_TESTS; k++)
            {
                int tempScore = scores[i][k];
                scores[i][k] = scores[minIndex][k];
                scores[minIndex][k] = tempScore;
            }

            // Swap Averages
            double tempAvg = averages[i];
            averages[i] = averages[minIndex];
            averages[minIndex] = tempAvg;

            // Swap Grades
            char tempGrade = grades[i];
            grades[i] = grades[minIndex];
            grades[minIndex] = tempGrade;
        }
    }
    cout << "Roster sorted alphabetically by name.\n";
}

// 2d. searchRoster (Sequential Search)
int searchRoster(const char names[][31], int count, const char target[])
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(names[i], target) == 0)
        {
            return i; 
        }
    }
    return -1;
}

// 2e. printRoster
void printRoster(const char names[][31], const int scores[][NUM_TESTS], const double averages[], const char grades[], int count)
{
    if (count == 0)
    {
        cout << "Roster is empty. Nothing to print.\n";
        return;
    }

    cout << "\n---------------------------------------------------------------\n";
    cout << left << setw(20) << "Student Name" 
         << right << setw(6) << "Test1" << setw(6) << "Test2" 
         << setw(6) << "Test3" << setw(6) << "Test4" 
         << setw(10) << "Average" << setw(7) << "Grade\n";
    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < count; i++)
    {
        cout << left << setw(20) << names[i] << right;
        for (int j = 0; j < NUM_TESTS; j++)
        {
            cout << setw(6) << scores[i][j];
        }
        cout << fixed << setprecision(2) 
             << setw(10) << averages[i] 
             << setw(6) << grades[i] << "\n";
    }
    cout << "---------------------------------------------------------------\n";
}

// 2f. printStats
void printStats(const double averages[], int count)
{
    if (count == 0)
    {
        cout << "No calculations available. Run Option 2 first.\n";
        return;
    }

    // Creating a local copy of valid elements to satisfy range-based for loop constraints
    double localAverages[MAX_STUDENTS];
    for (int i = 0; i < count; i++)
    {
        localAverages[i] = averages[i];
    }

    double sum = 0.0;
    double highest = localAverages[0];
    double lowest = localAverages[0];

    // Using range-based loop over the first 'count' elements of local data
    int idx = 0;
    for (auto val : localAverages)
    {
        if (idx >= count) break; // Restrict logic strictly to active dataset count

        sum += val;
        if (val > highest) highest = val;
        if (val < lowest)  lowest = val;
        idx++;
    }

    double classAverage = sum / count;

    cout << fixed << setprecision(2);
    cout << "\n===== Class Statistics =====\n";
    cout << "Class High Score: " << highest << "\n";
    cout << "Class Low Score:  " << lowest << "\n";
    cout << "Class Average:    " << classAverage << "\n";
}