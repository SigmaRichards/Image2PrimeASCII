TARGET=im2prime
LINK_IM2=`pkg-config --cflags opencv4`
LINK_TAR=-lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lgmp -pthread

output: main.o im2num.o num2im.o primetest.o
	g++ main.o im2num.o num2im.o primetest.o -o $(TARGET) $(LINK_TAR)

main.o: main.cpp
	g++ -c main.cpp

im2num.o: im2num.cpp im2num.h
	g++ -c im2num.cpp $(LINK_IM2)

num2im.o: num2im.cpp num2im.h
	g++ -c num2im.cpp $(LINK_IM2)

primetest.o: primetest.cpp primetest.h
	g++ -c primetest.cpp

clean:
	rm *.o $(TARGET) debug

debug:
	g++ -g main.cpp im2num.cpp num2im.cpp primetest.cpp $(LINK_TAR) $(LINK_IM2) -o debug
