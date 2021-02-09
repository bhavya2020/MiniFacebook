//
// Created by bhavya bansal on 04/02/21.
//

#ifndef POSTS_UTILITY_H
#define POSTS_UTILITY_H

#include <vector>
#include "../objects/Post.h"
#include "../dao/PostsDao.h"

class PostsService {

    PostsDao postsDao;

public:
     void showPostMenu(const Person &user) {
        while (true) {
            PostsChoice::PostsChoice choice = Choices::getPostsChoice();
            Utility::clearScreen();
            switch (choice) {
                case PostsChoice::VIEW: {
                    std::cout << "\n\t\t\t\tPOSTS\n";
                    for (const auto& post : postsDao.findAll()) {
                        std::cout << "\nBy: " << post.getBy();
                        std::cout << "\n" << post.getContent();
                        std::cout << "\n";
                    }
                    break;
                }
                case PostsChoice::POST: {
                    Post post;
                    post.setBy(user.getUname());
                    std::cout << "Enter your Post:\n";
                    std::string content;
                    Utility::getline(content);
                    post.setContent(content);
                    postsDao.insert(post);
                    break;
                }
                case PostsChoice::BACK:
                    return;
            }
            std::cout << "\nPress any key to return\n";
            Utility::getch();
        }
    }
};


#endif //POSTS_UTILITY_H
