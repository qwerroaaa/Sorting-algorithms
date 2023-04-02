#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdio>
using namespace std;
template <typename T>
class Sort {
public: 
    static unsigned long swapcounter;

    static bool check_sort(T** array, int length) 
    {
        for (int i = 1; i < length; i++)
            if (*array[i - 1] > *array[i])
                return false;
        return true;
    }

    static void Swap(T **a, T **b) 
    {
        T *temp = *a;
        *a = *b;
        *b = temp;
        swapcounter++;
    }

    static void sift(T** A, int i, int m)
    {
        int j = i, k = i * 2 + 1; //текущий и левый сын
        while (k <= m)
        {
            if (k < m && *A[k] < *A[k + 1]) k++; //большой сын
            if (*A[j] < *A[k])
            {
                Swap(&A[j], &A[k]);
                j = k;
                k = k * 2 + 1;
            } else {
                break;
            }
        }
    }

    static void heap_sort(T** A, int n)
    {
        //построение пирамиды
        for (int i = n / 2; i >= 0; i--)
            sift(A, i, n - 1);
        //сортировка массива
        for (int m = n - 1; m >= 1; m--)
        {
            // Перемещаем текущий корень в конец
            Swap(&A[0], &A[m]);
            //вызываем процедуру heapify на уменьшенной куче
            sift(A, 0, m - 1);
        }
    }

    static void shell_sort(T** A, int n)
    {
        int i, j, h;
        for (h = 1; h <= n / 9; h = h * 3 + 1);
        while (h >= 1)
        {
            for (i = h; i < n; i++)
            {
                for (j = i - h; j >= 0 && *A[j] > *A[j + h]; j -= h)
                    Swap(&A[j], &A[j + h]);
            }
            h = (h - 1) / 3;
        }
    }
};

class Olimp {
public:
    int id, NumberOfTasks, NumberOfPoints, usedTime;
    //конструктор
    Olimp(int newid = 0, int newNumberOfTasks = 0, int newNumberOfPoints = 0, int newusedTime = 0)
    {
        id = newid;
        NumberOfTasks = newNumberOfTasks;
        NumberOfPoints = newNumberOfPoints;
        usedTime = newusedTime;
    }

    bool operator<(const Olimp& obj) const {
        if (NumberOfPoints != obj.NumberOfPoints)
            return NumberOfPoints < obj.NumberOfPoints;

        if (usedTime != obj.usedTime)
            return usedTime < obj.usedTime;

        if (NumberOfTasks != obj.NumberOfTasks)
            return NumberOfTasks < obj.NumberOfTasks;

        return id < obj.id;
    }

    bool operator>(const Olimp& obj) const {
        if (NumberOfPoints != obj.NumberOfPoints)
            return NumberOfPoints > obj.NumberOfPoints;

        if (usedTime != obj.usedTime)
            return usedTime > obj.usedTime;

        if (NumberOfTasks != obj.NumberOfTasks)
            return NumberOfTasks > obj.NumberOfTasks;

        return id > obj.id;
    }
};

unsigned long Sort<int>::swapcounter = 0;
unsigned long Sort<Olimp>::swapcounter = 0;
template <typename T>
void FillArray(T *A, T **ArrPtr, int size, int type)
{
    if (type == 0) {
        for (int i = 0; i < size; i++)
            A[i] = i;
    }

    if (type == 1) {
        for (int i = 0; i < size; i++)
            A[i] = size - i - 1;
    }

    if (type == 2) {
        for (int i = 0; i < size; i++)
            A[i] = rand();
    }

    for (int i = 0; i < size; i++)
        ArrPtr[i] = &A[i];
}


int main()
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    int size;
    for (int type = 0; type < 3; type++)
    {
        //cout << "Number of type = " << type << "\n";
        for (int size = 1; size <= 2 * pow(10, 1); size *= 2)
        {
            int* Arr = new int[size];
            int** ArrPtr = new int* [size];

            Sort<int>::swapcounter = 0;
            //Shell sort
            FillArray(Arr, ArrPtr, size, type);
            Sort<int>::shell_sort(ArrPtr, size);
            if (Sort<int>::check_sort(ArrPtr, size)) {
                //cout << "Shell: " << " swapcounter = " << Sort<int>::swapcounter;
            }
            else {
                cout << "No! " << "\n";
            }


            Sort<int>::swapcounter = 0;
            //heap sort
            FillArray(Arr, ArrPtr, size, type);
            Sort<int>::heap_sort(ArrPtr, size);
            if (Sort<int>::check_sort(ArrPtr, size)) {
                //cout << " || Heap Sort: " << " swapcounter = " << Sort<int>::swapcounter << "\n";
            }
            else {
                cout << "No! " << "\n";
            }
        }
        //cout << "----------------------------------------------------------------------------" << "\n";
    }
    cout << "Olymp" << "\n";
    int length = 10, tasks, points, time;
    Olimp* OlimpArray = new Olimp[length];
    Olimp** OlimpIndexArray = new Olimp * [length];

    for (int i = 0; i < length; i++)
    {
        tasks = rand() % 11;
        points = rand() % 101;
        time = rand() % 301;

        OlimpArray[i] = Olimp(i, tasks, points, time);
    }

    for (int i = 0; i < length; i++)
    {
        OlimpIndexArray[i] = &OlimpArray[i];
    }

    for (int i = 0; i < length; i++)
        cout << i << " Кол-во баллов: " << OlimpIndexArray[i]->NumberOfPoints << " || Число решенных задач: " << OlimpIndexArray[i]->NumberOfTasks << " || Время: " << OlimpIndexArray[i]->usedTime << " || Номер заявки: " << OlimpIndexArray[i]->id << "\n";

    cout << "\n";

    Sort<Olimp>::heap_sort(OlimpIndexArray, length);
    for (int i = length - 1; i >= 0; i--)
        cout << length-i-1 << " Кол-во баллов: " << OlimpIndexArray[i]->NumberOfPoints << " || Число решенных задач: " << OlimpIndexArray[i]->NumberOfTasks << " || Время: " << OlimpIndexArray[i]->usedTime << " || Номер заявки: " << OlimpIndexArray[i]->id << "\n";
}