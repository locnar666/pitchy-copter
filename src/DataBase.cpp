#include "DataBase.h"
#include <cstring>
#include <iostream>
#include <stdio.h>

DataBase::DataBase()
{
    //ctor
    dbfile = "./Pitchy-copter_database.db";
}

DataBase::~DataBase()
{
    //dtor
}

void DataBase::openDatabase()
{
    sqlite3_initialize();
    sqlite3_open(dbfile.c_str(), &db);
}

void DataBase::closeDatabase()
{
    sqlite3_close_v2(db);
    sqlite3_shutdown();
}

bool DataBase::executeQuery(std::string query)
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

bool DataBase::insertPlayer(std::string nom, float score)
{
    std::ostringstream temps;
    temps << score;
    std::string scoreBDD = temps.str();

    std::string query = "INSERT INTO players VALUES('";
    query += nom;
    query += "', '";
    query += scoreBDD;
    query += "')";

    std::cout << query << std::endl;

    return executeQuery(query);
}

std::vector<DBPlayer*>* DataBase::getAllPlayers()
{
    std::string query = "SELECT rowid, * FROM players ORDER BY score DESC LIMIT 10";
    std::vector<DBPlayer*>* players = new std::vector<DBPlayer*>;
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
            player->score = sqlite3_column_double(stmt, 2);
        }
    }
    while (i == SQLITE_ROW);

    return players;
}

/*bool database::updatePlayer(DBPlayer* player)
{
    std::string query = "UPDATE players SET nom=?, prix=?, qtevendue=? WHERE rowid=?";
    sqlite3_stmt * stmt;
    sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str())+1, &stmt, NULL);

    //Binds
    sqlite3_bind_text(stmt, 1, player->nom.c_str(), strlen(player->nom.c_str()), 0);
    sqlite3_bind_double(stmt, 2, player->score);
    sqlite3_bind_int(stmt, 3, player->id);

    //Execute
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    return true;
}*/

bool DataBase::deletePlayer(int id)
{
    std::string query = "DELETE FROM players WHERE rowid=?";
    sqlite3_stmt * stmt;
    sqlite3_prepare_v2(db, query.c_str(), strlen(query.c_str())+1, &stmt, NULL);

    //Bind
    sqlite3_bind_int(stmt, 1, id);

    //Execute
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}
