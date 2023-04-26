                /*-----------------------------*/
                /*          File Data:         */
                /*-----------------------------*/
/*--------------------------------------------------------------
* File Usage :      
----------------------------------------------------------------
* Creators : 
----------------------------------------------------------------
* History : 
----------------------------------------------------------------*/

                /*---------------------------*/
                /*          Content:         */
                /*---------------------------*/
/*-------------------------------------------------------------
1-Section 1:   
2-Section 2:  
3-Section 3:   
4-Section 4:  
5-Section 5:
6-Section 6"
---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
        /*-----------------------------------------*/
        /*          1-Section 1:  Includes         */
        /*-----------------------------------------*/
/*---------------------------------------------------------------*/
#include "types.h"

#include "nvs.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "debug_uart.h"
#include "NV_access_config.h"
#include "NV_access_private.h"
#include "NV_access_public.h"
/*---------------------------------------------------------------*/
        /*-------------------------------------------*/
        /*          2-Section 2:  definitions        */
        /*-------------------------------------------*/
/*---------------------------------------------------------------*/

/*---------------------------------------------------------------*/
        /*--------------------------------------------------*/
        /*          3-Section 3:  global variables          */
        /*--------------------------------------------------*/
/*---------------------------------------------------------------*/
static char * data_partitions[] = 
{
    "slow_data",
    "fast_data_1",
    "fast_data_2",
    "fast_data_3",
    "fast_data_4",
    "fast_data_5",
};

/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  private functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/


void NV_error_log(error_t error_num)
{
    switch (error_num)
        {
        case  ESP_ERR_NVS_BASE :
            NVS_LOGD("error code is : ESP_ERR_NVS_BASE \r\n") ;
            break ;
        case  ESP_ERR_NVS_NOT_INITIALIZED :
            NVS_LOGD("error code is : ESP_ERR_NVS_NOT_INITIALIZED \r\n") ;
            break ;
        case  ESP_ERR_NVS_NOT_FOUND :
            NVS_LOGD("error code is : ESP_ERR_NVS_NOT_FOUND \r\n") ;
            break ;
        case  ESP_ERR_NVS_TYPE_MISMATCH :
            NVS_LOGD("error code is : ESP_ERR_NVS_TYPE_MISMATCH \r\n") ;
            break ;
        case  ESP_ERR_NVS_READ_ONLY :
            NVS_LOGD("error code is : ESP_ERR_NVS_READ_ONLY \r\n") ;
            break ;
        case  ESP_ERR_NVS_NOT_ENOUGH_SPACE :
            NVS_LOGD("error code is : ESP_ERR_NVS_NOT_ENOUGH_SPACE \r\n") ;
            break ;
        case  ESP_ERR_NVS_INVALID_NAME :
            NVS_LOGD("error code is : ESP_ERR_NVS_INVALID_NAME \r\n") ;
            break ;
        case  ESP_ERR_NVS_INVALID_HANDLE :
            NVS_LOGD("error code is : ESP_ERR_NVS_INVALID_HANDLE \r\n") ;
            break ;
        case  ESP_ERR_NVS_REMOVE_FAILED :
            NVS_LOGD("error code is : ESP_ERR_NVS_REMOVE_FAILED \r\n") ;
            break ;
        case  ESP_ERR_NVS_KEY_TOO_LONG :
            NVS_LOGD("error code is : ESP_ERR_NVS_KEY_TOO_LONG \r\n") ;
            break ;
        case  ESP_ERR_NVS_PAGE_FULL :
            NVS_LOGD("error code is : ESP_ERR_NVS_PAGE_FULL \r\n") ;
            break ;
        case  ESP_ERR_NVS_INVALID_STATE :
            NVS_LOGD("error code is : ESP_ERR_NVS_INVALID_STATE \r\n") ;
            break ;
        case  ESP_ERR_NVS_INVALID_LENGTH :
            NVS_LOGD("error code is : ESP_ERR_NVS_INVALID_LENGTH \r\n") ;
            break ;
        case  ESP_ERR_NVS_NO_FREE_PAGES :
            NVS_LOGD("error code is : ESP_ERR_NVS_NO_FREE_PAGES r\n") ;
            break ;
        case  ESP_ERR_NVS_VALUE_TOO_LONG :
            NVS_LOGD("error code is : ESP_ERR_NVS_VALUE_TOO_LONG \r\n") ;
            break ;
        case  ESP_ERR_NVS_PART_NOT_FOUND :
            NVS_LOGD("error code is : ESP_ERR_NVS_PART_NOT_FOUND \r\n") ;
            break ;
        case  ESP_ERR_NVS_NEW_VERSION_FOUND :
            NVS_LOGD("error code is : ESP_ERR_NVS_NEW_VERSION_FOUND \r\n") ;
            break ;
        case  ESP_ERR_NVS_XTS_ENCR_FAILED :
            NVS_LOGD("error code is : ESP_ERR_NVS_XTS_ENCR_FAILED \r\n") ;
            break ;
        case  ESP_ERR_NVS_XTS_DECR_FAILED :
            NVS_LOGD("error code is : ESP_ERR_NVS_XTS_DECR_FAILED \r\n") ;
            break ;
        case  ESP_ERR_NVS_XTS_CFG_FAILED :
            NVS_LOGD("error code is : ESP_ERR_NVS_XTS_CFG_FAILED \r\n") ;
            break ;
        case  ESP_ERR_NVS_XTS_CFG_NOT_FOUND :
            NVS_LOGD("error code is : ESP_ERR_NVS_XTS_CFG_NOT_FOUND  \r\n") ;
            break ;
        case  ESP_ERR_NVS_ENCR_NOT_SUPPORTED :
            NVS_LOGD("error code is : ESP_ERR_NVS_ENCR_NOT_SUPPORTED \r\n") ;
            break ;
        case  ESP_ERR_NVS_KEYS_NOT_INITIALIZED :
            NVS_LOGD("error code is : ESP_ERR_NVS_KEYS_NOT_INITIALIZED \r\n") ;
            break ;
        case  ESP_ERR_NVS_CORRUPT_KEY_PART :
            NVS_LOGD("error code is : ESP_ERR_NVS_CORRUPT_KEY_PART  \r\n") ;
            break ;
        case  ESP_ERR_NVS_WRONG_ENCRYPTION :
            NVS_LOGD("error code is : ESP_ERR_NVS_WRONG_ENCRYPTION \r\n") ;
            break ;
        case  ESP_ERR_NVS_CONTENT_DIFFERS :
            NVS_LOGD("error code is : ESP_ERR_NVS_CONTENT_DIFFERS  \r\n") ;
            break ;
        case ESP_OK :
            NVS_LOGD("ESP_OK \r\n") ; 
            break;               
        case ESP_FAIL  :
            NVS_LOGD("error code is : ESP_FAIL \r\n") ; 
            break;           
        case ESP_ERR_NO_MEM :
            NVS_LOGD("error code is : ESP_ERR_NO_MEM \r\n") ; 
            break;             
        case ESP_ERR_INVALID_ARG :
            NVS_LOGD("error code is :  ESP_ERR_INVALID_ARG\r\n") ; 
            break;        
        case ESP_ERR_INVALID_STATE :
            NVS_LOGD("error code is : ESP_ERR_INVALID_STATE \r\n") ; 
            break;      
        case ESP_ERR_INVALID_SIZE  :
            NVS_LOGD("error code is :ESP_ERR_INVALID_SIZE  \r\n") ; 
            break;      
        case ESP_ERR_NOT_FOUND  :
            NVS_LOGD("error code is : ESP_ERR_NOT_FOUND \r\n") ; 
            break;         
        case ESP_ERR_NOT_SUPPORTED   :
            NVS_LOGD("error code is :  ESP_ERR_NOT_SUPPORTED\r\n") ; 
            break;    
        case ESP_ERR_TIMEOUT    :
            NVS_LOGD("error code is : ESP_ERR_TIMEOUT \r\n") ; 
            break;         
        case ESP_ERR_INVALID_RESPONSE :
            NVS_LOGD("error code is :  ESP_ERR_INVALID_RESPONSE\r\n") ; 
            break;
        case ESP_ERR_INVALID_CRC   :
            NVS_LOGD("error code is :  ESP_ERR_INVALID_CRC\r\n") ; 
            break;      
        case ESP_ERR_INVALID_VERSION  :
            NVS_LOGD("error code is :  ESP_ERR_INVALID_VERSION\r\n") ; 
            break;
        case ESP_ERR_INVALID_MAC   :
            NVS_LOGD("error code is : ESP_ERR_INVALID_MAC \r\n") ; 
            break;      
        case ESP_ERR_WIFI_BASE :
            NVS_LOGD("error code is : ESP_ERR_WIFI_BASE \r\n") ; 
            break;          
        case ESP_ERR_MESH_BASE :
            NVS_LOGD("error code is : ESP_ERR_MESH_BASE  \r\n") ; 
            break;  
        default:
            NVS_LOGD("ERROR IS ::: %d\r\n" , error_num ) ;
                break;
        }
}

/*---------------------------------------------------------------*/
        /*-------------------------------------------------*/
        /*          4-Section 4:  public functions         */
        /*-------------------------------------------------*/
/*---------------------------------------------------------------*/
BOOL NV_access_write_data(int32_t partition_ID, void * buffer, size_t length)
{
    nvs_handle_t handle;
    error_t res ;
    nvs_flash_init_partition(data_partitions[partition_ID]);
    #if NV_ACCESS_DEBUG
    uart_send("\r\nopen partitions:");
    #endif
    res = nvs_open_from_partition(data_partitions[partition_ID],NAME_SPACE,NVS_READWRITE,&handle);
    #if NV_ACCESS_DEBUG
    uart_send("\r\nthe result of open partition:"); 
    NV_error_log(res) ;   
    #endif
    res = nvs_set_blob(handle, KEY_NAME, buffer, length);
    #if NV_ACCESS_DEBUG
    uart_send("\r\nthe result of set data:");
    NV_error_log(res) ;
    #endif
    res=nvs_commit(handle);
    #if NV_ACCESS_DEBUG
    NV_error_log(res);
    #endif
    nvs_close(handle);
    return res ;
}
BOOL NV_access_read_data(int32_t partition_ID, void * buffer,size_t length)
{
    nvs_handle_t handle;
    error_t res ;
    nvs_flash_init_partition(data_partitions[partition_ID]);
    res = nvs_open_from_partition(data_partitions[partition_ID],NAME_SPACE,NVS_READWRITE,&handle);
    #if NV_ACCESS_DEBUG
    uart_send("\r\nthe result of open partition:");
    NV_error_log(res) ;
    #endif
    res = nvs_get_blob(handle, KEY_NAME, buffer, &length);
    #if NV_ACCESS_DEBUG
    uart_send("\r\nthe result of read data:");
    NV_error_log(res) ;
    #endif
    nvs_close(handle);
    return res ;
}
BOOL NV_access_check_partition_validation(int32_t partition_ID)
{

    return TRUE;
}
BOOL NV_access_init_partition( void )
{
    
    error_t error ;
    for (int8_t counter = 0 ; counter <6 ; counter ++ )
    {
        error = nvs_flash_init_partition(data_partitions[counter]);
        #if NV_ACCESS_DEBUG
        NV_error_log(error);
        /   /nvs_flash_erase_partition(data_partitions[counter]);
            debug("\r\ninit partision num %d",counter);
        #endif
    }
    return TRUE ;
}

