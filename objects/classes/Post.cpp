//
// Created by bhavya bansal on 04/02/21.
//

#include "../Post.h"

const std::string &Post::getBy() const {
    return by;
}

void Post::setBy(const std::string &by) {
    Post::by = by;
}

const std::string &Post::getContent() const {
    return content;
}

void Post::setContent(const std::string &content) {
    Post::content = content;
}

bool Post::operator==(const Post &post) const {
    return this->getBy() == post.getBy() && this->getContent() == post.getContent();
}
