/* tables.c */
#include "lr_parser.h"
#include "tables.h"

void DecompressAndPatchParseTable(LR_TABLE* parser, int gotoTable[], int gotoSz, int actionTable[], int actionSz)
{
     parser->gotoTable = (int*)malloc(parser->numStates * parser->numSymbols * sizeof(int));
     parser->actionTable = (ACTION*)malloc(parser->numStates * parser->numTokens * sizeof(ACTION));

     DecompressGotoTable(gotoTable, parser->gotoTable, gotoSz, parser->numStates * parser->numSymbols);
     DecompressActionTable(actionTable, parser->actionTable, actionSz, parser->numStates * parser->numTokens);
}

void DecompressGotoTable(int* source_data, int* dest_data, unsigned int compressed_size, unsigned int total_size)
{
    unsigned int mode = 0;
    unsigned int index = 0;
    unsigned int read_index = 0;
    int lengthRep = 0;
    int copy_value = 0;

    while (/*read_index < compressed_size && */index < total_size)
    {
        if (mode == 0)
        {
            lengthRep = source_data[read_index];
            read_index++;
            while (lengthRep && /*read_index < compressed_size &&*/
                    index < total_size)
            {
                dest_data[index] = source_data[read_index];
                index++; read_index++;
                lengthRep--;
            }
            lengthRep = 0;
            mode = 1;
        } 
        else if (mode == 1) 
        {
            lengthRep = source_data[read_index];
            read_index++;
            copy_value = source_data[read_index];
            read_index++;
            while (lengthRep && index < total_size)
            {
                dest_data[index] = copy_value;
                index++;
                lengthRep--;
            }
            lengthRep = 0;
            mode = 0;
        }
    }
}

void DecompressActionTable(int* source_data, ACTION* dest_data, unsigned int compressed_size, unsigned int total_size)
{
    unsigned int mode = 0;
    unsigned int index = 0;
    unsigned int read_index = 0;
    int lengthRep = 0;
    ACTION copy_value;
    copy_value.type = 0;
    copy_value.value = 0;

    while (/*read_index < compressed_size &&*/ index < total_size)
    {
        if (mode == 0)
        {
            lengthRep = source_data[read_index];
            read_index++;
            while (lengthRep && /*read_index < compressed_size &&*/
                    index < total_size)
            {
                dest_data[index].type = source_data[read_index];
                read_index++;
                dest_data[index].value = source_data[read_index];
                read_index++;
                index++;
                lengthRep--;
            }
            lengthRep = 0;
            mode = 1;
        } 
        else if (mode == 1) 
        {
            lengthRep = source_data[read_index];
            read_index++;
            copy_value.type = source_data[read_index];
            read_index++;
            copy_value.value = source_data[read_index];
            read_index++;
            while (lengthRep && index < total_size)
            {
                dest_data[index].type = copy_value.type;
                dest_data[index].value = copy_value.value;
                index++;
                lengthRep--;
            }
            lengthRep = 0;
            mode = 0;
        }
    }
}


