/*
==========================================================================================================
                                      ABC UNIVERSITY (ABCU)
                                   ADVISING ASSISTANCE PROGRAM
==========================================================================================================
Developer: Codden, Isaiah 
Project Title: ABCU Advising Assistance Program
Project Version: 1.0
Development Date: October 13, 2026
==========================================================================================================
*/
#include <iostream> // Support console output and input validation.
#include <fstream> // Handles CSV file access and data retrieval.
#include <sstream> // Separates CSV records into individual fields.
#include <string> // Manages course numbers, name , and filenames.
#include <vector> // Stores course objects and prerequisite records.
#include <algorithm> // Support Sorting and course comparisons.
#include <cctype> // Support character validation and formatting.
#include <unordered_set> // Support efficient duplicate detection

using namespace std;
/*
=========================================================================================================
                                         COURSE DATA STRUCTURE
=========================================================================================================
*/

// Establishes course attributes for organized storage and data retrieval.
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prerequisites;

    // Initializes course attributes to maintain consistent data organization.
    Course(const string& number, const string& name,
        const vector<string>& requiredCourses = {})
        : courseNumber(number),
        courseName(name),
        prerequisites(requiredCourses) {
    }
    // Identifies prerequisite dependencies during Course Evaluation.
    bool hasPrerequisites() const {
        return !prerequisites.empty();
    }
    // Calculates the prerequisite count for course analysis.
    size_t prerequisitesCount() const {
        return prerequisites.size();
    }
};
/*
===========================================================================================================
                                    INPUT NORMALIZATION
===========================================================================================================
*/

// Removes surrounding whitespace to preserve consistent data integrity.
string trimWhitespace(const string& text) {
    const size_t first = text.find_first_not_of("\t\r\n");

    if (first == string::npos) {
        return "";
    }
    const size_t last = text.find_last_not_of("\t\r\n");
    return text.substr(first, last - first + 1);
}
// Normalizes course identifiers to maintain uniform lookup behavior
string normalizeCourseNumber(const string& number) {
    string normalized = trimWhitespace(number);

    transform(normalized.begin(), normalized.end(),
        normalized.begin(),
        [](unsigned char character) {
            return static_cast<char>(toupper(character));
        });
    return normalized;
}
// Verifies identifier syntax to prevent malformed course records.
bool isValidCourseNumber(const string& number) {
    const string normalized = normalizeCourseNumber(number);

    size_t position = 0;

    // Identifies the alphabetic department prefix.
    while (position < normalized.size() &&
        isalpha(static_cast<unsigned char>(normalized[position]))) {
        ++position;
    }
    // Reqires 2 to 5 letters followed by exactly 3 digits.
    if (position < 2 || position > 5 ||
        normalized.size() - position != 3) {
        return false;
    }
    // Verifies every remaining character is numeric.
    for (size_t i = position; i < normalized.size(); ++i) {

        if (!isdigit(static_cast<unsigned char>(normalized[i]))) {
            return false;
        }
    }
    return true;
}
/*
===========================================================================================================
                                            CSV PARSING
===========================================================================================================
*/// Parses quoted CSV fields while maintaining record integrity.
vector<string> parseCSVline(const string& line) {
    vector<string> fields;
    string currentField;
    bool insideQuotes = false;
    bool quoteClosed = false;

    for (size_t i = 0; i < line.size(); ++i) {
        const char character = line[i];

        if (character == '"') {

            if (insideQuotes &&
            i + 1 < line.size() &&
            line[i + 1] == '"') {
            currentField += '"';
            ++i;
        }
        else if (insideQuotes) {
            insideQuotes = false;
            quoteClosed = true;
        }
        else if (trimWhitespace(currentField).empty()
            && !quoteClosed) {
            currentField.clear();
            insideQuotes = true;
        }
        else {
            throw runtime_error(
                "Unexpected quotation mark in CSV field.");
            }
        }
        else if (character == ',' && !insideQuotes) {
            fields.push_back(trimWhitespace(currentField));
            currentField.clear();
            quoteClosed = false;
        }
        else {
            if (quoteClosed &&
                !isspace(static_cast<unsigned char>(character))) {

                throw runtime_error(
                    "unexpected characters after closing quote.");
            }
            currentField += character;
        }
    }
    if (insideQuotes) {
        throw runtime_error(
            "Unclosed quotation mark in CSV record.");
    }
    fields.push_back(trimWhitespace(currentField));
    return fields;
}
/*
===========================================================================================================
                                    COURSE RECORD VALIDATION
===========================================================================================================
*/

// Validate course information to maintain data integrity and accuracy.
Course validateCourseRecord(const vector <string>& fields,
    size_t lineNumber) {

    const string location =
        "Line " + to_string(lineNumber) + ": ";

    // verifies required fields before constructing a course object.
    if (fields.size() < 2) {
        throw runtime_error(
            location + "Course number or title is missing.");
    }
    const string number = normalizeCourseNumber(fields[0]);
    const string title = trimWhitespace(fields[1]);

    // Rejects invalid identifiers to preserve course consistency.
    if (!isValidCourseNumber(number)) {
        throw runtime_error(
            location + "Invalid course number: " + number);
    }
    // Verifies course titles to preserve accurate record validation.
    if (title.empty()) {
        throw runtime_error(
            location + "Course title cannot be empty.");
    }
    vector<string> prerequisites;
    unordered_set<string> uniquePrerequisites;

    // Examines prerequisite relationships for duplicate dependencies.
    for (size_t i = 2; i < fields.size(); ++i) {

        const string prerequisite =
            normalizeCourseNumber(fields[i]);

        //Allows a trailing empty CSV field for courses without prerequisites.
        if (prerequisite.empty()) {
            bool remainingFieldsEmpty = true;

            for (size_t j = i; j < fields.size(); ++j) {
                if (!trimWhitespace(fields[j]).empty()) {
                    remainingFieldsEmpty = false;
                    break;
                }
            }
            if (remainingFieldsEmpty) {
                break;
            }
            throw runtime_error(
                location + "Empty prerequisite field.");
        }
        // Confirms every prerequisite follows the required identifier format.
        if (!isValidCourseNumber(prerequisite)) {
            throw runtime_error(
                location + "Invalid prerequisite: " + prerequisite);
        }
        // Prevents a course from referencing itself.
        if (prerequisite == number) {
            throw runtime_error(
                location + "A course cannot require itself.");
        }
        // Detects duplicate prerequisites before storing dependencies.
        if (!uniquePrerequisites.insert(prerequisite).second) {
            throw runtime_error(
                location + "Duplicate prerequisite: " + prerequisite);
        }
        prerequisites.push_back(prerequisite);
    }
    // Constructs a verified course object after prerequisite validation.
    return Course(number, title, prerequisites);
}
/*
===========================================================================================================
                                        COURSE FILE LOADING
===========================================================================================================
*/

// Maintains the active course collection for searching and sorting.
vector<Course> courses;

// Loads and verifies course records before updating the active collection.
bool loadCourseFromFile(const string& filename) {
    ifstream inputFile(filename);

    // Confirms file accessibility before beginning data extraction.
    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file: "
            << filename << endl;
        return false;
    }
    vector<Course> temporaryCourses;
    unordered_set<string> courseNumbers;
    string line;
    size_t lineNumber = 0;

    try {
        //Processes CSV records with validation and duplicate detection.
        while(getline(inputFile, line)) {
            ++lineNumber;

            if (trimWhitespace(line).empty()) {
                continue;
            }
            vector<string> fields = parseCSVline(line);
            Course newCourse =
                validateCourseRecord(fields, lineNumber);
            
            if (!courseNumbers.insert(newCourse.courseNumber).second) {

                throw runtime_error(
                    "Line " + to_string(lineNumber) +
                    ": Duplicate course number: " +
                    newCourse.courseNumber);
            }
            temporaryCourses.push_back(newCourse);
        }
        // Rejects empty datasets to preserve application reliability.
        if (temporaryCourses.empty()) {
            throw runtime_error(
                "The course data file contains no valid records.");
        }
        // Confirms that all prerequisite references exist in the dataset.
        for (const Course& course : temporaryCourses) {

            for (const string& prerequisite :
                course.prerequisites) {

                if (courseNumbers.find(prerequisite) ==
                    courseNumbers.end()) {
                    throw runtime_error(
                        "Course " + course.courseNumber +
                        " references missing prerequisite: " +
                        prerequisite);
                }
            }
        }
        // Commits verified records without losing previously loaded data
        courses.swap(temporaryCourses);
        cout << "Course data loaded successfully." << endl;
        cout << "Total courses loaded: "
            << courses.size() << endl;
        return true;
    }
    catch (const exception& error) {
        cout << "Error loading course data: "
            << error.what() << endl;
        cout << "Existing course data was preserved."
            << endl;
        return false;
    }
}
/*
===========================================================================================================
                                        COURSE SORTING AND DISPLAY
==========================================================================================================
*/

// Generates an ordered course listing while preserving stored records.
void printCourseList() {

    // Prevents empty datasets from producing misleading information.
    if (courses.empty()) {
        cout << "Please load the course data first." << endl;
        return;
    }
    // Creates a temporary collection for non-destructive sorting.
    vector<Course> sortedCourses = courses;

    // Applies a comparison algorithm for ascending course identifiers.
    sort(sortedCourses.begin(), sortedCourses.end(),
        [](const Course& first, const Course& second) {
            return first.courseNumber < second.courseNumber;
        });
    cout << "\nHere is a sample schedule:\n" << endl;

    //Display each course in ascending alphanumeric order.
    for (const Course& course : sortedCourses) {
        cout << course.courseNumber << ", "
            << course.courseName << endl;
    }
    cout << endl;
}
/*
============================================================================================================
                                                COURSE SEARCH
============================================================================================================
*/

// Locates a course using normalized identifiers and sequential retrieval.
const Course* findCourse(const string& courseNumber) {

    // Standardizes lookup input for consistent search operations.
    const string target = normalizeCourseNumber(courseNumber);

    if (target.empty()) {
        return nullptr;
    }
    // Searches the active course collection without modifying records.
    auto result = find_if(courses.begin(), courses.end(),
        [&target](const Course& course) {
            return course.courseNumber == target;
        });
    if (result == courses.end()) {
        return nullptr;
    }
    return &(*result);
}
/*
===========================================================================================================
                                         COURSE INFORMATION DISPLAY
===========================================================================================================
*/
// Declares prerequisite retrieval before course information processing
void printPrerequisites(const Course& course);

// Retrieves course details through normalized input and controlled searching.
void printCourseInformation() {

    // Prevents course searches before successful data initialization.
    if (courses.empty()) {
        cout << "Please load the course data first." << endl;
        return;
    }
    string requestedCourse;
    cout << "\nwhat course do you want to know about? ";
    getline(cin, requestedCourse);

    if (!cin) {
        cout << "Error: Unable to read course input." << endl;
        return;
    }
    requestedCourse = normalizeCourseNumber(requestedCourse);

    // Validates the identifier before executing the search operation.
    if (!isValidCourseNumber(requestedCourse)) {
        cout << "Invalid course number. "
            << "please enter a valid course identifier." << endl;
        return;
    }
    const Course* selectedCourse = findCourse(requestedCourse);

    if (selectedCourse == nullptr) {
        cout << "Course " << requestedCourse
            << " was not found." << endl;
        return;
    }
    cout << "\n" << selectedCourse->courseNumber
        << ", " << selectedCourse->courseName << endl;
    printPrerequisites(*selectedCourse);
    cout << endl;
}

/*
===========================================================================================================
                                    PREREQUISITE INFORMATION
===========================================================================================================
*/

// Display prerequisite relationships with accurate course identification.
void printPrerequisites(const Course& course) {

    // Handles courses without prerequisite dependencies.
    if (!course.hasPrerequisites()) {
        cout << "Prerequisites: None" << endl;
        return;
    }
    cout << "Prerequisites:" << endl;

    // Resolves course identifiers to provide meaningful prerequisites details.
    for (const string& prerequisite : course.prerequisites) {
        const Course* requiredCourse = findCourse(prerequisite);

        if (requiredCourse != nullptr) {
            cout << " " << requiredCourse->courseNumber
                << ", " << requiredCourse->courseName
                << endl;
        }
        else {
            cout << " " << prerequisite
                << " (Course information unavailable)"
                << endl;
        }
    }
}
/*
===========================================================================================================
                                    MAIN MENU DISPLAY
===========================================================================================================
*/

// Presents the advising interface with consistent menu organization.
void displayManu() {
    cout << "\n1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit." << endl;
    cout << "\nWhat would you like to do? ";
}
/*
===========================================================================================================
                                    MAIN PROGRAM EXECUTION
===========================================================================================================
*/

// Coordinates menu operations and maintains reliable application control.
int main() {
    string menuInput;
    string filename;
    bool programRunning = true;

    cout << "Welcome to the course planner." << endl;

    // Maintains the interactive menu until the user chooses to exit.
    while (programRunning) {
        displayManu();

        if (!getline(cin, menuInput)) {
            cout << "\nInput stream closed. exiting program."
                << endl;
            break;
        }
        menuInput = trimWhitespace(menuInput);
        
        // Routes validated selections to their corresponding operations.
        if (menuInput == "1") {
            cout << "\nEnter the course data filename: ";

            if (!getline(cin, filename)) {
                cout << "Unable to read the filename." << endl;
                break;
            }
            filename = trimWhitespace(filename);

            if (filename.empty()) {
                cout << "Error: filename cannot be empty."
                    << endl;
                continue;
            }
            loadCourseFromFile(filename);

        }
        else if (menuInput == "2") {
            printCourseList();
        }
        else if (menuInput == "3") {
            printCourseInformation();
        }
        else if (menuInput == "9") {
            cout << "Thank you for using the course planner!"
                << endl;
            programRunning = false;
        }
        else {
            cout << menuInput
                << " is not a valid option." << endl;
        }
    }
    return 0;
}
/*
===========================================================================================================
                                    DEVELOPER NOTE - PROGRAM EXECUTION
===========================================================================================================
This application was designed to provide ABC University Academic advisors with an organized and reliable
method of accessing course information.

before running the program, ensure that the ABCU Advising Program input CSV file is available

To load the course information:

1. Place the provided CSV file insde the ProjectTwo folder or another accessible directory.

2. Run the application and select Option 1 to load the course data.

3. When prompted for the filename, copy and paste the complete CSV file path into the console.

4.If the copied file path contains quotation marks(" "), remove them before pressing enter.

5. Once the file loads successfully, the application will confirm the total number of courses loaded.

6. Use Option 2 to display the complete alphanumeric course list or Option 3 to retrieve individual courses
and their prerequisites.

This program includes additional validation procedures, duplicate detection, input normalization,
and error handling to improve data integrity and maintainability.
===========================================================================================================
*/