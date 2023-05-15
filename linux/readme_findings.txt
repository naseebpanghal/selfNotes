1. auto-resize guest display is greyed out.
Install linux headers before running GuestAdditions on Linux VM.

2. many packages are removed and GUI is lost.
sudo apt-get install ubuntu-desktop^
Above command will install all the required packages for a desktop.

3. git merge vs rebase explained
https://stackoverflow.com/questions/16666089/whats-the-difference-between-git-merge-and-git-rebase

4. for system daemon debugging
By adding systemd.debug-shell=1 to the kernel command line, a root shell will be available on TTY9 (crlt+alt+F9) to run the command above.
and run 
$ systemctl list-jobs
