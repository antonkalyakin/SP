#include <iostream>
using namespace std;

const int M = 5; // величина М
int arr[10] = {3, 7, 1, 8, 4, 9, 2, 6, 5, 1}; // элементы массива

int main() {
int sum = 0, count = 0;

// Вычисление суммы элементов массива, превышающих величину М,
// и количества элементов, меньших М
for (int i = 0; i < 10; i++) {
if (arr[i] > M) {
sum += arr[i];
} else if (arr[i] < M) {
count++;
}
}
// Вывод результатов
std::cout << "Сумма больших: " << sum << std::endl;
std::cout << "Количество меньших: " << count << std::endl;

return 0;
}
