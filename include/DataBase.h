#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include "DBPlayer.h"

class database
{
    public:
        database();
        virtual ~database();

        void openDatabase();
        void closeDatabase();
        bool executeQuery(std::string query);

        bool insertPlayer(std::string nom, float score);
        std::vector<DBPlayer*> getAllPlayers();
        bool updatePlayer(DBPlayer* player);
        bool deletePlayer(int id);

    protected:

    private:
        sqlite3 * db;
        std::string dbfile;
};

#endif // DATABASE_H
