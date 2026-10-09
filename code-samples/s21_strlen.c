typedef long unsigned s21_size;

s21_size s21_strlen(const char *str)
{
    s21_size len = 0;
    for(; str[len]; len++);
    return len + 1;
} 