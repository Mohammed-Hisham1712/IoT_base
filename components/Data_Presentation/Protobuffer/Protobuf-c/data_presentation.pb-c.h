/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: data_presentation.proto */

#ifndef PROTOBUF_C_data_5fpresentation_2eproto__INCLUDED
#define PROTOBUF_C_data_5fpresentation_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1004001 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct ProtoBufferLedState ProtoBufferLedState;


/* --- enums --- */

typedef enum _LedStates {
  LED_STATES__LED_STATE_UNKOWN = 0,
  LED_STATES__LED_STATE_OFF = 1,
  LED_STATES__LED_STATE_ON = 2
    PROTOBUF_C__FORCE_ENUM_TO_BE_INT_SIZE(LED_STATES)
} LedStates;

/* --- messages --- */

struct  ProtoBufferLedState
{
  ProtobufCMessage base;
  LedStates led_state;
};
#define PROTO_BUFFER_LED_STATE__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&proto_buffer_led_state__descriptor) \
    , LED_STATES__LED_STATE_UNKOWN }


/* ProtoBufferLedState methods */
void   proto_buffer_led_state__init
                     (ProtoBufferLedState         *message);
size_t proto_buffer_led_state__get_packed_size
                     (const ProtoBufferLedState   *message);
size_t proto_buffer_led_state__pack
                     (const ProtoBufferLedState   *message,
                      uint8_t             *out);
size_t proto_buffer_led_state__pack_to_buffer
                     (const ProtoBufferLedState   *message,
                      ProtobufCBuffer     *buffer);
ProtoBufferLedState *
       proto_buffer_led_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   proto_buffer_led_state__free_unpacked
                     (ProtoBufferLedState *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*ProtoBufferLedState_Closure)
                 (const ProtoBufferLedState *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCEnumDescriptor    led_states__descriptor;
extern const ProtobufCMessageDescriptor proto_buffer_led_state__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_data_5fpresentation_2eproto__INCLUDED */
