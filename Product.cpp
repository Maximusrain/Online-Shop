/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#include <mysql.h>          ///MYSQL Library
#include <iomanip>

#include "Product.h"

Product::Product(int id, const std::string &name, const std::string &description, const std::string &brand, double price, int category, int amount, int owner)                    ///Constructor of class Product
{
    setProduct(id, name, description, brand, price, category, amount, owner);                                                                                                     ///Method to set the product
}

Product::Product()                                                                                                                                                                ///Deafault constructor
{
    setProduct();                                                                                                                                                                 ///Method the set the product with no parameters
}

void Product::setProduct(int id, const std::string &name, const std::string &description, const std::string &brand, double price, int category, int amount, int owner)           ///Here we set the object Product
{
    this->_id=id;
    this->_name=name;
    this->_description=description;
    this->_brand=brand;
    this->_price=price;
    this->_category=category;
    this->_amount=amount;
    this->_owner=owner;
}

void Product::setProduct()                                                                                                                                                      ///Here we set the object Product with no parameter
{
}

int Product::getId()                                                                                                                                                           ///Here we retrieve the id of the product
{
    return this->_id;
}

std::string Product::getName()                                                                                                                                                ///Here we retrieve the name of the product
{
    return this->_name;
}

std::string Product::getDescription()                                                                                                                                        ///Here we retrieve the description of the product
{
    return this->_description;
}

std::string Product::getBrand()                                                                                                                                             ///Here we retrieve the brand of the product
{
    return this->_brand;
}

double Product::getPrice()                                                                                                                                                 ///Here we retrieve the price of the product
{
    return this->_price;
}

int Product::getCategory()                                                                                                                                                 ///Here we retrieve the category of the product
{
    return this->_category;
}

int Product::getAmount()                                                                                                                                                  ///Here we retrieve the amount of the product
{
    return this->_amount;
}

int Product::getOwner()                                                                                                                                                  ///Here we retrieve the owner of the product
{
    return this->_owner;
}

void Product::create(MYSQL *connection, int ownerId)                                                                    ///This method will create a row in the table product
{
    int category=0, amount=0;
    double price=0;
    std::string name, description, brand, query;

    std::cout<<"Insert the name of the product: "<<std::endl;
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout<<"Insert a description: "<<std::endl;
    std::getline(std::cin, description);
    std::cout<<"Insert the brand of the product: "<<std::endl;
    std::getline(std::cin, brand);
    std::cout<<"Insert price value: "<<std::endl;
    std::cin>>price;
    std::cout<<"Insert category: "<<std::endl;
    std::cin>>category;
    std::cout<<"Insert amount: "<<std::endl;
    std::cin>>amount;

    query="INSERT INTO product(name, description, brand, price, category, amount, owner) VALUES('"+
            name +"', '"+ description +"', '"+ brand +"', '"+ std::to_string(price) +"', '"+ std::to_string(category) +"', '"+
            std::to_string(amount) +"', '"+ std::to_string(ownerId)+"')";                                       ///This is the query that will be executed to insert the product in the table product

    if(mysql_query(connection,query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;                                          ///If the query is wrong here we give back error state
}

void Product::read(MYSQL *connection)                                                                                   ///Retrieve from the table product al products
{
    MYSQL_RES *result;                                                                                                  ///Here we store the result of the query
    MYSQL_ROW row;                                                                                                      ///Here we store the rows from the table

    if(mysql_query(connection, "SELECT product.id_product, product.name, product.brand, product.price, category.name, product.amount FROM product LEFT JOIN category ON product.category=category.category_id"))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;                                          ///we execute the query if its wrong we gave error
    else
        result=mysql_store_result(connection);                                                                    ///Here we store the result of the query

    if(result->row_count>0)                                                                                             ///If we have more then 1 rows means products are in the tbale
    {
        while((row=mysql_fetch_row(result)))                                                                            ///Here we fetch the result in the rows and we print then untill they are not anymore rows
        {
            std::cout<<std::left<<std::setw(10)<<row[0]<<std::left<<std::setw(35)<<row[1]<<std::left<<std::setw(15)<<row[2]
            <<std::left<<std::setw(10)<<row[3]<<std::left<<std::setw(35)<<row[4]<<std::left<<std::setw(35)<<row[5]<<std::endl;
        }
        std::cout<<std::endl;
    }
    mysql_free_result(result);                                                                                          ///We remove the result from the memory
}

void Product::read(MYSQL *connection, int id)
{
    std::string query="SELECT product.id_product, product.name, product.brand, product.price, category.name, product.amount FROM product LEFT JOIN category ON product.category=category.category_id WHERE "+
            std::to_string(id) +"=product.owner";                                                                   ///This query retrieve product from the owner id
    MYSQL_RES *result;                                                                                                  ///Here we store the result of the query
    MYSQL_ROW row;                                                                                                      ///Here we store the rows from the table

    if(mysql_query(connection, query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
    else
        result=mysql_store_result(connection);

    if(result->row_count>0)
    {
        while((row=mysql_fetch_row(result)))
        {
            std::cout<<std::left<<std::setw(10)<<row[0]<<std::left<<std::setw(35)<<row[1]<<std::left<<std::setw(15)<<row[2]
            <<std::left<<std::setw(10)<<row[3]<<std::left<<std::setw(35)<<row[4]<<std::left<<std::setw(35)<<row[5]<<std::endl;
        }
        std::cout<<std::endl;
    }
    mysql_free_result(result);
}

void Product::readDescription(MYSQL *connection, int id)
{
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::string query="SELECT product.description FROM product WHERE "+ std::to_string(id) +"=product.id_product";  ///This query retrieve the description from the id of the product

    if(mysql_query(connection, query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;

    result=mysql_store_result(connection);

    if(result->row_count>0)
    {
        while((row=mysql_fetch_row(result)))
        {
            std::cout<<row[0]<<std::endl;                                                                               ///We print the description of the product
        }
        std::cout<<std::endl;
    }else
        std::cout<<"Product not found!!"<<std::endl;

    mysql_free_result(result);
}

void Product::update(MYSQL *connection, int id)                                                                         ///This method will update a product that a owner own fro the id of the product
{
    int category=0, amount=0;
    double price=0;
    std::string name, description, brand, query;

    std::cout<<"Insert the new name of the product: "<<std::endl;
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout<<"Insert a new description: "<<std::endl;
    std::getline(std::cin, description);
    std::cout<<"Insert the new brand of the product: "<<std::endl;
    std::getline(std::cin, brand);
    std::cout<<"Insert new price value: "<<std::endl;
    std::cin>>price;
    std::cout<<"Insert new category: "<<std::endl;
    std::cin>>category;
    std::cout<<"Insert new amount: "<<std::endl;
    std::cin>>amount;

    query="UPDATE product SET name='"+ name +"', description='"+ description +"', brand='"+ brand +"', price='"+
            std::to_string(price) +"', category='"+ std::to_string(category) +"', amount='"+ std::to_string(amount) +"' WHERE product.id_product="+ std::to_string(id);  ///This query update the product

    if(mysql_query(connection, query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
}

void Product::deleteProduct(MYSQL *connection, int id)                                                                  ///This method will delete a product in the table product
{
    std::string query="DELETE FROM product WHERE id_product='"+ std::to_string(id) +"'";

    if(mysql_query(connection, query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;
}