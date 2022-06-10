/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#include <mysql.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

#include "Cart.h"

Cart::Cart(int id, int user_id)                                                                                         ///Contructor for class Cart
{
    setCart(id,user_id);
}

Cart::Cart()                                                                                                            ///Contructor for class Cart
{
    Cart::setCart();
}

void Cart::setCart(int id, int user_id)                                                                                 ///Method set properties of the object Cart
{
    this->_id=id;
    this->user_id_=user_id;
}

void Cart::setCart()
{
}

int Cart::getId()                                                                                                       ///return the id of the cart
{
    return this->_id;
}

int Cart::getUserId()                                                                                                   ///return the id of the user of the cart
{
    return this->user_id_;
}

void Cart::create(MYSQL *connection, int user_id)                                                                       ///here we create the row inside th table cart
{
    std::string query;

    query="INSERT INTO cart(user) VALUES('"+ std::to_string(user_id) +"')";                                         ///query to insert inside the table cart

    if(mysql_query(connection,query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;                                          ///We check if the query is good or not if not we give error
}

void Cart::addToCart(MYSQL *connection, int user_id, int product_id)
{
    int amount=1, cart_id=0;
    Cart c;
    std::string query;
    MYSQL_RES *result;
    MYSQL_ROW row;

    query="SELECT cart.cart_id FROM cart WHERE "+ std::to_string(user_id) +"=cart.user";                            ///This query will select a cart that a user have

    if(mysql_query(connection,query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;

    result=mysql_store_result(connection);

    if(result->row_count==1)                                                                                            ///if we found one row that means that the cart already exist
    {
        row=mysql_fetch_row(result);
        cart_id=std::stoi(row[0]);
        query="INSERT INTO cart_item(cart, product, amount) VALUES('"+ std::to_string(cart_id) +"', '"+
              std::to_string(product_id) +"', '"+ std::to_string(amount) +"')";                                 ///So here we add to the cart

        if(mysql_query(connection,query.c_str()))
            std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
    }else                                                                                                               ///if we dont have one result that means that the cart doesnt exist so we need to create it
    {
        row=mysql_fetch_row(result);
        c.create(connection,user_id);                                                                                   ///Here we create the cart
        cart_id=std::stoi(row[0]);
        query="INSERT INTO cart_item(cart, product, amount) VALUES('"+ std::to_string(cart_id) +"', '"+
              std::to_string(product_id) +"', '"+ std::to_string(amount) +"')";

        if(mysql_query(connection,query.c_str()))
            std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
    }
    mysql_free_result(result);
}

void Cart::read(MYSQL *connection, int user_id)                                                                         ///Here we read all the item inside a cart
{
    int cart_id=0;
    std::vector<std::string>prod_col{"Id", "Name", "Brand", "Price", "Category", "Amount"};                             ///We use this vector to display what we nne to diplay
    std::string query;
    MYSQL_RES *result;
    MYSQL_ROW row;

    query="SELECT cart.cart_id FROM cart WHERE "+ std::to_string(user_id) +"=cart.user";                            ///Query that select a cart if exist

    if(mysql_query(connection, query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
    result=mysql_store_result(connection);

    if(result->row_count>0)                                                                                             ///If the query have more then one rows that means the cart is filled with some products
    {
        row=mysql_fetch_row(result);
        cart_id=std::stoi(row[0]);

        query="SELECT product.id_product, product.name, product.brand, product.price, category.name, cart_item.amount FROM cart_item INNER JOIN product ON cart_item.product=product.id_product LEFT JOIN category ON product.category=category.category_id WHERE cart_item.cart="+std::to_string(cart_id);             ///with this query we select all field of the table cart and we make some joins

        if(mysql_query(connection, query.c_str()))
            std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
        result=mysql_store_result(connection);

        if(result->row_count>0)
        {
            for(int i=0;i<1;i++)                                                                                        ///In this for we print the products found in the cart
            {
                for(int j=0;j<64;j++)
                    std::cout<<"*";

                std::cout<<" Your cart ";

                for(int j=0;j<65;j++)
                    std::cout<<"*";
                std::cout<<std::endl<<std::endl;

                std::cout << std::left << std::setw(10) << prod_col[0] << std::left << std::setw(35) << prod_col[1]
                          << std::left << std::setw(15) << prod_col[2]
                          << std::left << std::setw(10) << prod_col[3] << std::left << std::setw(35) << prod_col[4]
                          << std::left << std::setw(35) << prod_col[5] << std::endl;

                for (int j = 0; j < 140; j++)
                    std::cout << "-";
                std::cout << std::endl;

                while((row=mysql_fetch_row(result)))
                {
                    std::cout << std::left << std::setw(10) << row[0] << std::left << std::setw(35) << row[1] << std::left
                              << std::setw(15) << row[2]
                              << std::left << std::setw(10) << row[3] << std::left << std::setw(35) << row[4] << std::left
                              << std::setw(35) << row[5] << std::endl;
                }
            }
            std::cout<<std::endl;
        }else
            std::cout<<"Cart is empty!!"<<std::endl;
    }else
        std::cout<<"Cart still not created! Try to add a product to your cart!!"<<std::endl;

    mysql_free_result(result);
}

void Cart::deleteProductFromCart(MYSQL *connection, int product_id, int user_id)                                        ///this method is used to delete items from the cart of a user
{
    int cart_id;
    std::string query;
    MYSQL_RES *result;
    MYSQL_ROW row;

    query="SELECT cart.cart_id FROM cart WHERE "+ std::to_string(user_id) +"=cart.user";                            ///we select the cart

    if(mysql_query(connection, query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
    result=mysql_store_result(connection);

    if(result->row_count==1)                                                                                            ///if the row is just one that means the cart exist
    {
        row=mysql_fetch_row(result);
        cart_id=std::stoi(row[0]);

        query="SELECT cart_item.cart FROM cart_item WHERE "+ std::to_string(cart_id) +"=cart_item.cart";            ///Here we select the cart we need

        if(mysql_query(connection, query.c_str()))
            std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
        result=mysql_store_result(connection);

        if(result->row_count==1)                                                                                        ///If we have just one row that means the product we want to delete exist
        {
            query="DELETE FROM cart_item WHERE product='"+ std::to_string(product_id) +"' AND cart='"+ std::to_string(cart_id) +"'";            ///we delete the product

            if(mysql_query(connection, query.c_str()))
                std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
        }else
            std::cout<<"Cart is empty!!"<<std::endl;
    }else
        std::cout<<"Cart still not created! Try to add a product to your cart!!"<<std::endl;

    mysql_free_result(result);
}