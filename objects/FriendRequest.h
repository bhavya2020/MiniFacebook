//
// Created by bhavya bansal on 03/02/21.
//

#ifndef FRIEND_REQUEST_H
#define FRIEND_REQUEST_H

#include <string>
#include <utility>
#include "../enums/FriendRequestStatus.h"

class FriendRequest {

private:

    std::string to;
    std::string from;
    FriendRequestStatus::FriendRequestStatus status;

public:

    FriendRequest();

    FriendRequest(std::string to, std::string from);

    const std::string &getTo() const;

    void setTo(const std::string &to);

    const std::string &getFrom() const;

    void setFrom(const std::string &from);

    FriendRequestStatus::FriendRequestStatus getStatus() const;

    void setStatus(FriendRequestStatus::FriendRequestStatus status);

    bool operator==(const FriendRequest&) const;

};


#endif //FRIEND_REQUEST_H
