//
// Created by bhavya bansal on 04/02/21.
//

#ifndef FRIEND_REQUESTS_UTILITY_H
#define FRIEND_REQUESTS_UTILITY_H

#include <iostream>
#include <map>
#include <string>
#include "../objects/FriendRequest.h"
#include "../objects/Person.h"
#include "../dao/FriendRequestsDao.h"


class FriendRequestsService {

    FriendRequestsDao friendRequestsDao;
    PersonDao personDao;

private:

    void showFriendRequestsNotifications(const Person &user) {
        std::cout << "\n\t\t\t\tNOTIFICATIONS\n\n";
        auto friendRequests = friendRequestsDao.findFriendRequestWithStatusIn(
                std::vector<FriendRequestStatus::FriendRequestStatus>{FriendRequestStatus::ACCEPTED,
                                                                      FriendRequestStatus::REJECTED});
        if (friendRequests.empty()) {
            std::cout << "No New Notifications";
            return;
        }
        std::vector<FriendRequest> friendRequestsSeen;
        for (const auto &friendRequest : friendRequests) {
            if(friendRequest.getFrom() == user.getUname()) {
                std::cout << friendRequest.getTo();
                if (friendRequest.getStatus() == FriendRequestStatus::REJECTED)
                    std::cout << " rejected";
                if (friendRequest.getStatus() == FriendRequestStatus::ACCEPTED)
                    std::cout << " accepted";
                std::cout << " your friend request\n";
                friendRequestsSeen.push_back(friendRequest);
            }
        }
        friendRequestsDao.updateFriendRequestStatus(friendRequestsSeen, FriendRequestStatus::SEEN);
    }

    void showFriends(const Person &user) {
        auto friends = friendRequestsDao.findFriends(user.getUname());
        std::cout << "\n\t\t\t\tFRIENDS\n";
        int serialNumber = 1;
        for (const auto &usersFriend : friends) {
            std::cout << serialNumber;
            std::cout << " ";
            std::cout << usersFriend;
            std::cout << "\n";
            ++serialNumber;
        }
    }

    void sendFriendRequest(const std::string &from, const std::string &to) {
        FriendRequest friendRequest{to, from};
        friendRequestsDao.insert(friendRequest);
        Utility::clearScreen();
        std::cout << "\n\n\n\n\t\t\tFriend request Sent\n";
    }

    void showSendFriendRequestScreen(const Person &user) {
        std::cout << "\n\t\t\t\tSEND FRIEND REQUESTS\n";
        std::cout << "Whom do you want to send request:\n";
        int serialNumber = 0;
        std::map<int, std::string> possibleFriendsMap;
        auto users = personDao.findAll();
        auto friends = friendRequestsDao.findFriends(user.getUname());
        auto friendRequestsSentToMe = friendRequestsDao.findFriendRequestsWithTo(user.getUname());
        auto friendRequestsSentByMe = friendRequestsDao.findFriendRequestsWithFrom(user.getUname());
        for (const auto &temp : users) {
            bool isUserFriend = false;
            for (const auto &userFriend : friends) {
                if (userFriend == temp.getUname()) {
                    isUserFriend = true;
                    break;
                }
            }
            for (const auto &friendRequest: friendRequestsSentToMe) {
                if (friendRequest.getFrom() == temp.getUname()) {
                    isUserFriend = true;
                    break;
                }
            }
            for (const auto &friendRequest: friendRequestsSentByMe) {
                if (friendRequest.getTo() == temp.getUname()) {
                    isUserFriend = true;
                    break;
                }
            }
            if (!isUserFriend)
                if (temp != user) {
                    std::cout << ++serialNumber;
                    std::cout << " ";
                    std::cout << temp.getUname();
                    std::cout << "\n";
                    possibleFriendsMap[serialNumber] = temp.getUname();
                }
        }
        if (serialNumber == 0) {
            std::cout << "\nOops!!! No one to send request\n";
            return;
        }
        std::cout << "Your choice (0 for no one): ";
        int choice = Choices::getChoice(0, serialNumber);
        if (choice == 0)
            return;
        sendFriendRequest(user.getUname(), possibleFriendsMap[choice]);
    }

    void rejectFriendRequests(const Person &user) {
        auto allFriendRequests = friendRequestsDao.findFriendRequestsWithTo(user.getUname());
        std::vector<FriendRequest> friendRequestsToBeRejected;
        for(const auto &friendRequest : allFriendRequests){
            if(friendRequest.getStatus() == FriendRequestStatus::SENT){
                friendRequestsToBeRejected.push_back(friendRequest);
            }
        }
        friendRequestsDao.updateFriendRequestStatus(friendRequestsToBeRejected,FriendRequestStatus::REJECTED);
    }

    void acceptFriendRequest(const std::string &to, const std::string &from) {
        auto friendRequests = friendRequestsDao.findFriendRequestsWithToAndFrom(to,from);
        friendRequestsDao.updateFriendRequestStatus(friendRequests,FriendRequestStatus::ACCEPTED);
        friendRequestsDao.insertFriend(to,from);
        friendRequestsDao.insertFriend(from,to);
    }

    void showAcceptRejectRequestScreen(const Person &user) {

        char acceptMoreRequests = 'y';

        while (acceptMoreRequests == 'y' || acceptMoreRequests == 'Y') {

            std::cout << "\n\t\t\t\tACCEPT/REJECT FRIEND REQUEST\n";
            int serialNumber = 0;
            std::map<int, std::string> friendRequestsMap;
            auto friendRequests = friendRequestsDao.findFriendRequestsWithTo(user.getUname());
            for (const auto &friendRequest : friendRequests) {
                if (friendRequest.getStatus() == FriendRequestStatus::SENT) {
                    std::cout << ++serialNumber;
                    std::cout << " ";
                    std::cout << friendRequest.getFrom();
                    std::cout << " sent you a friend request\n";
                    friendRequestsMap[serialNumber] = friendRequest.getFrom();
                }
            }
            if (serialNumber == 0) {
                return;
            }
            std::cout << "\nWhich one do you want to accept(0 to reject all) ? ";
            int choice = Choices::getChoice(0, serialNumber);
            if (choice == 0) {
                rejectFriendRequests(user);
                return;
            }
            acceptFriendRequest(user.getUname(), friendRequestsMap[choice]);
            Utility::clearScreen();
            std::cout << "\nDo you want to accept more requests (y/n) ?\n";
            std::cin >> acceptMoreRequests;
            while (acceptMoreRequests != 'n' && acceptMoreRequests != 'y' && acceptMoreRequests != 'N' &&
                   acceptMoreRequests != 'Y') {
                std::cout << "\nInvalid choice\nEnter again: ";
                std::cin >> acceptMoreRequests;
            }
        }
        rejectFriendRequests(user);
    }

public:

    void showFriendRequestsMenu(const Person &user) {
        while (true) {
            FriendRequestChoice::FriendRequestChoice choice = Choices::getFriendRequestsChoice();
            Utility::clearScreen();
            switch (choice) {
                case FriendRequestChoice::NOTIFICATIONS:
                    showFriendRequestsNotifications(user);
                    break;
                case FriendRequestChoice::FRIENDS:
                    showFriends(user);
                    break;
                case FriendRequestChoice::SEND_FRIEND_REQUEST:
                    showSendFriendRequestScreen(user);
                    break;
                case FriendRequestChoice::ACCEPT_REJECT_FRIEND_REQUEST:
                    showAcceptRejectRequestScreen(user);
                    break;
                case FriendRequestChoice::BACK:
                    return;
            }
            std::cout << "\n\nPress any key to return...";
            Utility::getch();
        }
    }

};


#endif //FRIEND_REQUESTS_UTILITY_H
