#!/bin/sh

# This is run by GitLab-CI to deploy the code to the correct environment

# The following scripts are available:
# deploy-embers $DOMAIN [$SITE = 1/ production] [$USER = $DOMAIN] [$DEPLOY-VIA = SSH]
# deploy-redemma $SUBDOMAIN [$DEPLOY-VIA = SSH]

# The above are simple wrappers to these underlying scripts:
# deploy-via-ssh $HOST [$DOMAIN = $HOST] [$DRUPAL_PATH = httpdocs] [$USER = $DOMAIN] [$DEPLOY-VIA = SSH]
# deploy-via-drupal $HOST [$DOMAIN = $HOST] [$DRUPAL_PATH = httpdocs] [$USER = $DOMAIN] [$DEPLOY-VIA = SSH]

# Note: Deply-via-drupal executes drush updates after pulling the latest changes

# Want to use variables? Go for it!
C4DEV_USER="sandbox"

deploy_production(){
    echo "Production is not enabled on this repo"
}

deploy_staging(){
    echo "Staging is not enabled on this repo"
    # deploy-embers stage.edwardwomac.com stage $C4DEV_USER drupal
}

deploy_develop(){
    deploy-redemma kboo drupal
}

# HIC SVNT LEONES
# Catch the branch and trigger the expected environment -- DO NOT CHANGE (unless you know what you may be breaking)
echo "Triggering deployment for $CI_BUILD_REF_NAME branch..."
case "$CI_BUILD_REF_NAME" in
    release/*|staging|stage)
        deploy_staging
        ;;
    develop)
        deploy_develop
        ;;
    master)
        deploy_production
        ;;
esac

exit 0
