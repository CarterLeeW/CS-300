//============================================================================
// Name        : main.cpp
// Author      : Carter Wooton
// Version     : 1.0 October 16, 2022
// Description : CS300 Project Two
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================



struct Course {
    string courseId; // unique identifier
    string courseName;
    vector<string> preReqs;
    Course() {
        
    }
};

//============================================================================
// Course Vector functions
//============================================================================
// 
// forward declarations
void printCourseWithPreReqs(Course course);
void printCourseWithNoPreReqs(Course course);
int courseIdToInt(string string);

void PrintAll(vector<Course> courseList) {
    for (int i = 0; i < courseList.size(); ++i) {
        printCourseWithNoPreReqs(courseList.at(i));
    }
}

Course Search(vector<Course> courseList, string courseId) {
    Course course;
    for (int i = 0; i < courseList.size(); ++i) {
        if (courseList.at(i).courseId == courseId) {
            course = courseList.at(i);
        }
    }
    return course;
}


int partition(vector<Course>& courses, int begin, int end) {
    // Declare low and high indices and set the middle value to pivot
    int lowIndex = begin;
    int highIndex = end;
    int midIndex = lowIndex + (highIndex - lowIndex) / 2;
    Course pivot = courses[midIndex];
    bool done = false;

    while (!done) {

        // Increment low index while val of courses at lowIndex < pivot val
        while (courses.at(lowIndex).courseId < pivot.courseId) {
            lowIndex += 1;
        }

        // Decrement highIndex while pivot val < val of courses at highIndex
        while (pivot.courseId < courses.at(highIndex).courseId) {
            highIndex -= 1;
        }

        // Once lowIndex is greater than highIndex, the partitioning can end
        if (lowIndex >= highIndex) {
            done = true;
        }
        // Else swap lower value with higher value and move indices
        else {
            Course tmp = courses.at(lowIndex);
            courses.at(lowIndex) = courses.at(highIndex);
            courses.at(highIndex) = tmp;
            lowIndex += 1;
            highIndex -= 1;
        }
    }
    return highIndex;
}

/**
 * Perform a quick sort on courseId
 * @param courses address of the vector<Course> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void QuickSort(vector<Course>& courses, int begin, int end) {
    //set mid equal to 0
    int midIndex = 0;

    // Base case if partition is one or zero
    if (begin >= end) {
        return;
    }
    // Partition data within the array
    midIndex = partition(courses, begin, end);

    QuickSort(courses, begin, midIndex);
    QuickSort(courses, midIndex + 1, end);
}






//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing course info into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
vector<Course> loadCourses(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;
    vector<Course> courseList;

    ifstream file;
    file.open(csvPath);

    if (!file.is_open()) {
        cout << "File not opened sucessfully" << endl;
        return courseList;
    }
    cout << "Loading courses..." << endl;
    while (!file.eof()) {
        Course course;
        string lineRead;
        vector<string> courseInfo;

        getline(file, lineRead, '\n');
        // add course info to string stream
        stringstream courseStream(lineRead);

        // add course info to vector
        string val;
        while (getline(courseStream, val, ',')) {
            courseInfo.push_back(val);
        }

        // course has no prerequisites
        if (courseInfo.size() <= 2) {
            course.courseId = courseInfo.at(0);
            course.courseName = courseInfo.at(1);
        }
        // course has one or more prerequisites
        else {
            course.courseId = courseInfo.at(0);
            course.courseName = courseInfo.at(1);
            // add prerequisites to course preReqs vector
            for (int i = 2; i < courseInfo.size(); ++i) {
                course.preReqs.push_back(courseInfo.at(i));
            }
        }
        courseList.push_back(course);
    }

    cout << "Courses loaded successfully." << endl;
    return courseList;
}

void printCourseWithNoPreReqs(Course course) {
    cout << course.courseId << ", " << course.courseName << endl;
}

void printCourseWithPreReqs(Course course) {
    cout << course.courseId << ", " << course.courseName << endl;
    cout << "Prerequisites: ";
    // more than one preReq
    if (course.preReqs.size() >= 2) {
        for (int i = 0; i < course.preReqs.size() - 1; ++i) {
            cout << course.preReqs.at(i) << ", ";
        }
        cout << course.preReqs.at(course.preReqs.size() - 1) << endl;
    }
    // only one preReq
    else if (course.preReqs.size() == 1) {
        cout << course.preReqs.at(0) << endl;
    }
    // no preReqs
    else if (course.preReqs.size() == 0) {
        cout << "none" << endl;
    }
}

int main(int argc, char* argv[]) {

    string csvPath, courseKey;
    Course course;

    // Define a vector to hold all the courses
    vector<Course> courseList;

    cout << "Welcome to the course planner." << endl;

    // Menu with exception handling
    string choice = "0";

    while (choice.compare("9") != 0) {

        cout << endl;
        cout << "Menu:" << endl;
        cout << "  1. Load data structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit." << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;

        // Recieve user inout
        try {
            getline(cin, choice);

            // Catch bad inputs
            if ((choice.compare("1") != 0) && (choice.compare("2") != 0)
                && (choice.compare("3") != 0)
                && (choice.compare("9") != 0))
            {
                throw (choice);
            }
        }
        catch (string badChoice) {
            cout << endl;
            cout << badChoice << " is not a valid option." << endl;
            choice = "0";
        }

        switch (stoi(choice)) {
        case 1:
            cout << "Enter file name: ";
            getline(cin, csvPath);

            cout << endl;
            courseList = loadCourses(csvPath);
            break;

        case 2:
            cout << endl;
            cout << "Here is a sample schedule:" << endl;
            cout << endl;
            // sort vector before printing
            QuickSort(courseList, 0, courseList.size() - 1);
            PrintAll(courseList);
            break;

        case 3:
            string input;
            cout << "What course would you like to know more about?" << endl;
            getline(cin, input);
            course = Search(courseList, input);
            cout << endl;
            // course exists
            if (!course.courseId.empty()) {

                printCourseWithPreReqs(course);
            }
            // course not found
            else {
                cout << "Course: " << input << " not found." << endl;
            }
            break;
        }
    }

}