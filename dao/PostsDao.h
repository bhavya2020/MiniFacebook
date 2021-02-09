//
// Created by bhavya bansal on 05/02/21.
//

#ifndef POSTS_DAO_H
#define POSTS_DAO_H

#include "Dao.h"
#include "../objects/Post.h"

class PostsDao: public Dao<Post> {

public:

    PostsDao() : Dao{"posts.dat"} {}

};

#endif //POSTS_DAO_H
