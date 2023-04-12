#include <stdio.h>
#include <string.h>

char currentState[] = "idle";

char *events[] = {"idle", "Reading Temp", "Display Temp"};

char *transitions[] = {"Solicitar Temp","Temp Update", "Data Transfer", "Stop Reading" };

void Temp_Machine_State(char *ev, char *tr){
    if(strcmp(ev, "idle") == 0){
        if(strcmp(tr, "Solicitar Temp") == 0){
            strcpy(currentState, "Reading Temp");
            printf("%s\n", currentState);
        }
    }else if(strcmp(ev, "Reading Temp") == 0){
        if(strcmp(tr, "Data Transfer") == 0){
            strcpy(currentState, "Display Temp");
            printf("%s\n", currentState);
        }else if(strcmp(tr , "Solicitar Temp") == 0){
            strcpy(currentState, "Reading Temp");
            printf("%s\n", currentState);
        }
    }else if(strcmp(ev , "Display Temp")== 0){
        if(strcmp(tr, "Stop Reading") == 0){
            strcpy(currentState, "idle");
            printf("%s\n", currentState);
        }else if(strcmp(tr , "Solicitar Temp") == 0){
            strcpy(currentState, "Reading Temp");
            printf("%s\n", currentState);
        }
    }
}

int main() {
    Temp_Machine_State("idle", "Solicitar Temp");
    printf("current state is %s\n", currentState);
   

    return 0;
}
