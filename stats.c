#include <ctype.h>

void usage();
int is_valid_int(char *s);
int *generate_population(int size, int lower, int upper);
void get_stats(int *a, int size, int *min, int *max, double *mean, double *stddev);

int main(int argc, char *argv[])
{
    return 0;
}

int is_valid_int(char *s)
{
    if (s == NULL)
    {
        return -1;    
    }

    if (*s == '-')
    {
        ++s;
    }
    while (*s != '\0')
    {
        if (!isdigit(*s))
        {
            return 0;
        }
        ++s;
    }
    return 1;
}
