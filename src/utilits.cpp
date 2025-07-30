#include <stdio.h>
#include <assert.h>

#include "../include/global.h"
#include "../include/utilits.h"

int CheckFile(FILE* file)
{
    if (file == NULL)
    {
        printf("file not opened\n");
        return CHECK_FILE_ERROR;
    }

    return CHECK_FILE_OK;
}

void CheckFclose(FILE* file_ptr)
{
    assert(file_ptr);

    int fclose_return = fclose(file_ptr);

    if (fclose_return != 0)
    {
        printf("file closed wrong, fclose_return = %d\n", fclose_return);
    }
}

void FillingDataPoison(stackelem_t *data, int num_el_poison)
{
    for (int i = 0; i <= num_el_poison; i++)
    {
        data[i] = POISON;
    }
}
