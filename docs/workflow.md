 To connect to the repo:

    Click link in the invite email you get
    Login, change your password
    Add your computers' private ssh key
    Browse the project and you'll see the git URL to clone

Note:

    We generally follow gitflow principles for branch management. http://danielkummer.github.io/git-flow-cheatsheet/
    At the moment, this means:
        We have deployment scripts that will automagically deploy updates to the site when they are pushed to the appropriate branch. [Or eventually we'll do that, for now we will ssh in and pull the updates.]
        Production site is set to the master branch.
        Development site is set to the dev branch.
        When working locally, typically we commit our updates to a feature branch. 
        When they are ready, we commit to the develop branch. Then other developers can review locally. 
        When those are ready for further review and testing we commit to the dev branch.


# Code Roll workflow

We use git tags that are versioned using the date of the roll.
List the existing tags to see if one has been created yet today. If so, increment by .1, starting with .1

$: git tag
0.0.1
2015-12-21
2015-12-23
2015-12-24
2015-12-24.1

Create the release branch

$: git flow release start 2015-12-29

Since we don't have a stage site you can immediately close the release branch

$: git flow release finish 2015-12-29

For the tag message I like to list the tickets included in the roll

Now push everything up

$: git push --all
$: git push --tags

## Updating Staging

ssh in to server with kboo user

$ cd /var/www/vhosts/dev.kboo.fm
$ git fetch
$ git checkout 2015-12-29

then run Drupal update db (if needed) and clear cache
$: drush @kboo.d7.dev updatedb
$: drush @kboo.d7.dev cc all

## Updating Production

ssh in to server  with kboo user

$ cd /var/www/vhosts2/migrate.kboo.fm
$ git fetch
$ git checkout 2015-12-29

then run Drupal update db (if needed) and clear cache
$: drush @kboo.d7.prod updatedb
$: drush @kboo.d7.prod cc all
