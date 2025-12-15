#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;

const int NUM_QUESTIONS = 20;

// Function prototypes
void getAnswers(const string& filename, char answers[], int size);
int gradeExam(const char key[], const char student[],
    int numQuestions, int missedQuestions[],
    char missedAnswers[][2]);
void writeReport(const int missedQuestions[], char missedAnswers[][2],
    int numIncorrect, int numQuestions);

int main()
{
    char answerKey[NUM_QUESTIONS];
    char studentAnswers[NUM_QUESTIONS];
    int missedQuestions[NUM_QUESTIONS];
    char missedAnswers[NUM_QUESTIONS][2]; // [row][0] = correct, [row][1] = student

    string keyFileName;
    string studentFileName;

    cout << "Enter the name of the answer key file (e.g., CorrectAnswers.txt): ";
    getline(cin, keyFileName);

    cout << "Enter the name of the student answers file (e.g., StudentAnswers.txt): ";
    getline(cin, studentFileName);

    // Read key + student answers
    getAnswers(keyFileName, answerKey, NUM_QUESTIONS);
    getAnswers(studentFileName, studentAnswers, NUM_QUESTIONS);

    // Grade exam
    int numIncorrect = gradeExam(answerKey, studentAnswers,
        NUM_QUESTIONS, missedQuestions,
        missedAnswers);

    // Display report
    writeReport(missedQuestions, missedAnswers, numIncorrect, NUM_QUESTIONS);

    return 0;
}

// Reads answers from a file into an array EXACTLY as written (no uppercase conversion)
void getAnswers(const string& filename, char answers[], int size)
{
    ifstream inFile(filename);

    if (!inFile)
    {
        cout << "Error: Could not open file \"" << filename << "\".\n";
        exit(1);
    }

    int count = 0;
    char ch;

    while (count < size && inFile >> ch)
    {
        answers[count] = ch;  // store raw character as-is
        count++;
    }

    if (count < size)
    {
        cout << "Error: File \"" << filename
            << "\" does not contain enough answers.\n";
        exit(1);
    }

    inFile.close();
}

// Compares student answers to answer key
int gradeExam(const char key[], const char student[],
    int numQuestions, int missedQuestions[],
    char missedAnswers[][2])
{
    int numIncorrect = 0;

    for (int i = 0; i < numQuestions; i++)
    {
        if (key[i] != student[i])
        {
            missedQuestions[numIncorrect] = i + 1;
            missedAnswers[numIncorrect][0] = key[i];
            missedAnswers[numIncorrect][1] = student[i];
            numIncorrect++;
        }
    }

    return numIncorrect;
}

// Writes summary report
void writeReport(const int missedQuestions[], char missedAnswers[][2],
    int numIncorrect, int numQuestions)
{
    int numCorrect = numQuestions - numIncorrect;
    double percentCorrect =
        (static_cast<double>(numCorrect) / numQuestions) * 100.0;

    cout << "\n===== Exam Results =====\n";
    cout << "Total questions: " << numQuestions << endl;
    cout << "Number missed:   " << numIncorrect << endl;

    cout << fixed << setprecision(1);
    cout << "Percentage correct: " << percentCorrect << "%\n";

    if (percentCorrect >= 70.0)
        cout << "Status: PASS\n";
    else
        cout << "Status: FAIL\n";

    cout << "\nQuestions missed:\n";

    if (numIncorrect == 0)
    {
        cout << "None. Excellent work!\n\n";
        return;
    }

    cout << left << setw(12) << "Question"
        << setw(18) << "Correct Answer"
        << "Student Answer\n";

    cout << "----------------------------------------\n";

    for (int i = 0; i < numIncorrect; i++)
    {
        cout << left << setw(12) << missedQuestions[i]
            << setw(18) << missedAnswers[i][0]
            << missedAnswers[i][1] << endl;
    }
}
