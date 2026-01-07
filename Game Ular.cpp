#include <iostream>
#include <conio.h>      // Untuk _kbhit() dan _getch()
#include <windows.h>    // Untuk Sleep()
#include <cstdlib>      // Untuk rand()
using namespace std;

// ---------------------
// Variabel Global
// ---------------------
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
string playerName = "Echa";

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// ---------------------
// Setup Game
// ---------------------
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

// ---------------------
// Gambar Map
// ---------------------
void Draw() {
    system("cls");
    cout << "===== SNAKE GAME - " << playerName << " =====\n";

    // Border atas
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";  // Border kiri

            if (i == y && j == x)
                cout << "O";          // Kepala ular
            else if (i == fruitY && j == fruitX)
                cout << "F";          // Buah
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";  // Ekor
                        printTail = true;
                    }
                }
                if (!printTail) cout << " ";
            }

            if (j == width - 1) cout << "#"; // Border kanan
        }
        cout << endl;
    }

    // Border bawah
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
}

// ---------------------
// Input Tombol
// ---------------------
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a': dir = LEFT; break;
        case 'd': dir = RIGHT; break;
        case 'w': dir = UP; break;
        case 's': dir = DOWN; break;
        case 'x': gameOver = true; break; // Keluar
        }
    }
}

// ---------------------
// Logika Game
// ---------------------
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int tempX, tempY;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        tempX = tailX[i];
        tempY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    switch (dir) {
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
    default: break;
    }

    // Menabrak dinding
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Menabrak ekor
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    // Makan buah
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

// ---------------------
// Main Program
// ---------------------
int main() {
    Setup();

    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // Delay gerakan, bisa diubah 50=cepat, 150=pelan
    }

    cout << "\nGame Over! Terima kasih sudah bermain, " << playerName << "!\n";
    return 0;
}
