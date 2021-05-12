#include <windows.h>
#include <math.h>
#include <TIME.H>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#define n 11

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Лабораторна робота 5";

double** randm(int rows, int cols){
                double** matrix = (double**)malloc(rows * sizeof(double*));

                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));

                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        double temp = rand() % 21;
                        matrix[i][j]=temp/10;
                    }}
                return matrix;
            }

double** mulmr(double coef, double **matrix, int rows, int cols){
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < cols; j++)
                    {
                        matrix[i][j] = matrix[i][j] * coef;

                        if(matrix[i][j] < 1.0)
                        {
                            matrix[i][j] = 0;
                        } else matrix[i][j] = 1;
                        }
                }
                return matrix;
            }

struct queue { //структура черги
    int array[n];
    int front;
    int last;
};

struct queue* init() { // ініціалізація черги
    struct queue* q = malloc(sizeof(struct queue));
    q->front = -1;
    q->last = -1;
    return q;
}

int isEmpty(struct queue* q) { //перевірка чи порожня черга
    if (q->last == -1)
        return 1;
    else
        return 0;
}

void pushQueue(struct queue* q, int value) { // додавання елементів в чергу
    if (q->front == -1)
        q->front = 0;
    q->last++;
    q->array[q->last] = value;
}

int popQueue(struct queue* q) {
    int item;
    if (isEmpty(q)) {
        item = -1;
    }
    else {
        item = q->array[q->front];
        q->front++;
        if (q->front > q->last) q->front = q->last = -1;
    }
    return item;
}

struct stack {  //структура стеку
    int array[n];
    int top;
};

struct stack* initStack() { // ініціалізація стеку
    struct stack* stack = malloc(sizeof(struct stack));
    stack->top = 0;
    return stack;
}

void pushStack(struct stack* stack, int value) { // додавання елементів в стек
    if (stack->top < n) {
        stack->array[stack->top] = value;
        stack->top++;
    }
}

void flush(struct stack* stack) { // видалення вершини з голови стеку
    stack->top--;
}

int top(struct stack* stack) {  //вершина стеку
    if (stack->top > 0)
        return stack->array[stack->top - 1];
    else return -1;
}

int isEmptyStack(struct stack* stack) { //перевірка чи порожній стек
    if (stack->top == 0)
        return 1;
    else
        return 0;
}

void printGrapgMatrix(int **graphMatrix){

             for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%d ",graphMatrix[i][j]);
            }
            printf("\n");

        }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;

    w.lpszClassName = ProgName;
    w.hInstance = hInstance;
    w.lpfnWndProc = WndProc;
    w.hCursor = LoadCursor(NULL, IDC_ARROW);
    w.hIcon = 0;
    w.lpszMenuName = 0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style = CS_HREDRAW | CS_VREDRAW;
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    hWnd = CreateWindow(ProgName,
        "Lab 5 by Labiak Ivan",
        WS_OVERLAPPEDWINDOW,
        1200,
        100,
        700,
        800,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) {
        TranslateMessage(&lpMsg);
        DispatchMessage(&lpMsg);
    }
    return(lpMsg.wParam);
}

void paintLines(HDC hdc, int matrix[n][n], int nx[n], int ny[n], int start, int end) {
    float koef;
    int  radius = 16, divine = 1, xDif, yDif;
    if (matrix[start][end] == 1) {
        xDif = nx[start] - nx[end];
        yDif = ny[start] - ny[end];
        koef = sqrt(xDif * xDif + yDif * yDif) / radius;
        if (start == end) {
            MoveToEx(hdc, nx[end], ny[end], NULL);
            if(start<=3){
             Arc(hdc, nx[start]+20, ny[start]-5, nx[start]-40, ny[start]-60, nx[start], ny[start], nx[start], ny[start]);
            }else if(start<=7){
             Arc(hdc, nx[start]+50, ny[start]+10, nx[start], ny[start]-40, nx[start], ny[start], nx[start], ny[start]);
            }else if(start<=9){
             Arc(hdc, nx[start]+35, ny[start], nx[start]-20, ny[start]+50, nx[start], ny[start], nx[start], ny[start]);
            }
            else{
             Arc(hdc, nx[start]+35, ny[start], nx[start]-20, ny[start]+50, nx[start], ny[start], nx[start], ny[start]);
            }
        } else {
            MoveToEx(hdc, nx[start], ny[start], NULL);
            if ((ny[start] == ny[end]) && abs(nx[start] - nx[end]) > 200 ) {
          Arc(hdc, nx[end], ny[end]-50, nx[start], ny[start]+50, nx[end], ny[end], nx[start], ny[start]);
            }else if(nx[start] == nx[end]&& abs(ny[start] - ny[end]) > 200){
    if(start >=9 || end >=9){
      Arc(hdc, nx[end]-40, ny[end], nx[start]+40, ny[start], nx[start], ny[start], nx[end], ny[end]);
    }else if((start>=3 && start <=8) && (end >=3 && end<=8)){
        if(start>end){
      Arc(hdc, nx[end]-60, ny[end], nx[start]+60, ny[start], nx[start], ny[start], nx[end], ny[end]);
        }else{
      Arc(hdc, nx[start]-60, ny[start], nx[end]+60, ny[end], nx[end], ny[end], nx[start], ny[start]);
        }
    }else{
    LineTo(hdc, nx[end], ny[end]);
    }
            }else if (yDif == 0 && abs(xDif) > 200 && end <= 3) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] - 35);
            }
            else if (abs(xDif) == 300 && abs(yDif) == 300 && (end == 0 || end == 3)) {
                LineTo(hdc, nx[end] + xDif / 2, ny[end] + yDif / 1);
            }
            if((ny[start] ==ny[end]) &&(abs(nx[start] - nx[end]) > 200)){

            }else{
                if((start == 3 && end == 5 )||(start == 3 && end == 6 )||(start == 6 && end == 4 )||(start == 4 && end == 6 )||(start == 6 && end == 3 )
                    ||(start == 0 && end == 9 )||(start == 9 && end == 0 )){

                }else{
           LineTo(hdc, nx[end], ny[end]);

}

            }
        }
    }
}

void paintVertex(HDC hdc, int xPos[n], int yPos[n], char* nn[n], int i) {
    int dtx = 5, radius = 16;
    Ellipse(hdc, xPos[i] - radius, yPos[i] - radius, xPos[i] + radius, yPos[i] + radius);
    if(i<9){
           TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, nn[i], 1);
    }else{
    TextOut(hdc, xPos[i] - dtx, yPos[i] - 8, nn[i], 2);
    }

}

void printMatrix(HDC hdc, int A[n][n]) {
    char text[11];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sprintf_s(text, 2, "%d", A[i][j]);
            TextOutA(hdc, 200 + 10 * j, 500 + 20 * i, text, 1);
        }
    }
}

void simMatrix(int A[n][n], int* B[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == 1) {
                B[j][i] = 1;
                B[i][j] = 1;
            }
        }
    }
}

void generateMatrix(int* matrix[n][n], double k) {
    int element;
    double temp;
    double num;
    srand(0413);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
              temp = rand() % 21;
              temp = temp / 10;
            num = temp * k;
            if (num < 1) element = 0;
            else element = 1;
            matrix[i][j] = element;
        }
    }
}

void BFS(HDC hdc, int xPos[n], int yPos[n], char* nn[n], int A[n][n], int start) {  //в ширину
    struct queue* q = init();
    int visited[n] = { 0,0,0,0,0,0,0,0,0,0,0 };
    int distance[n][n] = {
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0}
    };
    int treeMatrix[n][n] = {
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0}
    };
    int k = 1, a = 0, dist = 0, curVertex, counter = 0;
    char text[4];
    pushQueue(q, start);
    visited[start] = 1;
    distance[dist][start] = 1;
    paintVertex(hdc, xPos, yPos, nn, start);
    sprintf_s(text, 2, "%d", a);
    TextOutA(hdc, xPos[start] - 20, yPos[start] + 15, text, 1);
    while (!isEmpty(q)) {
        curVertex = popQueue(q);
        for (int i = 0; i < n; i++) {
            if (A[curVertex][i] && visited[i] == 0) {
                k++;
                visited[i] = k;
                pushQueue(q, i);
                paintLines(hdc, A, xPos, yPos, curVertex, i);
                paintVertex(hdc, xPos, yPos, nn, i);
                dist = a + 1;
                distance[curVertex][i] = 1;
                treeMatrix[curVertex][i] = 1;
                sprintf_s(text, 2, "%d", dist);
                TextOutA(hdc, xPos[i] - 20, yPos[i] + 15, text, 1);
                Sleep(1500);
                // getch();
            }
        }
        a++;
    }


    for (int i = 0;i < n; i++) {
        paintVertex(hdc, xPos, yPos, nn, i);
        counter = 0;
        for (int j = 0;j < n; j++) {
            if (distance[i][j]) {
                //printf("[%d][%d] = %d\n",i,j,distance[i][j]);
                sprintf_s(text, 3, "L%d", i+1);
                TextOutA(hdc, 10, 550 + 25 * i, text, 2);
                sprintf_s(text, 3, "%d", j+1);
                TextOutA(hdc, 30 + 20 * counter, 550 + 25 * i, text, 2);
                counter++;
            }
            sprintf_s(text, 2, "%d", treeMatrix[i][j]);
            TextOutA(hdc, 500 + 10 * j, 500 + 20 * i, text, 1);
        }
    }
}

void DFS(HDC hdc, int xPos[n], int yPos[n], char* nn[n], int A[n][n], int start) {//углиб
    int distance[n][n] = {
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0}
    };
    int treeMatrix[n][n] = {
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0}
    };
    struct stack* s = initStack();
    int visited[n] = { 0,0,0,0,0,0,0,0,0,0,0 };
    int k = 1, dist = 0, curVertex, counter = 0, checker = 1;
    char text[4];
    pushStack(s, start);
    visited[start] = 1;
    distance[dist][start] = 1;
    paintVertex(hdc, xPos, yPos, nn, start);
    sprintf_s(text, 2, "%d", dist);
    TextOutA(hdc, xPos[start] - 20, yPos[start] + 15, text, 1);
    while (!isEmptyStack(s)) {
        curVertex = top(s);
        for (int i = 0; i < n; i++) {
            if (A[curVertex][i]) {
                if (visited[i] == 0) {
                    k++;
                    dist++;
                    visited[i] = k;
                    distance[dist][i] = 1;
                    treeMatrix[curVertex][i] = 1;
                    pushStack(s, i);
                    paintLines(hdc, A, xPos, yPos, curVertex, i);
                    paintVertex(hdc, xPos, yPos, nn, i);
                    sprintf_s(text, 3, "%d", dist);
                    TextOutA(hdc, xPos[i] - 20, yPos[i] + 15, text, 2);
                    Sleep(1500);
                  // getch();
                    break;
                }
            }
            if (i == n - 1) {
                flush(s);
                dist--;
            }
        }
    }
    for (int i = 0;i < n; i++) {
        paintVertex(hdc, xPos, yPos, nn, i);
        counter = 0;
        for (int j = 0;j < n; j++) {
            if (distance[i][j]) {
                sprintf_s(text, 3, "%d", i);
                TextOutA(hdc, 10, 450 + 25 * i, text, 2);
                sprintf_s(text, 3, "%d", j+1);
               // printf("%d\n",j+1);
                TextOutA(hdc, 30 + 20 * counter, 450 + 25 * i, text, 2);
                counter++;
            }
            sprintf_s(text, 2, "%d", treeMatrix[i][j]);
            TextOutA(hdc, 500 + 10 * j, 500 + 20 * i, text, 1);
        }
    }

    for (int i = 0;i < n; i++) {
        paintVertex(hdc, xPos, yPos, nn, i);
    }
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (messg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        int A[n][n];
        double B[n][n] = {
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0}
        };
        char* nn[11] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" ,"10","11"};
        int nx[n + 1] = { 350 },
            ny[n + 1] = { 100 };

        HPEN BlackPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));
        HPEN RedPen = CreatePen(PS_SOLID, 2, RGB(250, 0, 0));
        HPEN GreenPen = CreatePen(PS_SOLID, 2, RGB(39, 222, 11));

        SelectObject(hdc, BlackPen);

        generateMatrix(A, (1.0 - 1 * 0.01 - 3 * 0.005 - 0.15));
        simMatrix(A, B);
        printMatrix(hdc, B);

        //задаємо координати вершин
        int num = 110;
        for(int i = 0; i < n; i++)
        {
            if(i == 0)
            {
                nx[i] = num;
                ny[i] = num;
            } else if(i < 4)
            {
                nx[i] = nx[i - 1] + num;
                ny[i] = ny[i - 1];
            } else if(i < 7)
            {
                nx[i] = nx[i - 1];
                ny[i] = ny[i - 1] + num;
            } else if(i < 10)
            {
                nx[i] = nx[i - 1] - num;
                ny[i] = ny[i - 1];
            } else
            {
            nx[i] = nx[i - 1];
            ny[i] = ny[i - 1] - num*1.5;
            }
        }

        for (int start = 0; start < n;start++) {
            for (int end = start; end < n;end++) {
                paintLines(hdc, B, nx, ny, start, end);
            }
        }

        SelectObject(hdc, RedPen);
        for (int i = 0;i < n;i++) {
            paintVertex(hdc, nx, ny, nn, i);
        }

        SelectObject(hdc, GreenPen);

       // BFS(hdc, nx, ny, nn, B, 0); // пошук в ширину

        DFS(hdc, nx, ny, nn, B, 0); // пошук в глибину

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
