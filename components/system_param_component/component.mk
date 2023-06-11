ifdef CONFIG_SYSTEM_PARAM_INCLUDED 
 
COMPONENT_SRCDIRS := NV_access 
COMPONENT_SRCDIRS += fast_slow_access/NV_fast_access  
COMPONENT_SRCDIRS += fast_slow_access/NV_slow_acess  
COMPONENT_SRCDIRS += system_param  
COMPONENT_SRCDIRS += system_param_struct  
COMPONENT_SRCDIRS += system_param_interface  
  
  
COMPONENT_ADD_INCLUDEDIRS := NV_access  
COMPONENT_ADD_INCLUDEDIRS += fast_slow_access/NV_fast_access  
COMPONENT_ADD_INCLUDEDIRS += fast_slow_access/NV_slow_acess  
COMPONENT_ADD_INCLUDEDIRS += system_param  
COMPONENT_ADD_INCLUDEDIRS += system_param_struct              
COMPONENT_ADD_INCLUDEDIRS += system_param_interface               
                
endif                
               