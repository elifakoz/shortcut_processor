    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    
    struct ArrayTable {
        char name[10]; // array name
        char size[5]; // array size
        char type[10]; // int, float, etc.
    };
    struct ArrayTable AT[20];
    int ind=0;
    
    void ltrim(char* data,char* target){
        int len = strlen(data);
        int i=0,j=0,iflag=0,jflag=0;
        char* res = (char*)malloc(sizeof(char)*len);
        for(int i=0;i<len;i++){
            if(data[i]==' ' && iflag==0){
                continue;
            }
            else iflag = 1;
            if(iflag==1){
                res[j++]=data[i];
            }
        }
        res[j]='\0';
        strcpy(target,res);
    }
    
    int findArray(char* name){
        for(int i=0;i<ind;i++){
            if(strcmp(AT[i].name,name)==0){
                return i;
            }
        }
        return -1;
    }
    char* declare(char* name,char* size, char* type){
        char* result =(char*)malloc(sizeof(char)*300);
        strcpy(AT[ind].name,name);
        strcpy(AT[ind].size,size);
        strcpy(AT[ind].type,type);
        sprintf(result,"\t%s %s[%s];\n",type,name,size);
        ind++;
        return result;
    }
    char* read(int index,char* file){
        char* result = (char*)malloc(sizeof(char)*300);
        sprintf(result,"\tFILE* ff=fopen(\"%s\", \"r\");\n\tfor(int i=0; i<%s; i++)\n\t\tfscanf(ff, \"%s\", &%s[i]);\n\tfclose(ff)\n",file,AT[index].size,"\%d",AT[index].name);
        return result;
    }
    char* print(int index){
        char* result = (char*)malloc(sizeof(char)*300);
        sprintf(result,"\tfor(int i=0; i<%s; i++)\n\t\tprintf(\"%s \", %s[i])\n",AT[index].size,"\%d",AT[index].name);
        return result;
    }
    char* initialize(int index,int value){
        char* result = (char*)malloc(sizeof(char)*300);
        sprintf(result,"\tfor (int i=0; i<%s; i++)\n\t\t%s[i]=%d;\n",AT[index].size,AT[index].name,value);
        return result;
    }
    char* arithmethic(int index,char* first,char* second, char* sign){
        char* result = (char*)malloc(sizeof(char)*300);
        int firstindex = findArray(first);
        int secondindex = findArray(second);
        int firstVal,secondVal,isFirstArray,isSecondArray;
        if(firstindex==-1)
            isFirstArray = 0;
        else
            isFirstArray = 1;
        if(secondindex==-1)
            isSecondArray = 0;
        else 
            isSecondArray = 1;
        if(isFirstArray == 1 && isSecondArray==1){
            sprintf(result,"\tfor (int i=0; i<%s; i++)\n\t\t%s[i]=%s[i]%s%s[i];\n",AT[index].size,AT[index].name,AT[firstindex].name,sign,AT[secondindex].name);
        }
        else if(isFirstArray ==1 && isSecondArray == 0){
            sprintf(result,"\tfor (int i=0; i<%s; i++)\n\t\t%s[i]=%s[i]%s%s;\n",AT[index].size,AT[index].name,AT[firstindex].name,sign,second);
        }
        else if(isFirstArray==0 && isSecondArray==1){
            sprintf(result,"\tfor (int i=0; i<%s; i++)\n\t\t%s[i]=%s%s%s[i];\n",AT[index].size,AT[index].name,first,sign,AT[secondindex].name);
        }
        else{
            sprintf(result,"\tfor (int i=0; i<%s; i++)\n\t\t%s[i]=%s%s%s;\n",AT[index].size,AT[index].name,first,sign,second);
        }
        return result;
    }
    char* copy(int index,int from){
        char* result = (char*)malloc(sizeof(char)*300);
        sprintf(result,"\tfor (int i=0; i<%s; i++)\n\t\t%s[i]=%s[i];\n",AT[index].size,AT[index].name,AT[from].name);
        return result;
    }
    
    void executeCommand(char* filename){
        char * ccode = (char*)malloc(sizeof(char)*3000);
        strcpy(ccode,"int main()\n{\n");
        FILE* f = fopen(filename,"r");
        char line[50];
        while(!feof(f)){
            fscanf(f,"%[^\n]\n",line);
            int len = strlen(line);
            char* trimmed = (char*)malloc(sizeof(char)*len);
            ltrim(line,trimmed);
            char* result = strstr(line,"dec");
            char buf[len];
            if(result){
                strncpy(buf,&line[5],len-5);
                buf[len-5]='\0';
                char* name = strtok(buf,",");
                char* size = strtok(NULL,",");
                char* type = strtok(NULL,");");
                ltrim(name,name);
                ltrim(size,size);
                ltrim(type,type);
                strcat(ccode,declare(name,size,type));
                continue;
            }
            result = strstr(line,"read");
            if(result){
                strncpy(buf,&line[6],len-6);
                buf[len-6]='\0';
                char* filename = strtok(buf,",");
                char* name = strtok(NULL,");");
                ltrim(name,name);
                ltrim(filename,filename);
                int indis = findArray(name);
                strcat(ccode,read(indis,filename));
                continue;
            }
            result = strstr(line,"print");
            if(result){
                strncpy(buf,&line[7],len-7);
                buf[len-7]='\0';
                char* name = strtok(buf,")");
                ltrim(name,name);
                int indis = findArray(name);
                strcat(ccode,print(indis));
                continue;
            }
            result = strstr(line,"$");
            if(result){
                strncpy(buf,&line[1],len-1);
                buf[len-1]='\0';
                char* name = strtok(buf," = ");
                char* arithm = strtok(NULL,";");
                ltrim(name,name);
                ltrim(arithm,arithm);
                int indis = findArray(name);
                
                char* number = strtok(arithm,"=");
                int value = atoi(number);
                if((strstr(number,"+")||strstr(number,"-")||strstr(number,"*")||strstr(number,"/"))){
                    char signs[5]="+-/*";
                    int done = 0;
                    for(int i=0;i<4;i++){
                        char mark[4];
                        mark[0] = ' ';
                        mark[1] = signs[i];
                        mark[2] = ' ';
                        mark[3]='\0';
                        //printf("mark: %s\n",mark);
                        result = strstr(number,mark);
                        if(result){
                            char* first = strtok(number,mark);
                            char* second = strtok(NULL,mark);
                            char* firstName =(char*)malloc(sizeof(char)*10);
                            char* secondName =(char*)malloc(sizeof(char)*10);
                            if(strstr(first,"$")){
                                strncpy(firstName,&first[1],strlen(first)-1);
                            }
                            else strncpy(firstName,first,strlen(first));
                            if(strstr(second,"$")){
                                strncpy(secondName,&second[1],strlen(second)-1);
                            }
                            else strncpy(secondName,second,strlen(second));
                            strcat(ccode,arithmethic(indis,firstName,secondName,mark));
                            done = 1;
                            break;
                        }
                    }
                }
                else{
                    if(value==0){
                        ltrim(number,number);
                        char* firstName =(char*)malloc(sizeof(char)*10);
                        strncpy(firstName,&number[1],strlen(number)-1);
                        int firstindex = findArray(firstName);
                        strcat(ccode,copy(indis,firstindex));
                    }
                    else
                        strcat(ccode,initialize(indis,value));
                    continue;
                }
            }
        }
        fclose(f);
        strcat(ccode,"}");
        printf("%s\n",ccode);
    }
    
    
    int main(int argc,char** argv)
    {
        char file[50];
        if(argc==2){
            strcpy(file,argv[1]);
        }
        else{
            printf("Enter file name:");
            scanf("%s",file);
        }
        executeCommand(file);
        return 0;
    }
