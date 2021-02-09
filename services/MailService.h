//
// Created by bhavya bansal on 06/02/21.
//

#ifndef MAIL_SERVICE_H
#define MAIL_SERVICE_H


#include "../objects/Mail.h"
#include "../dao/MailDao.h"

class MailService {

    FriendRequestsDao friendRequestsDao;
    MailDao mailDao;

    void composeEmail(const Person &user) {
        std::string to;
        while (true) {
            std::cout << "\n\t\t\t\tCompose a mail to a friend\n";
            std::cout << "To: ";
            std::cin>>to;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::vector<std::string> friends = friendRequestsDao.findFriends(user.getUname());
            if (std::find(friends.begin(), friends.end(), to) == friends.end()) {
                Utility::clearScreen();
                std::cout << "Not your friend";
                std::cout << "\nEnter again(if you want to return press b): ";
                char check = Utility::getch();
                Utility::clearScreen();
                if (check == 'b' || check == 'B')
                    return;
            } else {
                break;
            }
        }
        std::cout << "\nSubject: ";
        std::string subject;
        Utility::getline(subject);
        std::cout << "\nBody:\n";
        std::string body;
        Utility::getline(body,'#');
        Mail mail{to, user.getUname(), subject, body};
        mailDao.insert(mail);
        Utility::clearScreen();
        std::cout << "\n\n\t\tMail Sent";
    }

    void showInbox(const Person &user) {

        std::cout << "\n\t\t\t\t\tInbox\n";

        auto mails = mailDao.findMailsWithTo(user.getUname());

        int serialNo = 0;
        std::map<int, Mail> mailMap;
        for (const auto &mail : mails) {
            if (mail.getStatus() != MailStatus::TRASH) {
                std::cout << ++serialNo << " ";
                std::cout << mail.getFrom() << ": ";
                std::cout << mail.getSubject();
                if (mail.getStatus() == MailStatus::NEW) {
                    std::cout << " *NEW";
                }
                std::cout << "\n";
                mailMap[serialNo] = mail;
            }
        }

        if (serialNo == 0){
            return;
        }

        std::cout << "\nWhich one to open(0 for no one) ?\n";
        int choice = Choices::getChoice(0, serialNo);
        if (choice == 0)
            return;

        Utility::clearScreen();
        Mail mail = mailMap[choice];
        std::cout << "From: " << mail.getFrom() << "\nSubject: " << mail.getSubject() << "\n\n" << mail.getBody()
                  << "\n";

        std::cout << "\n\nDo you want to send it to trash mail (y/n) ? ";

        char sentToTrash;
        std::cin >> sentToTrash;
        while (sentToTrash != 'n' && sentToTrash != 'y' && sentToTrash != 'N' && sentToTrash != 'Y') {
            std::cout << "\nInvalid choice\nEnter again: ";
            std::cin >> sentToTrash;
        }

        if (sentToTrash == 'y' || sentToTrash == 'Y') {
            mailDao.updateMailStatus(mail, MailStatus::TRASH);
        } else {
            if (mail.getStatus() == MailStatus::NEW) {
                mailDao.updateMailStatus(mail, MailStatus::INBOX);
            }
        }

    }

    void showSentEmails(const Person &user) {

        std::cout << "\n\t\t\t\t\tSent mail\n";

        auto mails = mailDao.findMailsWithFrom(user.getUname());

        if (mails.empty()) {
            return;
        }

        int serialNo = 0;
        std::map<int, Mail> mailMap;
        for (const auto &mail : mails) {
            std::cout << ++serialNo << " ";
            std::cout << mail.getTo() << ": ";
            std::cout << mail.getSubject();
            std::cout << "\n";
            mailMap[serialNo] = mail;
        }

        std::cout << "\nWhich one to open(0 for no one) ?\n";
        int choice = Choices::getChoice(0, serialNo);
        if (choice == 0)
            return;

        Utility::clearScreen();
        Mail mail = mailMap[choice];
        std::cout << "To: " << mail.getTo() << "\nSubject: " << mail.getSubject() << "\n\n" << mail.getBody()
                  << "\n";
    }

    void showTrashEmails(const Person &user) {

        std::cout << "\n\t\t\t\t\tTrash mail\n";

        auto mails = mailDao.findMailsWithTo(user.getUname());

        int serialNo = 0;
        std::map<int, Mail> mailMap;
        for (const auto &mail : mails) {
            if (mail.getStatus() == MailStatus::TRASH) {
                std::cout << ++serialNo << " ";
                std::cout << mail.getTo() << ": ";
                std::cout << mail.getSubject();
                std::cout << "\n";
                mailMap[serialNo] = mail;
            }
        }
        if (serialNo == 0){
            return;
        }
        std::cout << "\nWhich one to open(0 for no one) ?\n";
        int choice = Choices::getChoice(0, serialNo);
        if (choice == 0)
            return;

        Utility::clearScreen();
        Mail mail = mailMap[choice];
        std::cout << "To: " << mail.getTo() << "\nSubject: " << mail.getSubject() << "\n\n" << mail.getBody()
                  << "\n";
    }

public:

    void showMailMenu(const Person &user) {
        while (true) {
            MailChoice::MailChoice choice = Choices::getMailChoice();
            Utility::clearScreen();
            switch (choice) {
                case MailChoice::COMPOSE:
                    composeEmail(user);
                    break;
                case MailChoice::INBOX:
                    showInbox(user);
                    break;
                case MailChoice::SENT:
                    showSentEmails(user);
                    break;
                case MailChoice::TRASH:
                    showTrashEmails(user);
                    break;
                case MailChoice::BACK:
                    return;
            }
            std::cout << "\nPress any key to return\n";
            Utility::getch();
        }
    }
};


#endif //MAIL_SERVICE_H
