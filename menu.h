/**
 * @author Massimiliano Di Ubaldo
 * Group 1, Informatics
 * Academic year 2021/2022, Semester 2
*/

#ifndef MENU_H
#define MENU_H

///Menu for non logged user
int menu(MYSQL *connection);

///Menu for logged user but owner
int menuOwner(MYSQL *connection, int ownerId);

///Menu for logged user
int menuUser(MYSQL *connection);

#endif
