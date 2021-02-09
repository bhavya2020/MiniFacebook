//
// Created by bhavya bansal on 04/02/21.
//

#ifndef POSTS_H
#define POSTS_H

#include <string>

class Post {

private:

    std::string by;
    std::string content;

public:

    const std::string &getBy() const;

    void setBy(const std::string &by);

    const std::string &getContent() const;

    void setContent(const std::string &content);

    bool operator==(const Post&) const;

};


#endif //POSTS_H
