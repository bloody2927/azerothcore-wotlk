#!/bin/bash
## Just run it with bash or `git bash` on windows, and it will ask for the module's name and tada!
## By Barbz

##------------------------------- VARIABLES ---------------------------------##

MODULE_TEMPLATE_URL="https://github.com/azerothcore/skeleton-module/"
GIT_COMMIT_MSG_SETUP="setup_git_commit_template.sh"

##------------------------------- CODE ---------------------------------##

read -p "Enter the name of your future module: " "MODULE_NAME"
echo $MODULE_NAME | fgrep -q ' '

while [ $? -eq 0 ]
do
  echo 'Blanks are not allowed!'
  read -p "Enter the name of your future module: " MODULE_NAME
  echo $MODULE_NAME | fgrep -q ' '
done

if test -n "$MODULE_NAME"
then
    echo "--- Cloning 'skeleton-module' as $MODULE_NAME/"
    git clone --depth 1 -b master $MODULE_TEMPLATE_URL $MODULE_NAME

    echo "--- Removing 'skeleton-module/.git/' history"
    cd $MODULE_NAME && rm -rf .git/

    echo "--- Init new git repository"
    git init && git add -A && git commit -m "Initial commit - $MODULE_NAME"

    echo "--- Configure git for nice commit messages"
    source "$GIT_COMMIT_MSG_SETUP" || bash "$GIT_COMMIT_MSG_SETUP"

    echo "--- Ready to code"
fi

# Optionally configure a git remote for the new module
read -p "Do you want to set a git remote? (y/N) " CONFIGURE_GIT
case $CONFIGURE_GIT in
    [yY]*) ;;
    *)
        echo "Skipping remote configuration."
        exit 0
        ;;
esac

PS3='Select the remote host: '
select REMOTE_HOST in "github.com" "gitlab.com" "bitbucket.org" "Quit"; do
    case $REMOTE_HOST in
        "Quit"|"")
            echo "No remote host selected. Exiting."
            exit 0
            ;;
        *)
            break
            ;;
    esac
done

PS3='Select the protocol: '
select REMOTE_PROTOCOL in "HTTPS" "SSH" "Quit"; do
    case $REMOTE_PROTOCOL in
        "Quit"|"")
            echo "No protocol selected. Exiting."
            exit 0
            ;;
        "HTTPS"|"SSH")
            break
            ;;
        *)
            echo "Invalid option $REPLY"
            ;;
    esac
done

read -p "Enter your username for $REMOTE_HOST: " USER_NAME

if [ "$REMOTE_PROTOCOL" = "HTTPS" ]; then
    REMOTE_URL="https://$REMOTE_HOST/$USER_NAME/$MODULE_NAME.git"
else
    REMOTE_URL="git@$REMOTE_HOST:$USER_NAME/$MODULE_NAME.git"
fi

git remote add origin "$REMOTE_URL"
echo "Remote 'origin' set to $REMOTE_URL"
