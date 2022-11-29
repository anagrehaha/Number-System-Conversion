//client

#include        <sys/socket.h>  
#include        <netinet/in.h>  
#include        <arpa/inet.h>
#include        <netinet/in.h>
#include        <stdio.h>
#include        <string.h>
#include        <stdlib.h>
#include        <errno.h>
#include        <unistd.h> 
#include        <libgen.h>
#include        <pthread.h>
#include        <limits.h>
#include        <sys/time.h>
#include        <ctype.h>
#include        <math.h>

int ctr = 0;
#define MAXSZ 100


//struct
struct converter{
char input_number[100],output_number[100];
char from_base,to_base;
};





//Error Checking Function
void error_checking(struct converter *check)
{
  
  while(1){
    printf("Enter the base you want to convert the number from it: ");

    
    if(ctr>0){
    fgetc(stdin);}
    scanf("%c",&check->from_base);
    ctr++;
    if(check->from_base == 'D' || check->from_base == 'd' || check->from_base == 'H' || check->from_base == 'h' || check->from_base == 'B' || check->from_base == 'b')
      break;
    else{
      fgetc(stdin);
      printf("Error : you entered an invalid base \n");
    }
  }
  int num = 0;
  while(1){
    printf("Enter the number you want to convert it (up to 10 digits): ");
    scanf("%s",check->input_number);
    if ((check->from_base == 'b' || check->from_base == 'B'))
    {
      for (int i = 0; i < strlen(check->input_number); i++) 
        {
          if (check->input_number[i] == '1' || check->input_number[i] == '0')
            num=1;
          else
          {
            printf("Invalid input, you should insert 0 or 1 \n");
            num = 0;
            break;
          }
        }
      if(num == 1)
        break;
    }
    if (check->from_base == 'd' || check->from_base == 'D') 
    {
      for (int i = 0; i < strlen(check->input_number); i++) 
      {
        if ('0' <= check->input_number[i] && check->input_number[i] <= '9')
          num = 1;
        else {
          num = 0;
          printf("You should insert any integer number between 0 and 9 \n");
          break;
        }
      }
      if (num == 1)
        break;
  }
    if (check->from_base == 'H' || check->from_base == 'h') 
    {
      for (int i = 0; i < strlen(check->input_number); i++) 
      {
        if (('0' <= check->input_number[i] && check->input_number[i] <= '9') || (check->input_number[i]) >= 'A' && check->input_number[i] <= 'F' || check->input_number[i] >= 'a' && check->input_number[i] <= 'f') 
          num = 1;
        else 
        {
          printf("You should insert any number between (0 and 9) and (between A and F(a and f)) \n");
          num = 0;
          break;
        }
      }
      if (num == 1)
        break;
    }
  }
  int stop=0;
  while(1){
    stop=0;
    printf("Enter the base you want to convert to it: ");
    fgetc(stdin);
    scanf("%c",&check->to_base);
    ///////////////////////////////
    if(check->from_base == 'b' || check->from_base == 'B')
    {
      if(check->to_base == 'd' || check->to_base == 'D' )
        stop=1;
        
      else if(check->from_base=='B' || check->from_base=='b')
         { 
           if(check->to_base=='H' || check->to_base=='h')
            stop=1;
          }
      else printf("Invalid Base\n");
    }
    ////////////////////////////////
     else if(check->from_base == 'D' || check->from_base== 'd'){
      if(check->to_base == 'H' || check->to_base == 'h' || check->to_base=='B' || check->to_base=='b')
        stop=1;
      else if(check->to_base == 'd' || check->to_base == 'D')
        printf("if you wish to convert decimal to decimal, then you already have the answer\n");
      else
        printf("Insert a valid base\n");
      }
    else if(check->from_base=='H' || check->from_base=='h'){
      if(check->to_base=='b' || check->to_base=='B' || check->to_base =='d' || check->to_base == 'D')
        stop=1;
      else printf("Invalid Base\n");
    }
    if(stop == 1)
      break;
  }
}


int main(int argc, char ** argv) 
{
  if ( argc != 3 )
        {
                printf("Please enter the IP and the port number of the server.\n");
        exit(-1);
        }
  else
  {

    int sockfd;//to create socket
    struct sockaddr_in serverAddress;//client will connect on this
    int n;
    char buffer[8000];
    char token[800]; 
    char done[800] = "notdone";
    struct converter attempt;
    int checkerr;
  //  token = malloc(sizeof(char)*100);
 //create socket
 sockfd=socket(AF_INET,SOCK_STREAM,0); //initialize the socket addresses
    if (sockfd < 0) {perror("socket() error"); close(sockfd); exit(-1);} //error checks socket creations

    //set up server information
   memset(&serverAddress,0,sizeof(serverAddress));
   serverAddress.sin_family=AF_INET;
   inet_pton(AF_INET, argv[1], &serverAddress.sin_addr);
  serverAddress.sin_port = htons(atoi(argv[2]));    //client  connect to server on port

    
   checkerr = connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));//send TCP CONNECTION TO SERVER
    if (checkerr < 0)
    {
      perror("connection error\n");
      close(sockfd);
      exit(-1);
    }

    printf("*****client has connection successfully****\n");
  //welcoming client printfs..
    printf("Welcome to my conversion system\n***\n");
    printf("this system only supports conversion of Binary, Decimal, Hexadecimal numbers.\n");
    printf("\nEnter (B/b) for binaey, (D/d) for decimal and (H/h) for hexadecimal\n\n");
    

   checkerr = recv(sockfd, buffer, sizeof(buffer), 0); //receive welcome message
    if (checkerr < 0)
    {
      perror("read error\n");
      close(sockfd);
      exit(-1);
    }
    printf("%s",buffer);




    
 while(1)
  {
   // memset(buffer, '\0', strlen(buffer));
    
        if (strcmp(done,"done") != 0)
        {
          error_checking(&attempt);
          strcat(token,(attempt.input_number));
          strcat(token,":");
          strcat(token,&(attempt.from_base));
          strcat(token,":");
          strcat(token,&(attempt.to_base));
          strcpy(buffer, token);
          checkerr = send(sockfd, buffer, sizeof(buffer), 0);
          if (checkerr< 0 )
          {
            perror("send error\n");
            close(sockfd);
            exit(-1);
          }
          checkerr = recv(sockfd, buffer, sizeof(buffer), 0);
          if (checkerr < 0)
          {
            perror("recv error\n");
            close(sockfd);
            exit(-1);
          }
          strcpy(attempt.output_number, buffer);
          if (attempt.to_base == 'd' || attempt.to_base == 'D')
          {
            printf("\nDecimal number: %s\n", attempt.output_number);
          }
          else if (attempt.to_base == 'h' || attempt.to_base == 'H')
          {
            printf("\nHexadecimal number %s\n",attempt. output_number);
          }
          else if (attempt.to_base == 'b' || attempt.to_base =='B')
          {
            printf("\nBinary number %s\n", attempt.output_number);
          }
          else
          {
            printf("\nUn supported conversion\n");
          }

          // printfs to ask the user if they want to carry on (done thingy)
         
          printf("Enter done if you want to finish converting. Or enter any other character if you want to complete converting\n");
          printf(": ");
          scanf("%s",done);
          strcpy(buffer,done);
          
        }
        else
        {
          checkerr = send(sockfd, buffer, sizeof(buffer), 0);
          if (checkerr< 0 )
          {
            perror("send error\n");
            close(sockfd);
            exit(-1);
          }
          close(sockfd);
          break;
        }
  
        memset(attempt.input_number, '\0', strlen(attempt.input_number));
        memset(&attempt.to_base,'\0',strlen(&attempt.to_base));
        memset(&attempt.from_base, '\0', strlen(&attempt.from_base));
        memset(attempt.input_number,'\0',strlen(attempt.input_number));
        memset(token,'\0',strlen(token));
    }
}
  return 0;
}




