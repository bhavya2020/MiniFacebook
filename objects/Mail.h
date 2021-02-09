//
// Created by bhavya bansal on 03/02/21.
//

#ifndef MAIL_H
#define MAIL_H

#include <string>
#include "../enums/MailStatus.h"

class Mail {

private:

    std::string to;
    std::string from;
    std::string subject;
    char body[1000]{};
    MailStatus::MailStatus status;

public:

    Mail();

    Mail(std::string to, std::string from, std::string subject, const std::string& body);

    Mail(const Mail &);

    const std::string &getTo() const;

    void setTo(const std::string &to);

    const std::string &getFrom() const;

    void setFrom(const std::string &from);

    const std::string &getSubject() const;

    void setSubject(const std::string &subject);

    std::string getBody() const;

    void setBody(const std::string &body);

    MailStatus::MailStatus getStatus() const;

    void setStatus(MailStatus::MailStatus status);

    bool operator==(const Mail&) const;
};


#endif //MAIL_H
