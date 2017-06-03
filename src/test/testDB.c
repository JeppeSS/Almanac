#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>

#include "../database/database.h"


int main(void){

    DB db;

    db_init(&db, "localhost", "root", "kirk3kLokke_muf%fin", "Almanac");
    db_clean(&db);
    
    db_generate(&db);
    
    db_clean(&db);
    db_close(&db);

    return EXIT_SUCCESS;
}
