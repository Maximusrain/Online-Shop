/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#ifndef CART_H
#define CART_H

#include <mysql.h>

///Class Cart to create object cart
class Cart
{
private:
    int _id=0, user_id_=0;

public:
    /** Constructor for class Cart
    * @param id id of the user of type int
    * @param user_id id of the user of type int
    */
    Cart(int id, int user_id);

    /** Default constructor
     */
    Cart();


    /** Setter for class Cart
    * @param id id of the user of type int
    * @param user_id id of the user of type int
    */
    void setCart(int id, int user_id);

    /** Setter for class Cart
    */
    void setCart();


    /** Method to get the id of the cart
    * @return cart id of type int
    */
    int getId();

    /** Method to get the id of the user
    * @return cart id of the use of type int
    */
    int getUserId();


    /** Method will create a row in the table Cart in the db online_shop
    * @param connection database connection
    * @param user_id id of the user
    */
    void create(MYSQL *connection, int user_id);

    /** Method will add an item to the cart of a user
    * @param connection database connection
    * @param user_id id of the user
    * @param product_id id of the product we want to add
    */
    void addToCart(MYSQL *connection, int user_id, int product_id);

    /** Method will read all the item of a cart of a user
    * @param connection database connection
    * @param user_id id of the user
    */
    void read(MYSQL *connection, int user_id);

    /** Method will remove an item from the cart of a user
    * @param connection database connection
    * @param user_id id of the user
    * @param product_id id of the product we want to delete
    */
    void deleteProductFromCart(MYSQL *connection, int product_id, int user_id);
};

#endif
