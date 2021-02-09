//
// Created by bhavya bansal on 03/02/21.
//

#include "../FriendRequest.h"

#include <utility>

FriendRequest::FriendRequest(std::string to, std::string from) : to(std::move(to)), from(std::move(from)), status(FriendRequestStatus::SENT) {}

const std::string &FriendRequest::getTo() const {
    return to;
}

void FriendRequest::setTo(const std::string &to) {
    FriendRequest::to = to;
}

const std::string &FriendRequest::getFrom() const {
    return from;
}

void FriendRequest::setFrom(const std::string &from) {
    FriendRequest::from = from;
}

FriendRequestStatus::FriendRequestStatus FriendRequest::getStatus() const {
    return status;
}

void FriendRequest::setStatus(FriendRequestStatus::FriendRequestStatus status) {
    FriendRequest::status = status;
}

bool FriendRequest::operator==(const FriendRequest &friendRequest) const {
    return this->getFrom() == friendRequest.getFrom() && this->getTo() == friendRequest.getTo() && this->getStatus() == friendRequest.getStatus();
}

FriendRequest::FriendRequest() = default;
