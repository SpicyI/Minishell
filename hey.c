int main()
{
    char **str;
    int i = 0;

    str = ft_split("heola  kol me", ' ');
    while(i < 4)
    {
        free(str[i]);
        i++;
    }
}