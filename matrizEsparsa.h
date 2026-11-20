#ifndef MATRIZESPARSA_H
#define MATRIZESPARSA_H

#include <vector>
#include <list>

typedef struct{
    vector<double> values;
    vector<int> col_index;
    vector<int> row_ptr;
} CSR;

#endif