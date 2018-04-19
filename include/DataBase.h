#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <vector>
#include <sstream>

#include "DBPlayer.h"
/*!
 * \class DataBase
 * \brief Creation et interaction avec une bdd sous sqlite
 * \date 19 avril 2018
 *
 * \brief Creer/edite une bdd
 *
 */


class DataBase
{
    public:
        DataBase();
        virtual ~DataBase();
        /*!
         * \brief ouvre la base de donnees
        */
        void openDatabase();
        /*!
         * \brief ferme la base de donnees
        */
        void closeDatabase();
        /*!
         * \brief execute la requete
         * \param query requete
        */
        bool executeQuery(std::string query);
        /*!
         * \brief insert un nouveau joueur
         * \param nom nom du joueur
         * \param score score du joueur
        */
        bool insertPlayer(std::string nom, float score);

        /*!
         * \brief tableau dynamique qui va rechercher et stocker les joueurs
        */
        std::vector<DBPlayer*>* getAllPlayers();

        /*!
         * \brief suppression joueur
         * \param id id du joueur
        */
        bool deletePlayer(int id);

    protected:

    private:
        sqlite3 * db;
        std::string dbfile;
};

#endif // DATABASE_H
