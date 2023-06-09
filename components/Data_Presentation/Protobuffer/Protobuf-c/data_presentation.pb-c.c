/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: data_presentation.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "data_presentation.pb-c.h"
void   proto_buffer_led_state__init
                     (ProtoBufferLedState         *message)
{
  static const ProtoBufferLedState init_value = PROTO_BUFFER_LED_STATE__INIT;
  *message = init_value;
}
size_t proto_buffer_led_state__get_packed_size
                     (const ProtoBufferLedState *message)
{
  assert(message->base.descriptor == &proto_buffer_led_state__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t proto_buffer_led_state__pack
                     (const ProtoBufferLedState *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &proto_buffer_led_state__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t proto_buffer_led_state__pack_to_buffer
                     (const ProtoBufferLedState *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &proto_buffer_led_state__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
ProtoBufferLedState *
       proto_buffer_led_state__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (ProtoBufferLedState *)
     protobuf_c_message_unpack (&proto_buffer_led_state__descriptor,
                                allocator, len, data);
}
void   proto_buffer_led_state__free_unpacked
                     (ProtoBufferLedState *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &proto_buffer_led_state__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor proto_buffer_led_state__field_descriptors[1] =
{
  {
    "led_state",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_ENUM,
    0,   /* quantifier_offset */
    offsetof(ProtoBufferLedState, led_state),
    &led_states__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned proto_buffer_led_state__field_indices_by_name[] = {
  0,   /* field[0] = led_state */
};
static const ProtobufCIntRange proto_buffer_led_state__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor proto_buffer_led_state__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "ProtoBufferLedState",
  "ProtoBufferLedState",
  "ProtoBufferLedState",
  "",
  sizeof(ProtoBufferLedState),
  1,
  proto_buffer_led_state__field_descriptors,
  proto_buffer_led_state__field_indices_by_name,
  1,  proto_buffer_led_state__number_ranges,
  (ProtobufCMessageInit) proto_buffer_led_state__init,
  NULL,NULL,NULL    /* reserved[123] */
};
static const ProtobufCEnumValue led_states__enum_values_by_number[3] =
{
  { "LED_STATE_UNKOWN", "LED_STATES__LED_STATE_UNKOWN", 0 },
  { "LED_STATE_OFF", "LED_STATES__LED_STATE_OFF", 1 },
  { "LED_STATE_ON", "LED_STATES__LED_STATE_ON", 2 },
};
static const ProtobufCIntRange led_states__value_ranges[] = {
{0, 0},{0, 3}
};
static const ProtobufCEnumValueIndex led_states__enum_values_by_name[3] =
{
  { "LED_STATE_OFF", 1 },
  { "LED_STATE_ON", 2 },
  { "LED_STATE_UNKOWN", 0 },
};
const ProtobufCEnumDescriptor led_states__descriptor =
{
  PROTOBUF_C__ENUM_DESCRIPTOR_MAGIC,
  "LedStates",
  "LedStates",
  "LedStates",
  "",
  3,
  led_states__enum_values_by_number,
  3,
  led_states__enum_values_by_name,
  1,
  led_states__value_ranges,
  NULL,NULL,NULL,NULL   /* reserved[1234] */
};
