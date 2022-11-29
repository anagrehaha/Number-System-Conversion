#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//Struct
struct converter{
char input_number[10],output_number[10];
char from_base,to_base;
};
//Power Function
int Power_function(int base,int exp){
  if(exp==0)
    return 1;
  else
    return Power_function(base,exp-1)*base;
}
 //Error Checking Function
void error_checking(struct converter *check){
  while(1){
    printf("Enter the base you want to convert the number from it: ");
    scanf("%c",&check->from_base);
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
          printf("You should insert any number between (0 and 9) and (between "
                 "A and F(a and f)) \n");
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
    if(check->from_base == 'b' || check->from_base == 'B'){
      if(check->to_base == 'd' || check->to_base == 'D'){
        stop=1;}
      else if(check->to_base=='h' || check->to_base=='H')
        printf("this system doesn't support binary to hexadecimal conversion\n");
      else if(check->to_base == 'b' || check->to_base == 'B')
        printf("if you wish to convert binary to binary, then you already have the answer.\n");
      else
        printf("Insert a valid base \n");
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
       ///////////////////////////////////
    else if(check->from_base == 'H' || check->from_base == 'h'){
      if(check->to_base == 'd' || check->to_base == 'D')
        stop=1;
      else if(check->to_base=='B' || check->to_base=='b')
        printf("this system doesn't support hexadecimal to binary conversion\n");
      else
        printf("Insert a valid base\n");
    }
    if(stop == 1)
      break;
  }
}
//Binary To Decimal Function
void Binary_To_Decimal(struct converter *convert1){
  int input = atoi(convert1->input_number),i=0;
  int dec[16];
  long long output=0;
  while(i < strlen(convert1->input_number)){
    dec[i] = input % 10;
    input/=10;
    output+=dec[i] * Power_function(2,i);
    i++;
  }
  sprintf(convert1->output_number,"%llu",output);
  printf("Value in binary = %s\n",convert1->output_number);
}
//Decimal To Binary Function
void Decimal_To_Binary(struct converter *convert2){
  int input = atoi(convert2->input_number), i = 1;
  long long bin=0;
  int remainder;
  long long output=0;
  while(input != 0){
    remainder = input %2;
    input = input / 2;
    bin += remainder*i;
    i*=10;
  }
  sprintf(convert2->output_number,"%lld",bin);
  printf("Value in binary = %s\n",convert2->output_number);

}
//Hexadecimal To Decimal Function
void Hexadecimal_To_Decimal(struct converter *convert3){
  int a[10];
  long long output=0;
  int length=strlen(convert3->input_number);
  for(int i = 0 ; i < length ; i++){
    if (convert3->input_number[i] == 'A' || convert3->input_number[i] == 'a')
      a[i] = 10;
    if (convert3->input_number[i] == 'B' || convert3->input_number[i] == 'b')
      a[i] = 11;
    if (convert3->input_number[i] == 'C' || convert3->input_number[i] == 'c')
      a[i] = 12;
    if (convert3->input_number[i] == 'D' || convert3->input_number[i] == 'd')
      a[i] = 13;
    if (convert3->input_number[i] == 'E' || convert3->input_number[i] == 'e')
      a[i] = 14;
    if (convert3->input_number[i] == 'F' || convert3->input_number[i] == 'f')
      a[i] = 15;
    if (convert3->input_number[i] >= '0' && convert3->input_number[i] <= '9')
      a[i] = convert3->input_number[i] - '0' ;
  }
  int x = length;
  for(int i = 0 ; i < x ; i++){
    output+=a[i] * Power_function(16,--length);
  }
  sprintf(convert3->output_number,"%lld",output);
  printf("Value in decimal (from Hexadecimal) = %s\n",convert3->output_number);
}
//Decimal To Hexadecimal Function
void Decimal_To_Hexadecimal(struct converter *convert4){
  int i = 0,length = strlen(convert4->output_number);
  long long input = atoi(convert4->input_number);
  while(input != 0){
    int t = 0;
    t = input % 16;
    if (t < 10){
      convert4->output_number[i] = t + '0';
    }
    else {
      convert4->output_number[i] = t + '7';
    }
    input/=16;
    t = 0;
    i++;
  }
  printf("Value in hexadecimal = ");
  for(int k = i-1 ; k>=0 ; k--)
    printf("%c",convert4->output_number[k]);
  printf("\n");
}
int main(void) {
  printf("Welcome to my conversion system\n*************************************\n");
printf("\nEnter (B/b) for binaey, (D/d) for decimal and (H/h) for hexadecimal\n\n");
  struct converter attempt;
  error_checking(&attempt);
  if((attempt.from_base == 'b' || attempt.from_base == 'B') && (attempt.to_base == 'D' || attempt.to_base == 'd'))
    Binary_To_Decimal(&attempt);
  else if((attempt.from_base == 'h' || attempt.from_base == 'H') && (attempt.to_base == 'D' || attempt.to_base == 'd'))
    Hexadecimal_To_Decimal(&attempt);
  else if (attempt.from_base == 'd' || attempt.from_base == 'D') {
    if (attempt.to_base == 'B' || attempt.to_base == 'b')
      Decimal_To_Binary(&attempt);
    else if(attempt.to_base == 'H' || attempt.to_base == 'h')
      Decimal_To_Hexadecimal(&attempt);
    }
  else
    printf("this will not actually ever be printed either\n");
  printf("Thanks for using my conversion system\nGood Bye.");
  return 0;
}
