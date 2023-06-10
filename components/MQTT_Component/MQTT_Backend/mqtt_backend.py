#! /usr/bin/python3

from paho.mqtt import client as mqtt_client
import data_presentation_pb2 as protobuffer_data
import argparse
import stat
import os

def mqtt_led_state_process(payload):
    protobuf_led_state = protobuffer_data.ProtoBufferLedState()
    protobuf_led_state.ParseFromString(payload)

    if(protobuf_led_state.led_state == protobuffer_data.LED_STATE_OFF):
        print('LED is OFF')
    elif(protobuf_led_state.led_state == protobuffer_data.LED_STATE_ON):
        print('LED is ON')
    else:
        print('LED state unkown!')

def get_mqtt_topics(username, topics_path):
    topics = []

    with open(topics_path, 'r') as topics_file:
        for line in topics_file:
            line = line.split(' ')
            topic = username + '/' + line[0].strip(), int(line[1].strip())
            topics.append(topic)

    return topics

def on_connect(client, topics, flags, rc):

    if rc == 0:
        print('Successful connection!')
    else:
        print('Failed connection!')
    
    for topic in topics:
        print('Subscribing to {} with QoS {}'.format(topic[0], topic[1]))
        client.subscribe(topic)

def on_message(client, userdata, msg):
    print('[RECV] {} {}'.format(msg.topic, str(msg.payload)))
    
    topic_fields = msg.topic.split('/')

    if topic_fields[-1] == 'led_state':
        mqtt_led_state_process(msg.payload)


def main():

    broker_port = 1883

    parser = argparse.ArgumentParser(
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
        description=__doc__)

    parser.add_argument(
        '--id', metavar='Client-ID',
        help="""
            Client-Id used when connecting to broker. If not specified a default
            client-Id will be used (client-backend)""")

    parser.add_argument(
        '--username', metavar='Username',
        help='Username used for authenticating client when connecting')

    parser.add_argument(
        '--pw', metavar='Password',
        help='Password used for authenticating client when connecting')
    
    parser.add_argument(
        '--topics', metavar='Topics',
        help='Path to a file containing all topics to subscribe to'
    )

    parser.add_argument(
        '--host', metavar='Host',
        help='IP address or hostname of MQTT broker. Defaults to loopback address')

    args = parser.parse_args()

    if args.id is not None:
        client_id = args.id
    else:
        client_id = 'mqtt-python'
    
    if args.username is not None:
        username = args.username
    else:
        username = None
    
    if args.pw is not None:
        passwd = args.pw
    else:
        passwd = None
    
    if args.topics is not None:
        topics_path = args.topics
    else:
        print("""ERROR: A path to a file containing all topics to subsribe to should be provided""")
        return
    
    if args.host is not None:
        broker_addr = args.host
    else:
        broker_addr = '127.0.0.1'

#    print('Client-Id: {}'.format(client_id))
#    print('Username: {}'.format(username))
#    print('Password: {}'.format(passwd))
#    print('topics_path: {}'.format(topics_path))

    if os.path.isfile(topics_path) is False:
        print('Error: {} no such file'.format(topics_path))
        exit(-1)
    
    fstat = os.stat(topics_path)
    if bool(fstat.st_mode & stat.S_IRUSR) is not True:
        print('Error: Cannot read {}. Permission denied'.format(topics_path))
        exit(-1)

    topics = get_mqtt_topics(username, topics_path)

    client = mqtt_client.Client(client_id, clean_session=True, transport='tcp', 
                                                                    userdata= topics)
    client.on_connect = on_connect
    client.on_message = on_message
    
    if username is not None:
        client.username_pw_set(username, passwd)
    
    client.connect(broker_addr, broker_port)

    client.loop_forever()

if __name__ == '__main__':
    main()