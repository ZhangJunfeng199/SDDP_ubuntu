# build rule for all project
all:
	cd src;make;test -d ../bin || mkdir -p ../bin/;cp ./sddp_nuvo_app ../bin/;
	
# clean rule for all project
clean:
	test -d ./bin && rm -f ./bin/sddp_nuvo_app;cd src;make clean;
