#include "../include/ccgit.h"

int main(int argc, char *argv[]){

    if (argc < 2){
        printf("Usage: ccgit <command>\n");
        return 1;
    }

    if (strcmp(argv[1], "init") == 0) 
        init_repo();
    else if (strcmp(argv[1], "add") == 0 && argc == 3) 
        add_file(argv[2]);
    else if (strcmp(argv[1], "commit") == 0 && argc == 3) 
        commit_changes(argv[2]);
    else if (strcmp(argv[1], "status") == 0) 
        status();
    else if (strcmp(argv[1], "revert") == 0) 
        revert();
    else 
        printf("Unknown command\n");
    
    return 0;
}
