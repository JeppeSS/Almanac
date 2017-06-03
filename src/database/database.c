#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "database.h"

int db_init(DB *db, const char *server, const char *user, const char *pass, const char *dataB){

    db->con = mysql_init(NULL);

    if(!db->con){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    if (!mysql_real_connect(db->con, server,
         user, pass, NULL, 0, NULL, 0)) {
        
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        mysql_close(db->con);
        return EXIT_FAILURE;
    }

    db->dbName = dataB;

    fprintf(stdout, "[OK] Database initialized\n");
    
    return EXIT_SUCCESS;
}


int db_generate(DB *db){
    const char *almanac = "CREATE DATABASE Almanac";

    if(mysql_query(db->con, almanac)){

        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        mysql_close(db->con);
        return EXIT_FAILURE;
    }


    fprintf(stdout, "[OK] Build Database: Almanac\n");

    if(mysql_select_db(db->con, db->dbName)){

        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }


    const char *log_create = "CREATE TABLE log (timestamp DATETIME, identity LONGTEXT, service LONGTEXT, action VARCHAR(200))";


    if(mysql_query(db->con, log_create)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }


    fprintf(stdout, "[OK] Created Table log\n");

    const char *identity_reg_create = "CREATE TABLE identity_reg (fullname VARCHAR(200), organization VARCHAR(200), role VARCHAR(200), id LONGTEXT)";

    if(mysql_query(db->con, identity_reg_create)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[OK] Created Table identity_reg\n");

    const char *service_reg_create = "CREATE TABLE service_reg (name VARCHAR(200), description VARCHAR(200), permission VARCHAR(200), id LONGTEXT)";

    if(mysql_query(db->con, service_reg_create)){
        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[OK] Created Table service_reg\n");


    return EXIT_SUCCESS;

}

int db_clean(DB *db){
    
    const char *dropAll = "DROP DATABASE IF EXISTS Almanac";

    if(mysql_query(db->con, dropAll)){

        fprintf(stderr, "[ERROR] %s\n", mysql_error(db->con));
        return EXIT_FAILURE;
    }

    fprintf(stdout, "[OK] Cleaned Database\n");

    return EXIT_SUCCESS;
}

int db_close(DB *db){

    /* Close connection */
    mysql_close(db->con);

    fprintf(stdout, "[OK] Database connection closed\n");

    return EXIT_SUCCESS;

}