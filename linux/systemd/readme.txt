This service will run whenever system reboot(via reboot command) happens vs cold boot.

Do the following things to register service systemd daemon

1) copy file to /lib/systemd/system/naseeb_reboot.service
2) cd /etc/systemd/system/reboot.target.wants/
  2.a) create symlink to naseeb_reboot.service -> /lib/systemd/system/naseeb_reboot.service
3) sudo systemctl daemon-reload

