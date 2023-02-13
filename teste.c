#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <telebot.h>

int cadastro(char *token);

#define SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))

int main(int argc, char *argv[])
{
    printf("Welcome to Echobot\n");

    FILE *fp = fopen(".token", "r");
    if (fp == NULL)
    {
        printf("Failed to open .token file\n");
        return -1;
    }

    char token[1024];
    if (fscanf(fp, "%s", token) == 0)
    {
        printf("Failed to read token\n");
        fclose(fp);
        return -1;
    }
    printf("Token: %s\n", token);
    fclose(fp);

    telebot_handler_t handle;
    if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE)
    {
        printf("Telebot create failed\n");
        return -1;
    }

    telebot_user_t me;
    if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE)
    {
        printf("Failed to get bot information\n");
        telebot_destroy(handle);
        return -1;
    }

    printf("ID: %d\n", me.id);
    printf("First Name: %s\n", me.first_name);
    printf("User Name: %s\n", me.username);

    telebot_put_me(&me);

    int index, count, offset = -1;
    telebot_error_e ret;
    telebot_message_t message;
    telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};
    int i=0,n=0,m=0;
    char mat[100], var[4096];

    while (1)
    {
        telebot_update_t *updates;
        ret = telebot_get_updates(handle, offset, 20, 0, update_types, 0, &updates, &count);
        if (ret != TELEBOT_ERROR_NONE)
            continue;
        //printf("Number of updates: %d\n", count);
        for (index = 0; index < count; index++)
        {
            message = updates[index].message;
            char str[4096];
            
            if (message.text)
            {
                printf("%s: %s \n", message.from->first_name, message.text);
                sleep(1);

                if (strstr(message.text, "/1")){
                     snprintf(str, SIZE_OF_ARRAY(str), "Qual é sua matrícula ?");
                     n=1; m=0;                    
                }
                else if (strstr(message.text, "/2")){
                    snprintf(str, SIZE_OF_ARRAY(str), "Qual matricula deseja apagar ?");
                    m=1;
                    n=0;
                }
                //Tira foto
                else if (strstr(message.text, "/3")){
                    m=0;
                    n=0;
                    system("fswebcam image.jpg");
                    telebot_send_photo(handle, message.chat->id, "image.jpg", true, "", "HTML",false,0,"");                                     
                }
                
                //Finaliza
               else if (strstr(message.text, "/4")){
                    snprintf(str, SIZE_OF_ARRAY(str), "Até mais !");
                    m=0;
                    n=0;
                    printf("n=%d m=%d \n",n,m);
                    sleep(1);
                    exit(-1);
                }
                else if (n==1){
                    
                    fp = fopen("info.txt", "a");
                    
                    if (fp == NULL)
                    {
                        printf("Failed to open info.txt file\n");
                        return -1;
                    }
                    else
                    {
                        printf("Arquivo aberto com sucesso!\n");
                    }                    
                    
                    for(i=0; (message.text)[i]!='\0';i++)
                    {
                        putc((message.text)[i],fp);
                        mat[i]=(message.text)[i];
                    }
                    mat[i+1]='\0';
                    putc(' ',fp);
                    fclose(fp);
                    n=2; m=0;
                    snprintf(str, SIZE_OF_ARRAY(str), "Qual seu token ?");
                    printf("n=%d \n",n);
                    
                }
                
                else if (n==2){
                    m=0;
                
                    fp = fopen("info.txt", "a");
                    for(i=0; (message.text)[i]!='\0';i++)
                    {
                            putc((message.text)[i],fp);
                    }
                    putc('\n',fp);
                    fclose(fp);
                    n=3;
                    snprintf(str, SIZE_OF_ARRAY(str), "Pressione /x para tirar a foto");
                    printf("n=%d \n",n);
                    
                }
                
                else if (strstr(message.text, "/x") && n==3){
                m=0;
                n=0;
                sleep(2);
                system("fswebcam image.jpg");
                printf("n=%d \n",n);
                sprintf(var,"mv image.jpg image/%s.jpg",mat);
                system(var);
                }

                
              //Apagar cadastro : m=1 (ler matricula), m=2 (apaga matricula)                                  
               
                else if (m==1){
                    n=0;
                    m=0;
                    for(i=0; (message.text)[i]!='\0';i++)
                    {
                        mat[i]=(message.text)[i];
                    }
                    mat[i+1]='\0';
                    printf("%s",mat);
                    sprintf(var, "grep -v %s info.txt > teste.txt",mat);
                    system(var);
                    system("mv teste.txt info.txt");                    
                }

                else {
                    snprintf(str,SIZE_OF_ARRAY(str), "Escolha dentre as opções : \n /1) Novo Cadastro \n /2) Excluir Cadastro \n /3) Foto \n /4) Finalizar sessão \n");
                }
                    
                    ret = telebot_send_message(handle, message.chat->id, str, "HTML", false, false, updates[index].message.message_id, "");
                }
                
                if (ret != TELEBOT_ERROR_NONE)
                {
                    printf("Failed to send message: %d \n", ret);
                }
            
            offset = updates[index].update_id + 1;
        }
        
        telebot_put_updates(updates, count);

        sleep(1);
    }

    telebot_destroy(handle);

    return 0;
}

int cadastro(char *token)
{
char str[4096];

int i;    
 FILE *fp = fopen("info.txt", "w");
 
    
if (fp == NULL)
{
    printf("Failed to open info.txt file\n");
    return -1;
}

telebot_handler_t handle;
    if (telebot_create(&handle, token) != TELEBOT_ERROR_NONE)
    {
        printf("Telebot create failed\n");
        return -1;
    }

    telebot_user_t me;
    if (telebot_get_me(handle, &me) != TELEBOT_ERROR_NONE)
    {
        printf("Failed to get bot information\n");
        telebot_destroy(handle);
        return -1;
    }

    telebot_put_me(&me);

    int index, count, offset = -1;
    telebot_error_e ret;
    telebot_message_t message;
    telebot_update_type_e update_types[] = {TELEBOT_UPDATE_TYPE_MESSAGE};
    
 while (1)
    {
        telebot_update_t *updates;
        ret = telebot_get_updates(handle, offset, 20, 0, update_types, 0, &updates, &count);
        if (ret != TELEBOT_ERROR_NONE)
            continue;
        for (index = 0; index < count; index++)
        {
            message = updates[index].message;
            
            
            snprintf(str, SIZE_OF_ARRAY(str), "Qual seu nome ?");
            int n=1;
            
            if (message.text)
            {
                printf("%s: %s \n", message.from->first_name, message.text);
                sleep(1);

                if (n==1){
                    for(i=0; (message.text)[i]!='\0';i++){
                        putc((message.text)[i],fp);
                        putc(' ',fp);
                    }
                n=2;
                }
                
                else if (n==2){
                    for(i=0; (message.text)[i]!='\0';i++){
                            putc((message.text)[i],fp);
                            putc('\n',fp);
                    }
                fclose(fp);
                n=0;   
                break;
                }               
            }
        }
        
        telebot_put_updates(updates, count);

        break;
    }
    return 0;
}
