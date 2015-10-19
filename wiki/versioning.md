# Version Control

### Why do we need version control?

* ___keep track___ of what we have done and ___revert___ to previous versions
* ___share___ our work
* efficiently ___work together___ with other developers

### What do we expect from our version control tool?

* ___fetch___ code from others
* allow work on ___different features concurrently___
* facilitate easy ___merging___ of diverged code
* provide ___annotated work history___
* ___browse and switch___ to any point in history
* ___remotely store___ and ___publish___ files on a server
* store data compressed for minimum size
* easy to use
* fast operation

## Git

In this course we will use [Git](https://git-scm.com).<br /> 
A [GitLab](https://gitlab.phys.ethz.ch) server is maintained by ETH D-PHYS, and there is a [global one](https://github.com).<br />
A nice [tutorial](https://www.atlassian.com/git/tutorials/) can be found online.<br />

## Other version control systems

#### Repository model
Server/client -> clients have only working copy of repository tree. communitate with server on every commit<br />
Distributed -> clients have working copy + local repository. communicate with server for sync with other clients<br />

#### Concurrency model
Lock -> only serial working on files is possible through locks<br />
Merge -> allows concurrent working on files, but requires automatic or manual merge to resolve conflicts<br />

#### Storage model
Changeset -> only difference to previous or next version of a file is stored<br />
Snapshot -> files stored as a whole in compressed format<br />


|             | cvs           | svn                    | git         | hg          | perforce                 |
|-------------|---------------|------------------------|-------------|-------------|--------------------------|
| cost        | free          | free                   | free        | free        | free for educational use |
| repository  | server/client | server/client          | distributed | distributed | server/client            |
| concurrency | merge         | merge or lock          | merge       | merge       | merge or lock            |
| storage     | changeset     | changeset and snapshot | snapshot    | changeset   | changeset                |
