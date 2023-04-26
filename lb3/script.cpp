#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    srand(time(0));
    long long n = rand() % 5 + 3;
    long long array[n][n];
    
    cout << "\tИсходная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            array[i][j] = rand() % 9 + 1;
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    long long *ptr_array = &array[0][0];
    long long *end_array = &array[n-1][n-1];

    if (n <= 1) {
        cout << "Bad array size!" << endl;
        return -1;
    }

    asm(
            "mov $8, %%rax\n\t"
            "mulq %[n]\n\t" // cдвиг для перехода по строкам
            "mov %[ptr_array], %%rbx\n\t"// Поместили указатель на начало матрицы в rbx
            "mov %%rbx, %%rcx\n\t" // Поместили указатель на начало матрицы в rcx
            "add %%rax, %%rcx\n\t" // сдвинули указатель вниз на одну строку
            "add $8, %%rcx\n\t" // сдвинули указатель вправо на один столбец
            "push %%rcx\n\t" // Поместили в стек адрес следующего элемента главной диагонали
            "push %%rax\n\t" // Поместили в стек сдвиг для перехода по строкам
            "mov %[n], %%rcx\n\t"
            "dec %%rcx\n\t" // Уменьшили на 1 значение rcx (n-1)
            "mulq %%rcx\n\t" // Умножили rax (сдвиг для перехода по строкам) на rcx (n-1)
            "add %%rax, %[ptr_array]\n\t"// получили указатель на первый элемент последней строки матрицы
            "mov %%rbx, %%rcx\n\t" // Вернули в rcx указатель на начало матрицы
 
        "loop_start:\n\t"
            "add $8, %%rbx\n\t" // переместились на один элемент вправо
            "pop %%rax\n\t" // Взяли в rax из стека смещение на следующую строку
            "add %%rax, %%rcx\n\t" // переместились вниз на один элемент
            "push %%rax\n\t" // Вернули в стек смещение на следующую строку
            "push (%%rbx)\n\t" // Обмен значений элементов матрицы через стек
            "push (%%rcx)\n\t" //помещаем в стек значение элемента матрицы
            "pop (%%rbx)\n\t" //извлекаем из стека значение элемента
            "pop (%%rcx)\n\t"
            "cmp %%rcx, %[ptr_array]\n\t"// Проверили что не достугнута последняя строка матрицы
            "je next_iteration\n\t" // Если достигнута - переход на next_iteration
            "jmp loop_start\n\t" // Если НЕ достигнута - переход на start_loop
            
        "next_iteration:\n\t"
            "add $8, %[ptr_array]\n\t" // Сдвинули указатель на один элемент последней строки матрицы вправо
            "mov %[ptr_array], %%rax\n\t"// Переместили указатель в rax
            "cmp %%rax, %[end_array]\n\t" // Проверили что достигнут конец матрицы
            "je end_asm\n\t" // Если достигнут - завершение, иначе продолжение
            "pop %%rax\n\t" // Взяли в rax из стека смещение на следующую строку
            "pop %%rbx\n\t" // Взяли в rbx из стека указатель на следующий элемент главной диагонали, он станет началом новой "усеченной" матрицы
            "mov %%rbx, %%rcx\n\t" // Поместили в rcx указатель на следующий элемент главной диагонали
            "add %%rax, %%rcx\n\t" // Сдвинули указатель в rcx на одну строку вниз
            "add $8, %%rcx\n\t" // Сдвинули указатель в rcx на один элемент вправо
            "push %%rcx\n\t" // Вернули rcx в стек
            "mov %%rbx, %%rcx\n\t" // Поместили в rcx значение из rbx
            "push %%rax\n\t" // Вернули rax в стек
            "jmp loop_start\n\t" // Переход на loop_start
        "end_asm:\n\t"
            :
            :[ptr_array]"m"(ptr_array), [end_array]"m"(end_array), [n]"m"(n) //список операндов входа и выхода
            :"%rax", "%rbx", "%rcx"
    );

cout<<endl<<"--------------------------------"<<endl;
cout<<"\tИзмененная матрица:"<<endl;
for (int i = 0; i < n; i++)
{
      for (int j = 0; j < n; j++)
      {
      cout<<array[i][j]<<" ";
      }
      cout<<endl;
}
return 0;
}

