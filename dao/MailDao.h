//
// Created by bhavya bansal on 06/02/21.
//

#ifndef MAIL_DAO_H
#define MAIL_DAO_H

#include "Dao.h"

class MailDao : public Dao<Mail> {

public:
    MailDao() : Dao{"mails.dat"} {}

    std::vector<Mail> findMailsWithTo(const std::string &to){
        Mail mail;
        File<Mail> file{FILE_NAME,INPUT,BINARY};
        std::vector<Mail> mails;
        while (file.read(mail)){
            if(mail.getTo() == to){
                mails.push_back(mail);
            }
        }
        std::reverse(mails.begin(),mails.end());
        return mails;
    }

    std::vector<Mail> findMailsWithFrom(const std::string &from){
        Mail mail;
        File<Mail> file{FILE_NAME,INPUT,BINARY};
        std::vector<Mail> mails;
        while (file.read(mail)){
            if(mail.getFrom() == from){
                mails.push_back(mail);
            }
        }
        std::reverse(mails.begin(),mails.end());
        return mails;
    }

    void updateMailStatus(Mail &mail, MailStatus::MailStatus newStatus ){
        File<Mail> file{FILE_NAME,INPUT_OUTPUT,BINARY};
        Mail temp;
        std::ios::pos_type location = file.getPosition();
        while (file.read(temp)){
            if(temp == mail){
                file.goTo(location);
                mail.setStatus(newStatus);
                file.write(mail);
                return;
            }
            location = file.getPosition();
        }

    }

};


#endif //MAIL_DAO_H
