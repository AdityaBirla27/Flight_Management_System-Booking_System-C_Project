#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BC 150
#define EC 50

typedef struct
{   
    int b[20];
    int e[20];
}plane;

struct book
{
	int code;
	char name[20];
	int cost;
    char row;
    int seat;
}b;

void booking(plane p[2]);
void viewall(char *filename);
void find();
void open_flight(plane p[2], char* filename, int x);
void view_flight(plane p[2], int x);
void update_flight(plane p[2], char* filename, int x);

int main()
{
    plane p[2]; //array for multiple plane
	int ch;
 	do{
	    printf("\n\n\n==================================");
    	printf("\n");
	    printf("  Airline Ticket booking ");
	    printf("\n");
	    printf("\n==================================");
    	printf("\n 1. Booking");
        printf("\n 2. View All Ticket");
	    printf("\n 3. Find Ticket ");
	    printf("\n 4. Seating plans ");
        printf("\n 0. Exit \n");
        printf("\nEnter your Choice:  ");
        scanf("%d",&ch);
        switch (ch)
    	{
        case 1 :
            booking(p);     //booking case
   		    break;

		case 2:
            printf("\n==================================");
            printf("\nFor flight Obj263:\n");   //viewall bookings
            viewall("Obj263booking.txt");
            printf("\n==================================");
            printf("\nFor flight Obj268:\n");
            viewall("Obj268booking.txt");
            printf("\n==================================");
            break;

		case 3:
            find();
   		    break;

        case 4:
            open_flight(p, "Obj263.txt", 0); //initialize seating plan for flight 1 and 2
            open_flight(p, "Obj268.txt", 1);
            int cf;
            while(cf != -1)     
            {
                printf("Choose Flight:\n1. Obj263 \n2. Obj268\n");
                scanf("%d", &cf);       
                if(cf == 1){
                    view_flight(p, 0);
                    break;
                }else if(cf == 2){
                    view_flight(p, 1);
                    break;
                }else{
                    printf("Select a valid option\n");
                }
            }
            break;
        
        case 0:
            exit(0);
            break;

        default:
            printf("Wrong choice !");
            break;
   	    }
    }while(ch!=0);
}


void booking(plane p[2])
{
	FILE *fp;
	struct book b;
    open_flight(p, "Obj263.txt", 0); //initialize seating plan for flight 1 and 2
    open_flight(p, "Obj268.txt", 1);
	printf("Enter  passenger name :  ");
	scanf("%s",b.name);   //input name
    int cf = 1;
    int fl;
    char *filename, *flightfile;
    //ask user to choose flight
    while(cf != -1)     
    {
        printf("Choose Flight:\n1. Obj263 \n2. Obj268\n");
        scanf("%d", &cf);       
        if(cf == 1)
        {
            fl = 0;     //flight variable for plane struct array
            filename = "Obj263.txt";        //seat file
            flightfile = "Obj263booking.txt";       //ticket file
            view_flight(p, fl);     //print seats
            break;
        }else if(cf == 2){
            fl = 1;     //repeat
            filename = "Obj268.txt";
            flightfile = "Obj268booking.txt";
            view_flight(p, fl);
            break;
        }else{
            printf("Enter valid option.\n");
        }
    }
    int ch = 1;
    int flag = 0;
    //ask user for business or economy class
    while(ch != -1)
    {
        printf("Enter prefrence: \n1. Business Class\n2. Economy Class\n");
        scanf("%d", &ch);       
        if (ch == 1)
        {
            //go through the seat information array and find the first empty seat. 1 is empty
            for(int i = 0; i < 20; i++)
            {
                if(p[fl].b[i] == 1)
                {
                    p[fl].b[i] = 0;     //say seat is taken. assign 0
                    flag = 1;           //raise flag
                    b.seat = i/4 + 1;   //find the exact row
                    //find alphabet corresponding to seat
                    if(i%4 == 0)    
                        b.row = 'A';    
                    else if(i%4 == 1)
                        b.row = 'B';
                    else if(i%4 == 2)
                        b.row = 'C';
                    else
                        b.row = 'D';
                    view_flight(p, fl);     //view seating after newly booked flight to confirm booking
                    update_flight(p, filename, fl);     //update the seating information to file
                    break;
                }
            }
            //if flagged, assign cost and break away
            if(flag){
                b.cost = BC;
                break;
            }
            printf("Business Class is full. please select a different option\n");
        }else if(ch == 2){
            //same thing for economy class like business class
            for(int i = 0; i < 20; i++)
            {
                if(p[fl].e[i] == 1)
                {
                    p[fl].e[i] = 0;
                    flag = 1;
                    b.seat = i/4 + 6;
                    if(i%4 == 0)
                        b.row = 'A';
                    else if(i%4 == 1)
                        b.row = 'B';
                    else if(i%4 == 2)
                        b.row = 'C';
                    else
                        b.row = 'D';
                    update_flight(p, filename, fl);
                    break;
                }
            }
            if(flag){
                b.cost = EC;
                break;
            }
            printf("Economy Class is full. please select a different option\n");
        }else{
            printf("Please select a valid option.\n");
        }
    }
    //find the next unique ticket token
    int id = 0;
    char tmp[1024];
    fp = fopen(flightfile, "r");
    if(fp == NULL)
    {
        printf("File not Found");
    }else{
        //loop through file till you read last line
        while(!feof(fp))
            fgets(tmp, 1024, fp);
        char *tokenPtr = strtok(tmp, " ");      //tokenize last line
        id = atoi(tokenPtr);    //convert to int
        fclose(fp);
    }
    //if token ends up being 0, init 2000
    if(id < 2000)
        id = 2000;
    id++;
    b.code = id;        //init booking code for ref
    fp=fopen(flightfile, "a");
    if(fp == NULL)
    {
        printf("File not Found");
    }else{
        fprintf(fp,"%d %s %d %d %c\n",b.code,b.name,b.cost, b.seat, b.row);     //write data
        printf("Congratulations,Booking successfull");
    }
    printf("\n");
    fclose(fp);
}


void find()
{
	struct book b;
	FILE *fp;
    int cf;
    char *file, *flight;
    //choose which file the ticket is from
    while(cf != -1)
    {
        printf("Choose Flight:\n1. Obj263 \n2. Obj268\n");
        scanf("%d", &cf);
        if(cf == 1)
        {
            file = "Obj263booking.txt";
            flight = "Obj263";
            break;
        }else if(cf == 2){
            file = "Obj268booking.txt";
            flight = "Obj268";
            break;
        }else{
            printf("enter valid code\n");
        }
    }
	int ch;
	printf("Enter ticket code :");
	scanf("%d",&ch);
	fp = fopen(file,"r");
	if(fp == NULL)
	{
		printf("file does not found !");
		exit(1);
	}
	else
	{
        //scan all space delimited values from file
		while(!feof(fp))
		{
			fscanf(fp,"%d %s %d %d %c", &b.code, b.name, &b.cost, &b.seat, &b.row);
			if(b.code == ch)        //compare the reference ids
			{
				printf("\n Record Found\n");
				printf("\n\t\tTicket Code : %d",b.code);
				printf("\n\t\tPassenger name : %s",b.name);
				printf("\n\t\tPrice : %d",b.cost);
                printf("\n\t\tSeat : %d%c",b.seat, b.row);
                printf("\n\t\tFlight : %s", flight);
				break;
			}
		}
	}
	fclose(fp);
}


void viewall(char *filename)
{
	char ch;
	FILE *fp;
	fp = fopen(filename,"r");
	if(fp == NULL)
	{
		printf("Not found !");
		exit(1);
	}
	else
	{
        //print file one character at a time
		while( (ch=fgetc(fp))!= EOF )
      		printf("%c",ch);
	}
	fclose(fp);
}

void view_flight(plane p[2], int x)
{
    int c = 0, i = 0, j = 0;
    printf("\nFlight plan:\n");
    while(c < 10)
    {
        //print seat values for business class then economy
        //underscore(95) = Empty. Block(220) = Full
        if(c < 5)
        {
            if(c == 0){
                printf("Business Class - $150\n");
                printf("\tSeats\tA B \t C D\n\n");
            }
            printf("\t%5d\t", c+1);
            printf("%c %c \t %c %c\n", p[x].b[i]?95:220, p[x].b[i+1]?95:220, p[x].b[i+2]?95:220, p[x].b[i+3]?95:220);
            i += 4;
            c++;
        }else{
            if(c == 5){
                printf("Economy Class - $50\n");
                printf("\tSeats\tA B \t C D\n\n");
            }
            printf("\t%5d\t", c+1);
            printf("%c %c \t %c %c\n", p[x].e[j]?95:220, p[x].e[j+1]?95:220, p[x].e[j+2]?95:220, p[x].e[j+3]?95:220);
            j += 4;
            c++;
        }
    }
}


void update_flight(plane p[2], char* filename, int x)
{
    FILE* fp;
	fp = fopen(filename, "w");
	if(fp == NULL)
	{
		printf("File not Found");
	}else{
        int c = 0, i = 0, j = 0;
        //overwrite data to file systematically
        while(c < 10)
        {
            if(c < 5)
            {
                fprintf(fp, "%d %d \t %d %d\n", p[x].b[i], p[x].b[i+1], p[x].b[i+2], p[x].b[i+3]);
                i += 4;
                c++;
            }else{
                fprintf(fp, "%d %d \t %d %d\n", p[x].e[j], p[x].e[j+1], p[x].e[j+2], p[x].e[j+3]);
                j += 4;
                c++;
            }
        }
        fclose(fp);
    }
} 


void open_flight(plane p[2], char* filename, int x)
{
    FILE* fp;
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		printf("File not Found");
	}else{
		int c = 0, i = 0, j = 0;
        //assign seat values to specific array elements
		while (!feof(fp))
		{
			if(c < 5)
			{
				fscanf(fp, "%d %d %d %d", &p[x].b[i], &p[x].b[i+1], &p[x].b[i+2], &p[x].b[i+3]);
				i += 4;
				c++;
			}else{
				fscanf(fp, "%d %d %d %d", &p[x].e[j], &p[x].e[j+1], &p[x].e[j+2], &p[x].e[j+3]);
                j += 4;
				c++;
			}
		}
		fclose(fp);
	}
}
