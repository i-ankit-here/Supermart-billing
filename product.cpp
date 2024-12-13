#include "iostream"
#include "iomanip"
using namespace std;
class item{
protected:
    int itemid;
    char name[50];
    float price;
    int quantity;
    float discount;
    float tax;
public:
    item(){
        setName();
        setPrice();
        setQuantity();
    };
    void setName(){
        cout<<"Enter name of item: ";
        cin>>name;
    };
    void setPrice(){
        cout<<"Enter price of item: ";
        cin>>price;
    };
    void setQuantity(){
        cout<<"Enter quantity of item: ";
        cin>>quantity;
    };

    virtual void display() = 0;
    virtual float calculate_discount() = 0;
    virtual float calculate_tax() = 0;

};

class electronic:public item{
    float static tax_percent;
    float static discount_percent;
public:
    electronic():item(){
        tax = calculate_tax();
        discount = calculate_discount();
    }
    void display(){
        cout<<"------------------------------------------------------------"<<endl;
        cout<<setw(25)<<"Name of item: "<<name<<endl;
        cout<<setw(25)<<"Price of item: "<<price<<endl;
        cout<<setw(25)<<"Quantity of item: "<<quantity<<endl;
        cout<<setw(25)<<"Tax(%): "<<tax_percent<<endl;
        cout<<setw(25)<<"Discout(%): "<<discount_percent<<endl;
        cout<<setw(25)<<"Final Price of item: "<<price+tax-discount<<endl;
        cout<<"------------------------------------------------------------"<<endl;
    }
    float calculate_discount(){
        return price*discount_percent/(float)100;
    }
    float calculate_tax(){
        return price*tax_percent/(float)100;
    }
};

float electronic::tax_percent = 12;
float electronic::discount_percent = 10;

class grocery:public item{
    float static tax_percent;
    float static discount_percent;
public:
    grocery():item(){
        tax = calculate_tax();
        discount = calculate_discount();
    }
    void display(){
        cout<<"Name of item: "<<name<<setw(40)<<endl;
        cout<<"Price of item: "<<price<<endl;
        cout<<"Quantity of item: "<<quantity<<endl;
        cout<<"Tax(%): "<<tax_percent<<endl;
        cout<<"Discout(%): "<<discount_percent<<endl;
        cout<<"Final Price of item: "<<price+tax-discount<<endl;
    }
    float calculate_discount(){
        return price*discount_percent/(float)100;
    }
    float calculate_tax(){
        return price*tax_percent/(float)100;
    }
};

float grocery::tax_percent = 12;
float grocery::discount_percent = 5;