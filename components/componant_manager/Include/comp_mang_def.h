#ifndef COMPONENT_MANAGER_DEF_H                                                          
#define COMPONENT_MANAGER_DEF_H                                                          
                                                          
#include "comp_mang.h"                                                          
/*****************************************************************                                                          
******************************************************************                                                          
 *                      GET GENERATOR ARCH                                                          
******************************************************************                                                          
******************************************************************/                                                          
/**                                                          
 * @brief                                                           
 *                                                           
 */                                                          
#define GENERATE_GET_NAME(MODULE,GET_ID)  T_ ## MODULE ## _GET_ ## GET_ID                                                          
/**                                                          
 * @brief                                                           
 *                                                           
 */                                                          
#define GENERATE_GET_TYPE(NAME1,NAME2,type) \                                                          
    typedef type GENERATE_GET_NAME(NAME1,NAME2)                                                          
/**                                                          
 * @brief                                                           
 *                                                           
 */                                                          
#define GET_VAR_PROTO(MODULE_NAME,SERVICE_ID,TYPE) \                                                          
    GENERATE_GET_TYPE(MODULE_NAME,SERVICE_ID,TYPE) \                                                          
/**                                                          
 * @brief                                                           
 *                                                           
 */                                                          
#define GET_VARIABLE(MODULE_NAME,VAR_ID,RET,VAR_PTR)   \                                                          
    {\                                                          
        GENERATE_GET_NAME(MODULE_NAME,VAR_ID) value ; \                                                          
        value =  VAR_PTR ;  \                                                          
        RET = component_manager_get(MODULE_NAME , VAR_ID , (void *)value);\                                                          
    }\                                                          
                                                          
/*****************************************************************                                                          
******************************************************************                                                          
 *                      SET GENERATOR ARCH                                                          
******************************************************************                                                          
******************************************************************/                                                          
#define GENERATE_SET_NAME(MODULE,GET_ID)  T_ ## MODULE ## _SET_ ## GET_ID                                                          
                                                          
#define GENERATE_SET_TYPE(NAME1,NAME2,type) \                                                          
    typedef type GENERATE_SET_NAME(NAME1,NAME2)                                                          
                                                          
#define SET_VAR_PROTO(MODULE_NAME,SERVICE_ID,TYPE) \                                                          
    GENERATE_SET_TYPE(MODULE_NAME,SERVICE_ID,TYPE) \                                                          
                                                          
#define SET_VARIABLE(MODULE_NAME,VAR_ID,ret,VAR_PTR)   \                                                          
    {\                                                          
        GENERATE_SET_NAME(MODULE_NAME,VAR_ID) value ; \                                                          
        value =  VAR_PTR ;  \                                                          
        ret = component_manager_set(MODULE_NAME , VAR_ID , (void *)value);\                                                          
    }\                                                          
                                                              
                                                          
/*****************************************************************                                                          
******************************************************************                                                          
 *                      REQUEST GENERATOR ARCH                                                          
******************************************************************                                                          
******************************************************************/                                                          
                                                          
/* DATA TYPES GENERATOR MACROS */                                                          
#define GENERATE_NAME(MODULE_NAME,REQUES_ID,DATA_TYPE,NUM) \                                                          
        T_ ## MODULE_NAME ## _ ## REQUES_ID ## _PARAM_ ## NUM                                                          
                                                          
#define GENERATE_DATA_TYPE(MODULE_NAME,REQUES_ID,DATA_TYPE,NUM) \                                                          
        typedef DATA_TYPE GENERATE_NAME(MODULE_NAME,REQUES_ID,DATA_TYPE,NUM) ;                                                          
                                                          
#define GENERATE_VARIABLE(MODULE_NAME,REQUES_ID,DATA_TYPE,NUM)  \                                                          
        GENERATE_NAME(MODULE_NAME,REQUES_ID,DATA_TYPE,NUM) T_ ##NUM ;                                                          
                                                          
                                                          
/* RESULT GENERATOR MACROS */                                                          
#define GENERATE_RESULT_NAME(MODULE_NAME,REQUES_ID,DATA_TYPE) \                                                          
        GENERATE_NAME(MODULE_NAME,REQUES_ID,DATA_TYPE,RESULT)                                                          
                                                          
#define GENERATE_RESULT_DATA_TYPE(MODULE_NAME,REQUES_ID,DATA_TYPE) \                                                          
        typedef DATA_TYPE GENERATE_RESULT_NAME(MODULE_NAME,REQUES_ID,DATA_TYPE)                                                           
                                                          
#define GENERATE_RESULT(MODULE_NAME,REQUES_ID,DATA_TYPE) \                                                          
        GENERATE_RESULT_NAME(MODULE_NAME,REQUES_ID,DATA_TYPE) T_ ##RESULT                                                           
                                                          
                                                          
#define FILL_VARIBLES(MODULE_NAME,REQUES_ID,VAR,NUM) \                                                          
        T_ ## NUM = VAR ;\                                                          
        REQ_ARGS.param_ ##NUM = (void*)T_ ## NUM ;                                                          
                                                          
/* REPEATING MACROS */                                                          
                                                          
#define CHOOSE_MACRO(_1,_2,_3,_4,_5,_6,MACRO,...) MACRO                                                          
                                                          
#define CONCAT_MACRO(a,b) a b                                                           
                                                          
#define __CONCAT_T(a,b)   a##b                                                          
#define CONCAT_MACRO2(a,b) __CONCAT_T(a,b)                                                          
                                                          
#define GET_ARGS_NUM(...)   CHOOSE_MACRO(__VA_ARGS__,6,5,4,3,2,1)                                                            
                                                          
#define GENERATE_ARGS_NUM_NAME(MODULE,ID,DATA_TYPE,...)\                                                          
        CONCAT_MACRO2(REQ_ ## MODULE ## _ ## ID ##_ARGS_NUM_, GET_ARGS_NUM(__VA_ARGS__))                                                          
                                                          
#define GENERATE_ARGS_NUM_TYPE(MODULE,ID,DATA_TYPE,...) \                                                          
        typedef DATA_TYPE GENERATE_ARGS_NUM_NAME(MODULE,ID,DATA_TYPE,__VA_ARGS__);                                                          
                                                          
#define GENERATE_ARGS_NUM_DATA(MODULE,ID,DATA_TYPE,...) \                                                          
        GENERATE_ARGS_NUM_NAME(MODULE,ID,DATA_TYPE,__VA_ARGS__) REG_NUM;                                                          
                                                          
                                                          
#define CH11(a) a                                                          
                                                          
#define CH21(a,b)   a                                                          
#define CH22(a,b)   b                                                          
                                                          
#define CH31(a,b,c) a                                                          
#define CH32(a,b,c) b                                                          
#define CH33(a,b,c) c                                                          
                                                          
#define CH41(a,b,c,d)   a                                                          
#define CH42(a,b,c,d)   b                                                          
#define CH43(a,b,c,d)   c                                                          
#define CH44(a,b,c,d)   d                                                          
                                                          
#define CH51(a,b,c,d,e) a                                                          
#define CH52(a,b,c,d,e) b                                                          
#define CH53(a,b,c,d,e) c                                                          
#define CH54(a,b,c,d,e) d                                                          
#define CH55(a,b,c,d,e) e                                                          
                                                          
#define CH61(a,b,c,d,e,f)   a                                                          
#define CH62(a,b,c,d,e,f)   b                                                          
#define CH63(a,b,c,d,e,f)   c                                                          
#define CH64(a,b,c,d,e,f)   d                                                          
#define CH65(a,b,c,d,e,f)   e                                                          
#define CH66(a,b,c,d,e,f)   f                                                          
                                                          
                                                          
#define EX11(ACTION,ARG1,ARG2,ARG3)         ACTION(ARG1,ARG2,ARG3, 1 )                                                          
                                                          
#define EX21(ACTION,ARG1,ARG2,ARG3)         ACTION(ARG1,ARG2, ARG3, 2 )                                                          
#define EX22(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH21(__VA_ARGS__), 1 ) EX21(ACTION,ARG1,ARG2,CH22(__VA_ARGS__))                                                          
                                                          
#define EX31(ACTION,ARG1,ARG2,ARG3)         ACTION(ARG1,ARG2, ARG3, 3 )                                                          
#define EX32(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH32(__VA_ARGS__), 2 ) EX31(ACTION,ARG1,ARG2,CH33(__VA_ARGS__))                                                          
#define EX33(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH31(__VA_ARGS__), 1 ) EX32(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
                                                          
#define EX41(ACTION,ARG1,ARG2,ARG3)         ACTION(ARG1,ARG2, ARG3, 4 )                                                          
#define EX42(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH43(__VA_ARGS__), 3 ) EX41(ACTION,ARG1,ARG2,CH44(__VA_ARGS__))                                                          
#define EX43(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH42(__VA_ARGS__), 2 ) EX42(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
#define EX44(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH41(__VA_ARGS__), 1 ) EX43(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
                                                          
#define EX51(ACTION,ARG1,ARG2,ARG3)         ACTION(ARG1,ARG2, ARG3, 5 )                                                          
#define EX52(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH54(__VA_ARGS__), 4 ) EX51(ACTION,ARG1,ARG2,CH55(__VA_ARGS__))                                                          
#define EX53(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH53(__VA_ARGS__), 3 ) EX52(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
#define EX54(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH52(__VA_ARGS__), 2 ) EX53(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
#define EX55(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH51(__VA_ARGS__), 1 ) EX54(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
                                                          
#define EX61(ACTION,ARG1,ARG2,ARG3)         ACTION(ARG1,ARG2, ARG3, 6 )                                                          
#define EX62(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH65(__VA_ARGS__), 5 ) EX61(ACTION,ARG1,ARG2,CH66(__VA_ARGS__))                                                          
#define EX63(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH64(__VA_ARGS__), 4 ) EX62(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
#define EX64(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH63(__VA_ARGS__), 3 ) EX63(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
#define EX65(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH62(__VA_ARGS__), 2 ) EX64(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
#define EX66(ACTION,ARG1,ARG2,...)          ACTION(ARG1,ARG2, CH61(__VA_ARGS__), 1 ) EX65(ACTION,ARG1,ARG2,__VA_ARGS__)                                                          
                                                          
                                                          
#define DO_ALL(ACTION,ARG1,ARG2,...)    \                                                          
        CONCAT_MACRO(CHOOSE_MACRO(__VA_ARGS__,EX66,EX55,EX44,EX33,EX22,EX11) , (ACTION,ARG1,ARG2,__VA_ARGS__) )                                                           
                                                          
                                                          
                                                          
#define EXECUTE_PROTO(MODULE,ID,RET,...)      \                                                          
        GENERATE_ARGS_NUM_TYPE(MODULE,ID,RET,__VA_ARGS__)\                                                          
        DO_ALL(GENERATE_DATA_TYPE,MODULE,ID,__VA_ARGS__) ;  \                                                          
        GENERATE_RESULT_DATA_TYPE(MODULE,ID,RET)        ;                                                           
                                                                  
                                                          
#define EXECUTE(MODULE,ID,RET,...)      \                                                          
        {       \                                                          
                GENERATE_ARGS_NUM_DATA(MODULE,ID,RET,__VA_ARGS__)\                                                          
                DO_ALL(GENERATE_VARIABLE,MODULE,ID,__VA_ARGS__)     \                                                          
                GENERATE_RESULT(MODULE,ID,RET) ; \                                                          
                ARGS REQ_ARGS ; \                                                          
                (void) (REG_NUM);\                                                          
                DO_ALL(FILL_VARIBLES,MODULE,ID,__VA_ARGS__) \                                                          
                T_RESULT = RET ;       \                                                          
                REQ_ARGS.ret = T_RESULT;\                                                          
                component_manager_request(MODULE,ID, &REQ_ARGS); \                                                          
        }                                                          
                                                          
                                                           
#endif                                                          
                                                          
/* Excute function macros */                                                          
                                                          
/*                                                          
                                                          
Request_PROTO ( Module_name , request_ID , res , var1 , var2 , var3 ) ;                                                          
                                                          
                                                          
                                                          
1- typedef var1 T_ ##Module_name _ ##Request_ID_  ##Var_nume                                                          
2- typedef var2 T_ ##Module_name _ ##Request_ID_  ##Var_nume                                                          
3- typedef var3 T_ ##Module_name _ ##Request_ID_  ##Var_nume                                                          
                                                          
4- typedef res  T_ ##Module_name _ ##Request_ID Result                                                           
                                                          
I-- generate var name macro ;                                                          
II- generate result name macro ;                                                          
III genetrate var data tayep ;                                                          
IV  generate result data taype ;                                                          
                                                          
                                                          
                                                          
                                                          
Request(Module_name, Request_ID , Res , var1 , var2 , var3 ) ;                                                          
                                                          
1- T_ ##Module_name _ ##Request_ID Result       T_result (create result)                                                          
                                                          
2- T_ ##Module_name _ ##Request_ID_  ##Var_nume     T_ ##var_num ( create var1 )                                                          
3- T_ ##Module_name _ ##Request_ID_  ##Var_nume     T_ ##var_num ( create var2 )                                                          
4- T_ ##Module_name _ ##Request_ID_  ##Var_nume     T_ ##var_num ( create var3 )                                                          
                                                          
5- T_result = Res ;                                                          
6- T_1 = var1 ;                                                           
7- T_2 = var2 ;                                                           
8- T_3 = var3 ;                                                          
                                                          
9  - create args type ;                                                          
                                                          
10 - args->result = T_result ;                                                           
11 - args->var1 = T_1 ;                                                          
12 - args->var2 = T_2 ;                                                           
13 - args->var3 = T_3 ;                                                          
                                                          
call request ( MODULE_NAME , REQUEST_ID , ARGS ) ;                                                          
                                                          
                                                          
depemding types in this funcrion.                                                          
2- T_ ##Module_name _ ##Request_ID_  ##Var_num     T_ ##var_num ( create var1 )                                                          
3- T_ ##Module_name _ ##Request_ID_  ##Var_num     T_ ##var_num ( create var2 )                                                          
4- T_ ##Module_name _ ##Request_ID_  ##Var_num     T_ ##var_num ( create var3 )                                                          
                                                          
6- T_1 = var1 ;                                                           
7- T_2 = var2 ;                                                           
8- T_3 = var3 ;                                                          
                                                          
11 - args->var1 = T_1 ;                                                          
12 - args->var2 = T_2 ;                                                           
13 - args->var3 = T_3 ;                                                          
                                                          
all of this operations might be different from one operations to another ;                                                          
let's make one action but.                                                          
                                                          
--- this is the action which must be repeated.                                                          
1- T_ ##Module_name _ ##Request_ID_  ##Var_nume     T_ ##var_num                                                           
2- T_ ##var_num = arg_num ;                                                          
3- args->T_ ##var_num = T_ ##var_num ;                                                          
                                                          
                                                          
*/                                                          
                                                          
                                                          
