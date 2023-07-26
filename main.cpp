#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


struct Person{
    string name, surname;
    long int id;
};



bool comparePersons(Person a, Person b) {
    if (a.id != b.id) {
        return a.id < b.id;
    } else if (a.surname != b.surname) {
        return a.surname < b.surname;
    } else {
        return a.name < b.name;
    }
}

Person* findMedian(Person* arr, int n) // wyznaczenie mediany median
{

    if (n <= 10) //magiczna linijka która naprawiła wszystko
    {
        sort(arr, arr + n, comparePersons);
        return &arr[n / 2]; // zwraca medianę
    }

    // divide the array into groups of 5
    int i;
    for (i = 0; i < n / 5; i++) //
    {
        sort(arr + i * 5, arr + i * 5 + 5, comparePersons); // sortujemy tablice po 5 elementów
        swap(arr[i], arr[i * 5 + 2]); // wstawiamy medianę w miejsce arr[i]
    }

    // if n is not divisible by 5, handle the remaining elements
    if (i * 5 < n)
    {
        sort(arr + i * 5, arr + n, comparePersons);
        swap(arr[i], arr[i * 5 + (n - i * 5) / 2]);
        i++;
    }


    Person *medianOfMedians = findMedian(arr, i);

    return medianOfMedians;
}



int partition(Person *arr, int low, int high, Person pivot)
{

    int i = low - 1, j = high + 1;
    for (int k = 0; k < high; ++k) {
        do { // w gore
            i++;
        } while (comparePersons(arr[i] , pivot) == true);

        //w dol
        do {
            j--;
        } while (comparePersons (arr[j] , pivot) == false);

        // If two pointers met.
        if (i >= j){
            return j;
        }

        swap(arr[i], arr[j]); // zamiana wi+
    }

}

void medianOfMediansSort(Person *arr, int low, int high, int k)
{

    if (low < high)
    {

        Person *pivot = findMedian(arr + low, high - low + 1);
        int partitionIndex = partition(arr, low, high, *pivot); //index of last elemeny on smaller side
        if ( high - low + 1 <= 10) // To trzeba koniecznie robić po medianie median
        {
            sort(arr+low, arr+high, comparePersons);
            return;
        }
        if (k == partitionIndex){
            return;
        }
        if( k < partitionIndex){ // jeśli k jest mniejszy niż ostatni otsortowany element idź w prawo
            medianOfMediansSort(arr, low, partitionIndex, k); // ograniczamy z góry
        }
        else{  // jeśli w lewo
            medianOfMediansSort(arr, partitionIndex + 1, high, k);  // ograniczamy z dołu
        }
    }

}



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n,k;
    cin >> n >> k;
    // vector<Person> people;
    Person *people = new Person[n];
    for (int i = 0; i < n; ++i) {
        Person person;
        cin >> person.name >> person.surname >> person.id;
        // people.push_back(person);
        people[i] = person;
    }

    if (n <= 10)
    {
        sort(people, people + n, comparePersons);
        cout << people[k].name << '\n' << people[k].surname << '\n' << people[k].id;
        return 0;
    }
    medianOfMediansSort(people, 0, n - 1, k);
    cout << people[k].name << '\n' << people[k].surname << '\n' << people[k].id;

    //   Person kthPerson = medianOfMediansSort(people, 0, n-1, k);
    //   cout << kthPerson.name << " " << kthPerson.surname << " " << kthPerson.id;


    delete[] people;
    return 0;
}