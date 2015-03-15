# KDE

## Build and run

Build:

    make

To run you have two choices:

-   install and run from `PATH` (best option):

        sudo make install
        kdecheat

-   run directly from this directory:

        make run

    The downside of this method is that certain features are only available if you install, for example `ui.rc` files.

    But this method is faster.

## General information

KDE is built on top of QT.

If factors out many parts of applications, such as providing

- standard actions with standard shortcuts and menu items
- a configuration method.

    This greatly simplifies the harsh task of configuration management.

API tutorials can be found at <http://techbase.kde.org>. <http://userbase.kde.org> is only for end-user docs.

A good way to learn APIs it to look for very simple applications, download the source and see how they behave. A good one is `ksnakeduel`:

    git clone git://anongit.kde.org/ksnakeduel

## ui.rc file

Specifies GUI parts via an XML file.

This file is parsed whenever the application will be launched.

In this way, it is simple to reconfigure the application without recompiling.

The file must be installed to work: it is not enough to be on the same directory as the executable.
