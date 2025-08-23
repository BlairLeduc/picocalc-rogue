extern int rogue_main(int argc, char **argv, char **envp);

int main(int argc, char **argv, char **envp)
{
    while (1)
    {
        rogue_main(argc, argv, envp);
    }
}