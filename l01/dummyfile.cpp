void main() {
    int size = 10;
	int** array;
	array = new int* [size];

    for (int i = 0; i < size; ++i) { // my_array[0].size(); /* size of x */
        for (int j = 0; j < size; ++j) {
            array[i][j] = 1;
        }
        //std::cout << std::endl;
    }

    // print array
    for (int i = 0; i < size; ++i) { // my_array[0].size();
        for (int j = 0; j < size; ++j) {
            std::cout << array[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}