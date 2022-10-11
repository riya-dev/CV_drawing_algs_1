// Riya Dev
// Period 5
// // grid jumps down and across
// cd project1
// g++ -std=c++11 -o l01 -Wall l01.cpp
// ./l01>triangle.ppm

#include <iostream>
#include <fstream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* pow */

const int size = 800;


void illuminate(int y, int x, int** arr){
    arr[x][y] = 0;
}

void notoutofbounds(int** array, int x, int y) {
    if (x >= 0 && x < size && y >= 0 && y < size)
        //array[x][y] = 0;
        illuminate(x, y, array);
}

// driving force x -> dx < dy

int** linecase1(int x1, int x2, int y1, int y2, int** arr) { // x1 < x2, y1 < y2, dx < dy = default bresenham's
    //std::cout << x1 << y1 << x2 << y2 << "\n";

    int dx = x2 - x1; // |
    int dy = y2 - y1; // _
    int e = dx - dy;
    int i = x1;

    for (int j = y1; j <= y2; j++) {
        //arr[i][j] = 0; // illuminate
        notoutofbounds(arr, i, j);
        if (e >= 0) {
            i++;
            e -= dy;
        }
        e += dx;
    }
    return arr;
}

int** linecase2(int x1, int x2, int y1, int y2, int** arr) { // x1 < x2 && y1 > y2 && dx > dy
    //std::cout << x1 << y1 << x2 << y2 << "\n";

    int dx = x1 - x2; // |
    int dy = y2 - y1; // _
    int e = dx - dy;
    int i = x1;

    for (int j = y1; j <= y2; j++) {
        //arr[i][j] = 0; // illuminate
        notoutofbounds(arr, i, j);
        if (e >= 0) {
            i--;
            e -= dy;
        }
        e += dx;
    }
    return arr;
}

int** linecase3(int x1, int x2, int y1, int y2, int** arr) { // y1 = y2 && x1 < x2 && dx < dy
    for (int i = x1; i < x2; i++) {
        //arr[i][y1] = 0;
        notoutofbounds(arr, i, y1);
    }
    return arr;
}

// driving force y -> dx > dy

int** linecase4(int x1, int x2, int y1, int y2, int** arr) { //x1 < x2 && y1 < y2 && dx > dy
    //std::cout << "case 4 " << x1 << y1 << " " << x2 << y2 << "\n";

    int dx = x2 - x1; // |
    int dy = y2 - y1; // _
    int e = dy - dx;
    int j = y1;

    for (int i = x1; i <= x2; i++) {
        //arr[i][j] = 0; // illuminate
        notoutofbounds(arr, i, j);
        if (e >= 0) {
            j++;
            e -= dx;
        }
        e += dy;
    }
    return arr;
}

int** linecase5(int x1, int x2, int y1, int y2, int** arr) {
    //std::cout << "case 5 " << x1 << y1 << " " << x2 << y2 << "\n";

    int dx = x2 - x1; // |
    int dy = y1 - y2; // _
    int e = dy - dx;
    int j = y1;

    for (int i = x1; i <= x2; i++) {
        //arr[i][j] = 0; // illuminate
        notoutofbounds(arr, i, j);
        if (e >= 0) {
            j--;
            e -= dx;
        }
        e += dy;
    }
    return arr;
}

int** linecase6(int x1, int x2, int y1, int y2, int** arr) { //x1 == x2 && y1 < y2
    //std::cout << "case 6" << x1 << y1 << " " << x2 << y2 << "\n";

    for (int j = y1; j < y2; j++) {
        //arr[x1][j] = 0;
        notoutofbounds(arr, x2, j);
    }
    return arr;
}

void chooselinefunction(int x1, int x2, int y1, int y2, int** array) {
    // the 6 freaking cases

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // driving force x -> dx > dy

    // case 1
    if (x1 < x2 && y1 < y2 && dx <= dy) {
        //std::cout << "case 1a" << x1 << y1 << " " << x2 << y2 << "\n";
        array = linecase1(x1, x2, y1, y2, array);
    }
    else if (x2 < x1 && y2 < y1 && dx <= dy) {
        //std::cout << "case 1b" << x1 << y1 << " " << x2 << y2 << "\n";
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        array = linecase1(x1, x2, y1, y2, array);
    }

    // case 2
    else if (x1 > x2 && y1 < y2 && dx <= dy) {
        //std::cout << "case 2a" << x1 << y1 << " " << x2 << y2 << "\n";
        array = linecase2(x1, x2, y1, y2, array);
    }
    else if (x1 < x2 && y1 > y2 && dx <= dy) {
        //std::cout << "case 2b" << x1 << y1 << " " << x2 << y2 << "\n";
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        array = linecase2(x1, x2, y1, y2, array);
    }

    // case 3
    else if (y1 == y2 && x1 < x2) { // use higher precedence operator first
        //std::cout << "case 3a" << x1 << y1 << " " << x2 << y2 << "\n";
        array = linecase3(x1, x2, y1, y2, array);
    }
    else if (y1 == y2 && x1 > x2) {
        //std::cout << "case 3b" << x1 << y1 << " " << x2 << y2 << "\n";
        int temp = x1;
        x1 = x2;
        x2 = temp;
        array = linecase3(x1, x2, y1, y2, array);

    }

    // driving force y -> dy > dx

    // case 4
    else if (x1 < x2 && y1 < y2 && dx > dy) {
        //std::cout << "case 4a" << x1 << y1 << " " << x2 << y2 << "\n";
        array = linecase4(x1, x2, y1, y2, array);
    }
    else if (x2 < x1 && y2 < y1 && dx > dy) {
        //std::cout << "case 4b" << x1 << y1 << " " << x2 << y2 << "\n";
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        array = linecase4(x1, x2, y1, y2, array);
    }

    // case 5
    else if (x1 < x2 && y1 > y2 && dx > dy) {
        //std::cout << "case 5a" << x1 << y1 << " " << x2 << y2 << "\n";
        array = linecase5(x1, x2, y1, y2, array);
    }
    else if (x2 < x1 && y2 > y1 && dx > dy) {
        //std::cout << "case 5b" << x1 << y1 << " " << x2 << y2 << "\n";
        int temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
        array = linecase5(x1, x2, y1, y2, array);
    }

    // case 6
    else if (x1 == x2 && y1 < y2) { // use higher precedence operator first
        array = linecase6(x1, x2, y1, y2, array);
    }
    else if (x1 == x2 && y2 < y1) {
        int temp = y1;
        y1 = y2;
        y2 = temp;
        array = linecase6(x1, x2, y1, y2, array);
    }
}

void triangle(int** array, int x1, int y1, int x2, int y2, int x3, int y3) {
    // ppm -> P3 size size
    //std::cout << "(" << x1 << ", " << y1 << ")" << "(" << x2 << ", " << y2 << ")" << "(" << x3 << ", " << y3 << ")" << "\n";

    //line 1 - point 1 & point 2
    // (x1, y1) (x2, y2)
    chooselinefunction(x1, x2, y1, y2, array);

    //line 2 - point 1 & point 3
    //(x1, y1) (x3, y3)
    chooselinefunction(x1, x3, y1, y3, array);

    //line 3 - point 2 & point 3
    //(x2, y2) (x3, y3)
    chooselinefunction(x2, x3, y2, y3, array);
}

double distance(int x1, int y1, int x2, int y2) {
    return (sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

void eulerline(int** array, int x1, int y1, int x2, int y2) {
    //centroid and circumcenter coordiinates
    //x1, x2, y1, y2, array

    double m = (double)(y1 - y2) / (x1 - x2);
    int yi = m * -x1 + y1;
    int yf = m * (size - x1 - 1) + y1;
    std::cout << yi << " " << yf;
    // y - y1 = m (x - x1) -> y = mx - mx1 + y1
    // y - y2 = m(x - x2)  -> y = mx - mx2 + y2

    chooselinefunction(0, size - 1, yi, yf, array);
}

void circle(int** array, int xcenter, int ycenter, int R) {
    int y = R;
    int xmax = (int)(R * 0.70710678);
    int ysquare = y * y;
    int ty = (2 * y) - 1;
    int y2_new = ysquare;

    //std::cout << y << " " << xmax << " " << ysquare << " " << ty << " " << y2_new << "\n";

    for (int x = 0; x <= xmax + 1; x++) {
        if ((ysquare - y2_new) >= ty) {
            ysquare -= ty;
            y -= 1;
            ty -= 2;
        }
        notoutofbounds(array, y + xcenter, x + ycenter);
        notoutofbounds(array, -y + xcenter, x + ycenter);
        notoutofbounds(array, y + xcenter, -x + ycenter);
        notoutofbounds(array, -y + xcenter, -x + ycenter);

        notoutofbounds(array, x + xcenter, y + ycenter);
        notoutofbounds(array, -x + xcenter, y + ycenter);
        notoutofbounds(array, x + xcenter, -y + ycenter);
        notoutofbounds(array, -x + xcenter, -y + ycenter);

        y2_new -= (2 * x) - 3;
    }
}

void circles(int** array, int x1, int y1, int x2, int y2, int x3, int y3) {
    //line 1 - (x1, y1) (x2, y2)
    double a = distance(x1, y1, x2, y2);

    //line 2 - (x1, y1) (x3, y3)
    double b = distance(x1, y1, x3, y3);

    //line 3 - (x2, y2) (x3, y3)
    double c = distance(x2, y2, x3, y3);

    //semiperimeter
    double s = ((a + b + c) / 2);

    //radius of incircle
    double r = sqrt(((s - a) * (s - b) * (s - c)) / s);

    // radius of circumcircle
    int R = (int)((a * b * c) / (4 * r * s));

    r = (int)r;

    // circumcenter - center of circumcircle

    //undefined slope case

    //std::cout << "(" << x1 << ", " << y1 << ")" << "(" << x2 << ", " << y2 << ")" << "(" << x3 << ", " << y3 << ")" << "\n";

    int x12 = abs(x2 + x1) / 2; //midpoint of AB
    int y12 = abs(y2 + y1) / 2;
    //circle(array, x12, y12, 10);

    int x23 = abs(x3 + x2) / 2;
    int y23 = abs(y3 + y2) / 2;
    //circle(array, x23, y23, 10);

    double m12 = (double)(y2 - y1) / (x2 - x1);
    m12 = -1 / m12;
    double m23 = (double)(y3 - y2) / (x3 - x2);
    m23 = -1 / m23;

    //chooselinefunction(x12, (y12-10)/m12 + x12, y12, m12*(x12-10)+y12, array);
    //chooselinefunction(x23, (y23 - 10) / m23 + x23, y23, m23 * (x23 - 10) + y23, array);

    //std::cout << "m12 " << m12 << " m23 " << m23 << "\n";
    //std::cout << "(" << y23 << "-" << y12 << "+ (" << m12 << "*" << x12 << ") - (" << m23 << "*" << x23 << ")) / (" << m12 << " -" << m23 << "))" << "\n";

    int xcircumcenter = ((double)y23 - (double)y12 + (m12 * x12) - (m23 * x23)) / (m12 - m23);
    int ycircumcenter = (m12 * (xcircumcenter - x12) + y12);

    //std::cout << xcircumcenter << " " << ycircumcenter << "\n";

    circle(array, xcircumcenter, ycircumcenter, R);

    //incenter - center of incircle
    int xincenter = (int)((c * x1 + b * x2 + a * x3) / (a + b + c));
    int yincenter = (int)((c * y1 + b * y2 + a * y3) / (a + b + c));

    circle(array, xincenter, yincenter, r);

    // euler line

    int xcentroid = (int)((x1 + x2 + x3) / 3);
    int ycentroid = (int)((y1 + y2 + y3) / 3);

    eulerline(array, xcentroid, ycentroid, xcircumcenter, ycircumcenter);

    //nine point circle
    /*One way to find the center of the nine point circle(O) is to find the midpoint f the segment that connects the
    orthocenter(H) and the circumcenter(N), which is the intersection point of the perpendicular bisectors of each
    side of the original triangle.
    */
    int xorthocenter = (m23 * x1 - y1 - m12 * x3 + y3) / (m23 - m12);
    int yorthocenter = m12 * (xorthocenter - x3) + y3;

    int xninepointcenter = abs(xcircumcenter + xorthocenter) / 2;
    int yninepointcenter = abs(ycircumcenter + yorthocenter) / 2;

    int rninepoint = distance(xninepointcenter, yninepointcenter, x12, y12);

    circle(array, xninepointcenter, yninepointcenter, rninepoint);
}

int main() {
    std::ofstream file;
    file.open("triangle.ppm");
    file << "P3" << " " << size << " " << size << " " << "1\n";

    int** array;
    array = new int* [size];

    // fill with 1s
    for (int row = 0; row < size; ++row)
        array[row] = new int[size];
    for (int row = 0; row < size; ++row)
        for (int col = 0; col < size; ++col)
            array[row][col] = 1;

    srand(time(NULL));
    double rx1 = rand() % size;
    double ry1 = rand() % size;

    double rx2 = rand() % size;
    double ry2 = rand() % size;

    double rx3 = rand() % size;
    double ry3 = rand() % size;

    triangle(array, rx1, ry1, rx2, ry2, rx3, ry3);
    circles(array, rx1, ry1, rx2, ry2, rx3, ry3);

    // print array in console
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            file << array[i][j] << " " << array[i][j] << " " << array[i][j] << ' ';
        file << std::endl;
    }
    file << "\n";

    file.close();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file