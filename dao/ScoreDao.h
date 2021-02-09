//
// Created by bhavya bansal on 07/02/21.
//

#ifndef SCORE_DAO_H
#define SCORE_DAO_H

#include "Dao.h"
#include "../objects/Score.h"

class ScoreDao : public Dao<Score> {

public:

    ScoreDao() : Dao{"scores.dat"} {}

};

#endif //SCORE_DAO_H
