/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include  <iostream>
#include <mysql.h>

///Class to make connection to database
class DatabaseConnection
{
private:
    char *_host, *_user, *_password, *_dbName, *_unixSocket;
    unsigned int _port;
    unsigned long _clientFlag;

public:
    /** Constructor for class DatabaseConnection
    * @param host host of the db of type char
    * @param user user of the db of type char
    * @param password password of the db of type char
    * @param port port of the db of type unsigned int
    * @param unixSocket unisocket of the db of type char
    * @param clientFlag client flag of the db of type unsigned long
    */
    DatabaseConnection(char *host, char *user, char *password, char *dbName, unsigned int port, char *unixSocket, unsigned long clientFlag);


    /** Method for the class DatabaseConnection
   * @param host host of the db of type char
   * @param user user of the db of type char
   * @param password password of the db of type char
   * @param port port of the db of type unsigned int
   * @param unixSocket unisocket of the db of type char
   * @param clientFlag client flag of the db of type unsigned long
   */
    void setDatabaseConnection(char *host, char *user, char *password, char *dbName, unsigned int port, char *unixSocket, unsigned long clientFlag);


    /** Method to get the host
    * @return host of type char
    */
    char *getHost();

    /** Method to get the User
    * @return user of type char
    */
    char *getUser();

    /** Method to get the password
    * @return password of type char
    */
    char *getPassword();

    /** Method to get the dbname
    * @return dbname of type char
    */
    char *getDbName();

    /** Method to get the port
    * @return port of type unsigned int
    */
    unsigned int getPort();

    /** Method to get the unix socekt
    * @return unix socket of type char
    */
    char *getUnixSocket();

    /** Method to get the clientflag
    * @return clientflag of type unsigned long
    */
    unsigned long getClientFlag();


    /** Method to connect to the database
    * @return connection to the databse of type MYSQL
    */
    MYSQL *connectionToDatabase();
};

#endif
