//
// Created by bhavya bansal on 05/02/21.
//

#ifndef FRIEND_REQUESTS_DAO_H
#define FRIEND_REQUESTS_DAO_H

#include <vector>
#include "Dao.h"
#include "../objects/FriendRequest.h"

class FriendRequestsDao : public Dao<FriendRequest> {

public:

    FriendRequestsDao() : Dao{"friend_requests.dat"} {}

    std::vector<FriendRequest>
    findFriendRequestWithStatusIn(const std::vector<FriendRequestStatus::FriendRequestStatus> &statuses) {
        std::vector<FriendRequest> friendRequests;
        File<FriendRequest> file{FILE_NAME, INPUT, BINARY};
        FriendRequest friendRequest;
        while (file.read(friendRequest)) {
            if (std::find(statuses.begin(), statuses.end(), friendRequest.getStatus()) != statuses.end()) {
                friendRequests.push_back(friendRequest);
            }
        }
        return friendRequests;
    }

    void updateFriendRequestStatus(const std::vector<FriendRequest> friendRequests,
                                   FriendRequestStatus::FriendRequestStatus newStatus) {

        for (auto friendRequest : friendRequests) {
            File<FriendRequest> file{FILE_NAME, INPUT_OUTPUT, BINARY};
            std::ios::pos_type location = file.getPosition();
            FriendRequest temporary;
            while (file.read(temporary)) {
                if (temporary == friendRequest) {
                    file.goTo(location);
                    friendRequest.setStatus(newStatus);
                    file.write(friendRequest);
                    break;
                }
                location = file.getPosition();
            }
        }
    }

    std::vector<std::string> findFriends(const std::string &of) {
        File<std::string> file{of, INPUT, TEXT};
        std::vector<std::string> friends;
        std::string usersFriend;
        while (file.read(usersFriend)) {
            friends.push_back(usersFriend);
        }
        return friends;
    }

    std::vector<FriendRequest> findFriendRequestsWithTo(const std::string &username) {
        File<FriendRequest> file{FILE_NAME, INPUT, BINARY};
        std::vector<FriendRequest> friendRequests;
        FriendRequest friendRequest;
        while (file.read(friendRequest)) {
            if (friendRequest.getTo() == username) {
                friendRequests.push_back(friendRequest);
            }
        }
        return friendRequests;
    }

    std::vector<FriendRequest> findFriendRequestsWithFrom(const std::string &username) {
        File<FriendRequest> file{FILE_NAME, INPUT, BINARY};
        std::vector<FriendRequest> friendRequests;
        FriendRequest friendRequest;
        while (file.read(friendRequest)) {
            if (friendRequest.getFrom() == username) {
                friendRequests.push_back(friendRequest);
            }
        }
        return friendRequests;
    }

    std::vector<FriendRequest> findFriendRequestsWithToAndFrom(const std::string &to, const std::string &from) {
        File<FriendRequest> file{FILE_NAME, INPUT, BINARY};
        std::vector<FriendRequest> friendRequests;
        FriendRequest friendRequest;
        while (file.read(friendRequest)) {
            if (friendRequest.getTo() == to && friendRequest.getFrom() == from) {
                friendRequests.push_back(friendRequest);
            }
        }
        return friendRequests;
    }

    void insertFriend(const std::string &of, const std::string &newFriend){
        File<std::string> file{of, OUTPUT_APPEND, TEXT};
        file.write(newFriend);
    }

};


#endif //FRIEND_REQUESTS_DAO_H
