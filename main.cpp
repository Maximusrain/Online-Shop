/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#include <iostream>
#include <mysql.h>
#include <vector>
#include <iomanip>

#include "DatabaseConnection.h"
#include "menu.h"
#include "Product.h"
#include "User.h"
#include "Cart.h"

///Main function
int main()
{
    int choice=0,id_prod=0;
    DatabaseConnection db{"127.0.0.1", "root", "", "online_shop", 3306, nullptr, 0};            ///Here we create the object DatabaseConnection
    Product p;
    User u, user;
    Cart c;
    MYSQL* connection=db.connectionToDatabase();                                                                                                ///Here we connect to the db and we save the connection

    do
    {
        choice=menu(connection);
        switch (choice)
        {
            case 1:
                std::cout<<"Insert the Id of the product you want to read about: ";
                std::cin>>id_prod;
                if(id_prod<0)
                    std::cout<<"Id not found!!"<<std::endl;
                p.readDescription(connection,id_prod);
                break;
            case 2:
                user.setUser(u.loginUser(connection));
                if(user.getPermission()==1)
                {
                    do
                    {
                        choice=menuOwner(connection,user.getId());
                        switch (choice)
                        {
                            case 1:
                                p.create(connection,user.getId());
                                break;
                            case 2:
                                std::cout<<"Insert the Id of the product you want to read about: ";
                                std::cin>>id_prod;
                                if(id_prod<0)
                                    std::cout<<"Id not found!!"<<std::endl;

                                p.readDescription(connection,id_prod);
                                break;
                            case 3:
                                std::cout<<"Insert the Id of the product you want to update: ";
                                std::cin>>id_prod;
                                if(id_prod<0)
                                    std::cout<<"Id not found!!"<<std::endl;

                                p.update(connection,id_prod);
                                break;
                            case 4:
                                std::cout<<"Insert the Id of the product you want to delete: ";
                                std::cin>>id_prod;
                                if(id_prod<0)
                                    std::cout<<"Id not found!!"<<std::endl;

                                p.deleteProduct(connection,id_prod);
                                break;
                            case 0:
                                std::cout<<"End of the Program.\n";
                                break;
                            default:
                                std::cout<<"Choice not valid!!\n";
                        }
                    }while(choice!=0);
                }else if(user.getPermission()==2)
                {
                    do
                    {
                        choice=menuUser(connection);
                        switch (choice)
                        {
                            case 1:
                                std::cout<<"Insert the Id of the product you want to read about: ";
                                std::cin>>id_prod;
                                if(id_prod<0)
                                    std::cout<<"Id not found!!"<<std::endl;
                                p.readDescription(connection,id_prod);
                                break;
                            case 2:
                                std::cout<<"Insert the Id of the product you want to add to your cart: ";
                                std::cin>>id_prod;
                                if(id_prod<0)
                                    std::cout<<"Id not found!!"<<std::endl;
                                c.addToCart(connection, user.getId(), id_prod);
                                break;
                            case 3:
                                c.read(connection, user.getId());
                                break;
                            case 4:
                                std::cout<<"Insert the Id of the product you want to delete from your cart: ";
                                std::cin>>id_prod;
                                if(id_prod<0)
                                    std::cout<<"Id not found!!"<<std::endl;
                                c.deleteProductFromCart(connection,id_prod,user.getId());
                                break;
                            case 0:
                                std::cout<<"End of the Program.\n";
                                break;
                            default:
                                std::cout<<"Choice not valid!!\n";
                        }
                    } while (choice!=0);
                }else
                    choice=menu(connection);
                break;
            case 3:
                u.create(connection);
                std::cout<<"Account created successfully!!"<<std::endl<<std::endl;
                break;
            case 0:
                std::cout<<"End of the Program.\n";
                break;
            default:
                std::cout<<"Choice not valid!!\n";
        }
    }while (choice!=0);

    return 0;
}

int menu(MYSQL *connection)
{
    Product p;
    int choice;
    std::vector<std::string>prod_col{"Id", "Name", "Brand", "Price", "Category", "Amount"};

    for(int i=0;i<1;i++)
    {
        for(int j=0;j<64;j++)
            std::cout<<"*";

        std::cout<<" Online Shop ";

        for(int j=0;j<63;j++)
            std::cout<<"*";
        std::cout<<std::endl<<std::endl;

        std::cout<<std::left<<std::setw(10)<<prod_col[0]<<std::left<<std::setw(35)<<prod_col[1]<<std::left<<std::setw(15)<<prod_col[2]
        <<std::left<<std::setw(10)<<prod_col[3]<<std::left<<std::setw(35)<<prod_col[4]<<std::left<<std::setw(35)<<prod_col[5]<<std::endl;

        for(int j=0;j<140;j++)
            std::cout<<"-";
        std::cout<<std::endl;
    }
    p.read(connection);

    std::cout<<"1. Read the description of a product\n";
    std::cout<<"2. Login\n";
    std::cout<<"3. Register\n";
    std::cout<<"0. Exit\n\n";
    std::cout<<"Choice: ";
    std::cin>>choice;

    return choice;
}

int menuOwner(MYSQL *connection, int ownerId)
{
    Product p;
    int choice;
    std::vector<std::string>prod_col{"Id", "Name", "Brand", "Price", "Category", "Amount"};

    for(int i=0;i<1;i++)
    {
        for(int j=0;j<64;j++)
            std::cout<<"*";

        std::cout<<" Online Shop ";

        for(int j=0;j<63;j++)
            std::cout<<"*";
        std::cout<<std::endl<<std::endl;

        std::cout<<std::left<<std::setw(10)<<prod_col[0]<<std::left<<std::setw(35)<<prod_col[1]<<std::left<<std::setw(15)<<prod_col[2]
        <<std::left<<std::setw(10)<<prod_col[3]<<std::left<<std::setw(35)<<prod_col[4]<<std::left<<std::setw(35)<<prod_col[5]<<std::endl;

        for(int j=0;j<140;j++)
            std::cout<<"-";
        std::cout<<std::endl;
    }
    p.read(connection, ownerId);

    std::cout<<"1. Add a product\n";
    std::cout<<"2. See a product\n";
    std::cout<<"3. Update a product\n";
    std::cout<<"4. Delete a product\n";
    std::cout<<"0. Exit\n\n";
    std::cout<<"Choice: ";
    std::cin>>choice;

    return choice;
}

int menuUser(MYSQL *connection)
{
    Product p;
    int choice;
    std::vector<std::string>prod_col{"Id", "Name", "Brand", "Price", "Category", "Amount"};

    for(int i=0;i<1;i++)
    {
        for(int j=0;j<64;j++)
            std::cout<<"*";

        std::cout<<" Online Shop ";

        for(int j=0;j<63;j++)
            std::cout<<"*";
        std::cout<<std::endl<<std::endl;

        std::cout<<std::left<<std::setw(10)<<prod_col[0]<<std::left<<std::setw(35)<<prod_col[1]<<std::left<<std::setw(15)<<prod_col[2]
                 <<std::left<<std::setw(10)<<prod_col[3]<<std::left<<std::setw(35)<<prod_col[4]<<std::left<<std::setw(35)<<prod_col[5]<<std::endl;

        for(int j=0;j<140;j++)
            std::cout<<"-";
        std::cout<<std::endl;
    }
    p.read(connection);

    std::cout<<"1. Read the description of a product\n";
    std::cout<<"2. Add a product to your cart\n";
    std::cout<<"3. Check your cart\n";
    std::cout<<"4. Delete a product from your cart\n";
    std::cout<<"0. Exit\n\n";
    std::cout<<"Choice: ";
    std::cin>>choice;

    return choice;
}