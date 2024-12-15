#include "inventory.cpp"

class billItem{
    int Bitemid;
    char Btype[30];
    char Bname[50];
    float Bprice;
    int Bquantity;
    float Bdiscount;
    float Btax;
    float Bdiscount_percent;
    float Btax_percent;
    float Btotal;
    friend class bill;
public:
    billItem(char NAME[50],char TYPE[50],int ID,float PRICE,float DISCOUNT_PERCENT,float TAX_PERCENT){
        strcpy(Bname,NAME);
        strcpy(Btype,TYPE);
        Bitemid = ID;
        Bdiscount_percent = DISCOUNT_PERCENT;
        Btax_percent = TAX_PERCENT;
        setQuantity();
        Bprice = Bquantity*PRICE;
        Bdiscount = calculate_discount();
        Btax = calculate_tax();
        Btotal = Bprice+Btax-Bdiscount;
        Bprice = PRICE;
    }
    void setQuantity(){
        cout<<"Enter quantity of item: ";
        cin>>Bquantity;
    };
    float calculate_discount(){
        return Bprice*Bdiscount_percent/(float)100;
    }
    float calculate_tax(){
        return Bprice*Btax_percent/(float)100;
    }
};

class bill{
    vector<billItem> Items;
    char buyer[50];
    long long mob;
    fstream file;
public:
    bill(){}
    bill(inventory &stock){
        system("cls");
        cout<<"Enter the name of recipient: ";
        cin>>buyer;
        cout<<"Enter phone no: ";
        cin>>mob;
        menuBill(stock);
    }
    ~bill(){}
    void menuBill(inventory &stock){
        cout<<"1. Add items to bill"<<endl;
        cout<<"2. Remove an item from bill"<<endl;
        cout<<"3. Show bill"<<endl;
        cout<<"4. Generate bill"<<endl;
        cout<<"0. Cancel Bill"<<endl;
        cout<<"Enter your response: ";
        int n;
        cin>>n;
        switch (n)
        {
        case 1:
            addItem(stock);
            system("cls");
            menuBill(stock);
            break;
        case 2:
            removeItem(stock);
            system("cls");
            menuBill(stock);
            break;
        case 3:
            showBill();
            system("cls");
            menuBill(stock);
            break;
        case 4:
            generateBill();
            system("cls");
            menuBill(stock);
            break;
        case 0:
            cancelBill(stock);
            throw -1;
            break;
        default:
            break;
        }

    }
    void addItem(inventory &stock){
        system("cls");
        cout<<"1. Add Item by Name"<<endl;
        cout<<"2. Add Item by Id"<<endl;
        cout<<"3. Show stock"<<endl;
        cout<<"0. Back"<<endl;
        cout<<"Enter your response: ";
        int n;
        cin>>n;
        try{    
            switch (n)
                {
                case 1:
                    {cout<<"Enter name of item: ";
                    char str[50];
                    cin>>str;
                    int i = stock.searchByName(str);
                    if(i==-1)throw("Item does not exists");
                    stock.products[i]->display();
                    billItem *temp = new billItem(stock.products[i]->name,stock.products[i]->type,stock.products[i]->itemid,stock.products[i]->price,stock.products[i]->getDiscount_percent(),stock.products[i]->getTax_percent());
                    if(stock.products[i]->quantity < temp->Bquantity)throw("Requested quantity is not available");
                    stock.products[i]->quantity -= temp->Bquantity;
                    cout<<"Item added successfully"<<endl;
                    Items.push_back(*temp);
                    break;}
                case 2:
                    {cout<<"Enter id of item: ";
                    int id;
                    cin>>id;
                    int i = stock.searchByid(id);
                    if(i==-1)throw("Item does not exists");
                    stock.products[i]->display();
                    billItem *temp = new billItem(stock.products[i]->name,stock.products[i]->type,stock.products[i]->itemid,stock.products[i]->price,stock.products[i]->getDiscount_percent(),stock.products[i]->getTax_percent());
                    if(stock.products[i]->quantity < temp->Bquantity)throw("Requested quantity is not available");
                    stock.products[i]->quantity -= temp->Bquantity;
                    cout<<"Item added successfully"<<endl;
                    Items.push_back(*temp);
                    break;}
                case 3:
                    stock.show();

                    break;
                case 0:
                    break;
                default:
                    break;
            }
        }catch(const char err[]){
            cout<<err<<endl;
        }catch(...){
            cout<<"Some error occured while adding the item"<<endl;
        }
        cout<<"Enter anything: ";
        string a;
        cin>>a;
        cin.ignore();
    }

    int searchById(int id){
        int i = 0;
        for(;i<Items.size();i++){
            if(Items[i].Bitemid == id)return i;
        }
        return -1;
    };
    int searchByName(char name[50]){
        int i = 0;
        for(;i<Items.size();i++){
            if(strcmpi(Items[i].Bname,name)==0)return i;
        }
        return -1;
    };
    void removeItem(inventory &stock){
        system("cls");
        cout<<"1. Remove by name"<<endl;
        cout<<"2. Remove by Product Id"<<endl;
        cout<<"0. Back"<<endl;
        cout<<"Enter your response: ";
        int n;
        cin>>n;
        try{
            int i;
            int j;
            switch (n)
            {
            case 1:
                char name[50];
                cout<<"\nEnter the name of Product: ";
                cin>>name;
                i = searchByName(name);
                j = stock.searchByName(name);
                if(-1 == i)throw "Product does not exists";
                break;
            case 2:
                cout<<"\nEnter the id of Product: ";
                int id;
                cin>>id; 
                i = searchById(id);
                j = stock.searchByid(id);
                if(-1 == i)throw "Product does not exists";
                break;
            case 0:
                return;
                break;

            default:
                return;
                break;
            }
            stock.products[j]->quantity+=Items[i].Bquantity;
            Items.erase(Items.begin()+i);
            cout<<"Item removed successfully"<<endl;
        }
        catch(char const err[]){
            cout<<err<<endl;
            return;
        }
        catch(...){
            cout<<"some error occured while removing the product\n";
            return;
        }
        cout<<"Enter anything: ";
        string a;
        cin>>a;
        cin.ignore();
    }

    void generateBill(){
        system("cls");
        showBill(1);
        ofstream outFile;
        outFile.open(buyer);
        float totalPrice = 0;
        outFile<<std::right<<setw(85)<<"SMART MART BILL"<<std::left<<endl;
        outFile<<"Name: "<<buyer<<endl;
        outFile<<"Phone: "<<mob<<endl;
        
        outFile<<"+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------+"<<endl;
        outFile<<"|"<<std::left<<setw(20)<<"Name"<<"|"<<setw(15)<<"Product Id"<<"|"<<setw(20)<<"Type"<<"|"<<setw(15)<<"Price"<<"|"<<setw(15)<<"Quantity"<<"|"<<setw(15)<<"Tax(%)"<<"|"<<setw(15)<<"Tax"<<"|"<<setw(15)<<"Discount(%)"<<"|"<<setw(15)<<"Discount"<<"|"<<setw(15)<<"Final Price"<<"|"<<endl;
        outFile<<"+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------+"<<endl;
        for(auto it:Items){
            outFile<<"|"<<std::left<<setw(20)<<it.Bname<<"|"<<setw(15)<<it.Bitemid<<"|"<<setw(20)<<it.Btype<<"|"<<setw(15)<<it.Bprice<<"|"<<setw(15)<<it.Bquantity<<"|"<<setw(15)<<it.Btax_percent<<"|"<<setw(15)<<it.Btax<<"|"<<setw(15)<<it.Bdiscount_percent<<"|"<<setw(15)<<it.Bdiscount<<"|"<<setw(15)<<it.Btotal<<"|"<<endl;
            totalPrice+=it.Btotal;
        }
        outFile<<"+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------+"<<endl;
        
        outFile<<"Total"<<std::right<<setw(158)<<totalPrice<<std::left<<endl;
        cout<<"\t\t\tBILL GENERATED\n"<<endl;
        throw 1;
    }

    void cancelBill(inventory &stock){
        for(int i = 0;i<Items.size();i++){
            int id = Items[i].Bitemid;
            int j = stock.searchByid(id);
            stock.products[j]->quantity += Items[i].Bquantity;
        }
        Items.clear();
    }

    void showBill(int i = 0){
        float totalPrice = 0;
        cout<<"Name: "<<buyer<<endl;
        cout<<"Phone: "<<mob<<endl;
        
        cout<<"+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------+"<<endl;
        cout<<"|"<<std::left<<setw(20)<<"Name"<<"|"<<setw(15)<<"Product Id"<<"|"<<setw(20)<<"Type"<<"|"<<setw(15)<<"Price"<<"|"<<setw(15)<<"Quantity"<<"|"<<setw(15)<<"Tax(%)"<<"|"<<setw(15)<<"Tax"<<"|"<<setw(15)<<"Discount(%)"<<"|"<<setw(15)<<"Discount"<<"|"<<setw(15)<<"Final Price"<<"|"<<endl;
        cout<<"+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------+"<<endl;
        for(auto it:Items){
            cout<<"|"<<std::left<<setw(20)<<it.Bname<<"|"<<setw(15)<<it.Bitemid<<"|"<<setw(20)<<it.Btype<<"|"<<setw(15)<<it.Bprice<<"|"<<setw(15)<<it.Bquantity<<"|"<<setw(15)<<it.Btax_percent<<"|"<<setw(15)<<it.Btax<<"|"<<setw(15)<<it.Bdiscount_percent<<"|"<<setw(15)<<it.Bdiscount<<"|"<<setw(15)<<it.Btotal<<"|"<<endl;
            totalPrice+=it.Btotal;
        }
        cout<<"+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------+"<<endl;
        
        cout<<"Total"<<std::right<<setw(158)<<totalPrice<<std::left<<endl;
        if(i==0)cout<<"Enter anything: ";
        else cout<<"Generate Bill "<<endl;
        string a;
        cin>>a;
        cin.ignore();
    }
};