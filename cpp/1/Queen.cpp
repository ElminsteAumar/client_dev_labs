#include "Queen.hpp"
#include <stdlib.h>
#include <fstream>
#include <iostream>

// constructor
Queen::Queen() {
    srand(time(NULL));
    
    // dynamically allocate memory
    desk = new int*[N];
    for (int i = 0; i < N; i++)
        desk[i] = new int[N];
    
    // initialize desk
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            desk[i][j] = 0;
        }
    }

    // initialize queen position
    int i = N;
    while (i != 0) {
        int x = rand()%N, y = rand()%N;
        if (desk[x][y] == 1) continue;
        desk[x][y] = 1;
        i--;
    }
}

Queen::~Queen() {
    for (int i = 0; i < N; ++i)
        delete [] desk[i];
    delete [] desk;
}

// helper functions
void Queen::save() {
    // save to file;
    std::ofstream f;
    f.open("output.txt", std::ios::app);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            f << desk[i][j] << " ";
        }
        f << "\n";
    }
    f << "\n";
    f.close();
}

void Queen::show() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << desk[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Queen::info() {
    std::cout << "Мокроусов Владислав ІП-71 ФІОТ" << std::endl;
}

int Queen::argmin(int arr[]) {
    int min = arr[0], j = 0;
    
    for (int i = 0; i < N; i++) if (arr[i] < min) min = arr[i];
    for (int i = 0; i < N; i++) if (arr[i] == min) j++;
        
    int arrRand[j], k = 0;
    for (int i = 0; i < N; i++) {
        if (arr[i] == min) {
            arrRand[k] = i;
            k++;
        }
    }
    
    return arrRand[rand() % j];
}

// arrange functions (by row/col)
void Queen::setRow() {
    // set one queen for each row
    int fRows[N] = {0}, qpos[N][2];
    freeRows(fRows, qpos);
    
    // iterate rows with more than 1 piece
    for (int i = 0; i < N; i++) {
        if (fRows[i] != 2) continue;

        int j = 0;
        while (fRows[i] != 1) {
            if (qpos[j][0] == i) {
                for (int k = 0; k < N; k++)
                    if (fRows[k] == 0 && moveRow(k, i, qpos[j][1])) break;
            }
            freeRows(fRows, qpos);
            if (fRows[i] == 1) break;
            
            j++;
            if (j == N) j = 0;
        }
    }
}

void Queen::setCol() {
    // set one queen for each row
    int fCols[N] = {0}, qpos[N][2];
    freeCols(fCols, qpos);

    // iterate cols with more than 1 piece
    for (int i = 0; i < N; i++) {
        if (fCols[i] != 2) continue;

        int j = 0;
        while (fCols[i] != 1) {
            if (qpos[j][1] == i) {
                for (int k = 0; k < N; k++)
                    if (fCols[k] == 0 && moveCol(k, qpos[j][0], i)) break;
            }
            freeCols(fCols, qpos);
            if (fCols[i] == 1) break;
            
            j++;
            if (j == N) j = 0;
        }
    }
}

// get free rows/cols
void Queen::freeRows(int rows[], int qpos[N][2]) {
    int k = 0, m; // free rows; k,m - counters
    
    for (int i = 0; i < N; i++) {
        m = 0; // nums pieces in row
        for (int j = 0; j < N; j++) {
            if (desk[i][j] == 1) {
                qpos[k][0] = i; // row
                qpos[k][1] = j; // col
                
                m++;
                k++;
            }
        }
        
        switch (m) {
            case 0:
                rows[i] = 0; // row is clear
                break;
            case 1:
                rows[i] = 1; // 1 piece in a row
                break;
            default:
                rows[i] = 2;
                break;
        }
    }
}

void Queen::freeCols(int cols[], int qpos[N][2]) {
    int k = 0, m; // free cols; k,m - counters
    
    for (int i = 0; i < N; i++) {
        m = 0;
        for (int j = 0; j < N; j++) {
            if (desk[j][i] == 1) {
                qpos[k][0] = j; // row
                qpos[k][1] = i; // col
                
                m++;
                k++;
            }
        }
        
        switch (m) {
            case 0:
                cols[i] = 0; // col is clear
                break;
            case 1:
                cols[i] = 1; // 1 piece in a col
                break;
            default:
                cols[i] = 2;
                break;
        }
    }
}

// main algorithm
int Queen::conflicts(int x1, int y1, int qrow) {
    // return number of conflicts at position (x1, y1), queen at (qrow, y1)
    int conf = 0;
    int fRows[N] = {0}, qpos[N][2];
    freeRows(fRows, qpos);
    desk[qrow][y1] = 0;
    
    for (int i = 0; i < N; i++) {
        if (qpos[i][1] == y1) continue; // skip queen at that col
        if (attacks(qpos[i][0], qpos[i][1], x1, y1)) conf++;
    }
    desk[qrow][y1] = 1;
    return conf;
}

bool Queen::solve(int iter = 100) {
    this->setRow();
    this->setCol();
    
    int fRows[N] = {0}, qpos[N][2], x, y, rcol;
    freeRows(fRows, qpos); // get queen positions
    
    for (int i = 0; i < iter; i++) {
        rcol = rand()%N; // random col
        int colConflicts[N];
        
        // get queen coords in random col
        for (int j = 0; j < N; j++) {
            if (qpos[j][1] == rcol) {
                x = qpos[j][0];
                break;
            }
        }
        
        for (int j = 0; j < N; j++)
            colConflicts[j] = conflicts(j, rcol, x);
        
        int min = argmin(colConflicts);
        if (x != min)
            move(x, rcol, min, rcol);
        
        freeRows(fRows, qpos); // get new queen positions
        if (solved(qpos)) return true; // check if solved
    }
    return false;
}

bool Queen::solved(int qpos[N][2]) {
    for (int i = 0; i < N; i++)
        if (conflicts(qpos[i][0], qpos[i][1], qpos[i][0]) != 0) return false;
    return true;
}
// attack function
bool Queen::attacks(int x, int y, int xpos, int ypos) {
    int n = x, m = y - 1;
    
    // left
    if (y >= 1) {
        while (m >= 0) {
            if (desk[n][m] == 1) break;
            if (n == xpos && m == ypos) return true;
            m--;
        }
        if (x >= 1) {
            // top-left diagonal
            for (n = x - 1, m = y - 1; m >= 0 && n >= 0; n--, m--) {
                if (desk[n][m] == 1) break;
                if (n == xpos && m == ypos) return true;
            }
        }
        if (x <= 6) {
            // bottom-left diagonal
            for (n = x + 1, m = y - 1; m >= 0 && n < N; n++, m--) {
                if (desk[n][m] == 1) break;
                if (n == xpos && m == ypos) return true;
            }
        }
        
    }
    // right
    if (y <= 6) {
        n = x, m = y + 1;
        while (m < N) {
            //std::cout << n << " " << m << std::endl;
            if (desk[n][m] == 1) break;
            if (n == xpos && m == ypos) return true;
            m++;
        }
        if (x >= 1) {
            // top-right diagonal
            for (n = x - 1, m = y + 1; m < N && n >= 0; n--, m++) {
                if (desk[n][m] == 1) break;
                if (n == xpos && m == ypos) return true;
            }
        }
        if (x <= 6) {
             // bottom-right diagonal
            for (n = x + 1, m = y + 1; m < N && n < N; n++, m++) {
                if (desk[n][m] == 1) break;
                if (n == xpos && m == ypos) return true;
            }
        }
    }
    if (x <= 6) {
        // bottom
        n = x + 1, m = y;
        while (n < N) {
            if (desk[n][m] == 1) break;
            if (n == xpos && m == ypos) return true;
            n++;
        }
    }
    if (x >= 1) {
        // top
        n = x - 1, m = y;
        while (n >= 0) {
            if (desk[n][m] == 1) break;
            if (n == xpos && m == ypos) return true;
            n--;
        }
    }
    return false;
}

// move functions
void Queen::move(int x1, int y1, int x2, int y2) {
    desk[x1][y1] = 0;
    desk[x2][y2] = 1;
    save();
}

bool Queen::moveRow(int k, int i, int j) {
    // k = row, (i, j) - position
    int m, n; // counters
    if (k == i) {
        return true;
    } else if (k < i) {
        n = i - 1, m = j;
        // top
        while (n >= 0) {
            if (desk[n][m] == 1) break;
            if (n == k) {
                move(i, j, n, m);
                return true;
            }
            n--;
        }
        // top-left diagonal
        for (n = i - 1, m = j - 1; m >= 0 && n >= 0; n--, m--) {
            if (n == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            } 
        }
        // top-right diagonal
        for (n = i - 1, m = j + 1; m < N && n >= 0; n--, m++) {
            if (n == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            }
        }
    } else {
        n = i + 1, m = j;
        
        // bottom
        while (n < N) {
            if (desk[n][m] == 1) break;
            if (n == k) {
                move(i, j, n, m);
                return true;
            }
            n++;
        }
        // bottom-left diagonal
        for (n = i + 1, m = j - 1; m >= 0 && n < N; n++, m--) {
            if (n == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            } 
        }
        // bottom-right diagonal
        for (n = i + 1, m = j + 1; m < N && n < N; n++, m++) {
            if (n == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            }
        }
    }
    return false;
}

bool Queen::moveCol(int k, int i, int j) {
    // k = col, (i, j) - position
    int m, n; // counters
    
    if (k == j) {
        return true;
    } else if (k < j) {
        n = i, m = j - 1;
        // left
        while (m >= 0) {
            if (desk[n][m] == 1) break;
            if (m == k) {
                move(i, j, n, m);
                return true;
            }
            m--;
        }
        // top-left diagonal
        for (n = i - 1, m = j - 1; m >= 0 && n >= 0; n--, m--) {
            if (m == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            } 
        }
        // bottom-left diagonal
        for (n = i + 1, m = j - 1; m >= 0 && n < N; n++, m--) {
            if (m == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            } 
        }
    } else {
        n = i, m = j + 1;
        // right
        while (m < N) {
            if (desk[n][m] == 1) break;
            if (m == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            }
            m++;
        }
        // top-right diagonal
        for (n = i - 1, m = j + 1; m < N && n >= 0; n--, m++) {
            if (m == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            }
        }
        // bottom-right diagonal
        for (n = i + 1, m = j + 1; m < N && n < N; n++, m++) {
            if (m == k && desk[n][m] == 0) {
                move(i, j, n, m);
                return true;
            }
        }
    }
    return false;
}