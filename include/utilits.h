#ifndef UTILITS
#define UTILITS

enum check_file_consts
{
    CHECK_FILE_OK    = 0,
    CHECK_FILE_ERROR = 1,
};

int  CheckFile         (FILE* file);
void CheckFclose       (FILE* file_ptr);
void FillingDataPoison (stackelem_t *data, int num_el_poison);

#endif
