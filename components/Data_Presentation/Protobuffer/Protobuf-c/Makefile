all: c_proto

c_proto: *.proto
	@protoc-c --c_out=./ -I . *.proto
