#ifndef DBPLAYER_H
#define DBPLAYER_H
#include <string>

/*!
 * \class DBPlayer
 * \brief classe exploitee par Database
 * \date 19 avril 2018
 *
 *
 */

class DBPlayer
{
    public:
        DBPlayer();
        virtual ~DBPlayer();

        std::string nom;
        int id;
        float score;

    protected:

    private:
};

#endif // DBPLAYER_H
