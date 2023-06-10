#include "wifi_prov_private.h"
#include "wifi_prov_handlers.h"
#include "types.h"

#include "esp_event.h"
#include "esp_log.h"
#include "esp_err.h"
#include "protocomm.h"
#include "protocomm_httpd.h"
#include "protocomm_security0.h"

#define WIFI_PROV_TAG                "WIFI_PROV"

#if CONFIG_WIFI_COMPONENT_LOGE_ENABLED
#define WIFI_PROV_LOGE_FORMAT        "[LINE:%d] [%s]"
#define WIFI_PROV_LOGE(__msg)        ESP_LOGE(WIFI_PROV_TAG, WIFI_PROV_LOGE_FORMAT,\
                                                                         __LINE__, __msg)
#else
#define WIFI_PROV_LOGE(_msg)
#endif

static wifi_prov_desc_t wifi_prov_desc[] = 
{
    {
        WIFI_CONFIG_AP_INFO_EP, 
        &wifi_config_ap_set_info_req_handler
    },
    {
        WIFI_CONFIG_CMD_EP,
        &wifi_config_cmd_req_handler
    }
};

#define WIFI_PROV_DESC_SIZE   (sizeof(wifi_prov_desc) / sizeof(wifi_prov_desc_t))


static protocomm_t* p_protocomm;

error_t wifi_prov_start(void)
{
    wifi_prov_desc_t* p_desc;
    protocomm_httpd_config_t httpd_config = {
        .ext_handle_provided = 0,
        .data = {
            .config = PROTOCOMM_HTTPD_DEFAULT_CONFIG()
        }
    };

    p_protocomm = protocomm_new();

    if(p_protocomm == NULL)
    {
        return RET_FAILED;
    }

    if(protocomm_httpd_start(p_protocomm, &httpd_config) != ESP_OK)
    {
        WIFI_PROV_LOGE("Cannot start HTTP server");

        return RET_FAILED;
    }

    if(protocomm_set_security(p_protocomm, "security_endpoint", 
                                                &protocomm_security0, NULL) != ESP_OK)
    {
        WIFI_PROV_LOGE("Cannot set Security 0");

        return RET_FAILED;
    }

    for(uint8_t i = 0; i < WIFI_PROV_DESC_SIZE; i++)
    {
        p_desc = &wifi_prov_desc[i];
        if(protocomm_add_endpoint(p_protocomm, p_desc->endpoint, 
                                        (protocomm_req_handler_t) p_desc->handler, NULL)
                                                                                 != ESP_OK)
        {
            WIFI_PROV_LOGE(p_desc->endpoint);

            return RET_FAILED;
        }                                            
    }

    return RET_OK;
}