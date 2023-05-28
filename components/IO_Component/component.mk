# ifdef CONFIG_IO_COMPONENT_INCLUDED

# COMPONENT_SRCDIRS := IO_sub_component/Input_handler/Input_handler_task
# COMPONENT_SRCDIRS += IO_sub_component/Input_handler/on_off_input_handler
# COMPONENT_SRCDIRS += IO_sub_component/Input_handler/Pressed_input_handler
# COMPONENT_SRCDIRS += IO_sub_component/IO_processor/IO_processor_task
# COMPONENT_SRCDIRS += IO_sub_component/IO_processor/Pressed_to_pin_processor
# COMPONENT_SRCDIRS += IO_sub_component/output_handler/output_handler_task
# COMPONENT_SRCDIRS += IO_sub_component/output_handler/Pin_driven_handler
# COMPONENT_SRCDIRS += IO_component_task
# COMPONENT_SRCDIRS += IO_component_param

# COMPONENT_ADD_INCLUDEDIRS := IO_sub_component/Input_handler/Input_handler_task
# COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/Input_handler/on_off_input_handler
# COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/Input_handler/Pressed_input_handler
# COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/IO_processor/IO_processor_task
# COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/IO_processor/Pressed_to_pin_processor
# COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/output_handler/output_handler_task
# COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/output_handler/Pin_driven_handler
# COMPONENT_ADD_INCLUDEDIRS += IO_component_task
# COMPONENT_ADD_INCLUDEDIRS += IO_component_param
# endif

ifdef CONFIG_IO_COMPONENT_INCLUDED 
#Basic Element of IO component to include.
COMPONENT_SRCDIRS := IO_component_task
COMPONENT_SRCDIRS += IO_component_param
COMPONENT_SRCDIRS += IO_component_interface

COMPONENT_ADD_INCLUDEDIRS := IO_component_task
COMPONENT_ADD_INCLUDEDIRS += IO_component_param
COMPONENT_ADD_INCLUDEDIRS += IO_component_interface

#sub component of IO Component.
COMPONENT_SRCDIRS += IO_sub_component/Input_handler/Input_handler_task
COMPONENT_SRCDIRS += IO_sub_component/IO_processor/IO_processor_task
COMPONENT_SRCDIRS += IO_sub_component/output_handler/output_handler_task

COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/Input_handler/Input_handler_task
COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/IO_processor/IO_processor_task
COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/output_handler/output_handler_task
#======================================================================
#input handler sub element 
#======================================================================
ifdef CONFIG_PRESSED_INPUT_HANDLER
COMPONENT_SRCDIRS += IO_sub_component/Input_handler/Pressed_input_handler
COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/Input_handler/Pressed_input_handler
endif

#=======================================================================
#IO processor handler sub element 
#======================================================================
ifdef CONFIG_PRESSED_TO_PIN_HANDLER
COMPONENT_SRCDIRS += IO_sub_component/IO_processor/Pressed_to_pin_processor
COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/IO_processor/Pressed_to_pin_processor
endif

#=======================================================================
#Output handler sub element 
#======================================================================
ifdef CONFIG_PIN_DRIVEN_OUTPUT_HANDLER
COMPONENT_SRCDIRS += IO_sub_component/output_handler/Pin_driven_handler
COMPONENT_ADD_INCLUDEDIRS += IO_sub_component/output_handler/Pin_driven_handler
endif

#=======================================================================
endif