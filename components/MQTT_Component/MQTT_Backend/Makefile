all: proto

proto: *.proto
	protoc -I=. --python_out=./ *.proto