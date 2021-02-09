#include "./utils/Utility.h"
#include "./utils/Choices.h"
#include "./services/UserService.h"
#include "./services/FriendRequestsService.h"
#include "./services/PostsService.h"
#include "./services/MailService.h"
#include "./services/GamesService.h"

int main() {

    Utility::clearScreen();

    UserService userService;
    PostsService postsService;
    FriendRequestsService friendRequestsService;
    MailService mailService;
    GamesService gamesService;

    while (true) {

        LandingChoice landingChoice = Choices::getLandingChoice();

        Person loggedInUser;

        switch (landingChoice) {
            case SIGN_UP: {
                loggedInUser = userService.signUp();
                break;
            }
            case SIGN_IN: {
               loggedInUser = userService.signIn();
                break;
            }
        }

        bool isLoggedOut = false;

        while (!isLoggedOut) {

            DashboardChoice dashboardChoice = Choices::getDashboardChoice();

            switch (dashboardChoice) {

                case PROFILE:
                    userService.showProfileMenu(loggedInUser);
                    break;
                case POSTS:
                    postsService.showPostMenu(loggedInUser);
                    break;
                case FRIEND_REQUESTS:
                    friendRequestsService.showFriendRequestsMenu(loggedInUser);
                    break;
                case MAILS:
                    mailService.showMailMenu(loggedInUser);
                    break;
                case GAMES:
                    gamesService.showGamesMenu(loggedInUser);
                    break;
                case SIGN_OUT: isLoggedOut = true;
                    break;
            }

        }

    }

}

