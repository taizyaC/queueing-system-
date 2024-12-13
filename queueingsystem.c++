#include <iostream>
#include <iomanip>
#include <vector>
#include<fstream>

using namespace std;

vector<double> rho_values, N_values, Q_values, RT_values;

double calculateN(double rho) {
    return rho / (1 - rho);
}

double calculateQ(double rho) {
    return (rho * rho) / (1 - rho);
}

double calculateRT(double N, double mu) {
    return N / mu;
}
void saveTableToFile(const string& filename, const vector<double>& x, const vector<double>& y) {
    ofstream file(filename);
    if (file.is_open()) {
        for (size_t i = 0; i < x.size(); ++i) {
            file <<fixed<<setw(10)<< y[i] << setw(10) << x[i] << endl;
        }
        file.close();
        cout << "Table saved to " << filename << endl;
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

void printTable(double start_rho, double end_rho, double step_rho, double mu) {
    cout << setw(10) << "ρ" << setw(10) << "N" << setw(10) << "Q" << setw(10) << "RT" << endl;
     
     

    for(double rho = start_rho; rho <= end_rho; rho += step_rho) {
        double N = calculateN(rho);
        double Q = calculateQ(rho);
        double RT = calculateRT(N, mu);
        cout << fixed << setprecision(3) << setw(10) << rho << setw(10) << N << setw(10) << Q << setw(10) << RT << endl;

         rho_values.push_back(rho);
        N_values.push_back(N);
        Q_values.push_back(Q);
        RT_values.push_back(RT);
    }
}

int main() {
    double mu; 
    double start_rho, end_rho, step_rho;
    
    cout << "Enter start value of ρ (rho): ";
    cin >> start_rho;
    
    cout << "Enter end value of ρ (rho): ";
    cin >> end_rho;

    cout << "Enter step value of ρ (rho): ";
    cin >> step_rho;
    
    cout << "Enter value for μ (mu): ";
    cin >> mu;
    
    if(start_rho < 0 || start_rho >= 1 || end_rho <= 0 || end_rho >= 1 || start_rho >= end_rho || step_rho <= 0 || mu <= 0) {
        cout << "Please enter the correct parameters" << endl;
        return 1;
    }
    
    printTable(start_rho, end_rho, step_rho, mu);
    
    saveTableToFile("N.txt", rho_values, N_values);
    saveTableToFile("Q.txt", rho_values, Q_values);
    saveTableToFile("RT.txt", rho_values, RT_values);
    
    return 0;
}
