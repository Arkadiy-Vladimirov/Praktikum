#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

Matrix read_mat(int n, int m);
void print_mat(Matrix &mat);

Matrix tranpose(Matrix &mat);


int main() {
    int n, m;
    std::cin >> n >> m;
    
    Matrix mat = read_mat(n, m);
    Matrix tmat = tranpose(mat);
    print_mat(tmat);

    return 0;
}


Matrix tranpose(Matrix &mat) {
    int n = mat.size();
    int m;
    if (n == 0) {
        m = 0;
    } else {
        m = mat[0].size();
    }
    Matrix tmat(m, std::vector<int>(n));

    for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        tmat[j][i] = mat[i][j];
    }
    }

    return tmat;
}

Matrix read_mat(int n, int m) {
    Matrix mat(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
        std::cin >> mat[i][j];
    }
    }
    return mat;
}

void print_mat(Matrix &mat) {
    int n = mat.size();
    if (n == 0) {
        return;
    }
    int m = mat[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return;
}