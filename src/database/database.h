#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>

/*
 * === Structure ==============================================================
 *         Name:  Database (DB)
 *
 *  Description: The database structure
 * ============================================================================
 */
typedef struct{
    
    MYSQL     *con;
    MYSQL_RES *res;
    MYSQL_ROW  row;

    const char *dbName;

} DB;

// Initializer
int db_init(DB *db, const char *server, const char *user, const char* pass, const char* dataB);

// Generator
int db_generate(DB *db);

// Cleanup
int db_clean(DB *db);

// Close
int db_close(DB *db);
#endif
