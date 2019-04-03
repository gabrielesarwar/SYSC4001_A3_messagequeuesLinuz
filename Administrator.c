//
//  Administrator.c
//  
//
//  Created by Abhiram Santhosh on 3/30/19.
//

#include "Administrator.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 12

struct message_st {
    
    long int message_type;
    char name[MAX_TEXT];
    char departmentName[MAX_TEXT];
    int employeeNum;
    int salary;
    int type; //type of message sent
    //0 for input
    //1 for check name
    //2 for check dept
    //3 for check salary
    //4 for check employee number
    //5 for check (dept name)
    //6 for delete
    //7 for end
};


int main () {
    
    int running = 1;
    int msgidAdminRecord;
    int msgidRecordAdmin;
    struct message_st myMessage;
    char userinputString[MAX_TEXT];
    int userinputNumber;
    
    msgidAdminRecord = msgget((key_t)1235, 0666 | IPC_CREAT);
    msgidAdminRecord = msgget((key_t)1234, 0555 | IPC_CREAT);// one to recieve back from record
    
    
    printf("here");
    
    
    
    if (msgidAdminRecord == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    
    
    while (running){
        
        
        //ask for what command the user wants
        printf("Enter a command: ");
        scanf("%s", &userinputString);
        printf("\n");
        myMessage.message_type = 1;
        //printf("%s", userinput);
        
        if(strcmp(userinputString,"input") == 0){
            
            printf("Enter a name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.name, userinputString);
            printf("\n");
            //printf("\n");
            
            printf("Enter a department name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.departmentName, userinputString);
            printf("\n");
            //printf("\n");
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            //printf("\n");
            
            printf("Enter a salary:");
            scanf("%i", &userinputNumber);
            myMessage.salary = userinputNumber;
            printf("\n");
            //printf("\n");
            
            myMessage.type = 0;
            
            
        }
        
        else if(strcmp(userinputString,"check_name") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 1;
            
        }
        
        else if(strcmp(userinputString,"check_department") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 2;
            
        }
        
        else if(strcmp(userinputString,"check_salary") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 3;
            
        }
        
        else if(strcmp(userinputString,"check_employee_number") == 0){
            
            printf("Enter a employee name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.name, userinputString);
            printf("\n");
            
            myMessage.type = 4;
            
        }
        
        else if(strcmp(userinputString,"check") == 0){
            
            printf("Enter a department name:");
            scanf("%s", &userinputString);
            strcpy(myMessage.departmentName, userinputString);
            printf("\n");
            
            myMessage.type = 5;
            
        }
        
        else if(strcmp(userinputString,"delete") == 0){
            
            printf("Enter a employee number:");
            scanf("%i", &userinputNumber);
            myMessage.employeeNum = userinputNumber;
            printf("\n");
            
            myMessage.type = 6;
            
        } else if(strcmp(userinputString,"end") == 0){
            printf("Messages ended");
            myMessage.type = 7;
            printf("\n");
        }
        
        
        else {
            printf("Error!");
        }
        
        
        if (msgsnd(msgidAdminRecord,(void *)&myMessage, sizeof(myMessage), 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        
        
        /*
        if (msgrcv(msgid, (void *)&myMessage, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        */
        
        if (strncmp(userinputString, "end", 3) == 0) {
            running = 0;
        }
        //---------------------------------------------------------------------------------
        //now when recieving 
        if (msgidAdminRecord == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    while (running){
        
        if (msgrcv(msgidRecordAdmin, (void *)&myMessage, BUFSIZ,
                   msg_to_receive, 0) == -1) {
            fprintf(stderr, "msgrcv failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        
        printf("The type of message was: %i \n", myMessage.type);
        
        if(myMessage.type == 0){
            //insert command
            printf("message type was input!");
            insertFirst(linkedListKey, myMessage.name, myMessage.departmentName, myMessage.employeeNum, myMessage.salary);
        }
        
       else if(myMessage.type == 1){
            //check name command
            printf("message type was check name! \n");
            struct node *result = NULL;
            result = findLink(myMessage.employeeNum);
            printf("The employee name is: %s", result->name);
            
        }
        else if(myMessage.type == 2){
            //check name command
            printf("message type was check name! \n");
            struct node *result = NULL;
            result = findLink(myMessage.employeeNum);
            printf("The employee department is: %s", result->departmentName);
            
        }
        else if(myMessage.type == 3){
            //check name command
            printf("message type was check salary! \n");
            struct node *result = NULL;
            result = findLink(myMessage.employeeNum);
            printf("The employee salary is: %s", result->name);
            
        }
       else if(myMessage.type == 4){
            //check name command
            printf("message type was check employee number! \n");
            struct node *result = NULL;
            result = findLink(myMessage.employeeNum);
            printf("The employee num is: %s", result->employeeNum);
          
        }
        else if(myMessage.type == 7){
            running = 0;
        }
       
        else {
            printf("error");
        }      
        
    }
    
    
    exit(EXIT_SUCCESS);
    
}
