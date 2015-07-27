/* tables.h */
#ifndef _TABLE_UTIL_H
#define _TABLE_UTIL_H

#include "lr_parser.h"

void DecompressAndPatchParseTable(LR_TABLE* parser, int gotoTable[], int gotoSz, int actionTable[], int actionSz);
void DecompressGotoTable(int* source_data, int* dest_data, unsigned int compressed_size, unsigned int total_size);
void DecompressActionTable(int* source_data, ACTION* dest_data, unsigned int compressed_size, unsigned int total_size);

#endif // _TABLE_UTIL_H
