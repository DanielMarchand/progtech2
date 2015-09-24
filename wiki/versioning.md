# How do we want to work?

* together with other developers
* keep track of what we have done
* undo to any point back in time
* keep efficient and secure backup of files
* publish our work

# Why version control?

* collaboration -> work on a project with other people
* annotated work history -> keep track of workflow
* can undo back in time -> go back to previous versions of your work
* secure backup -> store files on remote server
* compressed storage -> only store minimum ammount of data reproduce all files
* multiple branches -> work on different implementations of an idea

## Git

In this course we will use [Git](https://git-scm.com).<br> 
A server is maintained by ETH on [GitLab](https://gitlab.phys.ethz.ch) and a [global one](https://github.com)<br>
Nice [tutorial](https://www.atlassian.com/git/tutorials/) can be found online.<br>


## Other version control systems

#### repository model
server/client -> clients have only working copy of repository tree. communitate with server on every commit<br>
distributed -> clients have working copy + local repository. communicate with server for sync with other clients<br>

#### concurrency model
lock -> only serial working on files is possible through locks<br>
merge -> allows concurrent working on files, but requires automatic or manual merge to resolve conflicts<br>

#### storage model
changeset -> only difference to previous or next version of a file is stored<br>
snapshot -> files stored as a whole in compressed format<br>


|             | cvs           | svn                    | git         | hg          | perforce                 |
|-------------|---------------|------------------------|-------------|-------------|--------------------------|
| cost        | free          | free                   | free        | free        | free for educational use |
| repository  | server/client | server/client          | distributed | distributed | server/client            |
| concurrency | merge         | merge or lock          | merge       | merge       | merge or lock            |
| storage     | changeset     | changeset and snapshot | snapshot    | changeset   | changeset                |