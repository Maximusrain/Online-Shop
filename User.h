/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#ifndef USER_H
#define USER_H

#include <iostream>
#include <mysql.h>        ///MySQL library

///Class User to create object User
class User
{
private:
    int _id=0, _permission=0;
    std::string _username, _email, _password;

public:
    /** Constructor for class User
    * @param id id of the user of type int
    * @param username username of the user of type string
    * @param email email of the user of type string
    * @param password password of the user of type string
    * @param permission permission of the user of type int
    */
    User(int id, const std::string &username, const std::string &email, const std::string &password, int permission);

    /** Copy constructor for class User
    * @param u object of type User
    */
    User(User &u);

    /** Default constructor
    */
    User();


    /** Method to set the user
    * @param id id of the user of type int
    * @param username username of the user of type string
    * @param email email of the user of type string
    * @param password password of the user of type string
    * @param permission permission of the user of type int
    */
    void setUser(int id, const std::string &username, const std::string &email, const std::string &password, int permission);

    /** Method to set the user
    * @param u object of type User
    */
    void setUser(User u);

    /** Method to set the user with no parameter
    */
    void setUser();


    /** Method to retrieve the id of the user
    * @return id of the user of type int
    */
    int getId();

    /** Method to retrieve the username of the user
    * @return username of the user of type string
    */
    std::string getUserame();

    /** Method to retrieve the email of the user
    * @return email of the user of type string
    */
    std::string getEmail();

    /** Method to retrieve the password of the user
    * @return password of the user of type string
    */
    std::string getPassword();

    /** Method to retrieve the permission id of the user
    * @return permission id of the user of type int
    */
    int getPermission();


    /** Method will create a row in the table user in the db online_shop
    * @param connection database connection
    */
    void create(MYSQL *connection);

    /** Method to login in the application
    * @param connection database connection
    * @return object of type "User"
    */
    User loginUser(MYSQL *connection);
};

#endif