/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <mysql.h>          ///MYSQL Library

///Class Product to create object Product
class Product
{
private:
    int _id=0, _category=0, _amount=0, _owner=0;
    double _price=0;
    std::string _name, _description, _brand;

public:
    /** Constructor for class Product
    * @param id id of the user of type int
    * @param name name of the product of type string
    * @param description description of the product of type string
    * @param brand brand of the product of type string
    * @param price price of the product of type double
    * @param category category of the product of type int
    * @param amount amount of the product of type int
    * @param owner owner of the product of type int
    */
    Product(int id, const std::string &name, const std::string &description, const std::string &brand, double price, int category, int amount, int owner);

    /** Default constructor
    */
    Product();


    /** Method to set Product
    * @param id id of the user of type int
    * @param name name of the product of type string
    * @param description description of the product of type string
    * @param brand brand of the product of type string
    * @param price price of the product of type double
    * @param category category of the product of type int
    * @param amount amount of the product of type int
    * @param owner owner of the product of type int
    */
    void setProduct(int id, const std::string &name, const std::string &description, const std::string &brand, double price, int category, int amount, int owner);

    /** Method to set the Product with no parameter
    */
    void setProduct();


    /** Method to retrieve the id of the Product
    * @return id of the product of type int
    */
    int getId();

    /** Method to retrieve the name of the product
    * @return name of the product of type string
    */
    std::string getName();

    /** Method to retrieve the description of the product
    * @return description of the product of type string
    */
    std::string getDescription();

    /** Method to retrieve the brand of the product
    * @return brand of the product of type string
    */
    std::string getBrand();

    /** Method to retrieve the price of the Product
    * @return price of the product of type double
    */
    double getPrice();

    /** Method to retrieve the category of the Product
    * @return category of the product of type int
    */
    int getCategory();

    /** Method to retrieve the amount of the Product
    * @return amount of the product of type int
    */
    int getAmount();

    /** Method to retrieve the owner of the Product
    * @return owner of the product of type int
    */
    int getOwner();


    /** Method will create a row in the table product in the db online_shop
    * @param connection database connection
    * @param ownerId id of the onwer of the product
    */
    void create(MYSQL *connection, int ownerId);

    /** Method will read all product from the table product in the db online_shop
    * @param connection database connection
    */
    void read(MYSQL *connection);

    /** Method will read all product owned by a owner from the table product in the db online_shop
    * @param connection database connection
    * @param id id of the owner
    */
    void read(MYSQL *connection, int id);

    /** Method will retrieve the description of a product from the table product in the db online_shop
    * @param connection database connection
    * @param id id of the product
    */
    void readDescription(MYSQL *connection, int id);

    /** Method will update a product from table product in the db online_shop
    * @param connection database connection
    * @param id id of the product
    */
    void update(MYSQL *connection, int id);

    /** Method will delete a product from the table product in the db online_shop
    * @param connection database connection
    * @param id id of the product
    */
    void deleteProduct(MYSQL *connection, int id);
};

#endif