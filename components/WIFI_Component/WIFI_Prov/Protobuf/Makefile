all: c_proto http_client

c_proto: *.proto
	@protoc-c --c_out=./ -I . *.proto

http_client: HTTP_Client/protobuf_http_client.c HTTP_Client/protobuf_http_client.h *.proto
	gcc -o http_client.out HTTP_Client/protobuf_http_client.c wifi_config.pb-c.c -lprotobuf-c