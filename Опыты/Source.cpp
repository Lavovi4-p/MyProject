#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <windows.h>


using namespace std;

const int MAX_LEN = 100;     
const int MAX_DEPTS = 100;

struct Worker {
    char dept[MAX_LEN];  
    char fio[MAX_LEN];  
    int year;           
};

struct Stat {
    char dept[MAX_LEN];  
    int counts[50];      
    int total;          
};

int getCurrentYear() {     
    time_t t = time(nullptr);
    tm now;
    localtime_s(&now, &t);
    return 1900 + now.tm_year;
}

void createFile(const char* fname) {  
    ofstream out(fname, ios::binary);
    if (!out) {
        cerr << "������ �������� �����.\n";
        return;
    }

    int n;
    cout << "������� ������� ������: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        Worker w;
        cout << "\n������ " << i + 1 << ":\n";
        cout << "���� �������������: ";
        cin.getline(w.dept, MAX_LEN);
        cout << "���: ";
        cin.getline(w.fio, MAX_LEN);
        cout << "��� �����������: ";
        cin >> w.year;
        cin.ignore();
        out.write((char*)&w, sizeof(w));
    }

    out.close();
}

void viewFile(const char* fname) {  
    ifstream in(fname, ios::binary);
    if (!in) {
        cerr << "���� �� ������.\n";
        return;
    }

    Worker w;
    cout << "\n���������� �����:\n";

    while (in.read((char*)&w, sizeof(w))) {
        cout << "�������������: " << w.dept << "\n";
        cout << "���: " << w.fio << "\n";
        cout << "��� �����������: " << w.year << "\n\n";
    }

    in.close();
}

void addRecords(const char* fname) {  
    ofstream out(fname, ios::binary | ios::app);
    if (!out) {
        cerr << "������ �������� �����.\n";
        return;
    }

    int n;
    cout << "������� ������� ��������: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; ++i) {
        Worker w;
        cout << "\n������ " << i + 1 << ":\n";
        cout << "���� �������������: ";
        cin.getline(w.dept, MAX_LEN);
        cout << "���: ";
        cin.getline(w.fio, MAX_LEN);
        cout << "��� �����������: ";
        cin >> w.year;
        cin.ignore();
        out.write((char*)&w, sizeof(w));
    }

    out.close();
}

void analyze(const char* binFile, const char* txtFile) {
    ifstream in(binFile, ios::binary);
    if (!in) {
        cerr << "���� �� ������.\n";
        return;
    }

    Stat stats[MAX_DEPTS];
    int statCount = 0;
    for (int i = 0; i < MAX_DEPTS; ++i) {
        stats[i].total = 0;
        memset(stats[i].counts, 0, sizeof(stats[i].counts));
    }

    Worker w;
    int now = getCurrentYear();

    while (in.read((char*)&w, sizeof(w))) {
        int found = -1;
        for (int i = 0; i < statCount; ++i) {
            if (strcmp(stats[i].dept, w.dept) == 0) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            found = statCount++;
            strcpy_s(stats[found].dept, w.dept);
        }

        int exp = now - w.year;
        int idx = exp / 5;
        if (idx >= 50) idx = 49;

        stats[found].counts[idx]++;
        stats[found].total++;
    }

    in.close();

    ofstream out(txtFile);
    if (!out) {
        cerr << "������ ������ � ��������� ����.\n";
        return;
    }

    for (int i = 0; i < statCount; ++i) {
        out << "�������������: " << stats[i].dept << "\n";
        out << "����� �����������: " << stats[i].total << "\n";
        out << left << setw(15) << "��������" << setw(10) << "���-��" << "�������\n";


        for (int j = 0; j < 50; ++j) {
            if (stats[i].counts[j] > 0) {
                int from = j * 5 + 1;
                int to = from + 4;
                float percent = 100.0f * stats[i].counts[j] / stats[i].total;

                char interval[20];
                if (j == 49)
                    sprintf_s(interval, "%d+", from);
                else
                    sprintf_s(interval, "%d-%d", from, to);

                out << setw(15) << interval
                    << setw(10) << stats[i].counts[j]
                    << fixed << setprecision(2) << percent << "%\n";
            }
        }

        out << "\n";
    }

    out.close();
    cout << "������ ��������. ��������� � ����� " << txtFile << "\n";
}

void menu() {  
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    setlocale(LC_ALL, "Russian");
    const char* binFile = "workers.dat";
    const char* txtFile = "stats.txt";

    while (true) {
        cout << "\n����:\n"
            << "1. ������� ����\n"
            << "2. ����������� ����\n"
            << "3. �������� ������\n"
            << "4. ������ � ����� � ��������� ����\n"
            << "0. �����\n"
            << "�����: ";

        int ch;
        cin >> ch;
        cin.ignore();

        switch (ch) {
        case 1: createFile(binFile); break;
        case 2: viewFile(binFile); break;
        case 3: addRecords(binFile); break;
        case 4: analyze(binFile, txtFile); break;
        case 0: return;
        default: cout << "�������� �����.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
