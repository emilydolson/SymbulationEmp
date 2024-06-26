# Getting started with Symbulation development
 
This document is intended to help those just getting started with
Symbulation development. It details the initial one-time dependency
installs and any similar routines necessary to get started with
development.
 
Start by making your own copy of Symbulation and setting yourself up for
development; then, build Symbulation and run the tests; and finally, claim
an issue and start developing!
 
If you're unfamiliar with git and branching in particular, check out
the [git-scm book](http://git-scm.com/book/en/Git-Branching).
 
## One-time Preparation
 
1.  Get a [GitHub](http://github.com) account.
 
    (We use GitHub to manage Symbulation contributions.)
 
2.  Fork
    [github.com/anyaevostiar/SymbulationEmp](https://github.com/anyaevostinar/SymbulationEmp).
 
    Visit that page, and then click on the 'fork' button (upper
    right).
 
    This makes a copy of the Symbulation source code in your own GitHub
    account. If you have contributor permissions to the main Symbulation
    library, this step is optional (you can instead develop on a branch
    within the main repo).
 
3.  Clone your copy of Symbulation and Empirical to your local development environment.
 
    Your clone URLs should look something like this:
 
        https://github.com/yourusername/SymbulationEmp.git
        https://github.com/devosoft/Empirical.git
 
    and the UNIX shell command should be:
 
        git clone https://github.com/yourusername/SymbulationEmp.git
        git clone https://github.com/devosoft/Empirical.git
 
    (This makes a local copy of Symbulation on your development machine.)
 
4.  Add a git reference to the Symbulation repository:
 
        cd SymbulationEmp
        git remote add upstream https://github.com/anyaevostinar/SymbulationEmp.git
        cd ../
 
    (This makes it easy for you to pull down the latest changes in the
    main repository.)

 
### Building Symbulation and running the tests
 
To run the tests:
 
        make test
 
Congratulations! You're ready to develop!
 
## Claiming an issue and starting to develop
 
1.  Find an open issue and claim it.
 
    Once you've found an issue you like, make sure that no one has been
    assigned to it (see "assignee", bottom right near
    "notifications"). Then, add a comment "I am working on this
    issue." You've staked your claim!
 
    (We're trying to avoid having multiple people working on the same
    issue.)
 
2.  In your local copy of the source code, update your main branch
    from the main Symbulation main branch:
 
        git checkout main
        git pull upstream main
 
    (This pulls in all of the latest changes from whatever we've been
    doing on Symbulation.)
 
    It is possible that when you do a [git pull]{.title-ref} you will
    get a "merge conflict" -- This is what happens when something
    changed in the branch you're pulling in in the same place you made
    a change in your local copy.
 
    Git will complain loudly about merges and tell you specifically in
    which files they occurred. If you open the file, you'll see
    something vaguely like this in the place where the merge occurred:
 
        <<<<<<< HEAD
        Changes made on the branch that is being merged into. In most cases,
        this is the branch that you have currently checked out
        =======
        Changes made on the branch that is being merged in, almost certainly
        main.
        >>>>>>> abcde1234
 
    Though there are a variety of tools to assist with resolving merge
    conflicts they can be quite complicated at first glance and it is
    usually easy enough to manually resolve the conflict.
 
    To resolve the conflict you simply have to manually 'meld' the
    changes together and remove the merge markers. Make sure that you 
    don't remove someone else's changes while resolving the merge conflict!
 
    After this you'll have to add and commit the merge just like any
    other set of changes. You should also run the tests to make sure
    that everything works as expected.
 
3.  Create a new branch and link it to your fork on GitHub:
 
        git checkout -b fix/brief_issue_description
        git push -u origin fix/brief_issue_description
 
    where you replace "brief_issue_description" with 2-3 words,
    separated by underscores, describing the issue.
 
    (This is the set of changes you're going to ask to be merged into
    Symbulation.)
 
4.  Make some changes and commit them.
 
    Though this will largely be issue-dependent the basics of committing
    are simple. After you've made a cohesive set of changes, run the
    command [git status]{.title-ref}. This will display a list of all
    the files git has noticed you changed. A file in the 'untracked'
    section are files that haven't existed previously in the repository
    but git has noticed.
 
    To commit changes you have to 'stage' them--this is done by
    issuing the following command:
 
        git add path/to/file
 
    If you have a large quantity of changes and you don't want to add
    each file manually you can do `git add --patch` which will display
    each set of changes to you before staging them for commit.
 
    Once you have staged your changes, it's time to make a commit:
 
        git commit -m "added x change"
 
    Git will then open your default console text editor to write a
    commit message -- this is a short (typically 1-3 sentence)
    description of the changes you've made. Please make your commit
    message informative but concise -- these messages become part of
    the 'official' history of the project.
 
    Once your changes have been committed, push them up to the remote
    branch:
 
        git push
 
    If this is your first commit on a new branch git will error out,
    telling you the remote branch doesn't exist -- This is fine, as it
    will also provide the command to create the branch. Copy/paste/run
    and you should be set.
 
5.  Periodically update your branch from the Symbulation main
    branch:
 
        git pull upstream main
 
    (This pulls in all of the latest changes from whatever we've been
    doing on the upstream branch- important especially during periods of
    fast change or for long-running pull requests.)
 
6.  Run the tests *before* pushing to GitHub:
 
        make test
 
    Make sure they all pass!
 
7.  Push your branch to your own GitHub fork:
 
        git push origin
 
    (This pushes all of your changes to your own fork.)
 
8.  Repeat until you're ready to merge your changes into "official"
    Symbulation.
 
9.  Set up a Pull Request asking to merge things into the central
    Symbulation repository.
 
    In a Web browser, go to your GitHub fork of Symbulation, e.g.:
 
        https://github.com/yourusername/SymbulationEmp
 
    and you will see a list of "recently pushed branches" just above
    the source code listing. On the right side of that should be a
    "Compare & pull request" green button. Click on it!
 
    Now:
 
    > -   add a descriptive title ("updated tests for XXX")
    > -   put the issue number in the comment ("fixes issue #532")
 
    then click "Create pull request."
 
    (This creates a new issue where we can all discuss your proposed
    changes; the Symbulation team will be automatically notified and you
    will receive e-mail notifications as we add comments. See [GitHub
    flow](http://scottchacon.com/2011/08/31/github-flow.html) for more
    info.)
 
10. As you add new commits to address bugs or formatting issues, you can
    keep pushing your changes to the pull request by doing:
 
        git push origin
 
11. If we request changes, return to the step "Make some changes and
    commit them" and go from there. Any additional commits you make and
    push to your branch will automatically be added to the pull request
    (which is pretty dang cool.)
 
## After your first issue is successfully merged...
 
You're now an experienced GitHub user! Go ahead and take some more
tasks; you can broaden out beyond the low hanging fruit if you like.
 
## Your second contribution...
 
Here are a few pointers on getting started on your second (or third, or
fourth, or nth contribution).
 
So, assuming you've found an issue you'd like to work on there are a
couple things to do to make sure your local copy of the repository is
ready for a new issue--specifically, we need to make sure it's in sync
with the remote repository so you aren't working on an old copy. So:
 
    git checkout main
    git fetch --all
    git pull
 
This puts you on the latest main branch and pulls down updates from
GitHub with any changes that may have been made since your last
contribution (usually including the merge of your last contribution).
Then we merge those changes into your local copy of the main branch.
 
Now, you can go back to [Claiming an issue and starting to
develop](#claiming-an-issue-and-starting-to-develop).
 
## Pull request cleanup (commit squashing)
 
Submitters are invited to reduce the numbers of commits in their pull
requests either via [git rebase -i upstream/main]{.title-ref} or this
recipe:
 
    git pull ## make sure the local is up to date
    git pull upstream main ## get up to date
    ## fix any merge conflicts
    git status ## sanity check
    git diff upstream/main ## does the diff look correct? (no merge markers)
    git reset --soft upstream/main ## un-commit the differences from dib/main
    git status ## sanity check
    git commit --all ## package all differences in one commit
    git status ## sanity check
    git push ## should fail
    git push --force ## override what's in GitHub's copy of the branch/pull request
 
 

