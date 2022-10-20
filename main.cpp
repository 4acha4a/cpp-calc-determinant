#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


string ReadLine() {
    string s;
    getline(cin, s);
    return s;
}

int ReadLineWithNumber() {
    int result = 0;
    cin >> result;
    ReadLine();
    return result;
}

class Matrix {
    public:
    void createMatrix(const vector<vector<int>>& input){
        int index = 0;
        size = input.size();

        values_.resize(size);
        values_sign_.resize(size);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                values_[i].push_back(input[i][j]);
                ++index;
                if ((i + j) % 2 == 0) {
                    values_sign_[i].push_back(true);
                } else {
                    values_sign_[i].push_back(false);           
                }
            }
        }
    }

    int calcDeterminant() {
        int determinant = 0;
        if (size == 0) {
            throw invalid_argument("Matrix is empty");
        } else {
            if (size == 1) {
                return values_[0][0];
            } else {
                if (size == 2){
                    return values_[0][0] * values_[1][1] - values_[0][1] * values_[1][0];
                } else {
                    if (size >= 3) {
                        for (int i = 0; i < size; ++i) {
                            Matrix sub = subMatrix(0,i);
                            if (values_sign_[0][i]) {
                                determinant += values_[0][i]*sub.calcDeterminant();
                            } else {
                                determinant -= values_[0][i]*sub.calcDeterminant();
                            }
                        }
                    } 
                }
            }
        }
        return determinant;
    }

    Matrix subMatrix(const int index_row, const int index_column){
        Matrix matrix;
        matrix.size = size - 1;
        matrix.values_ = values_;
        matrix.values_sign_.resize(matrix.size);
        matrix.values_.erase(matrix.values_.begin() + index_row);
        for (size_t i = 0; i < matrix.size; ++i){
            matrix.values_[i].erase(matrix.values_[i].begin() + index_column);
        }
        for (size_t i = 0; i < matrix.size; ++i) {
            for (size_t j = 0; j < matrix.size; ++j) {
                if ((i + j) % 2 == 0) {
                    matrix.values_sign_[i].push_back(true);
                } else {
                    matrix.values_sign_[i].push_back(false);           
                }
            }
        }
        return matrix;
    }

    private:
        int size = 0;
        vector<vector<int>> values_;
        vector<vector<bool>> values_sign_; 

    bool is_integer(const float k) {
        return floor(k) == k;
    }
};

vector<int> InputToVecOfNum(const string& text) {
    vector<int> numbers;
    string number;
    for (const char c : text) {
        if (c == ' ') {
            if (!number.empty()) {
                numbers.push_back(stoi(number));
                number.clear();
            }
        } else {
            number += c;
        }
    }
    if (!number.empty()) {
        numbers.push_back(stoi(number));
    }

    return numbers;
}

int main(){
    Matrix matrix;
    int size = 0;
    vector<vector<int>> input;
    cout << "Enter matrix size:"s << endl;
    size = ReadLineWithNumber();

    cout << "Enter matrix elements:"s << endl;
    for (size_t i = 0; i < size; ++i) {
        input.push_back(InputToVecOfNum(ReadLine()));
    }
    matrix.createMatrix(input);

    int determinant = matrix.calcDeterminant();
    cout << "The matrix determinant is: "s << determinant << endl;
    return 0;
}