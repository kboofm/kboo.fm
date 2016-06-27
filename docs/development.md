# Development

This are some instructions to aid in development, if you want to install and configure the Calendar module.


## Updating a module

Note the modules are managed using [composer](getcomposer.org), and we are making extensive use of Features. So, ideally you would generally
- update composer
- add a new feature for the Calendar and it's settings
- update the environment set up feature so that it will cause Calendar to be enabled

I expected when you do composer up there will be other module updates that come through, which is fine. It's a good enough time to get all of those done right before launch (and there's a Drupal security update that just came out).

## Managing Drupal modules via Composer

To add a module, add a new entry alphabetically to the module list in the composer.json file, and specify the module version to use. For example, to add the views module you would add

```
"drupal/views": "7.3.11",
```

Afterwards, in your terminal cd to the directory containing the composer.json file and run composer up.

The new module should likely then be added as a dependency to the appropriate feature. Such as in /web/sites/all/modules/features/contrib_module_dependencies_base/contrib_module_dependencies_base.info

If the module needs to be updated to a newer version, the modify the version number for it's entry in composer.json and then run "composer up".

To delete a module, remove it's entry from composer.json, and then run "composer up". You will also want to remove the module from the module dependencies feature by editing the .info file mentioned above.

## Git notes

The developers follow gitflow standards, so you would ideally create a feature branch and when you think it's ready for review, create a merge request in gitlab from your feature branch into the develop branch.

Please name your feature branch the same as the "Jira ticket". Please also include ticket numbers in commit messages.

### Branch

To create the feature branch run the following in your terminal, presuming you've installed gitflow

```
git flow feature start KBOO-11
```

Immediately afterward publish the branch remotely by running the following in your terminal

```
git flow feature publish KBOO-11
```

When ever you are ready to push commits up to origin use

```
git push origin feature/KBOO-11
```

### Commit message format

Please add brackets around the Jira ticket id in your commit messages. Example below, notice the part with [KBOO-11].

This is the format that integrates with JIRA, and it is used by the custom app team.

```
git commit -am '[KBOO-11] did some work'
```
