//
// Created by bhavya bansal on 03/02/21.
//

#include "../Mail.h"

#include <utility>

Mail::Mail() = default;

Mail::Mail(std::string to, std::string from, std::string subject, const std::string& body) : to{std::move(to)}, from{std::move(from)}, subject{std::move(subject)}, status{MailStatus::NEW} {
    strcpy(this->body,body.c_str());
}

Mail::Mail(const Mail &mail) : to{mail.getTo()}, from{mail.getFrom()}, subject{mail.getSubject()}, status{mail.getStatus()} {
 strcpy(body,mail.getBody().c_str());
}

const std::string &Mail::getTo() const {
    return to;
}

void Mail::setTo(const std::string &to) {
    Mail::to = to;
}

const std::string &Mail::getFrom() const {
    return from;
}

void Mail::setFrom(const std::string &from) {
    Mail::from = from;
}

const std::string &Mail::getSubject() const {
    return subject;
}

void Mail::setSubject(const std::string &subject) {
    Mail::subject = subject;
}

std::string Mail::getBody() const {
    return std::string{body};
}

void Mail::setBody(const std::string &body) {
    strcpy(Mail::body, body.c_str());
}

MailStatus::MailStatus Mail::getStatus() const {
    return status;
}

void Mail::setStatus(MailStatus::MailStatus status) {
    Mail::status = status;
}

bool Mail::operator==(const Mail &mail) const {
    return this->getTo() == mail.getTo() && this->getFrom() == mail.getFrom() && this->getSubject() == mail.getSubject() &&
            this->getBody() == mail.getBody() && this->getStatus() == mail.getStatus();
}


