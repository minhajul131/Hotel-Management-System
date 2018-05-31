#include<iostream>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;


class hotel {

    private:
        int room_no;
        char name[40];
        char phn_no[20];
        char address[50];
        char entry_date[20];

    public:


            ///header function;
    void heading() {

            cout<<"\n\n";
            cout<<"\t\t\t\t\t@@-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-##";
            cout<<"\n";
            cout<<"\n\t\t\t\t\t\tHotel Management System\n";
            cout<<"\n";
            cout<<"\t\t\t\t\t##=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=@@";

    }


            ///room booking function;
    void bookRoom() {

            int x, flag;

            ofstream fout("Hotel.txt",ios::app);

            cout<<"\n\tEnter room number: ";
            cin>>x;

            flag=check(x);

            if(flag)
                cout<<"\n\tSorry..... The room is already booked";

            else {

                room_no=x;

                cin.ignore();
                cout<<"\n\tEnter your name: ";
                gets(name);

                cout<<"\tEnter your mobile number: ";
                gets(phn_no);

                cout<<"\tEnter your Address: ";
                gets(address);

                cout<<"\tEnter the date of entry: ";
                gets(entry_date);

                fout.write((char*)this, sizeof(*this));

                fout.close();
                cout<<"\tRoom Booked"<<endl;
            }

    }


            ///cheak room number;
    int check (int x) {

        int flag=0;

        ifstream fin("Hotel.txt",ios::in);

        while(!fin.eof()) {

            fin.read((char*)this,sizeof(*this));

            if(room_no==x){

                flag=1;
                break;
            }
        }
        fin.close();
        return(flag);
    }



            ///show booked room
    void showRoomDetail() {

        ifstream fin("Hotel.txt",ios::in);
        fin.read((char*)this,sizeof(*this));

        while(!fin.eof()) {

            cout<<"\n"<<"\tRoom Number  : "<<room_no;
            cout<<"\n"<<"\tName         : "<<name;
            cout<<"\n"<<"\tMobile Number: "<<phn_no;
            cout<<"\n"<<"\tAddress      : "<<address;
            cout<<"\n"<<"\tEntry Date   : "<<entry_date<<endl;

            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }



            ///edit customer detail
    void edit_detail(int a) {

        long pos,flag=0;
        fstream file("Hotel.txt",ios::in|ios::out|ios::binary);

        while(!file.eof()) {

            pos=file.tellg();

            file.read((char*)this,sizeof(*this));

            if(room_no==a) {

                cout<<"\n\t Enter New Details";
                cin.ignore();
                cout<<"\n\t Enter your name: ";
                gets(name);

                cout<<"\t Enter your mobile number: ";
                gets(phn_no);

                cout<<"\t Enter your Address: ";
                gets(address);

                cout<<"\t Enter the date of entry: ";
                gets(entry_date);


                file.seekg(pos);
                file.write((char*)this,sizeof(*this));
                cout<<"\n Record is Edited";
                flag=1;
                break;
            }
        }

        if(flag==0)
            cout<<"\n Sorry Room number not found or vacant...."<<endl;

        file.close();
    }




            ///delete customers record
    int delete_record (int roomNum) {

        ifstream fin;
        ofstream fout;

        fin.open("Hotel.txt", ios::in| ios::binary);

        if (!fin) {
            cout << "File Not Found\n";
        }
        else{

            fout.open("temp.txt", ios::out| ios::binary);
            fin.read((char*)this, sizeof(*this));

            while(!fin.eof()) {

                if(room_no != roomNum) /// when those title matched then it will return '0'

                    fout.write((char*)this, sizeof(*this));

                    fin.read((char*)this, sizeof(*this));
                }
            fin.close();
            fout.close();
            remove("Hotel.txt");
            rename("temp.txt","Hotel.txt");

        }
        cout<<"\tInformation deleted";
    }

};

///functions
int option() {

    int choice;

    cout<<"\n\n\n\n";
    cout<<"\n\t\t\t\t      # Menu #";
    cout<<"\n\t\t\t\t  ------------------- ";
    cout<<"\n\t\t\t\t| 1. Book a Room      |";
    cout<<"\n\t\t\t\t| 2. View Booked Room |";
    cout<<"\n\t\t\t\t| 3. Edit Detail      |";
    cout<<"\n\t\t\t\t| 4. Delete Room      |";
    cout<<"\n\t\t\t\t| 5. Exit             |";
    cout<<"\n\t\t\t\t  ------------------- ";

    cout<<"\n\n\t\t\t\t\tEnter your choice... ";
    cin>>choice;

    return choice;
}


int main() {

    hotel h;
    h.heading();
    system ("color 3");
    int a;

    while (1) {

        switch(option()) {

            case 1:
                h.bookRoom();
                break;

            case 2:
                h.showRoomDetail();
                break;

            case 3:
                cout<<"\n\t\t\tEnter Room number which you want to edit: ";
                cin>>a;
                h.edit_detail (a);
                break;
            case 4:
                cout<<"\n\t\t\tEnter Room number which you want to delete: ";
                cin>>a;
                h.delete_record (a);
               // cout<<"information deleted";
                break;

            case 5:
                exit (0);

            default:{

            cout<<"\n\t\t\t\tPress any key to continue!!"<<endl;
            }

        }
    }
    return 0;
}
