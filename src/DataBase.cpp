#include "DataBase.h"
#include <cstring>
#include <iostream>
#include <stdio.h>

database::database()
{
    //ctor
    dbfile = "./Pitchy-copter_database.db";
}

database::~database()
{
    //dtor
}

void database::openDatabase()
{
    sqlite3_initialize();
    sqlite3_open(dbfile.c_str(), &db);
}

void database::closeDatabase()
{
    sqlite3_close_v2(db);
    sqlite3_shutdown();
}

bool database::executeQuery(std::string query)
{
    char * errmsg = 0;
    if (sqlite3_exec(db, query.c_str(), NULL, 0, &errmsg)!= SQLITE_OK)
    {
        std::cout << errmsg << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool database::insertPlayer(std::string nom, float score)
{
    char bprix[10];
    char bqtevendue[10];
    sprintf(bprix, "%f", prix);
    sprintf(bqtevendue, "%d", qtevendue);

    std::string query = "INSERT INTO produits VALUES('";
    query += nom;
    query += "',";
    query += bprix;
    query += ",";
    query += bqtevendue;
    query += ")";

    std::cout << query << std::endl;

    return executeQuery(query);
}

std::vector<DBPlayer*> database::getAllPlayers()
{
    std::string query = "SELECT rowid, * FROM players";
    std::vector<DBPlayer*>;
    int i;

    sqlite3_stmt * stmt;
    sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str())+1, &stmt, NULL);

    do {
        i = sqlite3_step(stmt);
        if (i == SQLITE_ROW)
        {
            DBPlayer * player = new DBPlayer();
            players->push_back(player);

            player->id = sqlite3_column_int(stmt, 0);
            player->nom = (char*)sqlite3_column_text(stmt, 1);
            player->prix = sqlite3_column_double(stmt, 2);
            player->qtevendue = sqlite3_column_int(stmt, 3);
        }
    }
    while (i == SQLITE_ROW);

    return players;
}

bool database::updatePlayer(DBPlayer* player)
{
    std::string query = "UPDATE players SET nom=?, prix=?, qtevendue=? WHERE rowid=?";
    sqlite3_stmt * stmt;
    sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str())+1, &stmt, NULL);

    //Binds
    sqlite3_bind_text(stmt, 1, player->nom.c_str(), strlen(player->nom.c_str()), 0);
    sqlite3_bind_double(stmt, 2, player->prix);
    sqlite3_bind_int(stmt, 3, player->qtevendue);
    sqlite3_bind_int(stmt, 4, player->id);

    //Execute
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return true;
}

bool database::deletePlayer(int id)
{
    std::string query = "DELETE FROM produits WHERE rowid=?";
    sqlite3_stmt * stmt;
    if(sqlite3_prepare(db, "DELETE FROM produits" \
                           "WHERE rowid=?",
                    -1, &stmt, NULL) == SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return true;
    }

    return false;
}
