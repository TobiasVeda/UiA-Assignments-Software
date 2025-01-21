#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void calc_average(vector<int> *array, float *average){
    for (int i = 0; i < array->size(); ++i) {
    *average += (*array)[i];
    }
    *average = *average/(array->size());
};

void calc_median(vector<int> *array, float *median){
    float midpoint = 0;
    if((array->size()) % 2 == 0){ //% gir rest av kvotient. partall hvis rest er 0
        midpoint = (array->size()) / 2;
        *median = ((*array)[midpoint-1] + (*array)[midpoint]);
        *median = *median / 2;
    } else{
        midpoint = (array->size());
        midpoint = midpoint/2;
        midpoint = midpoint + 0.5; // ville brukt cmath round, men kan ikke bruke c library
//        midpoint = ((array->size()) / 2) +0.5; // resulterer i feil. ¯\_(ツ)_/¯
        *median = (*array)[midpoint-1];
    }
};



int main() {
   vector<int> array;
   int buffer;
   float average = 0;
   float median = 0;

    for (int i = 0; true; ++i) {
        buffer = 0;
        cin>> buffer;
        if (buffer == 0){
            break;
        }
        array.push_back(buffer);
    }

    calc_average(&array, &average);

    sort(array.begin(), array.end()); // -> gjør array til pointer?
    calc_median(&array, &median);

    cout <<"Average : " <<average <<endl;
    cout <<"Median : " <<median <<endl;

    sort(array.begin(), array.end(), greater<int>()); // -> gjør array til pointer?
    cout <<"Descending : ";
    for (int i = 0; i < array.size(); ++i) {
        cout <<array[i] <<" ";
    }
}
