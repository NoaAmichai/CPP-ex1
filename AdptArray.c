#include <string.h>
#include <stdlib.h>
#include "AdptArray.h"
/***
 * For solving the assignment, I got inspiration from the solution to Question 4 (Moed-A) in Systems Programming 1, as presented in the model.
 */

typedef struct AdptArray_ {
    int size;
    PElement *pElemArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
} AdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc_) {
    PAdptArray pArr = (PAdptArray) malloc(sizeof(AdptArray));
    if (pArr == NULL) {
        free(pArr);
        return NULL;
    }
    // initialize fields
    pArr->size = 0;
    pArr->pElemArr = NULL;
    pArr->delFunc = delFunc_;
    pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc_;
    return pArr;
}

Result SetAdptArrayAt(PAdptArray pArray, int index, PElement pNewElem) {
    PElement *newpElemArr;
    if (pArray == NULL)
        return FAIL;
    // expand the array if necessary
    if (index >= pArray->size) {
        if ((newpElemArr = (PElement *) calloc((index + 1), sizeof(PElement))) == NULL)
            return FAIL;
        memcpy(newpElemArr, pArray->pElemArr, (pArray->size) * sizeof(PElement));
        free(pArray->pElemArr);
        pArray->pElemArr = newpElemArr;
    }
    // delete previous element and insert new element
    if (((pArray->pElemArr)[index]) != NULL) {
        pArray->delFunc((pArray->pElemArr)[index]);
    }
    (pArray->pElemArr)[index] = pArray->copyFunc(pNewElem);
    // update array size
    pArray->size = (index >= pArray->size) ? (index + 1) : pArray->size;
    return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArray) {
    if (pArray == NULL)
        return;
    // delete all elements and free the array
    for (int i = 0; i < pArray->size; ++i) {
        if ((pArray->pElemArr)[i] != NULL) {
            pArray->delFunc((pArray->pElemArr)[i]);
        }
    }
    free(pArray->pElemArr);
    free(pArray);
}

PElement GetAdptArrayAt(PAdptArray pArr, int index) {
    if (pArr == NULL || index < 0 || index >= pArr->size || pArr->pElemArr[index] == NULL)
        return NULL;
    // return a copy of the element
    return pArr->copyFunc(pArr->pElemArr[index]);
}

int GetAdptArraySize(PAdptArray pArr) {
    if (pArr == NULL)
        return -1;
    // return the size of the array
    return pArr->size;
}

void PrintDB(PAdptArray pArr) {
    if (pArr == NULL || pArr->pElemArr == NULL)
        return;
    // print all non-null elements in the array
    for (int i = 0; i < pArr->size; ++i) {
        PElement elem = pArr->pElemArr[i];
        if (elem != NULL) {
            pArr->printFunc(elem);
        }
    }
}
