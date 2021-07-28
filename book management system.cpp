//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************

#include<fstream>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<windows.h>
#include<iostream>
using namespace std;

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************



class book
{
 int bno;
 char bcode[50];
 char a_id[20];
 float price;
 int n;
public:
    void input_details()
    {
     cout<<"\n ENTER THE DETAILS OF THE BOOK ( AUTHOR ID IS THE FIRST NAME OF THE AUTHOR, CODE IS THE IDENTIFYING NAME OF THE BOOK )";
     cout<<"\n Please enter the book No. ";
     cin>>bno;
     cout<<"\n\n Please enter the code of The book ";
     cin>>(bcode);                                         
     cout<<"\n\n Please enter the id of the author";
     cin>>(a_id);
     cout<<"\n Please Enter The Price of The book ";
     cin>>price;
     cout<<"\n Please Enter The no. of copies";
     cin>>n;
     }

    void input_moddetails()
    {
     cout<<"\n DETAILS OF THE BOOK YOU WANT TO MODIFY";
     cout<<"\n\n Please enter the book No.: ";
     cin>>bno;
     cout<<"\n Please enter the code of The book : ";
     cin>>(bcode);                                         
     cout<<"\nPlease enter the id of the author : ";
     cin>>(a_id);
     cout<<"\n Please Enter The Price of The book :  ";
     cin>>price;
     cout<<"\n Please Enter The no. of copies : ";
     cin>>n;
     }
     
    void show_details()
    {
     cout<<"\n The book No. of The book : "<<bno;
     cout<<"\n The Code of The book : ";
     puts(bcode);
     cout<<"\n The id of the author of the book : ";
     puts(a_id);
     cout<<"\n The Price of The book : "<<price;
    cout<<"\n No. of copies : "<<n<<endl<<endl;
    }

      int  getbno()
      {
      return bno;
      }



    void report()
    {
       cout<<bno<<setw(22)<<bcode<<setw(21)<<a_id<<setw(20)<<price<<setw(19)<<n<<endl;
    }
};         //class ends here









//***************************************************************
//    	global declaration for stream object, object
//****************************************************************

 fstream fp;   
 book bk;     


//***************************************************************
//    	function to write in file
//****************************************************************

void write_book()
   {
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do{
    system("cls");
    bk.input_details();
    fp.write((char*)&bk,sizeof(book));
    cout<<"\n\nDo you want to add more record..(y/n?)?";
    cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
   }



//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_spb(int n)
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
    if(bk.getbno()==n)
    {
        bk.show_details();
        flag=1;
    }
    }
    fp.close();
    if(flag==0)
    cout<<"\n\n Book does not exist";
    system("pause");
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_book()
{
    char ans='y';
    int n1;
    char found='y';
    long pos;
    system("cls");
    fp.open("book.dat",ios::in|ios::out);
    while((ans=='y')||(ans=='Y'))
    {
      cout<<"\n\n\t   MODIFY BOOK REOCORD.... ";
      cout<<"\n\n\tEnter The book no. of The book";
      cin>>n1;
      while(!fp.eof())
      {
          pos=fp.tellg();
          fp.read((char*)&bk,sizeof(bk));
          if(bk.getbno()==n1)
            {
            bk.show_details();
            found='y';
            bk.input_moddetails();
            fp.seekg(pos);
            fp.write((char*)&bk,sizeof(book));
            cout<<"\n\n\t Record Updated";
        break;
    }
        }
      cout<<"\n\n  Do you want to continue?";
      cin>>ans;
    }
    if(found=='n')
    cout<<"\n\n  Record not found";
    system("pause");
    fp.close();
}




//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_book()
 {
    int n1;
    char ans='y',found='y';
    system("cls");
    ofstream fp2;
    fp.open("book.dat",ios::in|ios::out);
    fp2.open("Temp.dat",ios::out);
    while((ans=='y')||(ans=='Y'))
    {
      cout<<"\n\n\n\tDELETE BOOK ...";
      cout<<"\n\n Enter The book no. of the book you want to delete : ";
      cin>>n1;
      while(!fp.eof())
      {
	fp.read((char*)&bk,sizeof(book));
	if(fp.eof())
	   break;
	if(bk.getbno()==n1)
	{
	   found='y';
	}
	else
	   fp2.write((char*)&bk,sizeof(book));
      }
     cout<<"\n\n Do you want to continue?(y/n)";
     cin>>ans;
    }
    if(found=='n')
      cout<<"\n\n Book record not found";
    fp.close();
    fp2.close();
    remove("book.dat");
    rename("Temp.dat","book.dat");
    cout<<"\n\n\tRecord Deleted ..";
    //getch();
    cout<<"\n\n New contents of the file are:?\n\n";
    fp.open("book.dat",ios::in|ios::out);
    while(!fp.eof())
    {
      fp.read((char*)&bk,sizeof(bk));
      if(fp.eof())
	  break;
      bk.show_details();
    }
    fp.close();
   }



//***************************************************************
//    	function to display Books list
//****************************************************************




    void display_allb()
    {
     system("cls");
     fp.open("book.dat",ios::in);
     if(!fp)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
       system("pause");
       return;
     }

     cout<<"\n\n\t\t\t\tBook LIST\n\n";
     cout<<"==========================================================================================\n";
     cout<<"BNO."<<setw(20)<<"BOOKCODE"<<setw(20)<<"AuthorID"<<setw(20)<<"PRICE"<<setw(19)<<"QTY";
     cout<<"\n==========================================================================================\n";

   while(fp.read((char*)&bk,sizeof(book)))
   {
     bk.report();
   }
     fp.close();
     system("pause");
}





//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
 system("cls");
 gotoxy(70,20);
 cout<<"| THE  BOOK  SHOP |                                                 ";
 system("pause");

}





//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
  int ch=0;
  intro();
  do
    {
       system("cls");
       cout<<"\n\n\n\tMAIN MENU";
       cout<<"\n\n\t1.CREATE BOOKS RECORDS";
       cout<<"\n\n\t2.DISPLAY ALL BOOKS RECORDS";
       cout<<"\n\n\t3.DISPLAY SPECIFIC BOOK RECORD ";
       cout<<"\n\n\t4.MODIFY BOOK RECORD";
       cout<<"\n\n\t5.DELETE BOOK RECORD";
       cout<<"\n\n\t6.EXIT";
       cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
       cin>>ch;
       system("cls");
       if(ch==1)
        write_book();
       if(ch==2)
        display_allb();
       if(ch==3)
        {
            int num;
            system("cls");
            cout<<"\n\n\tPlease Enter The book No. ";
            cin>>num;
            display_spb(num);
        }
       if(ch==4)
       modify_book();
       if(ch==5)
       delete_book();
       if(ch==6)
        exit(0);
    }while(ch!='6');
      
      return 0;
}
//***************************************************************
//    			END OF PROJECT