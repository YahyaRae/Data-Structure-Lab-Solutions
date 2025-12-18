#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

/* ===================== DATA STRUCTURES ===================== */

struct Student {
    int id;
    string name;
    string dept;
    int semester;
    double cgpa;
    int creditHours;
    int enrollmentYear;
};

struct Node {
    Student data;
    Node* next;
};

/* ===================== LINKED LIST UTILITIES ===================== */

Node* createNode(const Student& s) {
    Node* n = new Node;
    n->data = s;
    n->next = nullptr;
    return n;
}

void append(Node*& head, const Student& s) {
    Node* n = createNode(s);
    if (!head) {
        head = n;
        return;
    }
    Node* temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = n;
}

Node* copyList(Node* head) {
    Node* newHead = nullptr;
    while (head) {
        append(newHead, head->data);
        head = head->next;
    }
    return newHead;
}

void freeList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

/* ===================== FILE INPUT ===================== */

Node* loadStudents(const string& fileName, int& total) {
    ifstream in(fileName);
    if (!in.is_open()) {
        cout << "Input file error. Make sure students_data.txt is in Debug folder.\n";
        return nullptr;
    }

    in >> total;
    Node* head = nullptr;

    for (int i = 0; i < total; i++) {
        Student s;
        in >> s.id;
        in.ignore();

        getline(in, s.name, ' ');
        string last;
        getline(in, last, ' ');
        s.name += " " + last;

        in >> s.dept >> s.semester >> s.cgpa >> s.creditHours >> s.enrollmentYear;

        append(head, s);
    }

    in.close();
    return head;
}

/* ===================== MERGE SORT (CGPA RANKING) ===================== */

bool cgpaCompare(const Student& a, const Student& b) {
    if (a.cgpa != b.cgpa)
        return a.cgpa > b.cgpa;
    return a.creditHours > b.creditHours;
}

void split(Node* src, Node*& a, Node*& b) {
    Node* slow = src;
    Node* fast = src->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    a = src;
    b = slow->next;
    slow->next = nullptr;
}

Node* merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (cgpaCompare(a->data, b->data)) {
        a->next = merge(a->next, b);
        return a;
    } else {
        b->next = merge(a, b->next);
        return b;
    }
}

void mergeSort(Node*& head) {
    if (!head || !head->next) return;
    Node* a;
    Node* b;
    split(head, a, b);
    mergeSort(a);
    mergeSort(b);
    head = merge(a, b);
}

/* ===================== INSERTION SORT ===================== */

void insertionSort(Node*& head, bool (*cmp)(const Student&, const Student&)) {
    Node* sorted = nullptr;

    while (head) {
        Node* curr = head;
        head = head->next;

        if (!sorted || cmp(curr->data, sorted->data)) {
            curr->next = sorted;
            sorted = curr;
        } else {
            Node* temp = sorted;
            while (temp->next && !cmp(curr->data, temp->next->data))
                temp = temp->next;
            curr->next = temp->next;
            temp->next = curr;
        }
    }
    head = sorted;
}

bool enrollmentCompare(const Student& a, const Student& b) {
    if (a.enrollmentYear != b.enrollmentYear)
        return a.enrollmentYear < b.enrollmentYear;
    return a.id < b.id;
}

bool deptCompare(const Student& a, const Student& b) {
    if (a.dept != b.dept)
        return a.dept < b.dept;
    if (a.semester != b.semester)
        return a.semester < b.semester;
    return a.cgpa > b.cgpa;
}

bool nameCompare(const Student& a, const Student& b) {
    return a.name < b.name;
}

/* ===================== OUTPUT FILES ===================== */

void writeRankedByCGPA(Node* head) {
    ofstream out("ranked_by_cgpa.txt");
    int rank = 1;

    out << left << setw(5) << "Rank" << setw(10) << "ID"
        << setw(20) << "Name" << setw(6) << "Dept"
        << setw(5) << "Sem" << setw(6) << "CGPA"
        << setw(8) << "Credits" << setw(6) << "Year" << "\n";

    while (head) {
        out << setw(5) << rank++
            << setw(10) << head->data.id
            << setw(20) << head->data.name
            << setw(6) << head->data.dept
            << setw(5) << head->data.semester
            << setw(6) << fixed << setprecision(2) << head->data.cgpa
            << setw(8) << head->data.creditHours
            << setw(6) << head->data.enrollmentYear << "\n";
        head = head->next;
    }
    out.close();
}

void writeSortedByEnrollment(Node* head) {
    ofstream out("sorted_by_enrollment.txt");
    int currentYear = -1;
    double sum = 0;
    int count = 0;

    while (head) {
        if (head->data.enrollmentYear != currentYear) {
            if (count > 0)
                out << "Average CGPA: " << fixed << setprecision(2) << sum / count << "\n\n";

            currentYear = head->data.enrollmentYear;
            out << "Enrollment Year: " << currentYear << "\n";
            out << "---------------------------\n";
            sum = 0;
            count = 0;
        }

        out << head->data.id << " "
            << head->data.name << " "
            << fixed << setprecision(2) << head->data.cgpa << "\n";

        sum += head->data.cgpa;
        count++;
        head = head->next;
    }

    if (count > 0)
        out << "Average CGPA: " << sum / count << "\n";

    out.close();
}

void writeDepartmentAnalysis(Node* head) {
    ofstream out("department_analysis.txt");

    string currDept = "";
    int total = 0;
    double sum = 0, minC = 4.0, maxC = 0;

    while (head) {
        if (head->data.dept != currDept) {
            if (total > 0) {
                out << "Total Students: " << total << "\n";
                out << "Average CGPA: " << sum / total << "\n";
                out << "Highest CGPA: " << maxC << "\n";
                out << "Lowest CGPA: " << minC << "\n\n";
            }

            currDept = head->data.dept;
            out << "Department: " << currDept << "\n";
            out << "----------------------\n";
            total = 0; sum = 0; minC = 4.0; maxC = 0;
        }

        out << head->data.name << " "
            << "Sem " << head->data.semester << " "
            << fixed << setprecision(2) << head->data.cgpa << "\n";

        total++;
        sum += head->data.cgpa;
        minC = min(minC, head->data.cgpa);
        maxC = max(maxC, head->data.cgpa);
        head = head->next;
    }

    out.close();
}

void writePerformanceTiers(Node* head, int total) {
    ofstream out("performance_tiers.txt");

    Node* elite = nullptr;
    Node* high = nullptr;
    Node* good = nullptr;
    Node* sat = nullptr;
    Node* low = nullptr;

    while (head) {
        if (head->data.cgpa >= 3.70) append(elite, head->data);
        else if (head->data.cgpa >= 3.30) append(high, head->data);
        else if (head->data.cgpa >= 3.00) append(good, head->data);
        else if (head->data.cgpa >= 2.50) append(sat, head->data);
        else append(low, head->data);
        head = head->next;
    }

    insertionSort(elite, nameCompare);
    insertionSort(high, nameCompare);
    insertionSort(good, nameCompare);
    insertionSort(sat, nameCompare);
    insertionSort(low, nameCompare);

    out << "Elite Tier\n"; while (elite) { out << elite->data.name << "\n"; elite = elite->next; }
    out << "\nHigh Achievers\n"; while (high) { out << high->data.name << "\n"; high = high->next; }
    out << "\nGood Standing\n"; while (good) { out << good->data.name << "\n"; good = good->next; }
    out << "\nSatisfactory\n"; while (sat) { out << sat->data.name << "\n"; sat = sat->next; }
    out << "\nNeeds Improvement\n"; while (low) { out << low->data.name << "\n"; low = low->next; }

    out.close();
}

/* ===================== MAIN ===================== */

int main() {
    int total;
    Node* master = loadStudents("students_data.txt", total);
    if (!master) return 0;

    Node* cgpaList = copyList(master);
    mergeSort(cgpaList);
    writeRankedByCGPA(cgpaList);

    Node* enrollList = copyList(master);
    insertionSort(enrollList, enrollmentCompare);
    writeSortedByEnrollment(enrollList);

    Node* deptList = copyList(master);
    insertionSort(deptList, deptCompare);
    writeDepartmentAnalysis(deptList);

    Node* perfList = copyList(master);
    writePerformanceTiers(perfList, total);

    freeList(master);
    freeList(cgpaList);
    freeList(enrollList);
    freeList(deptList);
    freeList(perfList);

    return 0;
}
