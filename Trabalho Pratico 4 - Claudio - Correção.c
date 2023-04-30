#include <stdio.h>
#include <stdlib.h>

void quicksort(int nums[], int left, int right){
    int i, j, pivot, biggestNums;
    i = left;
    j = right;
    pivot = nums[(left + right) / 2];
    do{
        while(nums[i] < pivot){
            i++;
        }
        while(nums[j] > pivot){
            j--;
        }
        if(i <= j){
            biggestNums = nums[i];
            nums[i] = nums[j];
            nums[j] = biggestNums;
            i++;
            j--;
        }
    } while(i <= j);

    if (left < j){
        quicksort(nums, left, j);
    }

    if(right > i){
        quicksort(nums, i, right);
    }
}

int *maxSubsequence(int *nums, int numsSize, int k, int *returnSize){
    int i, j, c = 0, compJ = k + 1, *biggestNums = malloc(sizeof(int) *k), *result = malloc(sizeof(int) *k);
    (*returnSize) = k;

    int *sortedNums = malloc(sizeof(int) *numsSize);

    for(i = 0; i < numsSize; i++){
        sortedNums[i] = nums[i];
    }

    quicksort(sortedNums, 0, numsSize);

    for(i = 0; i < k; i++){
        biggestNums[i] = sortedNums[numsSize-1-i];
    }

    for(i = 0; i < numsSize; i++){
        for(j = 0; j < k; j++){
            if(nums[i] == biggestNums[j] && j != compJ){
                result[c++] = nums[i];
                compJ = j;
                break;
            }
        }
    }

    free(biggestNums);
    free(sortedNums);
    return result;
}

int main(){
    int *nums, numsSize = 0, k = 0, *returnSize, *result, i;

    printf("Size of vector: \n"); scanf("%d",&numsSize);
    if (numsSize < 1 || numsSize > 1000){
        do{
            printf("\nSize of array out of bounds (less than 1 or greater than 1000), choose another value: ");
            scanf("%d", &numsSize);
        } while(numsSize < 1 || numsSize > 1000);
    }

    printf("Choose a number for k: "); scanf("%d", &k);
    if (k < 1 || k > numsSize){
        do{
            printf("\nUnacceptable k value, choose another value: ");
            scanf("%d", &k);
        } while (k < 1 || k > numsSize);
    }

    nums = malloc(sizeof(int) *numsSize);
    returnSize = malloc(sizeof(int));
    
    for(int i = 0; i < numsSize; i++){
        do{
            printf("Value in nums[%d]: \n", i); scanf("%d", &nums[i]);
    } while(nums[i] < -105 || nums[i] > 105);
    }

    printf("\nUnordered array: \n");
    for(i = 0; i < numsSize; i++){
        printf("%d\n", nums[i]);
    }

    result = maxSubsequence(nums, numsSize, k, returnSize);

    printf("\nResult:\n");
    for(i = 0; i < k; i++){
        printf("%d\n", result[i]);
    }

    free(nums);
    free(returnSize);
    free(result);

    return 0;
}