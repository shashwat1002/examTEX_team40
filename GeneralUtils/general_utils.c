#include "general_utils.h"

void merge( McqQuestion** arr, int low, int mid, int high){
    int size = high - low + 1;

    // [low, mid) will be considered one subset
    // [mid, high] will be the other subset

    int final_counter = 0;
    McqQuestion** replace_ar = ( McqQuestion** ) malloc( size * sizeof( McqQuestion* ) );
    int counter1 = low;
    int counter2 = mid + 1;
    for(int i = 0; i < size; i++){
        replace_arr[i] = 0;
    }
    while(1){

        if(arr[counter1]->difficulty <= arr[counter2]->difficulty){
            replace_arr[final_counter] = arr[counter1];
            counter1++;
            //final_counter++;
        }
        else{
            replace_arr[final_counter] = arr[counter2];
            counter2++;
        }
        final_counter++;
        if(final_counter >= size){
            break;
        }
        if (counter1 >= mid+1) break;
        if (counter2 >= high+1) break;
        //assert(final_counter < size);
    }

    //one of the lists has been exhausted or we're done

    while(final_counter < size){
        if(counter1 <= mid){
            replace_arr[final_counter] = arr[counter1];
            counter1++;
        }

        if(counter2 <= high){
            replace_arr[final_counter] = arr[counter2];
            counter2++;
        }
        final_counter++;
    }

    final_counter = 0;
    for(int i = low; i <= high; i++){
        arr[i] = replace_arr[final_counter];
        final_counter++;
    }
}

void merge_sort(McqQuestion** arr, int low, int high){

    if(low >= high) return;
    int mid = (low + high-1) / 2;
    merge_sort(arr, low, mid);
    merge_sort(arr, mid+1, high);
    merge(arr, low, mid, high);
}
