 #ifndef SYSTEM_PARAM_DEFINTIONS_H
 #define SYSTEM_PARAM_DEFINTIONS_H

#include "fast_system_param.h"
#include "slow_system_param.h"

#define FAST_PARTITION  (1)
#define SLOW_PARTITION  (0)

/***********************************************************/
/*                  WIFI component stuct                   */
/***********************************************************/
typedef system_param_slow_t     WIFI_COMP_STRUCT;         
#define WIFI_COMP_PARTITION     SLOW_PARTITION


/***********************************************************/
/*                  IO component stuct                   */
/***********************************************************/
typedef system_param_fast_t   IO_COMP_STRUCT;        
#define IO_COMP_PARTITION     FAST_PARTITION



/***********************************************************/
/*                  IO component stuct                   */
/***********************************************************/


 #endif

 