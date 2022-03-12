/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.scalar.conf 11805 2005-01-07 09:37:18Z dts12 $
 */

#include <unistd.h>
#include <time.h>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>

#include "triton.h"
#include "statCore.h"

/** Initializes the statCore module */
void
init_statCore(void)
{
    static oid statCoreUpTime_oid[] = { 1,3,6,1,4,1,8072,100,1,1,1 };
    static oid statCoreCPU_oid[] = { 1,3,6,1,4,1,8072,100,1,1,2 };
    static oid statCoreMemRss_oid[] = { 1,3,6,1,4,1,8072,100,1,1,3 };

  DEBUGMSGTL(("statCore", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("statCoreUpTime", handle_statCoreUpTime,
                               statCoreUpTime_oid, OID_LENGTH(statCoreUpTime_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("statCoreCPU", handle_statCoreCPU,
                               statCoreCPU_oid, OID_LENGTH(statCoreCPU_oid),
                               HANDLER_CAN_RONLY
        ));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("statCoreMemRss", handle_statCoreMemRss,
                               statCoreMemRss_oid, OID_LENGTH(statCoreMemRss_oid),
                               HANDLER_CAN_RONLY
        ));
}

int
handle_statCoreUpTime(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
		struct timespec ts;

		clock_gettime(CLOCK_MONOTONIC, &ts);
		ts.tv_sec -= triton_stat.start_time;

    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_GAUGE,
                                     (u_char *)&ts.tv_sec /* XXX: a pointer to the scalar's data */,
                                     sizeof(ts.tv_sec)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_statCoreUpTime\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_statCoreCPU(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     (u_char *)&triton_stat.cpu /* XXX: a pointer to the scalar's data */,
                                     sizeof(triton_stat.cpu)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_statCoreCPU\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
int
handle_statCoreMemRss(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
	char statm_fname[128];
	FILE *f;
	unsigned long vmsize = 0, vmrss = 0;
	unsigned long page_size = sysconf(_SC_PAGESIZE);

	sprintf(statm_fname, "/proc/%i/statm", getpid());
	f = fopen(statm_fname, "r");
	if (f) {
		fscanf(f, "%lu %lu", &vmsize, &vmrss);
		fclose(f);
	}

	vmrss *= page_size;

    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER,
                                     (u_char *)&vmrss /* XXX: a pointer to the scalar's data */,
                                     sizeof(vmrss)/* XXX: the length of the data in bytes */);
            break;


        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_statCoreMemRss\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }

    return SNMP_ERR_NOERROR;
}
