/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#include <mysql.h>          ///MYSQL Library
#include <string>
#include <iostream>

#include "User.h"

User::User(int id, const std::string &username, const std::string &email, const std::string &password, int permission)  ///Constructor for class User
{
    setUser(id, username, email, password, permission);                                                                 ///Setter to set parameters of the object
}

User::User()                                                                                                            ///Deafult constructor for class User
{
    setUser();                                                                                                          ///Setter to set parameters of the object
}

User::User(User &u)                                                                                                     ///Copy constructor for class User
{
    setUser(u);                                                                                                         ///Setter to set parameters of the object
}

void User::setUser(int id, const std::string &username, const std::string &email, const std::string &password, int permission)  ///Setter for the object of type User
{
    this->_id=id;
    this->_username=username;
    this->_email=email;
    this->_password=password;
    this->_permission=permission;
}

void User::setUser(User u)                                                                                              ///Setter for the object of type User from another object of type User
{
    this->_id=u._id;
    this->_username=u._username;
    this->_email=u._email;
    this->_password=u._password;
    this->_permission=u._permission;
}

void User::setUser()                                                                                                    ///Setter for the object of type User default
{
}

int User::getId()                                                                                                       ///Getter for the id of the user
{
    return this->_id;
}

std::string User::getUserame()                                                                                          ///Getter for the username of the user
{
    return this->_username;
}

std::string User::getEmail()                                                                                            ///Getter for the email of the user
{
    return this->_email;
}

std::string User::getPassword()                                                                                         ///Getter for the password of the user
{
    return this->_password;
}

int User::getPermission()                                                                                               ///Getter for the permission of the user
{
    return this->_permission;
}

void User::create(MYSQL *connection)                                                                                    ///Method to create a row in the table user on the db online_shop
{
    int permission=2;                                                                                                   ///Permission is automatically to 2 that equals to normal permission
    std::string username, email, password, query;                                                                       ///The variable of type string query is used to store the query to execute in the db

    std::cout<<"Insert the username: "<<std::endl;
    std::cin.ignore();
    std::getline(std::cin, username);
    std::cout<<"Insert email: "<<std::endl;
    std::cin>>email;
    std::cout<<"Create password: "<<std::endl;
    std::cin.ignore();
    std::getline(std::cin, password);

    query="INSERT INTO user(username, email, password, permission) VALUES('"+ username +"', '"+ email +"', '"+ password +"', '"+ std::to_string(permission) +"')";      ///This query is used to create a row in the user table on the db online_shop

    if(mysql_query(connection,query.c_str()))
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;                                          ///If the query fails this will return the type of the error
}

User User::loginUser(MYSQL *connection)                                                                                 ///Method to login in in the system
{
    User user;
    std::string username, password, query;                                                                              ///The variable of type string query is used to store the query to execute in the db
    MYSQL_RES *result;                                                                                                  ///This pointer is pointing the result of the query
    MYSQL_ROW row;

    std::cout<<"Insert your username: "<<std::endl;
    std::cin.ignore();
    std::getline(std::cin, username);
    std::cout<<"Insert your password:"<<std::endl;
    std::getline(std::cin, password);

    query="SELECT * FROM user WHERE username='"+ username +"'";                                                         ///This query return a user from the table user in the db online_shop

    if(mysql_query(connection,query.c_str()))                                                                  ///Here we execute the query
        std::cout<<"Query failed!!"<<mysql_error(connection)<<std::endl;                                          ///If the query fails this will return the type of the error

    result=mysql_store_result(connection);                                                                        ///Here we store the result obtained by the query

    if(result->row_count==1)                                                                                            ///If result have one row that means that the use exist
    {
        row=mysql_fetch_row(result);                                                                                    ///So we fetch the result inside a ROW variable provided by MYSQL lib

        if(row[3]==password)                                                                                            ///If the password provided by the user is the same at the column password in the table user he is connect
        {
            std::cout<<"You logged in successfully!!!\n"<<std::endl;
            user={std::stoi(row[0]),row[1],row[2],row[3],std::stoi(row[4])}; ///Here we create an object of type User where we save the logged user
        }else
            std::cout<<"Incorrect password!!\n"<<std::endl;
    }else
        std::cout<<"Incorrect username or password!!\n"<<std::endl;

    mysql_free_result(result);                                                                                          ///The result from the query is been freed from the memory

    return user;
}