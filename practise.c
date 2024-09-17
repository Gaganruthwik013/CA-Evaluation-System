#include <stdio.h>
// Declaration
typedef struct student{
    int rno;
    char name[20];
    struct subject{
        int scode;
        char sname[20];
        int mark;
    }sub[3];
    int total;
    float per;
    int final;
}student;

//Create Module

void create(){
    //BUG HERE
    student *s;
    FILE *fp;
    int n,i,j;
    printf("Enter How many students you want: ");
    scanf("%d",&n);

    s=(student*)calloc(n,sizeof(student));
    fp=fopen("mystudent.txt","w");

    for(i=0;i<n;i++)
	{
        s[i].total=0;
        s[i].per=0;
        s[i].final=0;
        printf("Enter Roll No: ");
        scanf("%d",&s[i]);
        fflush(stdin);
        printf("Enter Name: ");
        scanf("%[^\n]s",s[i].name);
        for(j=0;j<3;j++){
            printf("Enter Marks of CA %d: ",j+1);
            scanf("%d",&s[i].sub[j].mark);
            s[i].total+=s[i].sub[j].mark;
        }
        if(s[i].total>90){
            printf("Marks entered by you is out of desired range.\n");
        }
        else{
            s[i].per = s[i].total * 1.11;
            s[i].final=(s[i].per/100) * 25;
            fwrite(&s[i],sizeof(student),1,fp);
            printf("\nRecord Added\n");
        }
    }
    fclose(fp);
}

// Display Module

void display(){
    student s1;
    FILE *fp;
    int j;
    fp=fopen("mystudent.txt","r");
    while(fread(&s1,sizeof(student),1,fp)){
        printf("\n%-5d%-20s",s1.rno,s1.name);
        for(int j=0;j<3;j++){
            printf("%4d",s1.sub[j].mark);
        }
        printf("%5d%7.2f %d",s1.total,s1.per,s1.final);
    }
    fclose(fp);
    printf("\n\n");
}

// Append Module

void append(){
    student *s;
    FILE *fp;
    int n,i,j;
    printf("Enter How many students you want: ");
    scanf("%d",&n);

    s=(student*)calloc(n,sizeof(student));
    fp=fopen("mystudent.txt","a");

    for(i=0;i<n;i++){
        s[i].total=0;
        s[i].per=0;
        printf("Enter Roll No: ");
        scanf("%d",&s[i]);
        fflush(stdin);
        printf("Enter Name: ");
        scanf("%[^\n]s",s[i].name);
        for(j=0;j<3;j++){
            printf("Enter Marks of CA %d: ",j+1);
            scanf("%d",&s[i].sub[j].mark);
            s[i].total+=s[i].sub[j].mark;
        }
        if(s[i].total>90){
            printf("Marks entered by you is out of desired range.\n");
        }
        else{
            s[i].per = s[i].total * 1.11;
            s[i].final=(s[i].per/100) * 25;
            fwrite(&s[i],sizeof(student),1,fp);
            printf("\nRecord Added\n");
        }
    }
    fclose(fp);
}

// Search Module

void search(){
    student s1;
    FILE *fp;
    int j;
    fp=fopen("mystudent.txt","r");
    int rno,found=0;
    printf("Enter Roll No to Search: ");
    scanf("%d",&rno);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno==rno){
            found=1;
            printf("\n%-5d%-20s",s1.rno,s1.name);
            for(int j=0;j<3;j++){
                printf("%4d",s1.sub[j].mark);
            }
            printf("%5d%7.2f %d",s1.total,s1.per,s1.final);
        }
    }
    if(!found)
        printf("\nRecord not Found\n");
    fclose(fp);
    printf("\n\n");
}

// Modify Module

void modify(){
   student s1;
   FILE *fp,*fp1;
   int j,rno, found=0;
   fp=fopen("mystudent.txt","r");
   fp1=fopen("temp.txt","w");
   printf("Enter Roll No to modify: ");
   scanf("%d",&rno);
   while(fread(&s1,sizeof(student),1,fp)){
       if(s1.rno==rno){
           s1.total=0;
           s1.per=0;
           s1.final=0;
           found=1;
           fflush(stdin);
           printf("Enter New Name: ");
           scanf("%[^\n]s",s1.name);
           for(j=0;j<3;j++){
               printf("Enter New Marks of CA %d: ",j+1);
               scanf("%d",&s1.sub[j].mark);
               s1.total+=s1.sub[j].mark;  
           }
           s1.per = s1.total * 1.11;
           s1.final=(s1.per/100) * 25;  
       }
       fwrite(&s1,sizeof(student),1,fp1);
   }
   fclose(fp);
   fclose(fp1);
   if(found){
       fp1=fopen("temp.txt","r");
       fp=fopen("mystudent.txt","w");

       while(fread(&s1,sizeof(student),1,fp1)){
           fwrite(&s1,sizeof(student),1,fp);
       }
       fclose(fp);
       fclose(fp1);
   }
   else
       printf("\nRecord not Found\n");
   fclose(fp);
   printf("\n\n");
}


// Delete Module

void delete(){
    student s1;
    FILE *fp,*fp1;
    int j;
    fp=fopen("mystudent.txt","r");
    fp1=fopen("temp.txt","w");
    int rno,found=0;
    printf("Enter Roll No to Delete: ");
    scanf("%d",&rno);
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno==rno){
            found=1;  
        }
        else
            fwrite(&s1,sizeof(student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);
    if(found){
        fp1=fopen("temp.txt","r");
        fp=fopen("mystudent.txt","w");

        while(fread(&s1,sizeof(student),1,fp1)){
            fwrite(&s1,sizeof(student),1,fp);
        }
        fclose(fp);
        fclose(fp1);
    }
    else
        printf("\nRecord not Found\n");
    fclose(fp);
    printf("Record Deleted Successfully");
    printf("\n\n");
}

int main(){
    // modify and delete module to be made
    int ch;
    do{
        printf("\n1.CREATE NEW RECORD");
        printf("\n2.DISPLAY RECORD");
        printf("\n3.APPEND RECORD");
        printf("\n4.SEARCH RECORD");
        printf("\n5.MODIFY RECORD");
        printf("\n6.DELETE RECORD");
        printf("\n7.EXIT");
        
        printf("\nEnter your Choice: ");
        scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            create();
            break;
        case 2:
            display();
            break;
        case 3:
            append();
            break;
        case 4:
            search();
            break;
        case 5:
            modify();
            break;
        case 6:
            delete();
            break;
        case 7:
            printf("Thank You for giving us chance to serve you.\nWe hope that we assisted you well. \n");
            break;
        default:
            printf("Entered Number is out of choice..Please give a valid Choice.");
            break;
        }
    }while(ch!=0);

    return 0;
}
