#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <map>


using namespace std;

class online_shopping
{
private:
    map<string,float> item;  //item_list with price
    map<string,pair<int,float> > cart; //cart item with quantity and price
    FILE *fp; //to open database i.e. items.txt
    char temp[100]; //temporary string
    int qty; //for scanning qty. of an item
    float price; //for scanning price of item from items.txt
public:
    online_shopping() //constructor : opens items.txt , reads names of items and prices and inserts in map<string,float> item
    {
        fp=fopen("items.txt","r");
        if(!fp) //if items.txt not present,exit by prompting this message
        {
            cout<<"Unable to connect to database,Please place items.txt in the same folder where this c++ file is present.";
        }
        else
        {
            while(fscanf(fp,"%s %f\n",temp,&price)!=EOF) //read item name and price one by one
            {
                    item.insert(make_pair(temp,price)); //insert item and price in map<string,float> item
            }
        }
    }
    void display_items() //displays list of items present in map<string,float> item
    {
        map<string,float>::iterator it;
        cout<<"\n\nITEM NAME:       "<<"PRICE\n";
        cout<<"___________________________________\n";
        for(it=item.begin();it!=item.end();it++)
            cout<<it->first<<"              "<<it->second<<endl; //it->first - item_name it-second - price

        cout<<"\n";
    }
    void display_menu() //displays menu for the user
    {
        cout<<"\n\nKEYWORD                  :"<<"ACTION"<<endl;
        cout<<"_____________________________________________\n";
        cout<<"disp_l                   :"<<"Display list of items in the website"<<endl;
        cout<<"add_c                    :"<<"Add an item to cart"<<endl;
        cout<<"disp_c                   :"<<"Display contents of cart"<<endl;
        cout<<"del_c                    :"<<"Delete an item from cart"<<endl;
        cout<<"exit                     :"<<"end shopping and exit"<<endl<<endl;
    }
    void add_item() //adds item to map<string,pair<int,float> > cart
    {
        cout<<"Enter item name : "; //enter item name
        scanf("%s",temp);
        map<string,float>::iterator it=item.find(temp);
        map<string,pair<int,float> >::iterator it1=cart.find(temp);
        if(it==item.end()) //if there is no such item in the website
        {
            cout<<"Looks like you entered a wrong item-name"<<endl; //prompt wrong item-name entered and return
            return;
        }
        cout<<"Enter quantity : "; //if item-name correct,enter its quantity
        scanf("%d",&qty);
        if(it1!=cart.end()) //if cart already contains this item,just update its quantity and price
        {
            (it1->second).first+=qty; //update quanityt
            (it1->second).second+=qty*(it->second); //update total price
        }
        else cart.insert(make_pair(temp,make_pair(qty,qty*it->second))); //if not already present,then insert the item in cart
        cout<<"\n\nItem added to cart successfully\n\n";
    }
    void display_cart() //display items of cart
    {
        cout<<"\n\n";
        map<string,pair<int,float> >::iterator it;
        for(it=cart.begin();it!=cart.end();it++)
        {
            cout<<it->first<<"      "<<it->second.first<<"      "<<it->second.second<<endl; //it->first=itemname it->second.first=qty   it->second.second=total price
        }
        cout<<"\n";
    }
    void delete_cart()  //delete item from cart
    {
        display_cart();
        cout<<"Enter item to delete : ";
        scanf("%s",temp);
        map<string,pair<int,float> >::iterator it=cart.find(temp); //first search for the item
        if(it==cart.end()) //if not found,prompt this message
        {
            cout<<"Item not in your cart\n\n";
            return;
        }
        else
        {
            cout<<"Enter quantity to delete : "; //else enter quantity
            cin>>qty;
            if(qty > it->second.first) //if quantity entered is more than what is present in cart,prompt this message
            {
                cout<<"Wrong quantity entered\n\n";
                return;
            }
            it->second.first-=qty; //else decrease the quantity
            if(it->second.first == 0) //if quantity left after removing items is 0,remove that item from the cart
                cart.erase(it);

            cout<<"Item deleted successfully\n\n";
        }
    }
    void end_shopping() //calculate the bill and display it to the user
    {
        map<string,pair<int,float> >::iterator it;
        float total=0; //total amount to be paid
        cout<<"ITEM     "<<"PRICE       "<<"TOTAL\n";
        cout<<"___________________________________\n";
        for(it=cart.begin();it!=cart.end();it++)
            {
                cout<<it->first<<"      "<<it->second.first<<"          "<<it->second.second<<endl<<endl; //it->first=itemname it->second.first=quantity it->second.second=subtotal
                total+=it->second.second;
            }
            cout<<endl<<endl;
            cout<<"TOTAL:  "<<total<<endl<<endl;
    }
    void start_shopping()
    {
        display_menu(); //call display_menu()
        while(true)
        {
        scanf("%s",temp);
        if(strcmp(temp,"disp_l")==0)
            display_items(); //call display_items()
        else if(strcmp(temp,"add_c")==0)
            add_item(); //call add_item()
        else if(strcmp(temp,"disp_c")==0)
            display_cart(); //call display_cart()
        else if(strcmp(temp,"del_c")==0)
            delete_cart(); //call delete_cart()
        else if(strcmp(temp,"exit")==0)
            {
            end_shopping(); //call end_shopping()
            break;
            }
        else cout<<"wrong choice"<<endl<<endl; //wrong choice entered
        }
    }

};

int main()
{
    online_shopping s; //object of online_shopping class;constructor is called here and database("items.txt") is loaded
    s.start_shopping(); //start shopping
}

