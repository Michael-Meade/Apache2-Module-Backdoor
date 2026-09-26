sudo rm /etc/apache2/mods-enabled/backdoor.load
sudo rm /etc/apache2/mods-available/backdoor.load
sudo service apache2 restart

sudo apxs -i -a -c test.c

echo "Clearing access.log..."
>/var/log/apache2/access.log
