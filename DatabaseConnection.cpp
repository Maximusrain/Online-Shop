/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#include <iostream>
#include <mysql.h>

#include "DatabaseConnection.h"

DatabaseConnection::DatabaseConnection(char *host, char *user, char *password, char *dbName, unsigned int port, char *unixSocket, unsigned long clientFlag)         ///Constructor of class DatabaseConnection
{
    setDatabaseConnection(host, user, password, dbName, port, unixSocket, clientFlag);
}

void DatabaseConnection::setDatabaseConnection(char *host, char *user, char *password, char *dbName, unsigned int port, char *unixSocket, unsigned long clientFlag)     ///Setter for the class Database connection
{
    this->_host=host;
    this->_user=user;
    this->_password=password;
    this->_dbName=dbName;
    this->_port=port;
    this->_unixSocket=unixSocket;
    this->_clientFlag=clientFlag;
}

char *DatabaseConnection::getHost()                                                                                     ///Method to get the host
{
    return this->_host;
}

char *DatabaseConnection::getUser()                                                                                     ///Method to get the User
{
    return this->_user;
}

char *DatabaseConnection::getPassword()                                                                                 ///Method to get the password
{
    return this->_password;
}

char *DatabaseConnection::getDbName()                                                                                   ///Method to get the db name
{
    return this->_dbName;
}

unsigned int DatabaseConnection::getPort()                                                                              ///Method to get the port
{
    return this->_port;
}

char *DatabaseConnection::getUnixSocket()                                                                               ///Method to get the unix socket
{
    return this->_unixSocket;
}

unsigned long DatabaseConnection::getClientFlag()                                                                       ///Method to get the client flag
{
    return this->_clientFlag;
}

MYSQL *DatabaseConnection::connectionToDatabase()                                                                       ///Method to connect to the db
{
    MYSQL* connection;                                                                                                  ///variable of type MYSQL to return the connection
    connection= mysql_init(nullptr);                                                                              ///We initialize the connection
    connection- mysql_real_connect(connection, getHost(), getUser(), getPassword(), getDbName(), getPort(), getUnixSocket(), getClientFlag());      ///We insert the data to connect to the db

    if(!connection)
        std::cout<<"Failed to connect!!"<<mysql_errno(connection)<<std::endl;                                     ///Here we check if the connection went good if yes we return the connection if not we return the error

    return connection;
}